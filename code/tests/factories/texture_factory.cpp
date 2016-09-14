#include <tests/factories/texture_factory.hpp>
#include <core/resources/texture.hpp>
#include <core/common/directory.hpp>


namespace Test {
namespace Texture_factory {


Core::Texture
get_dev_green()
{
  static const Core::Texture texture(Core::Directory::volatile_resource_path("/assets/textures/dev_grid_green_512.png"));
  assert(texture);
  
  return texture;
}


Core::Texture
get_dev_red()
{
  static const Core::Texture texture(Core::Directory::volatile_resource_path("/assets/textures/dev_grid_red_512.png"));
  assert(texture);
  
  return texture;
}


Core::Texture
get_dev_orange()
{
  static const Core::Texture texture(Core::Directory::volatile_resource_path("/assets/textures/dev_grid_orange_512.png"));
  assert(texture);
  
  return texture;
}


} // ns
} // ns