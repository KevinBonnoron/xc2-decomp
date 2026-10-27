#include "layer/layer_obj_top_mask_obj.h"

#include "layer/layer_manager.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_texture_obj.h"

namespace layer {

namespace {

struct unknown004 {
  u8 _00[0x08];
  u8 unknown08; // Inferred role: flags; original member name unknown.
  u8 _09[0x0c - 0x09];
  u32 unknown0c; // Inferred role: offset of the layout info; original member name unknown.
  u8 _10[0x24 - 0x10];
  u32 unknown24; // Inferred role: offset of the texture; original member name unknown.
  u8 _28[0x2c - 0x28];
  u32 unknown2c; // Inferred role: offset of the icon info; original member name unknown.
};

struct unknown005 {
  u8 _00[0x04];
  u32 unknown04; // Inferred role: width; original member name unknown.
  u8 _08[0x0c - 0x08];
  u32 unknown0c; // Inferred role: height; original member name unknown.
  f32 unknown10; // Inferred role: scale x; original member name unknown.
  f32 unknown14; // Inferred role: scale y; original member name unknown.
};

struct unknown006 {
  u32 unknown00; // Inferred role: icon max; original member name unknown.
};

} // namespace

LayerObjTopMaskObj::~LayerObjTopMaskObj() {
  baseRelease();
  releaseWorkBuffer();
}

void LayerObjTopMaskObj::createWorkBuffer(const void *data) {
  unknownb8 = data;
  const unknown004 *header = static_cast<const unknown004 *>(data);
  if (header->unknown24 != 0) {
    unknown2c8 = LayerManager::get()->unknown58->unknown40->createTextureObj(static_cast<const u8 *>(data) + header->unknown24);
  }
  if (header->unknown08 & 0x2) {
    unknown2d2 = reinterpret_cast<const unknown006 *>(static_cast<const u8 *>(unknownb8) + header->unknown2c)->unknown00;
  } else {
    unknown2d2 = 0;
  }
  unknown2d0 = 0;
  unknown290.setup(0x50);
  const unknown005 *info = reinterpret_cast<const unknown005 *>(static_cast<const u8 *>(unknownb8) + header->unknown0c);
  unknown180 = info->unknown10;
  unknown184 = info->unknown14;
  unknown188 = 1.0f;
  unknown18c = static_cast<f32>(info->unknown0c) / static_cast<f32>(info->unknown04);
  unknown190 = 0;
  unknown192 = 0;
  unknown194 = info->unknown04;
  unknown196 = info->unknown0c;
}

void LayerObjTopMaskObj::releaseWorkBuffer() {
  unknown290.release();
  if (unknown2c8 != nullptr) {
    unknown2c8->release();
    unknown2c8 = nullptr;
  }
}

void LayerObjTopMaskObj::resourceInit() {
  if (unknown2c8 != nullptr) {
    unknown2c8->setupResource();
  }
}

void LayerObjTopMaskObj::setDrawList(LayerSortMan *sortMan, bool is3D) {}

} // namespace layer
