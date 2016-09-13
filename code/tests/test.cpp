#include <tests/test.hpp>


namespace Test {


App::App(Core::Context &ctx)
: m_world(ctx)
{
}


App::~App()
{
}


void
App::on_update()
{
}


Core::World&
App::get_world()
{
  return m_world;
}


} // ns