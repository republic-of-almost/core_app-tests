#ifndef CAMERA_TEST_INCLUDED_0830B7C5_8EAF_4715_9114_25EA7A4CB24E
#define CAMERA_TEST_INCLUDED_0830B7C5_8EAF_4715_9114_25EA7A4CB24E


#include <tests/test.hpp>
#include <core/entity/entity.hpp>
#include <core/camera/camera.hpp>
#include <core/resources/material.hpp>


namespace Test {
namespace Camera_test_utils {


constexpr uint32_t max_cubes() { return 4; }


} // ns


/*
  Camera Test
  --
  Tests various rendering modes.
*/
class Camera_test : public App
{
public:

  explicit          Camera_test(Core::Context &ctx);
  void              on_think() override;
  
private:

  Core::Entity      m_entities[Camera_test_utils::max_cubes()];
  Core::Entity      m_camera_entity;
  Core::Camera      m_camera;
};


} // ns


#endif // inc guard