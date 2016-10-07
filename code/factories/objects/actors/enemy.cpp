/*
  Warning
  --
  This file is auto-generated changes here may be overwritten.
*/
#include "enemy.hpp"
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
enemy_create(Core::World &world, Core::Transform *override_transform)
{
  // Create Entity
  Core::Entity entity(world);
  
  // Setup entity
  {
    entity.set_name("Enemy");
  
    // Set tags
    constexpr uint32_t tag_actor = 1;
    constexpr uint32_t tag_enemy = 2;
    entity.set_tags(tag_actor | tag_enemy);
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
  
  // Setup rigidbody
  {
    Core::Rigidbody rb;
    rb.set_mass(0);
    rb.set_is_dynamic();
    rb.set_is_trigger();
 
    entity.set_rigidbody(rb);
  }
  
  // Setup Renderer
  {
    Core::Material_renderer mat_renderer;
    
    entity.set_renderer(mat_renderer);
  }

  return entity;
} // enemy_create function

} // ns
