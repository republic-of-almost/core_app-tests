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

// - phys test
#include <3rdparty/qu3e/q3.h>

/*
  FPS Demo
  --
  Creates a simple fps style scene.
*/


  q3Scene scene(1.0/60.0);

int
main()
{
  // ** SETUP WORLD AND CONTEXT ** //

  Core::Context_setup setup;
  setup.vsync = true;
  Core::Context context(800, 480, false, "FPS Test", setup);
  Core::World world(context);
  
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
    transform.set_position(math::vec3_init(0.f, 1.f, 10.f));
    
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
    rb.set_collider(Core::Box_collider(1,1,1));
    rb.set_mass(0);
    
    ground_entity.set_rigidbody(rb);
    
    
    Core::Material_renderer ground_renderer;
    ground_renderer.set_material(material_fb_or);
    ground_renderer.set_model(model_cube);
    
    ground_entity.set_renderer(ground_renderer);
  }
  
  //  Phys test
  
  scene.SetIterations(60);
	scene.SetAllowSleep(false);

  // Falling body
//  q3Body *falling = nullptr;
//  {
//    q3BodyDef bodyDef;
//    bodyDef.allowSleep = false;
//    bodyDef.position.Set(0.5f, 3.0f, 0.0f);
//    bodyDef.bodyType = eDynamicBody;
//    
//    q3Body *body = scene.CreateBody(bodyDef);
//    
//    q3BoxDef boxDef;
////    boxDef.SetDensity(0.5f);
//    
//    q3Transform localSpace;
//    q3Identity(localSpace);
//    boxDef.Set(localSpace, q3Vec3(1.f, 1.f, 1.f));
//    
//    body->AddBox(boxDef);
//    
//    falling = body;
//  }
  
//  q3Body *falling2 = nullptr;
//  {
//    q3BodyDef bodyDef;
//    bodyDef.allowSleep = false;
//    bodyDef.position.Set(0.0f, 4.0f, 0.0f);
//    bodyDef.bodyType = eDynamicBody;
//    
//    q3Body *body = scene.CreateBody(bodyDef);
//    
//    q3BoxDef boxDef;
////    boxDef.SetDensity(0.5f);
//    
//    q3Transform localSpace;
//    q3Identity(localSpace);
//    boxDef.Set(localSpace, q3Vec3(1.f, 1.f, 1.f));
//    
//    body->AddBox(boxDef);
//    
//    falling2 = body;
//  }
  
//  // Ground body
//  q3Body *ground;
//  {
//    q3BodyDef bodyDef;
//    q3Body *body = scene.CreateBody(bodyDef);
//    
//    q3BoxDef boxDef;
//    boxDef.SetRestitution(0);
//
//    q3Transform localSpace;
//    q3Identity(localSpace);
//
//    boxDef.Set(localSpace, q3Vec3(50.0f, 1.0f, 50.0f));
//    
//    body->AddBox(boxDef);
//    
//    ground = body;
//  }
  
  Core::Entity phys_box(world);
  {
    Core::Transform transform;
    transform.set_position(math::vec3_init(0.5, 3, 0));
    
    phys_box.set_transform(transform);
    
    Core::Material_renderer renderer;
    renderer.set_material(material_fb_red);
    renderer.set_model(model_cube);
    
    Core::Rigidbody rb;
    rb.set_collider(Core::Box_collider(1,1,1));
    
    phys_box.set_rigidbody(rb);
    phys_box.set_renderer(renderer);
  }
  
  Core::Entity phys_box2(world);
  {
    Core::Transform transform;
    transform.set_position(math::vec3_init(0, 2, 0));
    
    phys_box2.set_transform(transform);
    
    Core::Rigidbody rb;
    rb.set_collider(Core::Box_collider(1,1,1));
    
    phys_box2.set_rigidbody(rb);
    
    Core::Material_renderer renderer;
    renderer.set_material(material_fb_green);
    renderer.set_model(model_cube);
    
    phys_box2.set_renderer(renderer);
  }
  
  
  // ** RUN WINDOW AND APP ** //
  
  while(context.is_open())
  {
    // Phys test
//    scene.Step();
    
    auto to_core_trans = [](const q3Transform &other)
    {
      Core::Transform trans;
      trans.set_position(math::vec3_init(other.position.x, other.position.y, other.position.z));
      
      const float arr_mat[] = {
        other.rotation.ex.x, other.rotation.ex.y, other.rotation.ex.z,
        other.rotation.ey.x, other.rotation.ey.y, other.rotation.ey.z,
        other.rotation.ez.x, other.rotation.ez.y, other.rotation.ez.z,
      };
      
      math::mat3 rot = math::mat3_init_with_array(arr_mat);
      
      trans.set_rotation(math::quat_init_with_mat3(rot));
      
      return trans;
    };
    
//    phys_box.set_transform(to_core_trans(falling->GetTransform()));
//    phys_box2.set_transform(to_core_trans(falling2->GetTransform()));
//    ground_entity.set_transform(to_core_trans(ground->GetTransform()));
    
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
      
      cam_entity.set_transform(transform);
      
      if(controller.is_button_down_on_frame(Core::Button::button_0))
      {
//        falling->ApplyForceAtWorldPoint(q3Vec3(0, 300, 0), falling->GetTransform().position);
      }
    }
  
    // ** UPDATE THE WORLD ** //
    
    world.think();
  }
  
  
  return 0;
}