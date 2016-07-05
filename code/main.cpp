#include <core/world/world.hpp>
#include <core/context/context.hpp>
#include <core/entity/entity.hpp>
#include <core/entity/entity_ref.hpp>
#include <core/camera/camera.hpp>
#include <core/resources/shader.hpp>
#include <core/resources/texture.hpp>
#include <core/resources/material.hpp>
#include <core/model/model.hpp>
#include <core/common/directory.hpp>
#include <core/transform/transform.hpp>
#include <core/renderer/material_renderer.hpp>
#include <core/renderer/renderer.hpp>
#include <core/input/controller.hpp>



int
main()
{
  Core::Context context(800, 480, false, "FPS Test");
  Core::World world(context);
  
  // ** RESOURCES ** //
  
  Core::Shader shader_fullbright(Core::Directory::resource_path("assets/shaders/basic_fullbright.ogl"));
  Core::Texture texture_orange(Core::Directory::resource_path("assets/textures/dev_grid_orange_512.png"));
  Core::Material material_fb_or("fullbright-orange");
  material_fb_or.set_shader(shader_fullbright);
  material_fb_or.set_map_01(texture_orange);
  
  Core::Model model_plane(Core::Directory::resource_path("assets/models/unit_plane.obj"));
  
  // ** ENTITIES ** //

  Core::Entity cam_entity(world);
  Core::Camera main_camera(world);
  {
    cam_entity.set_name("Camera");
    
    Core::Transform transform;
    transform.set_position(math::vec3_init(0, 1, 0));
    
    cam_entity.set_transform(transform);
    
    main_camera.set_attached_entity(cam_entity);
    main_camera.set_priority(1);
    
    main_camera.set_width(800);
    main_camera.set_height(480);
  }
  
  Core::Entity ground_entity(world);
  {
    ground_entity.set_name("Ground Entity");
    
    Core::Transform transform;
    transform.set_scale(math::vec3_init(10, 1, 10));
    
    ground_entity.set_transform(transform);
    
    Core::Material_renderer ground_renderer;
    ground_renderer.set_material(material_fb_or);
    ground_renderer.set_model(model_plane);
    
    ground_entity.set_renderer(ground_renderer);
  }
  
  
  while(context.is_open())
  {
    // FPS Input
    {
      Core::Input::Controller controller(context, 0);
      
      // Move Axis
      {
        Core::Transform trans = cam_entity.get_transform();
        
        const math::vec3 fwd = math::vec3_scale(trans.get_forward(), controller.get_axis(0).y * world.get_delta_time());
        const math::vec3 left = math::vec3_scale(trans.get_left(), controller.get_axis(0).x * world.get_delta_time());
        const math::vec3 curr_pos = trans.get_position();
        const math::vec3 new_pos = math::vec3_add(math::vec3_add(curr_pos, fwd), left);
        
        trans.set_position(new_pos);
        
        cam_entity.set_transform(trans);
      }
    }
  
    world.think();
  }
  
  
  return 0;
}