#include <framework/actor.hpp>
#include <core/transform/transform.hpp>
#include <core/entity/entity_ref.hpp>
#include <core/world/world.hpp>
#include <math/vec/vec3.hpp>


namespace Core {
namespace Lib {


Actor::Actor(Core::World &world)
: m_entity(world)
, m_pending_force(math::vec3_zero())
{
}


Core::Transform
Actor::get_head_transform() const
{
  return Core::Transform();
}


void
Actor::apply_forces(const float dt)
{
}


void
Actor::move_fwd(const float fwd)
{
}


void
Actor::move_left(const float left)
{
}


void
Actor::jump(const float jmp)
{
}


Core::Entity_ref
Actor::get_ref() const
{
  return m_entity;
}


} // ns
} // ns
