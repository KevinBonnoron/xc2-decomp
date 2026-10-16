#pragma once
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerBase;

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
};

} // namespace layer
