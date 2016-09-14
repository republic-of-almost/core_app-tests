#include <tests/factories/shader_factory.hpp>
#include <core/resources/shader.hpp>
#include <core/common/directory.hpp>


namespace Test {
namespace Shader_factory {


Core::Shader
get_fullbright()
{
  static const Core::Shader shader(Core::Directory::volatile_resource_path("/assets/shaders/basic_fullbright.ogl"));
  assert(shader);
  
  return shader;
}


} // ns
} // ns