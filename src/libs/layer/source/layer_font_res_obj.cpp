#include "layer/layer_font_res_obj.h"

#include "grlib/cglib_texture.h"
#include "grlib/cglib_texture_buffer.h"
#include "layer/layer_manager.h"
#include "mtl/alloc_handle.h"

namespace layer {

LayerFontResObj::LayerFontResObj(LayerFontManager *manager) {
  unknown10 = nullptr;
  unknown1c = 0xcc;
  unknown20 = manager;
  unknown28 = 0;
  unknown08 = nullptr;
  unknown18 = LAYER_OBJ_TYPE_FONT_RES;
  unknown30 = nullptr;
  unknown60 = nullptr;
  unknown60 = nullptr;
  unknown68 = 1.0f;
  unknown6c = 1.0f;
  unknown70 = 0.0f;
  unknown74 = 0.0f;
}

void LayerFontResObj::setupResource() {
  const u8 *image = static_cast<const u8 *>(unknown30) + unknown38->unknown24;
  grlib::CGLibTextureBuffer *texture = new (LayerManager::get()->unknown2c) grlib::CGLibTextureBuffer();
  unknown60 = texture;
  grlib::CGLibTexture::createTextureImagePtrs(*texture, image, unknown38->unknown28, false, nullptr, true);
}

LayerFontResObj::~LayerFontResObj() {
  if (unknown60 != nullptr) {
    delete unknown60;
    unknown60 = nullptr;
  }
}

const LyrFontInfoData *LayerFontResObj::getFontInfo(u16 &index, u16 code) const {
  index = 0;
  const unknown003 &bucket = unknown40[unknown38->unknown20 & code];
  s32 high = bucket.unknown02;
  if (high != 0) {
    const u16 *indices = unknown48 + bucket.unknown00;
    s32 low = 0;
    do {
      s32 mid = (low + high) >> 1;
      u16 pos = indices[mid];
      const LyrFontInfoData *info = &unknown50[pos];
      if (info->unknown00 == code) {
        index = pos;
        return info;
      }
      if (info->unknown00 < code) {
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    } while (low <= high);
  }
  return unknown50;
}

void LayerFontResObj::getFontUvParms(f32 &u, f32 &v, f32 &w, f32 &h, u16 index) const {
  u32 row = index / unknown58->unknown10;
  u32 column = index % unknown58->unknown10;
  u = (column + unknown58->unknown08 * column + 1) / static_cast<f32>(unknown58->unknown00);
  v = (row + unknown58->unknown0c * row + 1) / static_cast<f32>(unknown58->unknown04);
  w = unknown68;
  h = unknown6c;
}

void LayerFontResObj::setFontData(const void *data) {
  const u8 *bytes = static_cast<const u8 *>(data);
  unknown30 = data;
  unknown38 = static_cast<const unknown001 *>(data);
  unknown50 = reinterpret_cast<const LyrFontInfoData *>(bytes + unknown38->unknown0c);
  unknown48 = reinterpret_cast<const u16 *>(bytes + unknown38->unknown10);
  unknown40 = reinterpret_cast<const unknown003 *>(bytes + unknown38->unknown18);
  unknown58 = reinterpret_cast<const unknown002 *>(bytes + unknown38->unknown2c);
  unknown70 = static_cast<f32>(unknown38->unknown30);
  unknown74 = unknown70 + unknown70;
  unknown68 = static_cast<f32>(unknown58->unknown08) / static_cast<f32>(unknown58->unknown00);
  unknown6c = static_cast<f32>(unknown58->unknown0c) / static_cast<f32>(unknown58->unknown04);
  unknown28 |= 4;
}

void LayerFontResObj::release() {
  unknown1c = 0x22;
  unknown28 |= 1 << LayerManager::s_nStkIdx;
}

} // namespace layer
