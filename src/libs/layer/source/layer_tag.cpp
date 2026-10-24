#include "layer/layer_tag.h"

namespace layer {

LayerStrInfo::LayerStrInfo() {}

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
