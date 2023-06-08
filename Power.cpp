#include "Power.h"

namespace myfx 
{
//-----------------------------------------------------------------------------
Power::Power()
	: mForce	{ 0.f }
	, mTorque	{ 0.f }
	{}

//-----------------------------------------------------------------------------
Power& Power::operator=(const Power& power)
{
	mForce = power.mForce;
	mTorque = power.mTorque;
	return *this;
}

}