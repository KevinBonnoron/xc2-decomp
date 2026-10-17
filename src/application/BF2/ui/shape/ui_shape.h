#pragma once
#include <stddef.h>

#include "mm_mtl/array.h"
#include "types.h"

namespace layer {
struct LayerPolyVertex;
} // namespace layer

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIShape {
public:
  static mm::mtl::RTTI m_rtti;

  UIShape();
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual ~UIShape();
  virtual void update(u32 frame);

  void setupBuffer(u32 vertexNum, u32 indexNum);
  void writeVertex(const layer::LayerPolyVertex *vertex, u32 num, u32 offset);
  void writeIndex(const u32 *index, u32 num, u32 offset);
  void setIndexRange(u32 range);

  mm::mtl::Array<layer::LayerPolyVertex> vertices;
  mm::mtl::Array<u32> indices;
  u32 indexRange;
  bool dirty;
};

static_assert(offsetof(UIShape, vertices) == 0x08, "");
static_assert(offsetof(UIShape, indices) == 0x20, "");
static_assert(offsetof(UIShape, indexRange) == 0x38, "");
static_assert(offsetof(UIShape, dirty) == 0x3c, "");
static_assert(sizeof(UIShape) == 0x40, "");

} // namespace ui
