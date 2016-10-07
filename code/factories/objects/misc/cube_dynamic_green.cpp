/*
  Warning
  --
  This file is auto-generated changes here may be overwritten.
*/
#include "cube_dynamic_green.hpp"
#include <core/world/world.hpp>
#include <core/entity/entity.hpp>
#include <core/transform/transform.hpp>
#include <core/renderer/renderer.hpp>
#include <core/physics/rigidbody.hpp>
#include <core/renderer/renderer.hpp>
#include <core/renderer/material_renderer.hpp>
#include <utilities/logging.hpp>
#include <assert.h>


namespace Factory_entity {


Core::Entity
cube_dynamic_green_create(Core::World &world, Core::Transform *override_transform)
{
  // Create Entity
  Core::Entity entity(world);
  
  // Setup entity
  {
    entity.set_name("Cube_dynamic_green");
  
    // Set tags
    constexpr uint32_t tag_dynamic = 4;
    entity.set_tags(tag_dynamic);
  }  
  
  // Transform
  {
    if(!override_transform)
    {
      entity.set_transform(
        Core::Transform(
          math::vec3_init(0, 0, 0),
          math::vec3_init(1, 1, 1),
          math::quat_init() // todo
        )
      );
    }
    else
    {
      entity.set_transform(*override_transform);
    }
  }
  
  // Setup Renderer
  {
//    Core::Material_renderer mat_renderer;
//    
//    entity.set_renderer(mat_renderer);
  }

  return entity;
} // cube_dynamic_green_create function

} // ns
