#include <tests/material_test.hpp>


namespace Test {


Material_test::Material_test(Core::Context &ctx)
: App(ctx)
, m_cube_entity(get_world())
, m_plane_cube(get_world())
{
  m_cube_entity.set_name("Material Test Cube");
  m_plane_cube.set_name("Material Test Plane");
}


void
Material_test::on_update()
{
}



} // ns