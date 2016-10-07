/*
  Warning
  --
  This file is auto-generated changes here may be overwritten.
*/
#ifndef CUBE_DYNAMIC_RED_INCLUDED_48416CAA_A645_4E3F_8BAD_B13144699C17
#define CUBE_DYNAMIC_RED_INCLUDED_48416CAA_A645_4E3F_8BAD_B13144699C17


#include <core/common/core_fwd.hpp>
#include <stdint.h>


/*
  Factory Entity Method
  --
  Creates a Cube_dynamic_red entity.
*/


namespace Factory_entity {


/*!
  Factory Method
  --
  Creates the Cube_dynamic_red entity.
  Takes in an optional tranform, otherwise it will be created with the
  the transform specified in the function. 
*/
Core::Entity
cube_dynamic_red_create(Core::World &world, const Core::Transform *override_transform = nullptr);


// Helper functions


/*!
  Returns the name the Cube_dynamic_red entity is created with.
*/
constexpr const char* cube_dynamic_red_default_name() { return "Cube_dynamic_red"; }


/*!
  Returns the tags the Cube_dynamic_red entity is created with.
*/
constexpr uint32_t cube_dynamic_red_default_tags() { return 4; }


} // ns


#endif // inc guard
