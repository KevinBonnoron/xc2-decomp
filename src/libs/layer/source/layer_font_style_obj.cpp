#include "layer/layer_font_style_obj.h"

#include <string.h>

#include "layer/layer_acc_font_style.h"
#include "layer/layer_font_manager.h"
#include "layer/layer_tag.h"
#include "mm_mtl/vector.h"

namespace layer {

namespace {

struct unknown005 {
  u8 _00[0x08];
  u32 unknown08; // Inferred role: offset of the style data table; original member name unknown.
  u32 unknown0c; // Inferred role: style data count; original member name unknown.
};

static_assert(offsetof(unknown005, unknown08) == 0x08, "");
static_assert(offsetof(unknown005, unknown0c) == 0x0c, "");

} // namespace

const f32 LayerFontStyleObj::RUBY_SCALE = 0.4f;

void LayerFontStyleObj::setStyleData(const void *data) {
  const unknown005 *header = static_cast<const unknown005 *>(data);
  unknown20 = data;
  m_styleDataMax = header->unknown0c;
  m_lyrFontStyleData = reinterpret_cast<const LyrFontStyleData *>(static_cast<const u8 *>(data) + header->unknown08);
}

const LyrFontStyleData *LayerFontStyleObj::getStyleData(u32 index) const {
  if (index < m_styleDataMax) {
    return m_lyrFontStyleData + index;
  }
  return m_lyrFontStyleData;
}

s32 LayerFontStyleObj::getStyleIndex(const char *name) const {
  for (u32 i = 0; i < m_styleDataMax; i++) {
    if (strcmp(static_cast<const char *>(unknown20) + m_lyrFontStyleData[i].unknown04, name) == 0) {
      return i;
    }
  }
  return -1;
}

const char *LayerFontStyleObj::getStyleName(u32 index) const { return static_cast<const char *>(unknown20) + m_lyrFontStyleData[index].unknown04; }

const char *LayerFontStyleObj::getFontName(u32 index) const { return static_cast<const char *>(unknown20) + m_lyrFontStyleData[index].unknown08; }

LayerFontStyleObj::LayerFontStyleObj(LayerFontManager *manager) {
  m_layerFontManager = manager;
  unknown18 = LAYER_OBJ_TYPE_FONT_STYLE;
  m_rubyScale = RUBY_SCALE;
  m_colorInfo = nullptr;
  m_iconInfo = nullptr;
}

LayerFontStyleObj::~LayerFontStyleObj() {
  releaseColorInfo();
  releaseIconInfo();
}

void LayerFontStyleObj::releaseColorInfo() {
  if (m_colorInfo != nullptr) {
    delete m_colorInfo;
    m_colorInfo = nullptr;
  }
}

void LayerFontStyleObj::releaseIconInfo() {
  if (m_iconInfo != nullptr) {
    delete m_iconInfo;
    m_iconInfo = nullptr;
  }
}

void LayerFontStyleObj::release() {
  unknown1c = 0x22;
  releaseColorInfo();
  releaseIconInfo();
  m_layerFontManager->releaseStyleObj(this);
}

} // namespace layer
