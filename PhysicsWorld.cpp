#include "PhysicsWorld.h"

namespace myfx
{
//-----------------------------------------------------------------------------
PhysicsWorld::PhysicsWorld()
    : mDeltaTime            { 1.f / 60.f }
    , cGravityAcceleration  { 0.f, -9.8f, 0.f }
{}

//-----------------------------------------------------------------------------
bool PhysicsWorld::addRigidBody(RigidBody* body)
{
    if (std::find(mRigidBodies.begin(), mRigidBodies.end(), body) == mRigidBodies.end())
    {
        mRigidBodies.push_back(body);
        return true;
    }
    else
    {
        return false;
    }
}

//-----------------------------------------------------------------------------
bool PhysicsWorld::removeRigidBody(RigidBody* body)
{
    auto itr = std::find(mRigidBodies.begin(), mRigidBodies.end(), body);
    if (itr != mRigidBodies.end())
    {
        mRigidBodies.erase(itr);
        return true;
    }
    else
    {
        return false;
    }
}

//-----------------------------------------------------------------------------
void PhysicsWorld::updateWorld()
{
    doBroadPhase_();

    doNarrowPhase_();

    doSolveConstraintPhase_();

    doAddForceTorque_();

    doIntegrate_();

    doResetForceTorque_();
}

//-----------------------------------------------------------------------------
void PhysicsWorld::doBroadPhase_()
{
    mCollisionCandidates.clear();
    for (glm::int32 idx1 = 0; idx1 < mRigidBodies.size(); idx1++)
    {
        for (glm::int32 idx2 = idx1 + 1; idx2 < mRigidBodies.size(); idx2++)
        {
            if (mRigidBodies[idx1]->getCollisionShape()->getShapeType() <= mRigidBodies[idx2]->getCollisionShape()->getShapeType())
            {
                mCollisionCandidates.push_back({ mRigidBodies[idx1], mRigidBodies[idx2] });
            }
            else
            {
                mCollisionCandidates.push_back({ mRigidBodies[idx2], mRigidBodies[idx1] });
            }
        }
    }
}

//-----------------------------------------------------------------------------
void PhysicsWorld::doNarrowPhase_()
{
    mCollisionDataArray.clear();
    for (const auto pair : mCollisionCandidates)
    {
        const auto collision_data = mCollisionDetector.getCollisionData(*pair.first, *pair.second);
        mCollisionDataArray.push_back(collision_data);
    }
}

//-----------------------------------------------------------------------------
void PhysicsWorld::doSolveConstraintPhase_()
{
    assert(mCollisionCandidates.size() == mCollisionDataArray.size());
    for (glm::int32 idx = 0; idx < mCollisionCandidates.size(); idx++)
    {
        auto* body1 = mCollisionCandidates[idx].first;
        auto* body2 = mCollisionCandidates[idx].second;
        const auto collision_data = mCollisionDataArray[idx];

        mConstraintSolver.solveConstraint(body1, body2, collision_data);
    }
}

//-----------------------------------------------------------------------------
void PhysicsWorld::doAddForceTorque_()
{
    assert(mCollisionCandidates.size() == mCollisionDataArray.size());

    // d—Í
    for (glm::int32 idx = 0; idx < mRigidBodies.size(); idx++)
    {
        mRigidBodies[idx]->setForce(mRigidBodies[idx]->getForce() + mRigidBodies[idx]->getMass() * cGravityAcceleration);
    }

    for (glm::int32 idx = 0; idx < mCollisionCandidates.size(); idx++)
    {
        auto* body1 = mCollisionCandidates[idx].first;
        auto* body2 = mCollisionCandidates[idx].second;
        const auto collision_data = mCollisionDataArray[idx];
        const auto r1 = collision_data.mTangent - body1->getPosition();
        const auto r2 = collision_data.mTangent - body2->getPosition();
        
        if (collision_data.mIsColliding)
        {
            // Œ‚—Í
            const auto force = mForceCalculator.getImpulse(body1, body2, collision_data) / mDeltaTime;
            body1->setForce(body1->getForce() +  force);
            body2->setForce(body2->getForce() + -force);
            body1->setTorque(body1->getTorque() + glm::cross(r1,  force));
            body2->setTorque(body2->getTorque() + glm::cross(r2, -force));


            // –€ŽC—Í
            const auto friction = mForceCalculator.getFrictionForce(body1, body2, collision_data, force);
            body1->setForce(body1->getForce() +  friction);
            body2->setForce(body2->getForce() + -friction);
            body1->setTorque(body1->getTorque() + glm::cross(r1,  friction));
            body2->setTorque(body2->getTorque() + glm::cross(r2, -friction));
        }
    }
}

//-----------------------------------------------------------------------------
void PhysicsWorld::doIntegrate_()
{
    for (glm::int32 idx = 0; idx < mRigidBodies.size(); idx++)
    {
        mIntegrator.integrateRigidBody(mRigidBodies[idx], mDeltaTime);
    }
}

//-----------------------------------------------------------------------------
void PhysicsWorld::doResetForceTorque_()
{
    for (glm::int32 idx = 0; idx < mRigidBodies.size(); idx++)
    {
        mRigidBodies[idx]->setForce(glm::zero<glm::vec3>());
        mRigidBodies[idx]->setTorque(glm::zero<glm::vec3>());
    }
}
}