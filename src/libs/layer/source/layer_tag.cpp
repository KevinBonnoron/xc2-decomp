#include "layer/layer_tag.h"

#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"

namespace layer {

LayerStrInfo::LayerStrInfo() {}

void LayerStrInfo::setCol4(const char *name, const mm::Col4 &color) {
  unknown10 = name;
  unknown00.m_col4[0] = color.r;
  unknown00.m_col4[1] = color.g;
  unknown00.m_col4[2] = color.b;
  unknown00.m_col4[3] = color.a;
}

void LayerStrInfo::setCol3(const char *name, const mm::Col3 &color) {
  unknown10 = name;
  unknown00.m_col3[0] = color.r;
  unknown00.m_col3[1] = color.g;
  unknown00.m_col3[2] = color.b;
}

void LayerStrInfo::setFloat(const char *name, f32 value) {
  unknown10 = name;
  unknown00.m_float = value;
}

void LayerStrInfo::setU32(const char *name, u32 value) {
  unknown10 = name;
  unknown00.m_u32 = value;
}

void LayerStrInfo::setS32(const char *name, s32 value) {
  unknown10 = name;
  unknown00.m_s32 = value;
}

void LayerTag::calcParseString(const u8 *string) {
  beginParseString();
  calcUTF8ParseString(string);
  endParseString();
}

void LayerTag::calcParseString(const wchar_t *string) {
  beginParseString();
  calcUTF16ParseString(string);
  endParseString();
}

u32 LayerTag::calcStringLength(const u8 *string) {
  u32 index = 0;
  u32 length = 0;
  while (string[index] != 0) {
    u8 code = string[index];
    if (static_cast<s8>(code) >= 0) {
      index += 1;
    } else if (code >= 0xc2 && code <= 0xdf) {
      index += 2;
    } else if ((code & 0xf0) == 0xe0) {
      index += 3;
    } else if ((code & 0xf8) == 0xf0) {
      index += 4;
    } else {
      index += 1;
    }
    length++;
  }

  return length;
}

u32 LayerTag::calcStringLength(const wchar_t *string) {
  u32 length = 0;
  u32 index = 0;
  while (string[index] != 0) {
    index += (string[index] & 0xfc00) == 0xd800 ? 2 : 1;
    length++;
  }

  return length;
}

LayerTagStr::LayerTagStr() : m_result(nullptr), unknown10(0), unknown14(0) {}

LayerTagStr::~LayerTagStr() {}

void LayerTagStr::setStockTbl(char *table, int size) {
  m_result = table;
  unknown10 = size;
}

void LayerTagStr::stockString(const char *string) {
  for (u32 i = 0; string[i] != 0; i++) {
    m_result[unknown14++] = string[i];
  }
}

void LayerTagStr::beginParseString() { unknown14 = 0; }

void LayerTagStr::endParseString() { m_result[unknown14] = 0; }

void LayerTagStr::parseNotTag(const u8 *string, u32 &index) {
  m_result[unknown14++] = string[index];
  index++;
}

void LayerTagStr::callTagNoUse(const u8 *tag) {
  for (u32 i = 0; tag[i] != 0; i++) {
    m_result[unknown14++] = tag[i];
  }
}

} // namespace layer
