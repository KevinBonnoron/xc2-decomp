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

void CGLibDecShdExtTbl::setDeclarationIdx(u32 offset, u32 index) {
  const unknown001 *header = unknown00->unknown00;
  if (offset == 0xffffffff || offset >= header->unknown08) {
    return;
  }
  const unknown002 *declarations = reinterpret_cast<const unknown002 *>(reinterpret_cast<const u8 *>(header) + header->unknown0c);
  unknown08 -= unknown10[offset] * declarations[offset].unknown04;
  if (index < 2) {
    unknown10[offset] = 0;
    return;
  }
  if (index > declarations[offset].unknown00) {
    unknown10[offset] = declarations[offset].unknown00 - 1;
    unknown08 += unknown10[offset] * declarations[offset].unknown04;
  } else {
    unknown10[offset] = index - 1;
    unknown08 += unknown10[offset] * declarations[offset].unknown04;
  }
}

} // namespace grlib
