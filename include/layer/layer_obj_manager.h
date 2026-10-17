#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {
class IDrDrawWorkInfo;
} // namespace ml

namespace layer {

class LayerBase;
class LayerSortMan;

enum LayerMemType {};
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
  void finalRender(const ml::IDrDrawWorkInfo *info);
  void end();

  const ml::IDrDrawWorkInfo *m_workInfo;
  u8 _08[0x10 - 0x08];
  LayerSortMan *m_sortMan;
};

static_assert(offsetof(LayerObjManager, m_sortMan) == 0x10, "");

} // namespace layer
