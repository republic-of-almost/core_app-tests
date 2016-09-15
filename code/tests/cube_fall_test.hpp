#ifndef CUBE_FALL_TEST_INCLUDED_4E7AA43D_9937_4B85_8AD4_EDD81760D987
#define CUBE_FALL_TEST_INCLUDED_4E7AA43D_9937_4B85_8AD4_EDD81760D987


#include <tests/test.hpp>
#include <core/entity/entity.hpp>
#include <core/camera/camera.hpp>
#include <core/resources/material.hpp>


namespace Test {
namespace Cube_fall_utils {


constexpr uint32_t max_cubes() { return 512; }
constexpr uint32_t max_materials() { return 4; }


} // ns


/*
  Cube fall
  --
  Physics test where cubes fall.
*/
class Cube_fall_test : public App
{
public:

  explicit          Cube_fall_test(Core::Context &ctx);
  void              on_think() override;
  
private:

  Core::Entity      m_entities[Cube_fall_utils::max_cubes()];
  Core::Material    m_cube_materials[Cube_fall_utils::max_materials()];
  uint32_t          m_entity_pivot = 0;
  float             m_rb_spawn_timer = 0.f;
  Core::Entity      m_ground_entity;
  Core::Entity      m_camera_entity;
  Core::Camera      m_camera;
};


} // ns


#endif // inc guard