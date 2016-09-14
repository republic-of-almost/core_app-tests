#include <tests/material_test.hpp>
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
constexpr float camera_height = 3.f;
constexpr float camera_tilt = math::tau() * 0.03f;

/*
  Scene settings.
*/
constexpr float scene_plane_scale = 10.f;
constexpr float scene_cube_scale = 2.f;
  
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
    uint32_t curr_mat = 0;
  
    const Core::Shader shader_fullbright(Core::Directory::volatile_resource_path("/assets/shaders/basic_fullbright.ogl"));
    assert(shader_fullbright);
    
    // Add material
    {
      Core::Material material_01("test_material_01");
      
      const Core::Texture texture_01(Core::Directory::volatile_resource_path("/assets/textures/dev_grid_green_512.png"));
      assert(texture_01);
    
      material_01.set_shader(shader_fullbright);
      material_01.set_map_01(texture_01);
      
      assert(curr_mat < Mat_utils::max_materials());
      m_materials[curr_mat++] = material_01;
    }

    // Add material
    {
      Core::Material material_02("test_material_02");
    
      const Core::Texture texture_02(Core::Directory::volatile_resource_path("/assets/textures/dev_grid_red_512.png"));
      assert(texture_02);
      
      material_02.set_shader(shader_fullbright);
      material_02.set_map_01(texture_02);
      
      assert(curr_mat < Mat_utils::max_materials());
      m_materials[curr_mat++] = material_02;
    }
    
    assert(curr_mat == Mat_utils::max_materials());
  }
  
  // ** Create Renderers And Attach ** //
  {
    {
      const Core::Model cube_model(Core::Directory::volatile_resource_path("/assets/models/unit_cube.obj"));
      assert(cube_model);
      
      uint32_t mat_id = 0;
      assert(mat_id < Mat_utils::max_materials());
      
      const Core::Material_renderer cube_material_renderer(m_materials[mat_id], cube_model);
      assert(cube_material_renderer);
      
      m_cube_entity.set_renderer(cube_material_renderer);
    }
    
    {
      const Core::Model plane_model(Core::Directory::volatile_resource_path("/assets/models/unit_plane.obj"));
      assert(plane_model);
      
      uint32_t mat_id = 1;
      assert(mat_id < Mat_utils::max_materials());
      
      const Core::Material_renderer plane_material_renderer(m_materials[mat_id], plane_model);
      assert(plane_material_renderer);
      
      m_plane_entity.set_renderer(plane_material_renderer);
    }
  }
}


void
Material_test::on_think()
{
  /*
    Orbits camera based on time.
  */
  m_camera_entity.set_transform(
    camera_transform(get_world().get_time_running() * 0.001f,
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