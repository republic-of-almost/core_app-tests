#include <tests/fps_test.hpp>
#include <tests/factories/texture_factory.hpp>
#include <tests/factories/shader_factory.hpp>
#include <tests/factories/model_factory.hpp>
#include <core/context/context.hpp>
#include <core/entity/entity_ref.hpp>
#include <core/resources/material.hpp>
#include <core/resources/shader.hpp>
#include <core/resources/texture.hpp>
#include <core/model/model.hpp>
#include <core/transform/transform.hpp>
#include <core/renderer/material_renderer.hpp>
#include <core/renderer/renderer.hpp>
#include <core/physics/collider.hpp>
#include <core/physics/rigidbody.hpp>
#include <core/physics/box_collider.hpp>


namespace Test {


Fps_test::Fps_test(Core::Context &ctx)
: App(ctx)
, m_player_entity(get_world())
, m_camera_entity(get_world())
, m_camera(m_camera_entity, ctx.get_width(), ctx.get_height())
{
  ctx.set_title("FPS Test");
  
  // Player
  {
    m_player_entity.set_name("Player");
  
    Core::Material player_mat("Player Mat");
    player_mat.set_shader(Shader_factory::get_fullbright());
    player_mat.set_map_01(Texture_factory::get_dev_green());
    
    m_player_entity.set_renderer(Core::Material_renderer(player_mat, Model_factory::get_unit_cube()));
    
    const float scale = 2.f;
    
    m_player_entity.set_transform(Core::Transform(
      math::vec3_init(0.f, 4.f, 0.f),
      math::vec3_init(scale, scale * math::g_ratio(), scale),
      math::quat_init()
    ));
    
    const Core::Box_collider box(0.5f, 0.5f, 0.5f);
    
    Core::Rigidbody rb;
    rb.set_mass(1.f);
    rb.set_collider(box);
    
    m_player_entity.set_rigidbody(rb);
  }
  
  // Camera
  {
    m_camera_entity.set_name("Camera");
    
    m_camera_entity.set_transform(
    Core::Transform(
      math::vec3_init(0.f, 3.f, 10.f),
      math::vec3_zero(),
      math::quat_init()
    ));
  }
  
  // Scene Entities
  {
    uint32_t scene_objs = 0;
  
    // Ground
    {
      assert(scene_objs < Fps_test_utils::max_scene_objects());
      
      Core::Entity ground(get_world());
      ground.set_name("Ground");
      
      Core::Material ground_mat("Ground Mat");
      ground_mat.set_shader(Shader_factory::get_fullbright());
      ground_mat.set_map_01(Texture_factory::get_dev_orange());
      
      ground.set_renderer(Core::Material_renderer(ground_mat, Model_factory::get_unit_cube()));
      
      ground.set_transform(Core::Transform(
        math::vec3_zero(),
        math::vec3_init(75.f, 1.f, 75.f),
        math::quat_init()
      ));
      
      const Core::Box_collider box(0.5f, 0.5f, 0.5f);
      
      Core::Rigidbody rb;
      rb.set_mass(0.f);
      rb.set_is_dynamic(false);
      rb.set_collider(box);
      
      ground.set_rigidbody(rb);
      
      m_scene[scene_objs] = static_cast<Core::Entity&&>(ground);
    }
  }
}


void
Fps_test::on_think()
{
  /*
    FPS Controls
  */
  {
  }

  /*
    Update and render the world
  */
  get_world().think();
}


} // ns