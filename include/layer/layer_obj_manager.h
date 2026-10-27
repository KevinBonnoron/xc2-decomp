#pragma once
#include <stddef.h>

#include "layer/layer_base.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {
class IDrDrawWorkInfo;
} // namespace ml

namespace layer {

class LayerObj;
class LayerSortMan;

enum LayerMemType {
  LAYER_MEM_TYPE_UNKNOWN_3 = 3,
};
enum LayerPrimitiveType {};

class LayerObjManager {
public:
  LayerBase *createObj(const void *data);
  LayerBase *createMaskObj(const void *data);
  LayerBase *createLayoutObj();
  LayerBase *createFontObj();
  LayerBase *createTexObj(const grlib::CGLibTextureBuffer &texture);
  LayerBase *createMemObj(u32 width, u32 height, LayerMemType type);
  LayerBase *createPolyObj(u32 vertexNum, u32 indexNum, u16 width, u16 height, LayerPrimitiveType type);
  LayerBase *createFilterObj();
  void begin();
  void apply(const ml::IDrDrawWorkInfo *info);
  void alphaRender(const ml::IDrDrawWorkInfo *info);
  void lastRender(const ml::IDrDrawWorkInfo *info);
  void finalRender(const ml::IDrDrawWorkInfo *info);
  void end();
  void setDeleteList(LayerObj *object);
  void allRelease();
  ~LayerObjManager();

  const ml::IDrDrawWorkInfo *unknown00; // Inferred role: work info; original member name unknown.
  u8 _08[0x10 - 0x08];
  LayerSortMan *unknown10;            // Inferred role: sort man; original member name unknown.
  LayerBase::unknown001 unknown18;    // Inferred role: active objects; original member name unknown.
  LayerBase::unknown001 unknown30[2]; // Inferred role: objects to add per buffer; original member name unknown.
  LayerBase::unknown001 unknown60;    // Inferred role: objects to delete; original member name unknown.
};

static_assert(offsetof(LayerObjManager, unknown10) == 0x10, "");
static_assert(offsetof(LayerObjManager, unknown18) == 0x18, "");
static_assert(offsetof(LayerObjManager, unknown30) == 0x30, "");
static_assert(offsetof(LayerObjManager, unknown60) == 0x60, "");

} // namespace layer
