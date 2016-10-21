#include <tests/fps_test.hpp>
#include <tests/factories/texture_factory.hpp>
#include <tests/factories/shader_factory.hpp>
#include <tests/factories/model_factory.hpp>
#include <core/context/context.hpp>
#include <core/entity/entity.hpp>
#include <core/entity/entity_ref.hpp>
#include <core/entity/entity_components.hpp>
#include <core/resources/material.hpp>
#include <core/input/controller.hpp>
#include <core/input/mouse.hpp>
#include <core/input/buttons.hpp>
#include <core/resources/shader.hpp>
#include <core/world/world.hpp>
#include <core/resources/texture.hpp>
#include <core/common/ray.hpp>
#include <core/model/model.hpp>
#include <core/transform/transform.hpp>
#include <core/transform/transform_utils.hpp>
#include <core/renderer/material_renderer.hpp>
#include <core/renderer/renderer.hpp>
#include <core/physics/collider.hpp>
#include <core/physics/collision.hpp>
#include <core/common/collision.hpp>
#include <core/physics/rigidbody.hpp>
#include <core/color/color.hpp>
#include <core/color/color_predefined.hpp>
#include <core/physics/box_collider.hpp>
#include <core/debug/line_renderer.hpp>
#include <utilities/logging.hpp>
#include <math/vec/vec2.hpp>
#include <factories/objects/object_factory.hpp>


namespace Test {


Fps_test::Fps_test(Core::Context &ctx)
: App(ctx)
//, m_player_entity(get_world())
, m_player_entity(Factory_entity::create(Factory_entity::get_id("Player"), get_world()))
, m_player_body(get_world())
, m_camera_entity(get_world())
, m_scene
  {
    Factory_entity::create(Factory_entity::get_id("Ground"), get_world()),
    Core::Entity(),
    Core::Entity(),
    Core::Entity(),
    Core::Entity(),
    Core::Entity(),
    Core::Entity(),
    Core::Entity(),
    Core::Entity(),
    Core::Entity(),
    Core::Entity(),
    Core::Entity(),
  }
, m_camera_offset(math::vec3_init(0, 0.1f, 10.f))
{
  ctx.set_title("FPS Test");
  
//  Core::Input::mouse_set_capture(get_ctx(), true);
  
  // Player
  {
    m_player_entity.set_name("Player");
  
    Core::Material player_mat("Player Mat");
    player_mat.set_shader(Shader_factory::get_fullbright());
    player_mat.set_map_01(Texture_factory::get_dev_orange());
    
    m_player_entity.set_renderer(Core::Material_renderer(player_mat, Model_factory::get_unit_cube()));
    
    const float scale = 0.4f;
    
    Core::Entity_component::set_transform(
      m_player_entity,
      Core::Transform(
        math::vec3_init(0.f, 4.f, 10.f),
        math::vec3_init(scale, scale * math::g_ratio(), scale),
        math::quat_init()
      )
    );
    
//    const Core::Box_collider box(0.5f, 0.5f, 0.5f);
//
//    Core::Rigidbody rb;
//    rb.set_mass(1.f);
//    rb.set_collider(box);
//    
//    m_player_entity.set_rigidbody(rb);
  }
  
  // Player body
  {
    m_player_body.set_name("Player_body");
    m_player_body.set_user_data((uintptr_t)&m_player_entity);
    
    Core::Material body_mat("Body Mat");
    body_mat.set_shader(Shader_factory::get_fullbright());
    body_mat.set_map_01(Texture_factory::get_dev_red());
    
    m_player_body.set_renderer(Core::Material_renderer(body_mat, Model_factory::get_unit_cube()));
    
    Core::Entity_component::set_transform(
      m_player_body,
      Core::Transform(
        math::vec3_zero(),
        math::vec3_init(3, 1, 3),
        math::quat_init_with_axis_angle(0, 1, 0, 2.f)
      )
    );
    
    const Core::Box_collider box(0.5f, 0.5f, 0.5f);

    Core::Rigidbody rb;
    rb.set_is_dynamic(false);
    rb.set_mass(0.f);
    rb.set_collider(box);
    rb.set_is_trigger(true);
    
    m_player_body.set_rigidbody(rb);
  }
  
  // Camera
  {
    m_camera_entity.set_name("Camera");
    
    Core::Entity_component::set_transform(
      m_camera_entity,
      Core::Transform(
        math::vec3_init(0.f, 3.f, 10.f),
        math::vec3_zero(),
        math::quat_init()
      )
    );
    
    const Core::Camera camera(ctx.get_width(), ctx.get_height());
    Core::Entity_component::set_camera(m_camera_entity, camera);
  }
  
  // Scene Entities
  {
    uint32_t scene_objs = 0;
    scene_objs++;
    // Ground
    {
//      assert(scene_objs < Fps_test_utils::max_scene_objects());
//      
//      Core::Entity ground(get_world());
//      ground.set_name("Ground");
//      
      Core::Material ground_mat("Ground Mat");
      ground_mat.set_shader(Shader_factory::get_fullbright());
      ground_mat.set_map_01(Texture_factory::get_dev_squares());
      m_scene[0].set_renderer(Core::Material_renderer(ground_mat, Model_factory::get_unit_cube()));
//
//      ground.set_renderer(Core::Material_renderer(ground_mat, Model_factory::get_unit_cube()));
//      
//      ground.set_transform(Core::Transform(
//        math::vec3_zero(),
//        math::vec3_init(75.f, 1.f, 75.f),
//        math::quat_init()
//      ));
//      
//      const Core::Box_collider box(0.5f, 0.5f, 0.5f);
//
//      Core::Rigidbody rb;
//      rb.set_mass(0.f);
//      rb.set_is_dynamic(false);
//      rb.set_collider(box);
//      
//      m_scene[0].set_rigidbody(rb);
//
//      m_scene[scene_objs++] = static_cast<Core::Entity&&>(ground);
    }
    
    // No Step box
    {
      assert(scene_objs < Fps_test_utils::max_scene_objects());
      
      Core::Entity no_step(get_world());
      no_step.set_name("No step box");
      
      Core::Material no_step_mat("No Step Mat");
      no_step_mat.set_shader(Shader_factory::get_fullbright());
      no_step_mat.set_map_01(Texture_factory::get_dev_red());
      
      no_step.set_renderer(Core::Material_renderer(no_step_mat, Model_factory::get_unit_cube()));
      
      Core::Entity_component::set_transform(
        no_step,
        Core::Transform(
          math::vec3_init(12.f, 1.f, 0.f),
          math::vec3_init(4.f, 1.f, 4.f),
          math::quat_init()
        )
      );
      
      const Core::Box_collider box(0.5f, 0.5f, 0.5f);
      
      Core::Rigidbody rb;
      rb.set_mass(1.f);
      rb.set_is_dynamic(true);
      rb.set_collider(box);
      
      no_step.set_rigidbody(rb);
      
      m_scene[scene_objs++] = static_cast<Core::Entity&&>(no_step);
    }
    
    // Step box
    {
      constexpr uint32_t number_of_boxes = 9;
    
      for(uint32_t i = 0; i < number_of_boxes; ++i)
      {
        assert(scene_objs < Fps_test_utils::max_scene_objects());
        
        Core::Entity step_box(get_world());
        step_box.set_name("Step Box");
        
        Core::Material step_mat("Step Mat");
        step_mat.set_shader(Shader_factory::get_fullbright());
        step_mat.set_map_01(Texture_factory::get_dev_green());
        
        step_box.set_renderer(Core::Material_renderer(step_mat, Model_factory::get_unit_cube()));
        
        constexpr float thickness = 0.2f;
        
        Core::Entity_component::set_transform(
          step_box,
          Core::Transform(
            math::vec3_init(1.f, 1.f + math::to_float(i) * thickness, 1.f),
            math::vec3_init(math::to_float(number_of_boxes + 2) - math::to_float(i),
                            thickness,
                            math::to_float(number_of_boxes + 2) - math::to_float(i)),
            math::quat_init()
          )
        );
        
        const Core::Box_collider box(0.5f, 0.5f, 0.5f);
        
        Core::Rigidbody rb;
        rb.set_mass(1.f);
        rb.set_is_dynamic(true);
        rb.set_collider(box);
        
        step_box.set_rigidbody(rb);
        
        m_scene[scene_objs++] = static_cast<Core::Entity&&>(step_box);
      }
    }
    
    // Wall
    {
      assert(scene_objs < Fps_test_utils::max_scene_objects());
  
      Core::Entity wall(get_world());
      wall.set_name("Wall");
      
      Core::Material no_step_mat("No Step Mat");
      no_step_mat.set_shader(Shader_factory::get_fullbright());
      no_step_mat.set_map_01(Texture_factory::get_dev_red());
      
      wall.set_renderer(Core::Material_renderer(no_step_mat, Model_factory::get_unit_cube()));
      
      Core::Entity_component::set_transform(
        wall,
        Core::Transform(
          math::vec3_init(-15.f, 10.f, 0.f),
          math::vec3_init(10.f, 10.f, 10.f),
          math::quat_init()
        )
      );
      
      const Core::Box_collider box(0.5f, 0.5f, 0.5f);
      
      Core::Rigidbody rb;
      rb.set_mass(1.f);
      rb.set_is_dynamic(true);
      rb.set_collider(box);
      
      wall.set_rigidbody(rb);
      
      m_scene[scene_objs++] = static_cast<Core::Entity&&>(wall);
    }
    
    // Double check we have it all and not 
    assert(scene_objs <= Fps_test_utils::max_scene_objects());
  }
  
  // Collision test
  {
    get_world().set_collision_callback([](const Core::Collision_type type, const Core::Collision_pair &coll)
    {
      printf("Collision with: %s \n", coll.with_this.get_entity().get_name());
      if(strcmp(coll.with_this.get_entity().get_name(), "Player_body") == 0)
      {
        Core::Entity_ref ref = coll.with_this.get_entity();
        Core::Entity *player_entity = reinterpret_cast<Core::Entity*>(ref.get_user_data());
        
        printf("Contact Points: %zu \n", coll.with_this.get_number_of_contacts());
        
        for(const Core::Contact &contact : coll.with_this)
        {
//          const Core::Contact contact = coll.with_this.get_contact(i);
          const math::vec3 bounce_back = math::vec3_scale(contact.get_normal(), contact.get_penetration_depth() * 10);
          
          // Needs to set the player transform as well as body.
          // Phil Scene graph should be next.
          
          Core::Transform body_transform = Core::Entity_component::get_transform(ref);
          body_transform.set_position(math::vec3_add(body_transform.get_position(), bounce_back));
          Core::Entity_component::set_transform(ref, body_transform);
          
          Core::Transform player_transform = Core::Entity_component::get_transform(*player_entity);
          player_transform.set_position(math::vec3_add(player_transform.get_position(), bounce_back));
          Core::Entity_component::set_transform(*player_entity, player_transform);
        }
      }
    });
  }
}


void
Fps_test::on_think()
{
    const Core::Transform player_transform = Core::Entity_component::get_transform(m_player_entity);
    
    math::vec3 next_step = player_transform.get_position();

  /*
    FPS Controls.
  */
  {
    const Core::Controller controller(get_ctx(), 0);
    
    /*
      Movement
    */
    {
      constexpr float move_speed = 7.f;
    
      const Core::Axis axis = controller.get_axis(0);
      const math::vec2 move_axis = math::vec2_init(axis.x, axis.y * -1.f);
      
      if(math::vec2_length(move_axis) > math::epsilon())
      {
        const math::vec2 move = math::vec2_normalize(move_axis);
        
        const float fwd  = math::get_y(move) * get_world().get_delta_time() * move_speed;
        const float left = math::get_x(move) * get_world().get_delta_time() * move_speed;
        
        Core::Transform trans = Core::Entity_component::get_transform(m_player_entity);
        
        const math::vec3 fwd_movement  = math::vec3_add(trans.get_position(), math::vec3_scale(trans.get_forward(), fwd));
        const math::vec3 left_movement = math::vec3_add(fwd_movement, math::vec3_scale(trans.get_left(), left));
        
        next_step = left_movement;
        
//        m_player_entity.set_transform(trans);
      }
    }
    
    /*
      Rotations
    */
    {
      const Core::Axis axis = controller.get_axis(1);
      const float rot_value  = axis.x * 0.02f;
      const float head_value = axis.y * 0.02f;

      Core::Transform trans = Core::Entity_component::get_transform(m_player_entity);
      
      const math::quat body_rot  = math::quat_init_with_axis_angle(Core::Transform_utils::get_world_up(), rot_value);
      const math::quat head_rot  = math::quat_init_with_axis_angle(Core::Transform_utils::get_world_left(), head_value);
      
      const math::quat accum_rot  = math::quat_multiply(trans.get_rotation(), body_rot);
      const math::quat accum_head = math::quat_multiply(head_rot, accum_rot);
      
      trans.set_rotation(accum_head);
      
      Core::Entity_component::set_transform(m_player_entity, trans);
    }
    
    /*
      Toggle camera offset
    */
    {
      if(controller.is_button_up_on_frame(Core::Gamepad_button::dpad_up))
      {
        if(math::vec3_length(m_camera_offset) > math::epsilon())
        {
          m_camera_offset = math::vec3_zero();
        }
        else
        {
          m_camera_offset = math::vec3_init(0, 0.3f, 10.f);
        }
      }
    }
  } // Fps controls
  
  /*
    Cast rays to figer out where to go.
  */
  {
    Core::Transform player_trans = Core::Entity_component::get_transform(m_player_entity);
    const math::vec3 curr_pos = player_trans.get_position();
    const math::vec3 world_down = math::vec3_scale(Core::Transform_utils::get_world_up(), -1.f);
    const math::vec3 ray_offset = math::vec3_add(world_down, math::vec3_init(0, -1, 0));
    
    const Core::Ray curr_ray(math::vec3_add(curr_pos, ray_offset), world_down);
    const Core::Ray step_ray(math::vec3_add(next_step, ray_offset), world_down);
    
    const Core::Collision curr_step_collision = get_world().find_entity_by_ray(curr_ray);
    const Core::Collision next_step_collision = get_world().find_entity_by_ray(step_ray);
//    assert(curr_step_collision);
    
    const Core::Contact curr_ray_contact = curr_step_collision.get_contact(0);
    const Core::Contact next_ray_contact = next_step_collision.get_contact(0);
    
    // Check if can move.
    if(curr_step_collision)
    {
      bool can_step_up = true;
      {
        if(math::get_y(next_ray_contact.get_position()) > (math::get_y(curr_ray_contact.get_position()) + 0.2f))
        {
          can_step_up = false;
        }
      }
    
      if(can_step_up)
      {
        if(next_step_collision.has_hit())
        {
          const math::vec3 height = math::vec3_add(next_ray_contact.get_position(), math::vec3_scale(Core::Transform_utils::get_world_up(), 4.f));
          player_trans.set_position(height);
          Core::Entity_component::set_transform(m_player_entity, player_trans);
          
          Core::Transform body_trans = Core::Entity_component::get_transform(m_player_body);
          body_trans.set_position(player_trans.get_position());
          Core::Entity_component::set_transform(m_player_body, body_trans);
        }
      }
    }
    
    // Debug lines
    Core::Debug::debug_line(curr_pos, curr_ray_contact.get_position(), Core::Color_utils::magenta());
    
    if(next_step_collision)
    {
      Core::Debug::debug_line(next_step, next_ray_contact.get_position(), Core::Color_utils::green());
    }
    else
    {
      Core::Debug::debug_line(next_step, math::vec3_add(next_step, math::vec3_scale(world_down, 10.f)), Core::Color_utils::red());
    }
  }
  
  /*
    Camera to player's head.
  */
  {
    const Core::Transform player_transform = Core::Entity_component::get_transform(m_player_entity);
    
    const math::vec3 back       = math::vec3_scale(player_transform.get_forward(), -1.f);
    const math::vec3 up         = player_transform.get_up();
    const math::vec3 player_pos = player_transform.get_position();
    const math::vec3 trail_pos  = math::vec3_add(player_pos, math::vec3_scale(back, get_z(m_camera_offset)));
    const math::vec3 final_pos  = math::vec3_add(trail_pos, math::vec3_scale(up, get_y(m_camera_offset)));
    
    Core::Entity_component::set_transform(
      m_camera_entity,
      Core::Transform(
        final_pos,
        math::vec3_one(),
        player_transform.get_rotation()
      )
    );
  }
  
//  get_world().get_overlapping_aabbs(const std::function<void (const Core::Collision_pairs *, const uint32_t)> &callback)

  /*
    Update and render the world
  */
  get_world().think();
}


} // ns