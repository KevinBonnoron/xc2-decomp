#pragma once
#include "types.h"

enum GrlPrimitiveType {
  GRL_PRIMITIVE_POINTS = 0,
  GRL_PRIMITIVE_TRIANGLES = 4,
  GRL_PRIMITIVE_TRIANGLE_STRIP = 5,
  GRL_PRIMITIVE_QUADS = 7,
};

namespace grlib {
class CGLibOneUniformBlock;
class CGLibVtxInstans;
class CGLibVtxOneInstans;
class CGLibVtxVertex;

class CGLibCtlVertex {
public:
  static void setVertex(CGLibVtxVertex &vertex);
  static void setAddVertex(CGLibVtxVertex &vertex, int offset, int stream, u32 divisor);
  static void setUniformVertex(CGLibOneUniformBlock &block, int stride, int offset, int stream, u32 divisor);
  static void setInstanceVertex(CGLibVtxInstans &instance, int stride, int offset, int stream, u32 divisor);
  static void setInstanceVertex(CGLibVtxOneInstans &instance, int stride, int offset, int stream, u32 divisor);
  static void renderVertex(GrlPrimitiveType type, int count);
  static void renderInstanceVertex(GrlPrimitiveType type, int count, int instanceCount);
};

} // namespace grlib
