/*
  Warning
  --
  This file is auto-generated changes here may be overwritten.
*/
#ifndef OBJECT_FACTORY_INCLUDED_8AD12DEE_4566_4188_BB5E_19B7ADB2DF8B
#define OBJECT_FACTORY_INCLUDED_8AD12DEE_4566_4188_BB5E_19B7ADB2DF8B


#include <core/common/core_fwd.hpp>
#include <stdint.h>


namespace Factory_entity {


/*!
  Generic Entity Factory method.
*/
Core::Entity
create(const uint32_t id, Core::World &world, Core::Transform *transform = nullptr);


constexpr bool
str_compare(char const *left, char const *right)
{
  return (*left && *right) ? (*left == *right && str_compare(left + 1, right + 1)) : (!*left && !*right);
}


constexpr uint32_t
get_id(const char *name)
{
  return

  str_compare(name, "Player") ? 1 : 
  str_compare(name, "Dynamic_green_cube") ? 2 : 
  str_compare(name, "Dynamic_red_cube") ? 3 : 
  str_compare(name, "Ground") ? 4 : 

  0;
}


} // ns


#endif // inc guard
