#include <tests/material_test.hpp>
#include <tests/factories/texture_factory.hpp>
#include <tests/factories/shader_factory.hpp>
#include <tests/factories/model_factory.hpp>
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


namespace {


/*
  General camera settings.
*/
constexpr float camera_distance = 10.f;
constexpr float camera_height   = 3.f;
constexpr float camera_tilt     = math::tau() * 0.03f;


/*
  Scene settings.
*/
constexpr float scene_plane_scale     = 10.f;
constexpr float scene_cube_scale      = 2.f;
constexpr float scene_delta_time_mod  = 0.0005f;
constexpr float scene_material_switch = 1.2f;


/*
  Calculates the camera orbit position for a given time.
*/
Core::Transform
camera_transform(const float time,
                 const float cam_tilt,
                 const float cam_dist,
                 const float cam_height)
{
  // Position of the camera over time.
  const float x = math::cos(time) * cam_dist;
  const float y = cam_height;
  const float z = math::sin(time) * cam_dist;
  const math::vec3 position = math::vec3_init(x, y, z);
  
  // Rotation of the camera over time.
  const math::quat rotation  = math::quat_init_with_axis_angle(0.f, 1.f, 0.f, time - math::quart_tau());
  const math::quat tilt_down = math::quat_init_with_axis_angle(1.f, 0.f, 0.f, cam_tilt);
  const math::quat final_rot = math::quat_multiply(tilt_down, rotation);
  
  // Build Transform
  const Core::Transform cam_trans (
    position,
    math::vec3_one(),
    final_rot
  );
  
  return cam_trans;
}


} // anon ns


namespace Test {


Material_test::Material_test(Core::Context &ctx)
: App(ctx)
, m_timer(0.f)
, m_cube_entity(get_world())
, m_plane_entity(get_world())
, m_camera_entity(get_world())
, m_camera(m_camera_entity, ctx.get_width(), ctx.get_height())
{
  namespace Mat_utils = ::Test::Material_test_utils;
  
  ctx.set_title("Material Renderer");

  // ** Setup Entities ** //
  {
    // Move cube up so its not intersecting with plane.
    {
      m_cube_entity.set_name("Material Test Cube");
      
      const Core::Transform cube_trans(
        math::vec3_init(0.f, scene_cube_scale * 0.5f, 0.f),
        math::vec3_init(scene_cube_scale),
        math::quat_init()
      );
      
      m_cube_entity.set_transform(cube_trans);
    }
    
    // Scale up plane
    {
      m_plane_entity.set_name("Material Test Plane");
      
      const Core::Transform scaled_up(
        math::vec3_zero(),
        math::vec3_init(scene_plane_scale, 1.f, scene_plane_scale),
        math::quat_init()
      );
      
      m_plane_entity.set_transform(scaled_up);
    }

    // Back and up for the camera.
    {
      m_camera_entity.set_name("Material Test Camera");

      m_camera_entity.set_transform(
        camera_transform(0.f,
                         camera_tilt,
                         camera_distance,
                         camera_height)
      );
    }
  }

  // ** Create Materials ** //
  {
    // Creates the material and stores it in the out.
    auto add_material = [](const Core::Shader &shd,
                           const Core::Texture &tex,
                           const uint32_t index,
                           Core::Material *out)
    {
      char name[256];
      memset(name, 0, sizeof(name));
      sprintf(name, "test_material_%02d", index);
    
      Core::Material material(name);
      material.set_shader(shd);
      
      if(tex)
      {
        material.set_map_01(tex);
      }
      
      *out = material;
    };
    
    uint32_t curr_mat = 0;
    assert(curr_mat < Mat_utils::max_materials());
    add_material(Shader_factory::get_fullbright(), Texture_factory::get_dev_green(), curr_mat, &m_materials[curr_mat]);
    
    ++curr_mat;
    assert(curr_mat < Mat_utils::max_materials());
    add_material(Shader_factory::get_fullbright(), Texture_factory::get_dev_red(), curr_mat, &m_materials[curr_mat]);

    ++curr_mat;
    assert(curr_mat < Mat_utils::max_materials());
    add_material(Shader_factory::get_fullbright(), Texture_factory::get_dev_squares(), curr_mat, &m_materials[curr_mat]);

    ++curr_mat;
    assert(curr_mat < Mat_utils::max_materials());
    add_material(Shader_factory::get_fullbright(), Texture_factory::get_dev_squares_large(), curr_mat, &m_materials[curr_mat]);

    ++curr_mat;
    assert(curr_mat < Mat_utils::max_materials());
    add_material(Shader_factory::get_fullbright(), Texture_factory::get_dev_colored_squares(), curr_mat, &m_materials[curr_mat]);

    ++curr_mat;
    assert(curr_mat < Mat_utils::max_materials());
    add_material(Shader_factory::get_noise(), Core::Texture(), curr_mat, &m_materials[curr_mat]);
    
    ++curr_mat;
    assert(curr_mat == Mat_utils::max_materials());
  }
  
  // ** Create Renderers And Attach ** //
  {
    {
      uint32_t mat_id = 0;
      assert(mat_id < Mat_utils::max_materials());
      
      const Core::Material_renderer cube_material_renderer(m_materials[mat_id], Model_factory::get_unit_cube());
      assert(cube_material_renderer);
      
      m_cube_entity.set_renderer(cube_material_renderer);
    }
    
    {
      uint32_t mat_id = 1;
      assert(mat_id < Mat_utils::max_materials());
      
      const Core::Material_renderer plane_material_renderer(m_materials[mat_id], Model_factory::get_unit_plane());
      assert(plane_material_renderer);
      
      m_plane_entity.set_renderer(plane_material_renderer);
    }
  }
}


void
Material_test::on_think()
{
  /*
    After a time, change the materials randomly.
  */
  {
    m_timer += get_world().get_delta_time();
    
    if(m_timer > scene_material_switch)
    {
      m_timer = 0.f;
      
      Core::Material_renderer cube_renderer = m_cube_entity.get_renderer();
      cube_renderer.set_material(m_materials[rand() % Material_test_utils::max_materials()]);
      m_cube_entity.set_renderer(cube_renderer);

      Core::Material_renderer plane_renderer = m_plane_entity.get_renderer();
      plane_renderer.set_material(m_materials[rand() % Material_test_utils::max_materials()]);
      m_plane_entity.set_renderer(plane_renderer);
    }
  }

  /*
    Orbits camera based on time.
  */
  m_camera_entity.set_transform(
    camera_transform(get_world().get_time_running() * scene_delta_time_mod,
                     camera_tilt,
                     camera_distance,
                     camera_height)
  );

  /*
    Allow the world to render.
  */
  get_world().think();
}


} // ns