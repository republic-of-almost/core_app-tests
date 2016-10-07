/*
  Warning
  --
  This file is auto-generated changes here may be overwritten.
*/
#ifndef DYNAMIC_RED_CUBE_INCLUDED_B4C103AB_BE92_4BD8_9BDE_5CA030171123
#define DYNAMIC_RED_CUBE_INCLUDED_B4C103AB_BE92_4BD8_9BDE_5CA030171123


#include <core/common/core_fwd.hpp>
#include <stdint.h>


/*
  Factory Entity Method
  --
  Creates a Dynamic_red_cube entity.
*/


namespace Factory_entity {


/*!
  Factory Method
  --
  Creates the Dynamic_red_cube entity.
  Takes in an optional tranform, otherwise it will be created with the
  the transform specified in the function. 
*/
Core::Entity
dynamic_red_cube_create(Core::World &world, const Core::Transform *override_transform = nullptr);


// Helper functions


/*!
  Returns the name the Dynamic_red_cube entity is created with.
*/
constexpr const char* dynamic_red_cube_default_name() { return "Dynamic_red_cube"; }


/*!
  Returns the tags the Dynamic_red_cube entity is created with.
*/
constexpr uint32_t dynamic_red_cube_default_tags() { return 4; }


} // ns


#endif // inc guard
