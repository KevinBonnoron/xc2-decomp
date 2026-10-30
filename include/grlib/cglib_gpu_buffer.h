#pragma once

namespace grlib {

class CGLibDblUniformBlock;
class CGLibOneUniformBlock;
class CGLibTextureBuffer;
class CGLibTriUniformBlock;

class CGLibGpuBuffer {
public:
  static void copyBuffer(CGLibTextureBuffer &dst, CGLibTextureBuffer &src);
  static void copyBuffer(CGLibOneUniformBlock &dst, CGLibOneUniformBlock &src);
  static void copyBuffer(CGLibDblUniformBlock &dst, CGLibDblUniformBlock &src);
  static void copyBuffer(CGLibTriUniformBlock &dst, CGLibTriUniformBlock &src);
};

} // namespace grlib
