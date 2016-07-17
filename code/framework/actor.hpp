#ifndef ACTOR_INCLUDED_38FEEE74_80BC_4273_9115_CB0CDFFE3387
#define ACTOR_INCLUDED_38FEEE74_80BC_4273_9115_CB0CDFFE3387


#include <core/common/core_fwd.hpp>
#include <core/entity/entity.hpp>
#include <math/vec3/vec_fwd.hpp>


namespace Core {
namespace Lib {


class Actor final
{
public:

  explicit          Actor(const Core::World &world);
  
  Core::Transform   get_head_transform() const;
  
  void              apply_forces(const float dt);

  void              move_fwd(const float fwd);
  void              move_left(const float left);
  void              jump(const float pwr);

  Core::Entity_ref  get_ref() const;

private:

  Core::Entity      m_entity;
  math::vec3        m_pending_force;
  
}; // class


} // ns
} // ns


#endif // inc guard
