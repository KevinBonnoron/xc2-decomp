#pragma once

namespace anm {
class ResASM;
}

namespace fw {
struct EffectResData;
}

namespace gf {

struct GF_OBJ_HANDLE;

namespace enemy {

bool registerAsmCallbackBattle(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm);
void registerAsmCallbackField(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm);
void registerAsmCallback(GF_OBJ_HANDLE *handle, anm::ResASM *resAsm, fw::EffectResData *effectData);

} // namespace enemy
} // namespace gf
