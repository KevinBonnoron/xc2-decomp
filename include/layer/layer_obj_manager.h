#pragma once
#include <stddef.h>

#include "layer/layer_base.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {
class CriticalSection;
class IDrDrawWorkInfo;
} // namespace ml

namespace layer {

class LayerManager;
class LayerObj;
class LayerSortMan;

enum LayerMemType {
  LAYER_MEM_TYPE_UNKNOWN_3 = 3,
};
enum LayerPrimitiveType {};

class LayerObjManager {
public:
  LayerObjManager(LayerManager *manager);
  LayerBase *createObj(const void *data);
  LayerBase *createMaskObj(const void *data);
  LayerBase *createLayoutObj();
  LayerBase *createFontObj();
  LayerBase *createTexObj(const grlib::CGLibTextureBuffer &texture);
  LayerBase *createMemObj(u32 width, u32 height, LayerMemType type);
  LayerBase *createPolyObj(u32 width, u32 height, u16 vertexNum, u16 indexNum, LayerPrimitiveType type);
  LayerBase *createFilterObj();
  static LayerBase *createStaticObj(const void *data);
  static LayerBase *createStaticMaskObj(const void *data);
  static LayerBase *createStaticLayoutObj();
  static LayerBase *createStaticFontObj();
  static LayerBase *createStaticTexObj(const grlib::CGLibTextureBuffer &texture);
  static LayerBase *createStaticMemObj(u32 width, u32 height, LayerMemType type);
  static LayerBase *createStaticPolyObj(u32 width, u32 height, u16 vertexNum, u16 indexNum, LayerPrimitiveType type);
  static LayerBase *createStaticFilterObj();
  void begin();
  void apply(const ml::IDrDrawWorkInfo *info);
  void alphaRender(const ml::IDrDrawWorkInfo *info);
  void lastRender(const ml::IDrDrawWorkInfo *info);
  void finalRender(const ml::IDrDrawWorkInfo *info);
  void end();
  void setDeleteList(LayerObj *object);
  void allRelease();
  ~LayerObjManager();
  static ml::CriticalSection &getCriticalSection();

  const ml::IDrDrawWorkInfo *unknown00; // Inferred role: work info; original member name unknown.
  u8 _08[0x10 - 0x08];
  LayerSortMan *unknown10;            // Inferred role: sort man; original member name unknown.
  LayerBase::unknown001 unknown18;    // Inferred role: active objects; original member name unknown.
  LayerBase::unknown001 unknown30[2]; // Inferred role: objects to add per buffer; original member name unknown.
  LayerBase::unknown001 unknown60;    // Inferred role: objects to delete; original member name unknown.
  u8 _78[0x90 - 0x78];
};

static_assert(offsetof(LayerObjManager, unknown10) == 0x10, "");
static_assert(offsetof(LayerObjManager, unknown18) == 0x18, "");
static_assert(offsetof(LayerObjManager, unknown30) == 0x30, "");
static_assert(offsetof(LayerObjManager, unknown60) == 0x60, "");
static_assert(sizeof(LayerObjManager) == 0x90, "");

} // namespace layer
