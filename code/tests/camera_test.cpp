#include <tests/camera_test.hpp>
#include <core/entity/entity_ref.hpp>
#include <core/common/directory.hpp>
#include <core/model/model.hpp>
#include <core/renderer/renderer.hpp>
#include <core/renderer/material_renderer.hpp>
#include <core/resources/shader.hpp>
#include <core/resources/texture.hpp>
#include <core/transform/transform.hpp>
#include <core/transform/transform_utils.hpp>
#include <core/context/context.hpp>


namespace {

/*
  General camera settings.
*/
constexpr float camera_distance = 10.f;

} // anon ns


namespace Test {


Camera_test::Camera_test(Core::Context &ctx)
: App(ctx)
, m_entities{Core::Entity(get_world()), Core::Entity(get_world()), Core::Entity(get_world()), Core::Entity(get_world())}
, m_camera_entity(get_world())
, m_camera(m_camera_entity, ctx.get_width(), ctx.get_height())
{
}


void
Camera_test::on_think()
{

  /*
    Allow the world to render.
  */
  get_world().think();
}


} // ns