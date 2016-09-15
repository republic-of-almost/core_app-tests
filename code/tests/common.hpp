#ifndef COMMON_INCLUDED_769755E9_22EC_4490_8A48_42771D868876
#define COMMON_INCLUDED_769755E9_22EC_4490_8A48_42771D868876


#include <core/common/core_fwd.hpp>


namespace Test {
namespace Common {


/*
  gets the orbit transform overtime.
*/
Core::Transform
Orbit_transform(const float time,
                const float tilt,
                const float distance,
                const float height);



} // ns
} // ns


#endif // inc guard