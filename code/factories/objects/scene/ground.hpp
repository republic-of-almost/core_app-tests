/*
  Warning
  --
  This file is auto-generated changes here may be overwritten.
*/
#ifndef GROUND_INCLUDED_4A356545_2B8A_493E_8ED4_04AEAA827B98
#define GROUND_INCLUDED_4A356545_2B8A_493E_8ED4_04AEAA827B98


#include <core/common/core_fwd.hpp>
#include <stdint.h>


/*
  Factory Entity Method
  --
  Creates a Ground entity.
*/


namespace Factory_entity {


/*!
  Factory Method
  --
  Creates the Ground entity.
  Takes in an optional tranform, otherwise it will be created with the
  the transform specified in the function. 
*/
Core::Entity
ground_create(Core::World &world, const Core::Transform *override_transform = nullptr);


// Helper functions


/*!
  Returns the name the Ground entity is created with.
*/
constexpr const char* ground_default_name() { return "Ground"; }


/*!
  Returns the tags the Ground entity is created with.
*/
constexpr uint32_t ground_default_tags() { return 24; }


} // ns


#endif // inc guard
