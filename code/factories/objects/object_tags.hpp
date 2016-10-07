/*
  Warning
  --
  This file is auto-generated changes here may be overwritten.
*/
#ifndef OBJECT_TAGS_INCLUDED_39F1E36B_3329_4400_BF32_A084795E2030
#define OBJECT_TAGS_INCLUDED_39F1E36B_3329_4400_BF32_A084795E2030


/*
  These object tags are used in the entity factory.
*/


#include <stdint.h>


namespace Object_tag {


enum ENUM {

  player_tag = 1,
  actor_tag = 2,
  dynamic_tag = 4,
  static_tag = 8,
  scene_tag = 16,

}; // enum


constexpr uint32_t number_of_tags() { return 5; }


} // ns


#endif // inc guard
