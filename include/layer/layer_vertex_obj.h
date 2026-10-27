#pragma once
#include <stddef.h>

#include "layer/layer_link_list.h"
#include "types.h"

namespace grlib {
class CGLibVtlMemPool;
class CGLibVtxIndex;
class CGLibVtxVertex;
} // namespace grlib

namespace layer {

class LayerManager;
class LayerVertexMan;

extern const u16 s_nVertexSize[];

class LayerVertexObj {
public:
  LayerVertexObj(const u8 *data, LayerManager *manager, LayerVertexMan *vertexMan);
  ~LayerVertexObj() {}
  void setupVertex(const u8 *data, LayerManager *manager);
  void vertexRelease();
  void release();
  void begin();
  bool setVertex(u32 index);
  void render(u32 index);

  LayerVertexObj *unknown00; // Inferred role: previous node; original member name unknown.
  LayerVertexObj *unknown08; // Inferred role: next node; original member name unknown.
  const u8 *unknown10;       // Inferred role: resource key; original member name unknown.
  s32 unknown18;             // Inferred role: reference count; original member name unknown.
  s16 unknown1c;             // Inferred role: current vertex index; original member name unknown.
  u8 _1e[0x20 - 0x1e];
  void *unknown20;                          // Inferred role: object memory; original member name unknown.
  s32 unknown28;                            // Inferred role: vertex count; original member name unknown.
  s32 unknown2c;                            // Inferred role: index count; original member name unknown.
  const u8 *unknown30;                      // Inferred role: resource data; original member name unknown.
  const u8 *unknown38;                      // Inferred role: vertex table; original member name unknown.
  const u8 *unknown40;                      // Inferred role: index table; original member name unknown.
  grlib::CGLibVtxVertex *unknown48;         // Inferred role: vertices; original member name unknown.
  grlib::CGLibVtxIndex *unknown50;          // Inferred role: indices; original member name unknown.
  grlib::CGLibVtlMemPool *unknown58;        // Inferred role: memory pool; original member name unknown.
  LayerLinkList<LayerVertexObj> *unknown60; // Inferred role: owner list; original member name unknown.
};

static_assert(offsetof(LayerVertexObj, unknown10) == 0x10, "");
static_assert(offsetof(LayerVertexObj, unknown18) == 0x18, "");
static_assert(offsetof(LayerVertexObj, unknown1c) == 0x1c, "");
static_assert(offsetof(LayerVertexObj, unknown20) == 0x20, "");
static_assert(offsetof(LayerVertexObj, unknown28) == 0x28, "");
static_assert(offsetof(LayerVertexObj, unknown2c) == 0x2c, "");
static_assert(offsetof(LayerVertexObj, unknown30) == 0x30, "");
static_assert(offsetof(LayerVertexObj, unknown38) == 0x38, "");
static_assert(offsetof(LayerVertexObj, unknown40) == 0x40, "");
static_assert(offsetof(LayerVertexObj, unknown48) == 0x48, "");
static_assert(offsetof(LayerVertexObj, unknown50) == 0x50, "");
static_assert(offsetof(LayerVertexObj, unknown58) == 0x58, "");
static_assert(offsetof(LayerVertexObj, unknown60) == 0x60, "");
static_assert(sizeof(LayerVertexObj) == 0x68, "");

class LayerVertexMan : public LayerLinkList<LayerVertexObj> {
public:
  LayerVertexMan(LayerManager *manager);
  ~LayerVertexMan();
  LayerVertexObj *createVertexObj(const u8 *data);
  void releaseVertexObj(LayerVertexObj *vertexObj);

  LayerManager *unknown18; // Inferred role: layer manager; original member name unknown.
};

static_assert(offsetof(LayerVertexMan, unknown18) == 0x18, "");
static_assert(sizeof(LayerVertexMan) == 0x20, "");

} // namespace layer
