#pragma once
#include <stddef.h>

#include "mm_mtl/array.h"
#include "types.h"
#include "ui/shape/ui_shape.h"

namespace layer {
struct LayerPolyVertex;
} // namespace layer

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UIShapeSimpleFace : public UIShape {
public:
  static mm::mtl::RTTI m_rtti;

  UIShapeSimpleFace(u32 vertexNum);
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual ~UIShapeSimpleFace();
  virtual void update(u32 frame);

  void writeFaceVertex(const layer::LayerPolyVertex *vertex, u32 num, u32 offset);

  mm::mtl::Array<layer::LayerPolyVertex> faceVertices;
  bool faceDirty;
};

static_assert(offsetof(UIShapeSimpleFace, faceVertices) == 0x40, "");
static_assert(offsetof(UIShapeSimpleFace, faceDirty) == 0x58, "");
static_assert(sizeof(UIShapeSimpleFace) == 0x60, "");

} // namespace ui
