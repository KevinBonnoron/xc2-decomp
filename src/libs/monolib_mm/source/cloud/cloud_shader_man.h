#pragma once
#include "types.h"

namespace cloud {

class CloudShaderMan {
public:
  CloudShaderMan();
  ~CloudShaderMan();
  void createShader();
  void update();

  u8 _000[0x1a8 - 0x000];
};

} // namespace cloud
