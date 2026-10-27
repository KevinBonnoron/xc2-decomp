#include "dr/dr_shd_mdo_ext_tbl_obj.h"

#include "grlib/cglib_dec_shader.h"

namespace ml {

DrShdMdoExtTblObj::DrShdMdoExtTblObj() : unknown00(nullptr), unknown08(nullptr) {}

int DrShdMdoExtTblObj::getDecWorkSize(int declarationNum, const u8 *data) {
  const unknown001 *header = reinterpret_cast<const unknown001 *>(data);
  const unknown002 *entry = reinterpret_cast<const unknown002 *>(data + header->unknown08);
  int count = header->unknown0c;
  int tblSize = count * 0x38;
  int declSize = declarationNum * 4;
  const u8 *tables = data + header->unknown18;
  u32 size = 0;
  for (int i = 0; i < header->unknown0c; i++) {
    size += grlib::CGLibDecShader::calcTblSize(tables + entry[i].unknown00);
  }
  int padding = 0;
  if ((size & 3) != 0) {
    padding = 4 - (size & 3);
  }
  return tblSize + declSize + size + padding;
}

} // namespace ml
