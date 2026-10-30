#include "layer/layer_font_icon_obj.h"

#include "layer/layer_manager.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_texture_obj.h"

namespace layer {

LayerFontIconObj::LayerFontIconObj(LayerFontManager *manager, const void *data, LAYER_TYPE type) {
  unknown20 = manager;
  unknown28 = 0;
  unknown18 = type;
  unknown30 = static_cast<const unknown004 *>(data);
  unknown40 = nullptr;
  unknown50 = 0.0f;
  unknown48 = 0;
  unknown4c = 0.0f;
  createIconRes();
}

LayerFontIconObj::~LayerFontIconObj() {
  if (unknown40 != nullptr) {
    unknown40->release();
    unknown40 = nullptr;
  }
}

void LayerFontIconObj::createIconRes() {
  const unknown004 *header = unknown30;
  const u8 *data = reinterpret_cast<const u8 *>(header);
  const unknown001 *size = reinterpret_cast<const unknown001 *>(data + header->unknown0c);
  unknown50 = static_cast<f32>(size->unknown04);
  unknown4c = static_cast<f32>(size->unknown0c);
  if (header->unknown24 != 0) {
    unknown40 = LayerManager::get()->unknown58->unknown40->createTextureObj(data + header->unknown24);
  }
  if (header->unknown08 & 2) {
    u32 offset = header->unknown2c;
    const u8 *table = reinterpret_cast<const u8 *>(unknown30);
    unknown38 = reinterpret_cast<const unknown002 *>(table + offset);
    unknown48 = *reinterpret_cast<const u16 *>(table + offset);
  } else {
    unknown38 = nullptr;
    unknown48 = 0;
  }
}

void LayerFontIconObj::getFontUvParms(f32 *uv, u16 index) const {
  if (unknown38 != nullptr) {
    u32 offset = unknown38->unknown18;
    u32 count = unknown48;
    const u8 *base = reinterpret_cast<const u8 *>(unknown38) + offset;
    u32 entryIndex = index;
    if (count <= index) {
      entryIndex = 0;
    }
    const unknown005 &entry = reinterpret_cast<const unknown005 *>(base)[entryIndex];
    uv[0] = unknown50 * entry.unknown00;
    uv[1] = unknown4c * entry.unknown04;
    uv[2] = entry.unknown08;
    uv[3] = entry.unknown0c;
    uv[4] = entry.unknown10;
    uv[5] = entry.unknown14;
  } else {
    uv[0] = unknown50;
    uv[1] = unknown4c;
    uv[2] = 1.0f;
    uv[3] = 1.0f;
    uv[4] = 0.0f;
    uv[5] = 0.0f;
  }
}

void LayerFontIconObj::getFontUvOnlyParms(f32 *uv, u16 index) const {
  if (unknown38 != nullptr) {
    u32 offset = unknown38->unknown18;
    u32 count = unknown48;
    const u8 *base = reinterpret_cast<const u8 *>(unknown38) + offset;
    u32 entryIndex = index;
    if (count <= index) {
      entryIndex = 0;
    }
    const unknown005 &entry = reinterpret_cast<const unknown005 *>(base)[entryIndex];
    uv[0] = entry.unknown08;
    uv[1] = entry.unknown0c;
    uv[2] = entry.unknown10;
    uv[3] = entry.unknown14;
  } else {
    uv[0] = 1.0f;
    uv[1] = 1.0f;
    uv[2] = 0.0f;
    uv[3] = 0.0f;
  }
}

void LayerFontIconObj::setupResource() {
  if (unknown40 != nullptr) {
    unknown40->setupResource();
  }
}

void LayerFontIconObj::release() {
  unknown1c = 0x22;
  unknown28 |= 1 << LayerManager::s_nStkIdx;
}

} // namespace layer
