#include "ag_Time.h"
#include <cassert>



/*!
  \file
  This file contains the implementation of the Time class.
*/



//------------------------------------------------------------------------------
// DEFINITION OF STATIC CLASS MEMBERS
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// DEFINITION OF CLASS MEMBERS
//------------------------------------------------------------------------------

ag::Time::Time()

  : d_time(time(0))

{
  assert(d_time != static_cast<std::time_t>(-1));
}



ag::Time::~Time()
{
}



ag::Time& ag::Time::operator-=(const Time& aTime)
{
  d_time -= aTime.d_time;
  return *this;
}



size_t ag::Time::inSeconds() const
{
  return static_cast<size_t>(d_time);
}



//------------------------------------------------------------------------------
// DEFINITION OF FREE OPERATORS
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// DEFINITION OF FREE FUNCTIONS
//------------------------------------------------------------------------------

ag::Time ag::operator-(const Time& lhs, const Time& rhs)
{
  ag::Time t(lhs);
  t -= rhs;
  return t;
}



//------------------------------------------------------------------------------
// DOCUMENTATION OF ENUMERATIONS
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// DOCUMENTATION OF INLINE FUNCTIONS
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// DOCUMENTATION OF PURE VIRTUAL FUNCTIONS
//------------------------------------------------------------------------------


