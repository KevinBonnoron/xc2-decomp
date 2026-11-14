#include <string.h>

#include "eflib/effect_system_manager.h"
#include "framework/asset/asset_manager.h"
#include "framework/effect/effect_caster.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/vector.h"
#include "ptlib/particle_system.h"
#include "scn/scn_obj_model_dr_sys.h"
#include "types.h"

namespace ml {
class DrMdlObj;
} // namespace ml

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

EffectCasterBase *EffectCasterSend::getCaster() { return m_caster; }

bool EffectCasterSend::checkCaster(EffectCasterBase *caster) { return this->m_caster == caster; }

void EffectCasterSend::sendData(mm::Mat44 &matrix, const char *name, int index) {
  if (m_caster == nullptr || effect::SystemManager::getPtr() == nullptr) {
    return;
  }

  MtxAndName *datas;
  if (effect::SystemManager::getPtr()->unknown7824d == 0) {
    datas = &unknown18[1][0];
  } else {
    datas = &unknown18[0][0];
  }
  MtxAndName &data = datas[index];
  data.unknown20 = matrix;
  if (name == nullptr) {
    strcpy(data.unknown04, "root");
  } else {
    strcpy(data.unknown04, name);
  }
  data.unknown00 = AssetManager::getHash(data.unknown04);
}

void EffectCasterSend::sendData(f32 scale) {
  if (m_caster == nullptr || effect::SystemManager::getPtr() == nullptr) {
    return;
  }

  m_mdlScl[effect::SystemManager::getPtr()->unknown7824d != 0] = scale;
}

void EffectCasterSend::sendDataFrame(f32 frame) {
  if (m_caster == nullptr || effect::SystemManager::getPtr() == nullptr) {
    return;
  }

  m_mdlFrame[effect::SystemManager::getPtr()->unknown7824d != 0] = frame;
}

void EffectCasterSend::sendDataStateName(const char *name) {
  if (m_caster == nullptr || effect::SystemManager::getPtr() == nullptr) {
    return;
  }

  unknown98[effect::SystemManager::getPtr()->unknown7824d != 0] = name;
}

const char *EffectCasterSend::getStateName() { return unknown98[effect::SystemManager::getPtr()->unknown7824d == 0].c_str(); }

EffectCasterSend::EffectCasterSend(mm::mtl::IAllocator *allocator)
    : unknown18{mm::mtl::Vector<MtxAndName>(allocator), mm::mtl::Vector<MtxAndName>(allocator)}, m_caster(nullptr), unknown78(allocator), unknown80(nullptr) {}

EffectCasterSend::~EffectCasterSend() {}

EffectCasterSend::MtxAndName *EffectCasterSend::getBindData(u32 &count) {
  if (m_caster == nullptr) {
    return nullptr;
  }

  MtxAndName *datas = m_caster->unknown20;
  count = m_caster->unknown28;
  return datas;
}

f32 EffectCasterSend::getMdlFrame() { return m_mdlFrame[effect::SystemManager::getPtr()->unknown7824d == 0]; }

f32 EffectCasterSend::getMdlScl() { return m_mdlScl[effect::SystemManager::getPtr()->unknown7824d == 0]; }

void EffectCasterSend::tailCopy() {
  u32 src = effect::SystemManager::getPtr()->unknown7824d != 0;
  u32 dst = effect::SystemManager::getPtr()->unknown7824d == 0;
  m_mdlScl[dst] = m_mdlScl[src];
  m_mdlFrame[dst] = m_mdlFrame[src];
  unknown98[dst] = unknown98[src];
}

ml::DrMdlObj *EffectCasterSend::getMdl() {
  unknown80 = m_caster->unknown18->unknown3d8;
  return unknown80;
}

// The game repeats the bind search per buffer (a helper is not inlined by clang: 42 vs 191 insns).
bool EffectCasterSend::getMdlMat(mm::Mat44 &matrix) {
  if (effect::SystemManager::getPtr() == nullptr) {
    return true;
  }

  u8 buffer = effect::SystemManager::getPtr()->unknown7824d;
  u32 hash = AssetManager::getHash("root");
  if (buffer == 0) {
    for (u32 i = 0; i < unknown18[1].size(); i++) {
      if (hash == unknown18[1][i].unknown00 && strcmp(unknown18[1][i].unknown04, "root") == 0) {
        matrix = unknown18[1][i].unknown20;
        return true;
      }
    }
  } else {
    for (u32 i = 0; i < unknown18[0].size(); i++) {
      if (hash == unknown18[0][i].unknown00 && strcmp(unknown18[0][i].unknown04, "root") == 0) {
        matrix = unknown18[0][i].unknown20;
        return true;
      }
    }
  }
  return false;
}

// The game repeats the bind search per buffer (a helper is not inlined by clang: 42 vs 191 insns).
bool EffectCasterSend::getEfpMat(mm::Mat44 &matrix, const char *name) {
  if (effect::SystemManager::getPtr() == nullptr || name == nullptr) {
    getMdlMat(matrix);
    if (name == nullptr) {
      ptlib::efWng("error EFP null");
    } else {
      ptlib::efWng("error EFP %s", name);
    }
    return false;
  }

  u8 buffer = effect::SystemManager::getPtr()->unknown7824d;
  u32 hash = AssetManager::getHash(name);
  if (buffer == 0) {
    for (u32 i = 0; i < unknown18[1].size(); i++) {
      if (hash == unknown18[1][i].unknown00 && strcmp(unknown18[1][i].unknown04, name) == 0) {
        matrix = unknown18[1][i].unknown20;
        return true;
      }
    }
  } else {
    for (u32 i = 0; i < unknown18[0].size(); i++) {
      if (hash == unknown18[0][i].unknown00 && strcmp(unknown18[0][i].unknown04, name) == 0) {
        matrix = unknown18[0][i].unknown20;
        return true;
      }
    }
  }
  getMdlMat(matrix);
  return false;
}

} // namespace fw

template void mm::mtl::Vector<fw::EffectCasterSend::MtxAndName>::push_back(const fw::EffectCasterSend::MtxAndName &);
