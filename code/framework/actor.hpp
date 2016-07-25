#ifndef ACTOR_INCLUDED_38FEEE74_80BC_4273_9115_CB0CDFFE3387
#define ACTOR_INCLUDED_38FEEE74_80BC_4273_9115_CB0CDFFE3387


#include <core/common/core_fwd.hpp>
#include <core/entity/entity.hpp>
#include <math/vec/vec_fwd.hpp>


namespace Core {
namespace Lib {


class Actor final
{
public:

  explicit          Actor(Core::World &world);
  
  Core::Transform   get_head_transform() const;
  
  void              apply_forces(const float dt);

  void              move_fwd(const float fwd);
  void              move_left(const float left);
  void              rotate(const float rt);

  Core::Entity_ref  get_head_ref() const;
  Core::Entity_ref  get_body_ref() const;

private:

  Core::Entity      m_head_entity;
  Core::Entity      m_body_entity;
  math::vec3        m_pending_force;
  Core::World       &m_world;
  
  float             m_accum_body_rot = 0;
  float             m_pending_body_rot = 0;
  
}; // class


} // ns
} // ns


#endif // inc guard
