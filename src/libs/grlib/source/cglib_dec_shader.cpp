#include "grlib/cglib_dec_shader.h"

#include <string.h>

namespace grlib {

CGLibDecShader::CGLibDecShader() : unknown38(nullptr), unknown40(0), unknown48(nullptr), unknown50(nullptr), unknown58(0), unknown60(nullptr) {}

u32 CGLibDecShader::calcWorkSize(const void *data, bool isCopy) {
  const unknown001 *header = static_cast<const unknown001 *>(data);
  if (header->unknown00 != 0x54434c53) {
    return 0;
  }
  if (header->unknown04 >> 1 != 0x801) {
    return 0;
  }
  u32 size = header->unknown10 * 0xd8;
  if (isCopy) {
    u32 padding = 0;
    if (header->unknown08 % 4 != 0) {
      padding = 4 - header->unknown08 % 4;
    }
    size = header->unknown08 + size + padding;
  }
  return size;
}

u32 CGLibDecShader::calcTblSize(const void *data) {
  const unknown001 *header = static_cast<const unknown001 *>(data);
  if (header->unknown00 != 0x54434c53) {
    return 0;
  }
  if (header->unknown04 >> 1 == 0x801) {
    return header->unknown08;
  }
  return 0;
}

void CGLibDecShader::changeShaderSetMem(const void *data) { unknown00 = static_cast<const unknown001 *>(data); }

void CGLibDecShader::getDeclarationInfo(const char *&name, int &num, int index) const {
  const unknown002 *declarations = reinterpret_cast<const unknown002 *>(reinterpret_cast<const u8 *>(unknown00) + unknown00->unknown0c);
  name = reinterpret_cast<const char *>(unknown00) + declarations[index].unknown08;
  num = declarations[index].unknown00;
}

u32 CGLibDecShader::getDeclarationMax() const { return unknown00->unknown08; }

u32 CGLibDecShader::getShaderMode() { return unknown00->unknown18; }

u32 CGLibDecShader::getDeclarationOfs(const char *name) const {
  const unknown002 *declarations = reinterpret_cast<const unknown002 *>(reinterpret_cast<const u8 *>(unknown00) + unknown00->unknown0c);
  int count = unknown00->unknown08;
  for (int i = 0; i < count; i++, declarations++) {
    if (strcmp(name, reinterpret_cast<const char *>(unknown00) + declarations->unknown08) == 0) {
      return i;
    }
  }
  return -1;
}

} // namespace grlib
