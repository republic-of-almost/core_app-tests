#include <tests/cube_fall_test.hpp>
#include <tests/common.hpp>
#include <tests/factories/texture_factory.hpp>
#include <tests/factories/shader_factory.hpp>
#include <tests/factories/model_factory.hpp>
#include <core/context/context.hpp>
#include <core/transform/transform.hpp>
#include <core/entity/entity.hpp>
#include <core/entity/entity_ref.hpp>
#include <core/entity/entity_components.hpp>
#include <core/resources/shader.hpp>
#include <core/resources/texture.hpp>
#include <core/model/model.hpp>
#include <core/renderer/material_renderer.hpp>
#include <core/renderer/renderer.hpp>
#include <core/physics/collider.hpp>
#include <core/physics/rigidbody.hpp>
#include <core/physics/box_collider.hpp>


namespace Test {


namespace {


constexpr float camera_distance = 15.f;
constexpr float camera_height   = 7.f;
constexpr float camera_tilt     = math::tau() * 0.03f;


constexpr float scene_delta_time_mod = 0.0005f;
constexpr float scene_rb_spawn_time  = 1.2f;


inline void
setup_collider(Core::Entity_ref ref,
               const float mass = 1.f)
{
  const Core::Box_collider collider(0.5, 0.5, 0.5);
  
  Core::Rigidbody rb;
  rb.set_collider(collider);
  rb.set_mass(mass);
  
  if(mass == 0.f)
  {
    rb.set_is_dynamic(false);
  }
  
  ref.set_rigidbody(rb);
}


} // anon ns


Cube_fall_test::Cube_fall_test(Core::Context &ctx)
: App(ctx)
, m_entity_pivot(0)
, m_rb_spawn_timer(0.f)
, m_ground_entity(get_world())
, m_camera_entity(get_world())
, m_camera(m_camera_entity, ctx.get_width(), ctx.get_height())
{
  ctx.set_title("Cube Fall Test");

  // Setup Ground
  {
    m_ground_entity.set_name("Ground Entity");
    
    Core::Entity_component::set_transform(
      m_ground_entity,
      Core::Transform(
        math::vec3_zero(),
        math::vec3_init(150.f, 0.25f, 150.f),
        math::quat_init()
      )
    );
    
    Core::Material ground_mat("Ground Material");
    ground_mat.set_shader(Shader_factory::get_fullbright());
    ground_mat.set_map_01(Texture_factory::get_dev_orange());
    
    const Core::Material_renderer ground_renderer(ground_mat, Model_factory::get_unit_cube());
    m_ground_entity.set_renderer(ground_renderer);
    
    setup_collider(m_ground_entity, 0.f);
  }

  // Setup Camera
  {
    m_camera_entity.set_name("Camera Entity");
    
    Core::Entity_component::set_transform(
      m_camera_entity,
      Common::Orbit_transform(0, camera_tilt, camera_distance, camera_height)
    );
  }
  
  // Create Cube Materials
  {
    uint32_t cube_mat = 0;
    char name[256];
    
    {
      memset(name, 0, sizeof(name));
      sprintf(name, "RB Material %d", cube_mat);
      
      assert(cube_mat < Cube_fall_utils::max_materials());
      
      m_cube_materials[cube_mat] = Core::Material(name);
      m_cube_materials[cube_mat].set_shader(Shader_factory::get_fullbright());
      m_cube_materials[cube_mat].set_map_01(Texture_factory::get_dev_red());
      
      ++cube_mat;
    }
    
    {
      memset(name, 0, sizeof(name));
      sprintf(name, "RB Material %d", cube_mat);
      
      assert(cube_mat < Cube_fall_utils::max_materials());
    
      m_cube_materials[cube_mat] = Core::Material("RB Material");
      m_cube_materials[cube_mat].set_shader(Shader_factory::get_fullbright());
      m_cube_materials[cube_mat].set_map_01(Texture_factory::get_dev_green());
      
      ++cube_mat;
    }

    {
      memset(name, 0, sizeof(name));
      sprintf(name, "RB Material %d", cube_mat);
      
      assert(cube_mat < Cube_fall_utils::max_materials());
    
      m_cube_materials[cube_mat] = Core::Material("RB Material");
      m_cube_materials[cube_mat].set_shader(Shader_factory::get_fullbright());
      m_cube_materials[cube_mat].set_map_01(Texture_factory::get_dev_squares());
      
      ++cube_mat;
    }

    {
      memset(name, 0, sizeof(name));
      sprintf(name, "RB Material %d", cube_mat);
      
      assert(cube_mat < Cube_fall_utils::max_materials());
    
      m_cube_materials[cube_mat] = Core::Material("RB Material");
      m_cube_materials[cube_mat].set_shader(Shader_factory::get_fullbright());
      m_cube_materials[cube_mat].set_map_01(Texture_factory::get_dev_colored_squares());
      
      ++cube_mat;
    }

    assert(cube_mat == Cube_fall_utils::max_materials());
  }
  
  // Callback
  {
    get_world().set_collision_callback([](const Core::Collision_type type, const Core::Collision_pair &collision)
    {
    });
  }
}


void
Cube_fall_test::on_think()
{
  /*
    Create new rbs
  */
  {
    m_rb_spawn_timer += get_world().get_delta_time();
  
    if(m_rb_spawn_timer > scene_rb_spawn_time)
    {
      Core::Entity new_cube = Core::Entity(get_world());
      new_cube.set_name("RB Cube");
      
      const Core::Material_renderer renderer(m_cube_materials[rand() % Cube_fall_utils::max_materials()],
                                             Model_factory::get_unit_cube());
      new_cube.set_renderer(renderer);
      
      setup_collider(new_cube);
    
      m_entities[m_entity_pivot % Cube_fall_utils::max_cubes()] = static_cast<Core::Entity&&>(new_cube);
      
      ++m_entity_pivot;
    }
  }
  
  /*
    Update camera orbit
  */
  Core::Entity_component::set_transform(
    m_camera_entity,
    Common::Orbit_transform(get_world().get_time_running() * scene_delta_time_mod, camera_tilt, camera_distance, camera_height)
  );
  
  /*
    Update the world
  */
  get_world().think();
}


} // ns