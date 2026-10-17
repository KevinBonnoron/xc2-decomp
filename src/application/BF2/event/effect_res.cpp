#include "event/effect_res.h"

#include "event/extend.h"
#include "event/res_manager.h"
#include "framework/effect/effect_pack.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/singleton.h"

namespace event {

EffectRes::EffectRes(const char *name) : flags(0), name(name), pack(nullptr) {
  mm::mtl::FixStr<256> path;
  path.format("event/evpa/%s", name);
  mm::mtl::Singleton<ResManager>::getPtr()->load(mm::mtl::Singleton<Extend>::getPtr()->pack_efb(path.c_str()), this, true);
  flags |= FLAG_LOADING;
}

EffectRes::~EffectRes() { mm::mtl::safeRelease(pack); }

const char *EffectRes::getName() const { return name.c_str(); }

fw::EffectPack *EffectRes::getResPack() const { return pack; }

bool EffectRes::isLoading() const { return (flags & FLAG_LOADING) != 0; }

void EffectRes::OnResEvent(const PARAM &param) {
  if (param.result == RES_RESULT_TYPE_SUCCESS) {
    pack = fw::EffectPack::createFromMemory(param.adr, param.size, param.path, false);
    flags &= ~FLAG_LOADING;
    return;
  }
  pack = nullptr;
  flags &= ~FLAG_LOADING;
}

} // namespace event
