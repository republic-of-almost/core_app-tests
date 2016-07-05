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
#include <core/renderer/material_renderer.hpp>
#include <core/renderer/renderer.hpp>



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
  cam_entity.set_name("Camera");
  
  Core::Camera main_camera(world);
  main_camera.set_attached_entity(cam_entity);
  
  Core::Entity ground_entity(world);
  {
    ground_entity.set_name("Ground Entity");
    
    Core::Material_renderer ground_renderer;
    ground_renderer.set_material(material_fb_or);
    ground_renderer.set_model(model_plane);
    
    ground_entity.set_renderer(ground_renderer);
  }
  
  
  
  
  while(context.is_open())
  {
    world.think();
  }
  
  
  return 0;
}