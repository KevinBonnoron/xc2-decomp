#include "layer/layer_font_icon_obj.h"

#include "layer/layer_manager.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_texture_obj.h"

namespace layer {

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
