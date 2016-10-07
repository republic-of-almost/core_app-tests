/*
  Warning
  --
  This file is auto-generated changes here may be overwritten.
*/
#ifndef PLAYER_INCLUDED_BE17F877_6CED_4285_A7E2_2867DF84AAA7
#define PLAYER_INCLUDED_BE17F877_6CED_4285_A7E2_2867DF84AAA7


#include <core/common/core_fwd.hpp>
#include <stdint.h>


/*
  Factory Entity Method
  --
  Creates a Player entity.
*/


namespace Factory_entity {


/*!
  Factory Method
  --
  Creates the Player entity.
  Takes in an optional tranform, otherwise it will be created with the
  the transform specified in the function. 
*/
Core::Entity
player_create(Core::World &world, const Core::Transform *override_transform = nullptr);


// Helper functions


/*!
  Returns the name the Player entity is created with.
*/
constexpr const char* player_default_name() { return "Player"; }


/*!
  Returns the tags the Player entity is created with.
*/
constexpr uint32_t player_default_tags() { return 3; }


} // ns


#endif // inc guard
