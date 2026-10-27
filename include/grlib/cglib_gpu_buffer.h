#pragma once

namespace grlib {

class CGLibOneUniformBlock;
class CGLibTextureBuffer;

class CGLibGpuBuffer {
public:
  static void copyBuffer(CGLibTextureBuffer &dst, CGLibTextureBuffer &src);
  static void copyBuffer(CGLibOneUniformBlock &dst, CGLibOneUniformBlock &src);
};

} // namespace grlib
