#ifndef MATERIAL_TEST_INCLUDED_204BB7D9_72F9_475E_93F3_7D5A6510F216
#define MATERIAL_TEST_INCLUDED_204BB7D9_72F9_475E_93F3_7D5A6510F216


#include <tests/test.hpp>
#include <core/entity/entity.hpp>
#include <core/camera/camera.hpp>
#include <core/resources/material.hpp>


namespace Test {
namespace Material_test_utils {

constexpr uint32_t max_materials() { return 2; }

} // ns


/*
  Material Test
  --
  Tests rendering materials through the Material Renderer.
  Camera spins around a scene that has a cube and a plane.
*/
class Material_test : public App
{
public:

  explicit          Material_test(Core::Context &ctx);
  
  void              on_think() override;
  
private:

  Core::Entity      m_cube_entity;
  Core::Entity      m_plane_entity;
  Core::Entity      m_camera_entity;
  Core::Camera      m_camera;
  Core::Material    m_materials[Material_test_utils::max_materials()];
};


} // ns


#endif // inc guard