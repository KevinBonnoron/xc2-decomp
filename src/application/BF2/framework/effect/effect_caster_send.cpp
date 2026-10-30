#include <string.h>

#include "eflib/effect_system_manager.h"
#include "framework/asset/asset_manager.h"
#include "framework/effect/effect_caster.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/vector.h"
#include "types.h"

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

  unknown065 *datas;
  if (effect::SystemManager::getPtr()->unknown7824d == 0) {
    datas = &unknown18[1][0];
  } else {
    datas = &unknown18[0][0];
  }
  unknown065 &data = datas[index];
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

  unknown88[effect::SystemManager::getPtr()->unknown7824d != 0] = scale;
}

void EffectCasterSend::sendDataFrame(f32 frame) {
  if (m_caster == nullptr || effect::SystemManager::getPtr() == nullptr) {
    return;
  }

  unknown90[effect::SystemManager::getPtr()->unknown7824d != 0] = frame;
}

void EffectCasterSend::sendDataStateName(const char *name) {
  if (m_caster == nullptr || effect::SystemManager::getPtr() == nullptr) {
    return;
  }

  unknown98[effect::SystemManager::getPtr()->unknown7824d != 0] = name;
}

const char *EffectCasterSend::getStateName() { return unknown98[effect::SystemManager::getPtr()->unknown7824d == 0].c_str(); }

EffectCasterSend::EffectCasterSend(mm::mtl::IAllocator *allocator)
    : unknown18{mm::mtl::Vector<unknown065>(allocator), mm::mtl::Vector<unknown065>(allocator)}, m_caster(nullptr), unknown78(allocator), unknown80(nullptr) {}

EffectCasterSend::~EffectCasterSend() {}

unknown065 *EffectCasterSend::getBindData(u32 &count) {
  if (m_caster == nullptr) {
    return nullptr;
  }

  unknown065 *datas = m_caster->unknown20;
  count = m_caster->unknown28;
  return datas;
}

f32 EffectCasterSend::getMdlFrame() { return unknown90[effect::SystemManager::getPtr()->unknown7824d == 0]; }

f32 EffectCasterSend::getMdlScl() { return unknown88[effect::SystemManager::getPtr()->unknown7824d == 0]; }

void EffectCasterSend::tailCopy() {
  u32 src = effect::SystemManager::getPtr()->unknown7824d != 0;
  u32 dst = effect::SystemManager::getPtr()->unknown7824d == 0;
  unknown88[dst] = unknown88[src];
  unknown90[dst] = unknown90[src];
  unknown98[dst] = unknown98[src];
}

} // namespace fw
