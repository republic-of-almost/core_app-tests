#ifndef TEST_INCLUDED_16850504_5A5A_4169_B8FF_902DCC07D756
#define TEST_INCLUDED_16850504_5A5A_4169_B8FF_902DCC07D756


#include <core/world/world.hpp>
#include <core/common/core_fwd.hpp>


namespace Test {


class App
{
public:
  
  explicit          App(Core::Context &ctx);
  virtual           ~App();

  virtual void      on_think();

protected:

  Core::World&      get_world();
  
private:

  Core::World       m_world;

};


} // ns


#endif // inc guard