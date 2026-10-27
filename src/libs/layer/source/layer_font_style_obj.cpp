#include "layer/layer_font_style_obj.h"

#include <string.h>

#include "layer/layer_acc_font_style.h"
#include "mm_mtl/vector.h"

namespace layer {

namespace {

struct unknown002 {
  u8 _00[0x08];
  u32 unknown08; // Inferred role: offset of the style data table; original member name unknown.
  u32 unknown0c; // Inferred role: style data count; original member name unknown.
};

static_assert(offsetof(unknown002, unknown08) == 0x08, "");
static_assert(offsetof(unknown002, unknown0c) == 0x0c, "");

} // namespace

void LayerFontStyleObj::setStyleData(const void *data) {
  const unknown002 *header = static_cast<const unknown002 *>(data);
  unknown20 = data;
  unknown28 = header->unknown0c;
  unknown30 = reinterpret_cast<const LyrFontStyleData *>(static_cast<const u8 *>(data) + header->unknown08);
}

const LyrFontStyleData *LayerFontStyleObj::getStyleData(u32 index) const {
  if (index < unknown28) {
    return unknown30 + index;
  }
  return unknown30;
}

s32 LayerFontStyleObj::getStyleIndex(const char *name) const {
  for (u32 i = 0; i < unknown28; i++) {
    if (strcmp(static_cast<const char *>(unknown20) + unknown30[i].unknown04, name) == 0) {
      return i;
    }
  }
  return -1;
}

const char *LayerFontStyleObj::getStyleName(u32 index) const { return static_cast<const char *>(unknown20) + unknown30[index].unknown04; }

const char *LayerFontStyleObj::getFontName(u32 index) const { return static_cast<const char *>(unknown20) + unknown30[index].unknown08; }

void LayerFontStyleObj::releaseColorInfo() {
  delete unknown48;
  unknown48 = nullptr;
}

void LayerFontStyleObj::releaseIconInfo() {
  delete unknown50;
  unknown50 = nullptr;
}

} // namespace layer
