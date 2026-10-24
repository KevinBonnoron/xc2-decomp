#include "framework/effect/effect_manager.h"

#include "dr/dr_creator.h"
#include "dr/dr_light_man.h"
#include "dr/dr_light_obj.h"
#include "dr/dr_man.h"
#include "dr/dr_mdl_base.h"
#include "dr/dr_mdl_obj.h"
#include "dr/dr_mdo_grp_obj.h"
#include "eflib/effect_system_manager.h"
#include "framework/effect/effect_caster.h"
#include "framework/effect/effect_data.h"
#include "framework/effect/effect_pack.h"
#include "framework/framework.h"
#include "mm_math/mm_mat44.h"
#include "mm_mtl/fixstr.h"
#include "mtl/mem_manager.h"

namespace ptlib {
struct DrDrawWorkInfoEF;
} // namespace ptlib

namespace fw {

bool EffectManager::initialize() { return true; }

bool EffectManager::isCommonLoaded() { return commonLoaded(); }

void EffectManager::getNum(u32 &emitterNum, u32 &particleNum, u32 &drawNum) {
  if (effect::SystemManager::isValid()) {
    effect::SystemManager::getPtr()->getNum(emitterNum, particleNum, drawNum);
  }
}

void EffectManager::efSystemEnd() {
  if (effect::SystemManager::getPtr() != nullptr) {
    effect::SystemManager::destroy();
    effect::SystemManager::setUserFuncClear();
  }
}

void EffectManager::addPack(EffectPack *pack) { (*packMap)[std::string(pack->name.c_str())] = pack; }

void EffectManager::removePack(EffectPack *pack) {
  PackMap::iterator it = packMap->find(std::string(pack->name.c_str()));
  if (it != packMap->end()) {
    packMap->erase(it);
  }
}

EffectPack *EffectManager::findPack(const char *name) {
  PackMap::iterator it = packMap->find(name);
  return it != packMap->end() ? it->second : nullptr;
}

void EffectManager::addData(EffectData *data) { (*dataMap)[std::string(data->getName())] = data; }

void EffectManager::removeData(EffectData *data) {
  DataMap::iterator it = dataMap->find(std::string(data->getName()));
  if (it != dataMap->end()) {
    dataMap->erase(it);
  }
}

EffectData *EffectManager::findData(const char *name) {
  DataMap::iterator it = dataMap->find(name);
  return it != dataMap->end() ? it->second : nullptr;
}

void EffectManager::setMasterPause(bool isPause) {
  if (masterPause == isPause) {
    return;
  }

  if (effect::SystemManager::getPtr() == nullptr) {
    return;
  }

  masterPause = isPause;
  effect::SystemManager::getPtr()->es_pause(masterPause);
}

bool EffectManager::isMasterPause() const { return masterPause; }

EffectCasterSend *EffectManager::getCaster(EffectCasterBase *caster) {
  for (u32 i = 0; i < LAYER_MAX; i++) {
    mm::mtl::IntrusiveList<EffectCasterSend> &casters = casterGroups[i].casters;
    for (mm::mtl::IntrusiveList<EffectCasterSend>::iterator it = casters.begin(); it != casters.end(); ++it) {
      if (it.get()->caster == caster) {
        return it.get();
      }
    }
  }

  return nullptr;
}

void EffectManager::remove(EffectCasterBase *caster) { effect::SystemManager::getPtr()->es_remove_cas(getCaster(caster)); }

void EffectManager::changeLayerCaster(EffectCasterBase *caster, u32 layer, u32 newLayer) {
  mm::mtl::IntrusiveList<EffectCasterSend> &casters = casterGroups[layer].casters;
  for (mm::mtl::IntrusiveList<EffectCasterSend>::iterator it = casters.begin(); it != casters.end(); ++it) {
    if (it.get()->caster == caster) {
      EffectCasterSend *send = it.get();
      casters.erase(it);
      casterGroups[newLayer].casters.push_back(send);
      return;
    }
  }
}

void EffectManager::sendCaster(EffectCasterBase *caster, mm::Mat44 &matrix, const char *name, int index) {
  for (u32 i = 0; i < LAYER_MAX; i++) {
    mm::mtl::IntrusiveList<EffectCasterSend> &casters = casterGroups[i].casters;
    for (mm::mtl::IntrusiveList<EffectCasterSend>::iterator it = casters.begin(); it != casters.end(); ++it) {
      if (it.get()->caster == caster) {
        it.get()->sendData(matrix, name, index);
        return;
      }
    }
  }
}

void EffectManager::sendCaster(EffectCasterBase *caster, f32 scale) {
  for (u32 i = 0; i < LAYER_MAX; i++) {
    mm::mtl::IntrusiveList<EffectCasterSend> &casters = casterGroups[i].casters;
    for (mm::mtl::IntrusiveList<EffectCasterSend>::iterator it = casters.begin(); it != casters.end(); ++it) {
      if (it.get()->caster == caster) {
        EffectCasterSend *send = it.get();
        if (send->caster != nullptr && effect::SystemManager::getPtr() != nullptr) {
          send->scales[effect::SystemManager::getPtr()->writeBuffer != 0] = scale;
        }
        return;
      }
    }
  }
}

void EffectManager::sendCasterFrame(EffectCasterBase *caster, f32 frame) {
  for (u32 i = 0; i < LAYER_MAX; i++) {
    mm::mtl::IntrusiveList<EffectCasterSend> &casters = casterGroups[i].casters;
    for (mm::mtl::IntrusiveList<EffectCasterSend>::iterator it = casters.begin(); it != casters.end(); ++it) {
      if (it.get()->caster == caster) {
        EffectCasterSend *send = it.get();
        if (send->caster != nullptr && effect::SystemManager::getPtr() != nullptr) {
          send->frames[effect::SystemManager::getPtr()->writeBuffer != 0] = frame;
        }
        return;
      }
    }
  }
}

void EffectManager::sendCasterStateName(EffectCasterBase *caster, const char *name) {
  for (u32 i = 0; i < LAYER_MAX; i++) {
    mm::mtl::IntrusiveList<EffectCasterSend> &casters = casterGroups[i].casters;
    for (mm::mtl::IntrusiveList<EffectCasterSend>::iterator it = casters.begin(); it != casters.end(); ++it) {
      if (it.get()->caster == caster) {
        it.get()->sendDataStateName(name);
        return;
      }
    }
  }
}

EffectCasterSend *EffectManager::getCasterCB(EffectCasterBase *caster) { return getCaster(caster); }

void EffectManager::setIBLSaturation(f32 saturation) { effect::SystemManager::getPtr()->setIBLSaturation(saturation); }

void EffectManager::setDirScale(f32 scale) { effect::SystemManager::getPtr()->setDirScale(scale); }

void EffectManager::setSpecScale(f32 scale) { effect::SystemManager::getPtr()->setSpecScale(scale); }

void EffectManager::setResponsiveAA(f32 responsiveAA) { effect::SystemManager::getPtr()->setResponsiveAA(responsiveAA); }

void EffectManager::setAllDisp(bool isDisp) { effect::SystemManager::getPtr()->setAllDisp(isDisp); }

void EffectManager::setDisableCollision(bool isDisable) { effect::SystemManager::getPtr()->setDisableCollision(isDisable); }

u32 EffectManager::create(const char *name, EffectPack *pack, bool isLoop) {
  void *data = search(name, pack);
  if (data == nullptr) {
    return 0;
  }

  return create(data, isLoop);
}

void *EffectManager::search(const char *name, EffectPack *pack) {
  if (pack != nullptr) {
    void *data = pack->searchEfb(name);
    if (data != nullptr) {
      return data;
    }
  }

  return seachAssetEffectHandle(name);
}

u32 EffectManager::create(void *data, bool isLoop) {
  if (effect::SystemManager::getPtr() == nullptr) {
    return 0;
  }

  return effect::SystemManager::getPtr()->es_create(data, isLoop);
}

u32 EffectManager::create(void *data, const effect::SendParam *param, bool isLoop) { return effect::SystemManager::getPtr()->es_create(data, param, isLoop); }

void EffectManager::kill(u32 handle) {
  if (handle != 0) {
    effect::SystemManager::getPtr()->es_fade_core(nullptr, handle, 1);
  }
}

void EffectManager::remove(u32 handle) {
  if (handle != 0) {
    effect::SystemManager::getPtr()->es_fade_core(nullptr, handle, -1);
  }
}

void EffectManager::dead(u32 handle) { effect::SystemManager::getPtr()->es_fade_core(nullptr, handle, 0); }

void EffectManager::fadeOutDead(u32 handle) {
  if (handle != 0) {
    effect::SystemManager::getPtr()->es_fade_core(nullptr, handle, 1);
  }
}

void EffectManager::fadeOutDead(u32 handle, u32 frame) {
  if (handle != 0) {
    effect::SystemManager::getPtr()->es_fade_core(nullptr, handle, frame);
  }
}

void EffectManager::setDisp(u32 handle, bool isDisp) {
  if (handle != 0) {
    effect::SystemManager::getPtr()->es_set_disp(handle, isDisp);
  }
}

void EffectManager::setAlpha(u32 handle, f32 alpha) {
  if (handle != 0) {
    effect::SystemManager::getPtr()->es_set_alpha(handle, alpha);
  }
}

void EffectManager::setSpeed(u32 handle, f32 speed) {
  if (handle != 0) {
    effect::SystemManager::getPtr()->es_set_speed(handle, speed);
  }
}

void EffectManager::setCategory(u32 handle, EF_CATEGORY category) {
  if (handle != 0) {
    effect::SystemManager::getPtr()->es_set_category(handle, category);
  }
}

void EffectManager::setViewnum(u32 handle, u32 viewnum) {
  if (handle != 0) {
    effect::SystemManager::getPtr()->es_set_viewnum(handle, viewnum);
  }
}

void EffectManager::setParamPosOnly(u32 handle, const effect::SendParam *param) {
  if (handle != 0) {
    effect::SystemManager::getPtr()->es_set_param_pos_only(handle, param);
  }
}

void EffectManager::setParamPosOnly2(u32 handle, const effect::SendParam *param) {
  if (handle != 0) {
    effect::SystemManager::getPtr()->es_set_param_pos_only2(handle, param);
  }
}

void EffectManager::setParam(u32 handle, const effect::SendParam *param) {
  if (handle != 0) {
    effect::SystemManager::getPtr()->es_set_param(handle, param);
  }
}

void EffectManager::setSignal(u32 handle) {
  if (handle != 0) {
    effect::SystemManager::getPtr()->es_fade_core(nullptr, handle, 1);
  }
}

bool EffectManager::isExist(u32 handle) { return effect::SystemManager::getPtr()->es_isalive(handle) > 0; }

bool EffectManager::getDeadFlag(u32 handle) { return effect::SystemManager::getPtr()->es_getDeadFlag(handle); }

bool EffectManager::isLoop(void *data) const { return effect::SystemManager::getPtr()->es_is_loop(data); }

bool EffectManager::isLoop(const char *name, EffectPack *pack) const { return isLoop(get()->search(name, pack)); }

bool EffectManager::containsCamAxis(void *data) const { return effect::SystemManager::getPtr()->es_contais_cam_axis(data); }

bool EffectManager::containsCamAxis(const char *name, EffectPack *pack) const { return containsCamAxis(get()->search(name, pack)); }

void *EffectManager::seachAssetEffectHandle(const char *name) {
  CommonEffect *end = commonEffects.end();
  for (CommonEffect *it = commonEffects.begin(); it != end; ++it) {
    if (it->pack != nullptr) {
      void *data = it->pack->searchEfb(name);
      if (data != nullptr) {
        return data;
      }
    }
  }

  return nullptr;
}

void *EffectManager::effectAllocSys(void *user, u32 size, u32 alignment, const char *name, u32 line) { return mtl::MemManager::allocate(get()->sysHandle, size, alignment, false, "no name", 0); }

void EffectManager::effectFreeSys(void *user, void *pointer) { mtl::MemManager::deallocate(pointer, 0, false); }

void *EffectManager::effectAllocRes(void *user, u32 size, u32 alignment, const char *name, u32 line) { return mtl::MemManager::allocate(get()->resHandle, size, alignment, false, "no name", 0); }

void EffectManager::effectFreeRes(void *user, void *pointer) { mtl::MemManager::deallocate(pointer, 0, false); }

mtl::ALLOC_HANDLE EffectManager::effectSysHandle() { return get()->sysHandle; }

mtl::ALLOC_HANDLE EffectManager::effectResHandle() { return get()->resHandle; }

void EffectManager::debugReadFileEnd(void *data) {
  if (data != nullptr) {
    mtl::MemManager::deallocate(data, 0, false);
  }
}

void EffectManager::debugOutputString(const char *string) {}

void EffectManager::warnOutputString(const char *string) {}

void *EffectManager::createMdl(const void *data, const char *name, int index, const void *group, int groupIndex) {
  ml::DrMdlObj *model = nullptr;
  if (group != nullptr && Framework::get() != nullptr) {
    model = static_cast<ml::DrMdoGrpObj *>(const_cast<void *>(group))->createInstantMdl(data, name, groupIndex);
    model->setMatrix(mm::Mat44::identity);
    model->setDisp(true);
    model->setOcclusionQuery(false);
  }

  return model;
}

void EffectManager::deleteMdl(void *model) {
  if (model != nullptr && Framework::get() != nullptr) {
    ml::DrMdlObj *object = static_cast<ml::DrMdlObj *>(model);
    object->setDisp(false);
    object->setDeleteCall(ml::DrMan::s_nDblStockIdx);
  }
}

void EffectManager::deleteLgt(u32 type, void *light) {
  if (light == nullptr || Framework::get() == nullptr) {
    return;
  }

  ml::DrMan *drMan = ml::DrMan::getIns();
  if (drMan == nullptr) {
    return;
  }

  ml::DrLightMan *lightMan = drMan->unknown588;
  if (lightMan == nullptr) {
    return;
  }

  switch (type) {
  case 1:
    lightMan->releaseInstantPntLight(static_cast<ml::DrLightObjPnt *>(light));
    break;
  case 2:
    lightMan->releaseInstantSptLight(static_cast<ml::DrLightObjSpt *>(light));
    break;
  }
}

void EffectManager::setMdlPos(void *model, void *position) {
  if (model != nullptr && position != nullptr) {
    static_cast<ml::DrMdlObj *>(model)->setOffsetPos(*static_cast<mm::Vec3 *>(position));
  }
}

void EffectManager::setMdlMatrix(void *model, void *matrix) {
  if (model != nullptr && matrix != nullptr) {
    static_cast<ml::DrMdlObj *>(model)->setMatrix(*static_cast<mm::Mat44 *>(matrix));
  }
}

void EffectManager::setMdlAlpha(void *model, f32 alpha) {
  if (model != nullptr) {
    static_cast<ml::DrMdlObj *>(model)->setAlpha(alpha);
  }
}

void EffectManager::setMdlSpeed(void *model, void *speed) {
  if (model != nullptr && speed != nullptr) {
    static_cast<ml::DrMdlObj *>(model)->setFrameSpd(*static_cast<f32 *>(speed));
  }
}

void EffectManager::setLgtPos(u32 type, void *light, void *position) {
  if (Framework::get() != nullptr && light != nullptr && position != nullptr) {
    ml::DrMan *drMan = ml::DrMan::getIns();
    if (drMan != nullptr && drMan->unknown588 != nullptr) {
      switch (type) {
      case 1:
        static_cast<ml::DrLightObjPnt *>(light)->setPos(*static_cast<mm::Vec3 *>(position));
        break;
      case 2:
        static_cast<ml::DrLightObjSpt *>(light)->setPos(*static_cast<mm::Vec3 *>(position));
        break;
      }
    }
  }
}

void EffectManager::setLgtMatrix(u32 type, void *light, void *matrix) {
  if (Framework::get() != nullptr && light != nullptr && matrix != nullptr) {
    ml::DrMan *drMan = ml::DrMan::getIns();
    if (drMan != nullptr && drMan->unknown588 != nullptr) {
      switch (type) {
      case 1:
        static_cast<ml::DrLightObjPnt *>(light)->setMat(*static_cast<mm::Mat44 *>(matrix));
        break;
      case 2:
        static_cast<ml::DrLightObjSpt *>(light)->setMat(*static_cast<mm::Mat44 *>(matrix));
        break;
      }
    }
  }
}

void *EffectManager::createGroup(int num, int flags) {
  if (Framework::get() == nullptr) {
    return nullptr;
  }

  ml::DrCreator creator;
  return creator.createInstantGrp(num, flags);
}

void EffectManager::destroyGroup(void *group) {
  if (group != nullptr && Framework::get() != nullptr) {
    static_cast<ml::DrMdlBase *>(group)->setDeleteCall(ml::DrMan::s_nDblStockIdx);
  }
}

bool EffectManager::isEfSystemValid() { return effect::SystemManager::isValid(); }

u32 EffectManager::getEmitterForm(u32 handle) {
  if (effect::SystemManager::getPtr() == nullptr) {
    return 0;
  }

  return effect::SystemManager::getPtr()->getEmitterForm(handle);
}

void EffectManager::getNumDetail(u32 &emitterNum, u32 &particleNum, u32 &drawNum, u32 &workNum) {
  if (effect::SystemManager::isValid()) {
    effect::SystemManager::getPtr()->getNumDetail(emitterNum, particleNum, drawNum, workNum);
  }
}

bool *EffectManager::getDispPTex() {
  static bool dummy;
  if (effect::SystemManager::getPtr() == nullptr) {
    return &dummy;
  }

  return &effect::SystemManager::getPtr()->dispParticleTexture;
}

bool *EffectManager::getWorkTex() {
  static bool dummy;
  if (effect::SystemManager::getPtr() == nullptr) {
    return &dummy;
  }

  return &effect::SystemManager::getPtr()->workTexture;
}

bool EffectManager::getDispEmitter() {
  if (effect::SystemManager::getPtr() == nullptr) {
    return false;
  }

  return effect::SystemManager::getPtr()->dispEmitter;
}

void EffectManager::setDispEmitter(bool isDisp) {
  if (effect::SystemManager::getPtr() != nullptr) {
    effect::SystemManager *system = effect::SystemManager::getPtr();
    system->isDispEmitterSet = true;
    system->dispEmitter = isDisp;
  }
}

bool EffectManager::isOldVersion() { return false; }

void EffectManager::setOldVersion(bool isOldVersion) {}

bool EffectManager::isDebugShader() { return false; }

void EffectManager::setDebugShader(bool isDebugShader) {}

bool EffectManager::isPerfMonitoring() { return false; }

void EffectManager::memoryDump() {
  mtl::MemManager::log(get()->sysHandle, true, nullptr);
  mtl::MemManager::log(get()->resHandle, true, nullptr);
  if (effect::SystemManager::getPtr() != nullptr) {
    effect::SystemManager::getPtr()->memoryDump();
  }
}

u32 EffectManager::createHateRing() { return create("cmn_000_000", nullptr, true); }

void EffectManager::destroyHateRing(u32 handle) { remove(handle); }

u32 EffectManager::createHateRingVec() { return create("cmn_000_001", nullptr, true); }

void EffectManager::destroyHateRingVec(u32 handle) { remove(handle); }

u32 EffectManager::createHateArrow() { return create("cmn_000_002", nullptr, true); }

void EffectManager::destroyHateArrow(u32 handle) { remove(handle); }

u32 EffectManager::createComboBall(u32 level) {
  if (level == 0) {
    return 0;
  }

  mm::mtl::FixStr<32> name;
  name.format("cmn_010_%03d", level - 1);
  return create(name.c_str(), nullptr, true);
}

void EffectManager::destroyComboBall(u32 handle) { kill(handle); }

void EffectManager::setPerfLoggingCsv(bool isLogging) {}

void EffectManager::begin() {
  if (isFinalized()) {
    return;
  }

  if (effect::SystemManager::getPtr() != nullptr) {
    effect::SystemManager::getPtr()->begin();
  }
}

void EffectManager::end() {
  if (isFinalized()) {
    return;
  }

  if (effect::SystemManager::getPtr() != nullptr) {
    effect::SystemManager::getPtr()->end();
  }
}

void EffectManager::opacityRender(const ml::IDrDrawWorkInfo *info) {
  if (isFinalized() || finalizing) {
    return;
  }

  if (effect::SystemManager::getPtr() != nullptr) {
    effect::SystemManager::getPtr()->opacityRender(reinterpret_cast<const ptlib::DrDrawWorkInfoEF *>(info));
  }
}

void EffectManager::alphaRender(const ml::IDrDrawWorkInfo *info) {
  if (isFinalized() || finalizing) {
    return;
  }

  if (effect::SystemManager::getPtr() != nullptr) {
    effect::SystemManager::getPtr()->alphaRender(reinterpret_cast<const ptlib::DrDrawWorkInfoEF *>(info));
  }
}

void EffectManager::lastRender(const ml::IDrDrawWorkInfo *info) {
  if (isFinalized() || finalizing) {
    return;
  }

  if (effect::SystemManager::getPtr() != nullptr) {
    effect::SystemManager::getPtr()->lastRender(reinterpret_cast<const ptlib::DrDrawWorkInfoEF *>(info));
  }
}

void EffectManager::blurRender(const ml::IDrDrawWorkInfo *info) {
  if (isFinalized() || finalizing) {
    return;
  }

  if (effect::SystemManager::getPtr() != nullptr) {
    effect::SystemManager::getPtr()->blurRender(reinterpret_cast<const ptlib::DrDrawWorkInfoEF *>(info));
  }
}

void EffectManager::finalRender(const ml::IDrDrawWorkInfo *info) {
  if (isFinalized() || finalizing) {
    return;
  }

  if (effect::SystemManager::getPtr() != nullptr) {
    effect::SystemManager::getPtr()->finalRender(reinterpret_cast<const ptlib::DrDrawWorkInfoEF *>(info));
  }
}

} // namespace fw
