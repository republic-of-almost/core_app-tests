#ifndef FPS_TEST_INCLUDED_3C43B889_69B9_4134_B3C8_962E93140A32
#define FPS_TEST_INCLUDED_3C43B889_69B9_4134_B3C8_962E93140A32


#include <tests/test.hpp>
#include <core/common/core_fwd.hpp>
#include <core/entity/entity.hpp>
#include <core/camera/camera.hpp>


namespace Test {
namespace Fps_test_utils {


constexpr uint32_t max_scene_objects() { return 1; }


} // ns


class Fps_test : public App
{
public:

  explicit          Fps_test(Core::Context &ctx);
  void              on_think();
  
private:

  Core::Entity      m_player_entity;
  Core::Entity      m_camera_entity;
  Core::Entity      m_scene[Fps_test_utils::max_scene_objects()];
  Core::Camera      m_camera;

}; // class


} // ns


#endif // inc guard