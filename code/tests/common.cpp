#include <tests/common.hpp>
#include <core/transform/transform.hpp>


namespace Test {
namespace Common {


Core::Transform
Orbit_transform(const float time,
                const float tilt,
                const float distance,
                const float height)
{
  // Position of the camera over time.
  const float x = math::cos(time) * distance;
  const float y = height;
  const float z = math::sin(time) * distance;
  const math::vec3 position = math::vec3_init(x, y, z);
  
  // Rotation of the camera over time.
  const math::quat rotation  = math::quat_init_with_axis_angle(0.f, 1.f, 0.f, time - math::quart_tau());
  const math::quat tilt_down = math::quat_init_with_axis_angle(1.f, 0.f, 0.f, tilt);
  const math::quat final_rot = math::quat_multiply(tilt_down, rotation);
  
  // Build Transform
  return Core::Transform(
    position,
    math::vec3_one(),
    final_rot
  );
}


} // ns
} // ns