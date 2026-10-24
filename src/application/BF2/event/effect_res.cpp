#include "event/effect_res.h"

#include "event/extend.h"
#include "event/res_manager.h"
#include "framework/effect/effect_pack.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/singleton.h"

namespace event {

EffectRes::EffectRes(const char *name) : unknown08(0), m_name(name), m_resPack(nullptr) {
  mm::mtl::FixStr<256> path;
  path.format("event/evpa/%s", name);
  mm::mtl::Singleton<ResManager>::getPtr()->load(mm::mtl::Singleton<Extend>::getPtr()->pack_efb(path.c_str()), this, true);
  unknown08 |= FLAG_LOADING;
}

EffectRes::~EffectRes() { mm::mtl::safeRelease(m_resPack); }

const char *EffectRes::getName() const { return m_name.c_str(); }

fw::EffectPack *EffectRes::getResPack() const { return m_resPack; }

bool EffectRes::isLoading() const { return (unknown08 & FLAG_LOADING) != 0; }

void EffectRes::OnResEvent(const PARAM &param) {
  if (param.result == RES_RESULT_TYPE_SUCCESS) {
    m_resPack = fw::EffectPack::createFromMemory(param.adr, param.size, param.path, false);
    unknown08 &= ~FLAG_LOADING;
    return;
  }
  m_resPack = nullptr;
  unknown08 &= ~FLAG_LOADING;
}

} // namespace event
