#pragma once

enum GrlPrimitiveType {
  GRL_PRIMITIVE_POINTS = 0,
};

namespace grlib {
class CGLibVtxVertex;

class CGLibCtlVertex {
public:
  static void setVertex(CGLibVtxVertex &vertex);
  static void renderVertex(GrlPrimitiveType type, int count);
  static void renderInstanceVertex(GrlPrimitiveType type, int count, int instanceCount);
};

} // namespace grlib
