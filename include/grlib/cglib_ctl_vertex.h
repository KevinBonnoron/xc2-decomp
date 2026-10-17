#pragma once
#include "types.h"

enum GrlPrimitiveType {
  GRL_PRIMITIVE_POINTS = 0,
};

namespace grlib {
class CGLibVtxInstans;
class CGLibVtxOneInstans;
class CGLibVtxVertex;

class CGLibCtlVertex {
public:
  static void setVertex(CGLibVtxVertex &vertex);
  static void setInstanceVertex(CGLibVtxInstans &instance, int stride, int offset, int stream, u32 divisor);
  static void setInstanceVertex(CGLibVtxOneInstans &instance, int stride, int offset, int stream, u32 divisor);
  static void renderVertex(GrlPrimitiveType type, int count);
  static void renderInstanceVertex(GrlPrimitiveType type, int count, int instanceCount);
};

} // namespace grlib
