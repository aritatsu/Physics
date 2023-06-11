#include "Inertia.h"

namespace myfx
{
//-----------------------------------------------------------------------------
Inertia::Inertia()
	: mMass						{ 0.f }
	, mMassInverse				{ 0.f }
	, mMomentofInertia			{ glm::zero < glm::mat3>() }
	, mMomentofInertiaInverse	{ glm::zero < glm::mat3>() }
{}

//-----------------------------------------------------------------------------
Inertia& Inertia::operator=(const Inertia& inertia)
{
	mMass = inertia.mMass;
	mMassInverse = inertia.mMassInverse;
	mMomentofInertia = inertia.mMomentofInertia;
	mMomentofInertiaInverse = inertia.mMomentofInertiaInverse;

	return *this;
}

}