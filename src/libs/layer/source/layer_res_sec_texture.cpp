#include "layer/layer_res_sec_texture.h"

#include "layer/layer_manager.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_texture_obj.h"

namespace layer {

namespace {

struct unknown001 {
  u8 _00[0x08];
  u8 unknown08; // Inferred role: flags; original member name unknown.
  u8 _09[0x24 - 0x09];
  u32 unknown24; // Inferred role: offset of the texture resource; original member name unknown.
  u8 _28[0x2c - 0x28];
  u32 unknown2c; // Inferred role: offset of the icon resource; original member name unknown.
};

struct unknown002 {
  u32 unknown00; // Inferred role: icon max; original member name unknown.
  u8 _04[0x18 - 0x04];
  u32 unknown18; // Inferred role: offset of the icon table; original member name unknown.
};

struct unknown003 {
  u8 _00[0x08];
  f32 unknown08; // Inferred role: uv x; original member name unknown.
  f32 unknown0c; // Inferred role: uv y; original member name unknown.
  f32 unknown10; // Inferred role: uv width; original member name unknown.
  f32 unknown14; // Inferred role: uv height; original member name unknown.
  u8 _18[0x1c - 0x18];
};

} // namespace

LayerResSecTexture::LayerResSecTexture(const void *data) : unknown08(nullptr) {
  unknown00 = data;
  const unknown001 *header = static_cast<const unknown001 *>(data);
  if (header->unknown24 != 0) {
    unknown08 = LayerManager::get()->unknown58->unknown40->createTextureObj(static_cast<const u8 *>(data) + header->unknown24);
  }
  if (header->unknown08 & 0x2) {
    unknown12 = reinterpret_cast<const unknown002 *>(static_cast<const u8 *>(unknown00) + header->unknown2c)->unknown00;
  } else {
    unknown12 = 0;
  }
  unknown10 = 0;
  unknown14 = 1.0f;
}

grlib::CGLibTextureBuffer *LayerResSecTexture::getTexture() { return unknown08->unknown30; }

void LayerResSecTexture::resourceInit() { unknown18.setup(LayerObjUtil::getUniformBlockSizeAlOff(LAYER_UNI_TYPE_UNKNOWN_10)); }

void LayerResSecTexture::update() {
  f32 *uniform = static_cast<f32 *>(unknown18.getBuff());
  if (unknown12 == 0) {
    uniform[0] = 1.0f;
    uniform[1] = 1.0f;
    uniform[2] = 0.0f;
    uniform[3] = 0.0f;
  } else {
    const u8 *icon = static_cast<const u8 *>(unknown00) + static_cast<const unknown001 *>(unknown00)->unknown2c;
    const unknown003 *entry = reinterpret_cast<const unknown003 *>(icon + reinterpret_cast<const unknown002 *>(icon)->unknown18) + unknown10;
    uniform[0] = entry->unknown08;
    uniform[1] = entry->unknown0c;
    uniform[2] = entry->unknown10;
    uniform[3] = entry->unknown14;
  }
  uniform[4] = unknown14;
  uniform[5] = 0.0f;
  uniform[6] = 0.0f;
  uniform[7] = 0.0f;
  unknown18.updateData();
}

} // namespace layer
