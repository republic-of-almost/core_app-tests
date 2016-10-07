/*
  Warning
  --
  This file is auto-generated changes here may be overwritten.
*/
#include "player.hpp"
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
player_create(Core::World &world, const Core::Transform *override_transform)
{
  // Create Entity
  Core::Entity entity(world);
  
  // Setup entity
  {
    entity.set_name("Player");
  
    // Set tags
    constexpr uint32_t tag_player = 1;
    constexpr uint32_t tag_actor = 2;
    entity.set_tags(tag_player | tag_actor);
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
} // player_create function

} // ns
