#include "layer/layer_texture_obj.h"

#include <new>

#include "grlib/cglib_texture_buffer.h"
#include "layer/layer_manager.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace layer {

namespace {

struct unknown001 {
  u8 _00[4];
  s32 unknown04; // Inferred role: image count; original member name unknown.
};
} // namespace

template void LayerLinkList<LayerTextureObj>::deleteList(LayerTextureObj *node);

LayerTextureMan::LayerTextureMan(LayerManager *manager) : unknown18(manager) {}

LayerTextureObj::LayerTextureObj(const u8 *data, LayerManager *manager, LayerTextureMan *textureMan)
    : unknown00(nullptr), unknown08(nullptr), unknown10(data), unknown18(1), unknown2c(0), unknown38(nullptr), unknown40(textureMan) {
  unknown28 = 1;
  setupTexture(data, manager);
}

void LayerTextureObj::textureRelease() {
  if (unknown38 != nullptr) {
    for (s32 i = 0; i < unknown2c; i++) {
      unknown30[i].~CGLibTextureBuffer();
    }
    if (unknown38 != nullptr) {
      mtl::MemManager::deallocate(unknown38, 0, false);
      unknown38 = nullptr;
    }
    unknown2c = 0;
  }
}

const grlib::CGLibTextureBuffer *LayerTextureObj::getTexture(int index) const { return &unknown30[index]; }

grlib::CGLibTextureBuffer *LayerTextureObj::getTexture(int index) { return &unknown30[index]; }

LayerTextureObj::~LayerTextureObj() { textureRelease(); }

void LayerTextureObj::release() {
  LayerLinkList<LayerTextureObj> *list = unknown40;
  s32 count = unknown18 - 1;
  if (unknown18 <= 0) {
    count = 0;
  }
  unknown18 = count;
  if (count <= 0) {
    list->deleteList(this);
  }
}

void LayerTextureObj::setupTexture(const u8 *data, LayerManager *manager) {
  textureRelease();
  unknown20 = data;
  unknown2c = reinterpret_cast<const unknown001 *>(data)->unknown04;
  unknown30 = static_cast<grlib::CGLibTextureBuffer *>(mtl::MemManager::allocate(manager->unknown2c, static_cast<size_t>(unknown2c) * sizeof(grlib::CGLibTextureBuffer), 0x10, false, "no name", 0));
  unknown38 = unknown30;
  for (s32 i = 0; i < unknown2c; i++) {
    new (&unknown30[i]) grlib::CGLibTextureBuffer();
  }
}

LayerTextureMan::~LayerTextureMan() {
  LayerTextureObj *textureObj = unknown00;
  while (textureObj != nullptr) {
    LayerTextureObj *next = textureObj->unknown08;
    delete textureObj;
    textureObj = next;
  }
  unknown10 = 0;
  unknown00 = nullptr;
  unknown08 = nullptr;
}

void LayerTextureMan::releaseTextureObj(LayerTextureObj *textureObj) {
  s32 count = textureObj->unknown18 - 1;
  if (textureObj->unknown18 <= 0) {
    count = 0;
  }
  textureObj->unknown18 = count;
  if (count <= 0) {
    deleteList(textureObj);
  }
}

LayerTextureObj *LayerTextureMan::createTextureObj(const u8 *data) {
  for (LayerTextureObj *textureObj = unknown00; textureObj != nullptr; textureObj = textureObj->unknown08) {
    if (textureObj->unknown10 == data) {
      textureObj->unknown18++;
      return textureObj;
    }
  }

  LayerTextureObj *textureObj = new (unknown18->unknown28) LayerTextureObj(data, unknown18, this);
  if (textureObj != nullptr) {
    unknown002(textureObj);
  }
  return textureObj;
}

} // namespace layer
