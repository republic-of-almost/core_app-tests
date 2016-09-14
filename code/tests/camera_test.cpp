#include <tests/camera_test.hpp>
#include <tests/factories/model_factory.hpp>
#include <tests/factories/texture_factory.hpp>
#include <tests/factories/shader_factory.hpp>
#include <core/entity/entity_ref.hpp>
#include <core/common/directory.hpp>
#include <core/model/model.hpp>
#include <core/renderer/renderer.hpp>
#include <core/renderer/material_renderer.hpp>
#include <core/resources/shader.hpp>
#include <core/resources/texture.hpp>
#include <core/transform/transform.hpp>
#include <core/transform/transform_utils.hpp>
#include <core/context/context.hpp>
#include <core/camera/camera_properties.hpp>
#include <core/color/color_predefined.hpp>


namespace {

/*
  General camera settings.
*/
constexpr float camera_distance = 10.f;
constexpr Core::Camera_type cam_type = Core::Camera_type::orthographic;


} // anon ns


namespace Test {


Camera_test::Camera_test(Core::Context &ctx)
: App(ctx)
, m_entities{Core::Entity(get_world()), Core::Entity(get_world()), Core::Entity(get_world()), Core::Entity(get_world())}
, m_camera_entity(get_world())
, m_camera(m_camera_entity, ctx.get_width(), ctx.get_height())
{
  // Setup entities
  for(uint32_t i = 0; i < Camera_test_utils::max_cubes(); ++i)
  {
    const float delta = math::tau() / Camera_test_utils::max_cubes();
    const float turn = i * delta;
    
    const float radius = 2.f;
    const float x = math::sin(turn) * radius;
    const float y = math::cos(turn) * radius;
    
    Core::Entity &entity = m_entities[i];
    entity.set_name("Camera");
    
    entity.set_transform(Core::Transform(
      math::vec3_init(x, y, camera_distance),
      math::vec3_init(1.f, 1.f, math::to_float(i * 2) + 1.f),
      math::quat_init_with_axis_angle(0.f, 0.f, 1.f, turn)
    ));
    
    Core::Material cube_material("cube_material");
    cube_material.set_map_01(Texture_factory::get_dev_orange());
    cube_material.set_shader(Shader_factory::get_fullbright());
    
    entity.set_renderer(Core::Material_renderer(
      Model_factory::get_unit_cube(),
      cube_material
    ));
  }
  
  // Setup Camera
  {
    m_camera_entity.set_name("Camera");
    
    m_camera_entity.set_transform(Core::Transform(
      math::vec3_init(0.f, 0.f, camera_distance),
      math::vec3_one(),
      math::quat_init()
    ));

    m_camera.set_type(cam_type);
    m_camera.set_clear_color(Core::Color_utils::gray());
    
    if(cam_type == Core::Camera_type::orthographic)
    {
      m_camera.set_width(ctx.get_width() >> 6);
      m_camera.set_height(ctx.get_height() >> 6);
    }
    else
    {
      m_camera.set_width(ctx.get_width());
      m_camera.set_height(ctx.get_height());
    }
  }
}


void
Camera_test::on_think()
{
  assert(false);

  /*
    Allow the world to render.
  */
  get_world().think();
}


} // ns