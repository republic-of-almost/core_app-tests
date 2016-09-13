#ifndef MATERIAL_TEST_INCLUDED_204BB7D9_72F9_475E_93F3_7D5A6510F216
#define MATERIAL_TEST_INCLUDED_204BB7D9_72F9_475E_93F3_7D5A6510F216


#include <tests/test.hpp>
#include <core/entity/entity.hpp>


namespace Test {


class Material_test : public App
{
public:

  explicit          Material_test(Core::Context &ctx);
  
  void              on_update() override;
  
private:

  Core::Entity      m_cube_entity;
  Core::Entity      m_plane_cube;
};


} // ns


#endif // inc guard