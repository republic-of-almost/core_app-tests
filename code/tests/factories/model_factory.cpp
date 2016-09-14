#include <tests/factories/model_factory.hpp>
#include <core/model/model.hpp>
#include <core/common/directory.hpp>


namespace Test {
namespace Model_factory {


Core::Model
get_unit_cube()
{
  static const Core::Model model(Core::Directory::volatile_resource_path("/assets/models/unit_cube.obj"));
  assert(model);
  
  return model;
}


Core::Model
get_unit_plane()
{
  static const Core::Model model(Core::Directory::volatile_resource_path("/assets/models/unit_plane.obj"));
  assert(model);
  
  return model;
}


} // ns
} // ns