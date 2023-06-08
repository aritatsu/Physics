#include "Inertia.h"

namespace myfx
{
//-----------------------------------------------------------------------------
Inertia::Inertia()
	: mMass				{ 1.f }
	, mMomentofInertia	{ 1.f }
{}

//-----------------------------------------------------------------------------
Inertia& Inertia::operator=(const Inertia& inertia)
{
	mMass = inertia.mMass;
	mMomentofInertia = inertia.mMomentofInertia;
	return *this;
}

}