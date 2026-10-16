#pragma once

namespace anm {
class ResASM;
}

namespace fw {
struct EffectResData;
}

namespace gf {

struct GF_OBJ_HANDLE;

class GfComEffectCaster {
public:
  static void registerAsmCallbackEffect(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm, fw::EffectResData *effectData);
};

} // namespace gf
