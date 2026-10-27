#include "grlib/cglib_dec_shd_ext_tbl.h"

#include "grlib/cglib_dec_shader.h"

namespace grlib {

CGLibDecShdExtTbl::CGLibDecShdExtTbl() {
  unknown08 = 0;
  unknown10 = nullptr;
  unknown00 = nullptr;
}

void CGLibDecShdExtTbl::setTbl(u8 *table) { unknown10 = table; }

void CGLibDecShdExtTbl::setObj(CGLibDecShader *shader) {
  unknown00 = shader;
  int count = shader->unknown00->unknown08;
  for (int i = 0; i < count; i++) {
    unknown10[i] = 0;
  }
  unknown08 = 0;
}

} // namespace grlib
