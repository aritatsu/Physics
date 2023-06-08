#include "Motion.h"

namespace myfx
{
//-----------------------------------------------------------------------------
Motion::Motion()
	: mVelocity			{ 0.f }
	, mAngularVelocity	{ 0.f }
{
}

//-----------------------------------------------------------------------------
Motion& Motion::operator=(const Motion& motion)
{
	mVelocity = motion.mVelocity;
	mAngularVelocity = motion.mAngularVelocity;
	return *this;
}
}