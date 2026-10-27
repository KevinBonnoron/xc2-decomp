#pragma once
#include <stddef.h>

#include "layer/layer_link_list.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerManager;
class LayerTextureMan;

class LayerTextureObj {
public:
  LayerTextureObj(const u8 *data, LayerManager *manager, LayerTextureMan *textureMan);
  ~LayerTextureObj();
  void setupTexture(const u8 *data, LayerManager *manager);
  void textureRelease();
  void release();
  const grlib::CGLibTextureBuffer *getTexture(int index) const;
  grlib::CGLibTextureBuffer *getTexture(int index);

  LayerTextureObj *unknown00; // Inferred role: previous node; original member name unknown.
  LayerTextureObj *unknown08; // Inferred role: next node; original member name unknown.
  const u8 *unknown10;        // Inferred role: resource key; original member name unknown.
  s32 unknown18;              // Inferred role: reference count; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  const u8 *unknown20; // Inferred role: resource data; original member name unknown.
  u8 unknown28;        // Inferred role: needs setup; original member name unknown.
  u8 _29[0x2c - 0x29];
  s32 unknown2c;                             // Inferred role: texture count; original member name unknown.
  grlib::CGLibTextureBuffer *unknown30;      // Inferred role: textures; original member name unknown.
  void *unknown38;                           // Inferred role: texture memory; original member name unknown.
  LayerLinkList<LayerTextureObj> *unknown40; // Inferred role: owner list; original member name unknown.
};

static_assert(offsetof(LayerTextureObj, unknown10) == 0x10, "");
static_assert(offsetof(LayerTextureObj, unknown18) == 0x18, "");
static_assert(offsetof(LayerTextureObj, unknown20) == 0x20, "");
static_assert(offsetof(LayerTextureObj, unknown28) == 0x28, "");
static_assert(offsetof(LayerTextureObj, unknown2c) == 0x2c, "");
static_assert(offsetof(LayerTextureObj, unknown30) == 0x30, "");
static_assert(offsetof(LayerTextureObj, unknown38) == 0x38, "");
static_assert(offsetof(LayerTextureObj, unknown40) == 0x40, "");
static_assert(sizeof(LayerTextureObj) == 0x48, "");

extern template void LayerLinkList<LayerTextureObj>::deleteList(LayerTextureObj *node);

class LayerTextureMan : public LayerLinkList<LayerTextureObj> {
public:
  LayerTextureMan(LayerManager *manager);
  ~LayerTextureMan();
  LayerTextureObj *createTextureObj(const u8 *data);
  void releaseTextureObj(LayerTextureObj *textureObj);

  LayerManager *unknown18; // Inferred role: layer manager; original member name unknown.
};

static_assert(offsetof(LayerTextureMan, unknown18) == 0x18, "");
static_assert(sizeof(LayerTextureMan) == 0x20, "");

} // namespace layer
