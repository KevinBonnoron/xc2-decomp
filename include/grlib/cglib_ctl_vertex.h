#pragma once
#include <stddef.h>

#include "types.h"

enum GrlPrimitiveType {
  GRL_PRIMITIVE_POINTS = 0,
  GRL_PRIMITIVE_TRIANGLES = 4,
  GRL_PRIMITIVE_TRIANGLE_STRIP = 5,
  GRL_PRIMITIVE_QUADS = 7,
};

namespace grlib {
namespace context {
class CGLibSystemContext;
} // namespace context
class CGLibDblUniformBlock;
class CGLibEtcUniformBlock;
class CGLibOneUniformBlock;
class CGLibTriUniformBlock;
class CGLibVtxStmOut;
class CGLibVtxInstans;
class CGLibVtxOneInstans;
class CGLibVtxVertex;

class CGLibCtlVertex {
public:
  static void setVertex(CGLibVtxVertex &vertex);
  static void setVertex(CGLibVtxVertex &vertex, u32 offset);
  static void setAddVertex(CGLibVtxVertex &vertex, int offset, int stream, u32 divisor);
  static void setUniformVertex(CGLibOneUniformBlock &block, int stride, int offset, int stream, u32 divisor);
  static void setUniformVertex(CGLibDblUniformBlock &block, int stride, int offset, int stream, u32 divisor);
  static void setUniformVertex(CGLibTriUniformBlock &block, int stride, int offset, int stream, u32 divisor);
  static void setStreamOutVertex(CGLibVtxStmOut &streamOut, int stride, int offset, int stream, u32 divisor);
  static void setInstanceVertex(CGLibVtxInstans &instance, int stride, int offset, int stream, u32 divisor);
  static void setInstanceVertex(CGLibVtxOneInstans &instance, int stride, int offset, int stream, u32 divisor);
  static void renderVertex(GrlPrimitiveType type, int count);
  static void renderInstanceVertex(GrlPrimitiveType type, int count, int instanceCount);
  static void renderIndirectVertex(GrlPrimitiveType type, const CGLibOneUniformBlock &block, u32 offset);
  static void renderIndirectVertex(GrlPrimitiveType type, const CGLibDblUniformBlock &block, u32 offset);
  static void renderIndirectVertex(GrlPrimitiveType type, const CGLibTriUniformBlock &block, u32 offset);
  static void renderIndirectVertex(GrlPrimitiveType type, const CGLibEtcUniformBlock &block, u32 offset);
  static void renderMultiIndirectVertex(GrlPrimitiveType type, u32 drawCount, u32 stride, const CGLibOneUniformBlock &block, u32 offset);
  static void renderMultiIndirectVertex(GrlPrimitiveType type, u32 drawCount, u32 stride, const CGLibDblUniformBlock &block, u32 offset);
  static void renderMultiIndirectVertex(GrlPrimitiveType type, u32 drawCount, u32 stride, const CGLibTriUniformBlock &block, u32 offset);
  static void renderMultiIndirectVertex(GrlPrimitiveType type, u32 drawCount, u32 stride, const CGLibEtcUniformBlock &block, u32 offset);

  // Inferred role: sets the stride and divisor of a vertex stream; original name unknown.
  static void unknown001(context::CGLibSystemContext *context, size_t stride, u32 divisor, int stream);
};

} // namespace grlib
