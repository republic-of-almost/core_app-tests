/*
  Warning
  --
  This file is auto-generated changes here may be overwritten.
*/
#ifndef ENEMY_INCLUDED_20D6F317_B8B5_4FF9_B1F1_EC8962DEB81F
#define ENEMY_INCLUDED_20D6F317_B8B5_4FF9_B1F1_EC8962DEB81F


#include <core/common/core_fwd.hpp>
#include <stdint.h>


/*
  Factory Entity Method
  --
  Creates a Enemy entity.
*/


namespace Factory_entity {


/*!
  Factory Method
  --
  Creates the Enemy entity.
  Takes in an optional tranform, otherwise it will be created with the
  the transform specified in the function. 
*/
Core::Entity
enemy_create(Core::World &world, const Core::Transform *override_transform = nullptr);


// Helper functions


/*!
  Returns the name the Enemy entity is created with.
*/
constexpr const char* enemy_default_name() { return "Enemy"; }


/*!
  Returns the tags the Enemy entity is created with.
*/
constexpr uint32_t enemy_default_tags() { return 3; }


} // ns


#endif // inc guard
