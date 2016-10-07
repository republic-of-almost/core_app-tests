/*
  Warning
  --
  This file is auto-generated changes here may be overwritten.
*/
#include "object_factory.hpp"
#include <core/entity/entity.hpp>
#include "actors/player.hpp"
#include "misc/dynamic_green_cube.hpp"
#include "misc/dynamic_red_cube.hpp"
#include "scene/ground.hpp"
#include <assert.h>


namespace Factory_entity {


Core::Entity
create(const uint32_t id, Core::World &world, Core::Transform *transform)
{
  switch(id)
  {
    case(0):
      assert(false); // no entity, perhaps we can make a dummy entity in future.
      return Core::Entity();    
    case(1):
      return player_create(world, transform);
    case(2):
      return dynamic_green_cube_create(world, transform);
    case(3):
      return dynamic_red_cube_create(world, transform);
    case(4):
      return ground_create(world, transform);
    default:
      assert(false); // no entity.
      return Core::Entity();
  }

  // Unreachable
}



} // ns
