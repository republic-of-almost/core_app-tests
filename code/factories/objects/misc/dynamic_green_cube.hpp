/*
  Warning
  --
  This file is auto-generated changes here may be overwritten.
*/
#ifndef DYNAMIC_GREEN_CUBE_INCLUDED_57CBA9A9_B842_4C32_90F2_C63EE1DCE3F5
#define DYNAMIC_GREEN_CUBE_INCLUDED_57CBA9A9_B842_4C32_90F2_C63EE1DCE3F5


#include <core/common/core_fwd.hpp>
#include <stdint.h>


/*
  Factory Entity Method
  --
  Creates a Dynamic_green_cube entity.
*/


namespace Factory_entity {


/*!
  Factory Method
  --
  Creates the Dynamic_green_cube entity.
  Takes in an optional tranform, otherwise it will be created with the
  the transform specified in the function. 
*/
Core::Entity
dynamic_green_cube_create(Core::World &world, const Core::Transform *override_transform = nullptr);


// Helper functions


/*!
  Returns the name the Dynamic_green_cube entity is created with.
*/
constexpr const char* dynamic_green_cube_default_name() { return "Dynamic_green_cube"; }


/*!
  Returns the tags the Dynamic_green_cube entity is created with.
*/
constexpr uint32_t dynamic_green_cube_default_tags() { return 4; }


} // ns


#endif // inc guard
