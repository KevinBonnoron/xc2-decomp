#include "layer/layer_font_tag.h"

namespace layer {

void LayerFontTag::getWorkSize(LayerTagWork &work, const u8 *string) {
  unknown28 = false;
  unknown30 = &work;
  calcParseString(string);
  u32 length = 0;
  while (length < 10000 && string[length] != 0) {
    length++;
  }
  work.unknown10 = length;
  work.unknown14 = length;
}

void LayerFontTag::getWorkSize(LayerTagWork &work, const wchar_t *string) {
  unknown28 = false;
  unknown30 = &work;
  calcParseString(string);
  u32 length = 0;
  while (length < 10000 && string[length] != 0) {
    length++;
  }
  work.unknown10 = length;
  work.unknown14 = length << 2;
}

void LayerFontTag::createWork(const u8 *string) {
  unknown28 = true;
  calcParseString(string);
}

void LayerFontTag::createWork(const wchar_t *string) {
  unknown28 = true;
  calcParseString(string);
}

void LayerFontTag::beginParseString() {
  unknown494[1] = 0;
  unknown49c = 0;
  unknown490 = 0;
  unknown494[0] = 0;
}

void LayerFontTag::calcTagColorEnd() { unknown68 = unknown78; }

void LayerFontTag::parseNotTag(const u8 *string, u32 &index) {
  u32 position = index;
  s8 code = string[position];
  if (unknown28) {
    if (code == '\n') {
      if (string[position + 1] == '\r') {
        index = position + 2;
      } else {
        index = position + 1;
      }
      createLineBreak();
    } else {
      if (code == '\\') {
        position++;
        index = position;
      }
      u16 result;
      u32 length;
      changeUtf8ToUtf16(result, string + position, length);
      index += length;
      createFontCode(result);
    }
  } else if (code == '\n') {
    if (string[position + 1] == '\r') {
      index = position + 2;
    } else {
      index = position + 1;
    }
    unknown49c++;
  } else {
    if (code < 0) {
      if (static_cast<u32>(code + 0x3e) < 0x1e) {
        position += 2;
      } else if ((code & 0xf0) == 0xe0) {
        position += 3;
      } else if ((code & 0xf8) == 0xf0) {
        position += 4;
      } else {
        position += 1;
      }
    } else {
      position += 1;
    }
    index = position;
    unknown30->unknown00++;
  }
}

void LayerFontTag::calcTagWide() { unknown29 = true; }

} // namespace layer
