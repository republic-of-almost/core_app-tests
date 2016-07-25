#include <framework/actor.hpp>
#include <core/transform/transform.hpp>
#include <core/entity/entity_ref.hpp>
#include <core/physics/ray.hpp>
#include <core/world/world.hpp>
#include <math/vec/vec3.hpp>


namespace Core {
namespace Lib {


Actor::Actor(Core::World &world)
: m_head_entity(world)
, m_body_entity(world)
, m_pending_force(math::vec3_zero())
, m_world(world)
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
  const math::vec3 pos = m_head_entity.get_transform().get_position();
  Core::Ray ray(m_world, pos, math::vec3_init(0, -1, 0));

  if(ray.has_hit())
  {
    // Get position and move up, this is where our head is.
    const auto hit_pos = ray.get_hit_position();
    const auto head_offset = math::vec3_init(0, 2, 0);
    const auto head_height = math::vec3_add(hit_pos, head_offset);
    
    Core::Transform trans = m_head_entity.get_transform();
    trans.set_position(head_height);
    m_head_entity.set_transform(trans);
  }

  // Calculate forces
  {
    Core::Transform head_transform = m_head_entity.get_transform();

    const math::vec3 scaled_force = math::vec3_scale(m_pending_force, dt);
    const math::vec3 rotated_force = math::quat_rotate_point(head_transform.get_rotation(), scaled_force);
    const math::vec3 final_position = math::vec3_add(head_transform.get_position(), rotated_force);
    
    head_transform.set_position(final_position);
    
    m_pending_force = math::vec3_zero();
    
    m_head_entity.set_transform(head_transform);
  }
  
  // Rotation
  {
    m_accum_body_rot += (m_pending_body_rot * dt);
    m_pending_body_rot = 0;
    const math::quat rot = math::quat_init_with_axis_angle(0, 1, 0, m_accum_body_rot);
    
    Core::Transform head_transform = m_head_entity.get_transform();
    head_transform.set_rotation(rot);
    m_head_entity.set_transform(head_transform);
  }
}


void
Actor::move_fwd(const float fwd)
{
  const math::vec3 force = math::vec3_scale(Core::Transform::get_world_forward(), fwd);
  m_pending_force = math::vec3_add(m_pending_force, force);
}


void
Actor::move_left(const float left)
{
  const math::vec3 force = math::vec3_scale(Core::Transform::get_world_left(), left);
  m_pending_force = math::vec3_add(m_pending_force, force);
}


void
Actor::rotate(const float rt)
{
  m_pending_body_rot += rt;
}


Core::Entity_ref
Actor::get_head_ref() const
{
  return m_head_entity;
}


} // ns
} // ns
