#include <core/world/world.hpp>
#include <core/context/context.hpp>
#include <core/entity/entity.hpp>
#include <core/entity/entity_ref.hpp>
#include <core/camera/camera.hpp>
#include <core/resources/shader.hpp>
#include <core/resources/texture.hpp>
#include <core/resources/material.hpp>
#include <core/model/model.hpp>
#include <core/physics/rigidbody.hpp>
#include <core/physics/box_collider.hpp>
#include <core/physics/collider.hpp>
#include <core/common/directory.hpp>
#include <core/transform/transform.hpp>
#include <core/renderer/material_renderer.hpp>
#include <core/renderer/renderer.hpp>
#include <core/input/controller.hpp>
#include <core/input/buttons.hpp>
#include <core/input/axis.hpp>
#include <core/color/color_predefined.hpp>
#include <core/common/ray.hpp>
#include <core/font/font.hpp>
#include <core/renderer/text_renderer.hpp>
#include <framework/actor.hpp>
#include <utilities/logging.hpp>
#include <cstring>

// - phys test
#include <3rdparty/qu3e/q3.h>


/*
  FPS Demo
  --
  Creates a simple fps style scene.
*/


int
main()
{
  // ** SETUP WORLD AND CONTEXT ** //

  Core::Context_setup setup;
  setup.vsync = true;
  Core::Context context(800, 480, false, "Tests", setup);
  
  
  Core::World world(context);
  
  world.set_collision_callback([](const Core::Collision_type type,
                                  const Core::Collision &collision)
  {
    
  });
  
  // Text
      std::vector<uint8_t> data;
    data.resize(256 * 256);
    
    for(auto &d : data)
    {
      d = 255;
    }
  
//  Core::Font my_font("/Users/PhilCK/Desktop/font/LiberationSerif-Regular.ttf");
  
//  Core::Entity text_entity(world);
//  text_entity.set_name("text-test");
//  
//  Core::Text_renderer text_renderer;
//  text_renderer.set_font(my_font);
//  text_renderer.set_text("Foo-bar-123-#!.[]<>^");
//  text_entity.set_renderer(text_renderer);
  
  
  // ** SETUP RESOURCES ** //
  
  const Core::Shader shader_fullbright(Core::Directory::volatile_resource_path("assets/shaders/basic_fullbright.ogl"));
  const Core::Texture texture_orange(Core::Directory::volatile_resource_path("assets/textures/dev_grid_orange_512.png"));
  const Core::Texture texture_red(Core::Directory::volatile_resource_path("assets/textures/dev_grid_red_512.png"));
  const Core::Texture texture_green(Core::Directory::volatile_resource_path("assets/textures/dev_grid_green_512.png"));
  
  Core::Material material_fb_or("fullbright-orange");
  material_fb_or.set_shader(shader_fullbright);
  material_fb_or.set_map_01(texture_orange);

  Core::Material material_fb_red("fullbright-red");
  material_fb_red.set_shader(shader_fullbright);
  material_fb_red.set_map_01(texture_red);

  Core::Material material_fb_green("fullbright-green");
  material_fb_green.set_shader(shader_fullbright);
  material_fb_green.set_map_01(texture_green);
  
  Core::Model model_plane(Core::Directory::volatile_resource_path("assets/models/unit_plane.obj"));
  Core::Model model_cube(Core::Directory::volatile_resource_path("assets/models/unit_cube.obj"));
  
  // ** SETUP ENTITIES ** //

  Core::Entity cam_entity(world);
  Core::Camera main_camera(world);
  {
    cam_entity.set_name("Camera");
    
    Core::Transform transform;
    transform.set_position(math::vec3_init(0.f, 3.f, 10.f));
    
    cam_entity.set_transform(transform);
    
    main_camera.set_attached_entity(cam_entity);
    main_camera.set_priority(1);
    
    main_camera.set_width(context.get_width());
    main_camera.set_height(context.get_height());
    main_camera.set_feild_of_view(math::quart_tau() * 0.5f);
    main_camera.set_clear_color(Core::Color_utils::gray());
  }
  
  Core::Entity ground_entity(world);
  {
    ground_entity.set_name("Ground Entity");
    
    Core::Transform transform;
    transform.set_scale(math::vec3_init(10.f, 1.f, 10.f));
    
    ground_entity.set_transform(transform);
    
    Core::Rigidbody rb;
    rb.set_collider(Core::Box_collider(0.5f, 0.5f, 0.5f));
    rb.set_mass(0);
    rb.set_is_dynamic(false);
    
    ground_entity.set_rigidbody(rb);
    
    Core::Material_renderer ground_renderer;
    ground_renderer.set_material(material_fb_or);
    ground_renderer.set_model(model_cube);
    
    ground_entity.set_renderer(ground_renderer);
  }
  
  // Make a bunch of entities
  constexpr uint32_t number_of_entities = 16;
  Core::Entity entities[number_of_entities];
  
  for(uint32_t i = 0; i < number_of_entities; ++i)
  {
    auto &phys_box = entities[i];
    phys_box = Core::Entity(world);
    
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    
    sprintf(buffer, "Rigidbody-%d", i);
    
    phys_box.set_name(buffer);
    
    Core::Transform transform;
    transform.set_scale(math::vec3_init(1.f, 1.f, 1.f));
    transform.set_position(math::vec3_init(0.5f,
                                           3.f + math::to_float(i),
                                           0.f));
    
    phys_box.set_transform(transform);
    
    Core::Material_renderer renderer;
    renderer.set_material(material_fb_red);
    renderer.set_model(model_cube);
    
    Core::Rigidbody rb;
    rb.set_collider(Core::Box_collider(0.5f, 0.5f, 0.5f));
    rb.set_is_trigger(false);
        
    phys_box.set_rigidbody(rb);
    phys_box.set_renderer(renderer);
  }
  
  Core::Lib::Actor actor(world);
  Core::Entity actor_view(world);
  {
    Core::Transform transform;
    transform.set_position(math::vec3_init(0.25f, 5.f, 0.25f));
    
    actor_view.set_transform(transform);
    
//    Core::Rigidbody rb;
//    rb.set_collider(Core::Box_collider(0.5f, 0.5f, 0.5f));
//    
//    actor.set_rigidbody(rb);
    
    Core::Material_renderer renderer;
    renderer.set_material(material_fb_green);
    renderer.set_model(model_cube);
    
    actor_view.set_renderer(renderer);
  }
  
  // ** RUN WINDOW AND APP ** //
  
  while(context.is_open())
  {
    // Actor
    {
      Core::Controller controller(context, 0);
      
      actor.move_fwd(controller.get_axis(0).y);
      actor.move_left(controller.get_axis(0).x);
      actor.rotate(controller.get_axis(1).x);
    
      actor.apply_forces(world.get_delta_time());
      actor_view.set_transform(actor.get_head_ref().get_transform());
    }
  
    // ** FPS INPUT ** //
    {
      Core::Controller controller(context, 0);
      Core::Transform transform = cam_entity.get_transform();
      
      // Move Axis
      {
        const float move_mul = world.get_delta_time() * 4.f;
      
        const math::vec3 fwd      = math::vec3_scale(transform.get_forward(), controller.get_axis(0).y * move_mul);
        const math::vec3 left     = math::vec3_scale(transform.get_left(), controller.get_axis(0).x * move_mul);
        const math::vec3 curr_pos = transform.get_position();
        const math::vec3 new_pos  = math::vec3_add(math::vec3_add(curr_pos, fwd), left);
        
        transform.set_position(new_pos);
      }
      
      // Rot Axis
      {
        const float rot_mul = world.get_delta_time() * 3.f;
      
        static float accum_x = 0.f;
        static float accum_y = 0.f;
        
        accum_x += controller.get_axis(1).x * rot_mul;
        accum_y += controller.get_axis(1).y * rot_mul;
        
        const math::quat yaw   = math::quat_init_with_axis_angle(Core::Transform::get_world_up(), accum_x);
        const math::quat pitch = math::quat_init_with_axis_angle(Core::Transform::get_world_left(), accum_y);
        const math::quat rot   = math::quat_multiply(pitch, yaw);
                
        transform.set_rotation(rot);
      }
      
//      cam_entity.set_transform(transform);
      
//      if(controller.is_button_down_on_frame(Core::Button::button_0))
      {
//        falling->ApplyForceAtWorldPoint(q3Vec3(0, 300, 0), falling->GetTransform().position);
      }
    }
  
    // ** UPDATE THE WORLD ** //
    
    world.think();
  }
  
  
  return 0;
}