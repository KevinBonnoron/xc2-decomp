#include "framework/framework.h"

#include "framework/anim/anim_manager.h"
#include "framework/applet.h"
#include "framework/asset/asset_manager.h"
#include "framework/coli/coli_manager.h"
#include "framework/dynamics/dynamics_manager.h"
#include "framework/effect/effect_manager.h"
#include "framework/lang_util.h"
#include "framework/layer/layerset_manager.h"
#include "framework/manager_register.h"
#include "framework/memory/framework_memory.h"
#include "framework/message/message_manager.h"
#include "framework/model/model_manager.h"
#include "framework/movie/movie_manager.h"
#include "framework/navi/navi_manager.h"
#include "framework/object/updatable_manager.h"
#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "framework/render/light_manager.h"
#include "framework/render/render_param.h"
#include "framework/resource/resource_manager.h"
#include "framework/script/script_manager.h"
#include "framework/sensor/sensor_manager.h"
#include "framework/sound/sound_layer_manager.h"
#include "framework/sound/sound_manager.h"
#include "framework/wind/wind_manager.h"
#include "fw/fw_bdat_manager.h"
#include "fw/fw_camera.h"
#include "fw/fw_pad.h"
#include "fw/fw_param_manager.h"
#include "ml/ml_mem.h"
#include "ml/scn.h"
#include "ml/work_cpu.h"
#include "ml/work_root.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixstr.h"
#include "mtl/mem_manager.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

Framework::Framework()
    : m_applet(nullptr), unknown50(nullptr), unknown58(nullptr), unknown60(nullptr), unknown70(nullptr), unknown84(STATE_UNKNOWN_0), unknown88(false), unknown89(false), unknown8a(false),
      unknown8c(1.0f) {}

Framework::~Framework() { destroyManager(); }

void Framework::createMemorySection() {
  MemorySectionInfo info;
  info.unknown00 = 6;
  info.unknown04 = ml::MlMem::getProductMem();
  info.unknown08 = 0x2600000;
  info.unknown10 = 0x1000;
  info.unknown14 = true;
  info.unknown18 = "fw::SoundCommon";
  info.unknown5c = mtl::ALLOCATOR_TYPE_UNKNOWN_1;
  FrameworkMemory::get().createSection(info);

  info.unknown00 = 8;
  info.unknown04 = ml::MlMem::getProductMem();
  info.unknown08 = 0x2800000;
  info.unknown10 = 0x1000;
  info.unknown14 = true;
  info.unknown18 = "fw::SoundPool";
  info.unknown5c = mtl::ALLOCATOR_TYPE_UNKNOWN_1;
  FrameworkMemory::get().createSection(info);

  info.unknown00 = 7;
  info.unknown04 = ml::MlMem::getProductMem();
  info.unknown08 = 0x4900000;
  info.unknown10 = 0x20;
  info.unknown14 = true;
  info.unknown18 = "fw::SoundProc";
  info.unknown5c = mtl::ALLOCATOR_TYPE_UNKNOWN_1;
  FrameworkMemory::get().createSection(info);

  info.unknown00 = 9;
  info.unknown04 = ml::MlMem::getProductMem();
  info.unknown08 = 0x4400000;
  info.unknown10 = 0x1000;
  info.unknown14 = false;
  info.unknown18 = "fw::Movie";
  info.unknown5c = mtl::ALLOCATOR_TYPE_UNKNOWN_1;
  FrameworkMemory::get().createSection(info);
}

void Framework::finalize() { destroyManager(); }

// __LINE__ of each operator new must be the one of the original source: it changes the encoding of the argument.
void Framework::createManager() {
  mm::mtl::IAllocator *allocator = getAllocator();
#line 248
  new (allocator, 16, __FILE__, __LINE__) ManagerRegister();
  LangUtil::initialize();
  RenderParam::initialize();
#line 263
  new (allocator, 16, __FILE__, __LINE__) AssetManager(allocator, unknown10.unknown20);
  if ((unknown10.unknown00 & 0x20) != 0) {
#line 268
    new (allocator, 16, __FILE__, __LINE__) CameraManager(unknown58);
  }
#line 272
  new (allocator, 16, __FILE__, __LINE__) ModelManager();
#line 275
  new (allocator, 16, __FILE__, __LINE__) AnimationManager();
#line 278
  new (allocator, 16, __FILE__, __LINE__) DyanmicsManager();
#line 281
  new (allocator, 16, __FILE__, __LINE__) TransformManager();
#line 284
  new (allocator, 16, __FILE__, __LINE__) MessageManager(allocator);
#line 287
  new (allocator, 16, __FILE__, __LINE__) UpdatableObjectManager(allocator, unknown10.unknown30);
#line 290
  new (allocator, 16, __FILE__, __LINE__) ResourceManager(allocator, unknown10.unknown2c);
  ResourceManager::setMemTMP(ml::WorkRoot::getMemTMP());
#line 296
  new (allocator, 16, __FILE__, __LINE__) PadManager();
#line 299
  new (allocator, 16, __FILE__, __LINE__) BdatManager(allocator);
#line 303
  new (allocator, 16, __FILE__, __LINE__) ScriptManager(allocator, unknown10.unknown34);
#line 306
  new (allocator, 16, __FILE__, __LINE__) ColiManager(allocator, 0x1000);
#line 309
  new (allocator, 16, __FILE__, __LINE__) NaviManager();
#line 312
  new (allocator, 16, __FILE__, __LINE__) LightManager();
#line 315
  new (allocator, 16, __FILE__, __LINE__) LayerSetManager();
#line 322
  new (allocator, 16, __FILE__, __LINE__) SoundManager(allocator);
#line 327
  new (allocator, 16, __FILE__, __LINE__) EffectManager(allocator, unknown10.unknown28, unknown58);
#line 331
  new (allocator, 16, __FILE__, __LINE__) MovieManager();
#line 334
  new (allocator, 16, __FILE__, __LINE__) ParamManager();
#line 336
  new (allocator, 16, __FILE__, __LINE__) WindManager();
#line 338
  new (allocator, 16, __FILE__, __LINE__) SoundLayerManager();
#line 340
  new (allocator, 16, __FILE__, __LINE__) SensorManager();
}

mm::mtl::IAllocator *Framework::getAllocator() {
  Framework *framework = get();
  return framework == nullptr ? nullptr : &framework->unknown3a0;
}

bool Framework::initializeManager() {
  UpdateInfo info = {0.0f, 0.0f, 0.0f};
  BdatManager::get()->update(info);
  ResourceManager::get()->update(info);
  if (ManagerRegister::get()->initialize() && BdatManager::isEnableBdat(0) && BdatManager::isEnableBdat(1) && EffectManager::get()->isCommonLoaded() && SoundManager::get()->isCommonLoaded() &&
      SoundManager::get()->isBattleLoaded()) {
    PadManager::initVibData();
    unknown84 = STATE_UNKNOWN_2;
    return true;
  }

  return false;
}

void Framework::destroyManager() {
  delete SensorManager::get();
  delete SoundLayerManager::get();
  delete WindManager::get();
  delete ParamManager::get();
  delete MovieManager::get();
  delete EffectManager::get();
  delete ScriptManager::get();
  delete UpdatableObjectManager::get();
  delete MessageManager::get();
  delete ResourceManager::get();
  delete ColiManager::get();
  delete LayerSetManager::get();
  delete LightManager::get();
  delete DyanmicsManager::get();
  delete AnimationManager::get();
  delete ModelManager::get();
  delete NaviManager::get();
  delete CameraManager::get();
  delete AssetManager::get();
  delete TransformManager::get();
  delete PadManager::get();
  delete BdatManager::get();
  delete SoundManager::get();
  RenderParam::finalize();
  delete ManagerRegister::get();
  get()->unknown58->renderStop();
}

bool Framework::finalizeManager() {
  bool isFinalized = ManagerRegister::get()->finalize();
  unknown84 = isFinalized ? STATE_UNKNOWN_5 : STATE_UNKNOWN_4;
  return isFinalized;
}

void Framework::prepareEnter() { unknown84 = STATE_UNKNOWN_3; }

void Framework::prepareExit() {}

void Framework::pauseEnter() {}

void Framework::pauseExit() {}

void Framework::activate() {
  for (IPauseTrigger *trigger : unknown298) {
    trigger->activate();
  }
}

void Framework::deactivate() {
  for (IPauseTrigger *trigger : unknown298) {
    trigger->deactivate();
  }
}

void Framework::beginFrame(const UpdateState &updateState) {
  if (updateState.isPause) {
    unknown78.unknown00 = 1.0f / unknown10.unknown04;
    unknown78.unknown08 = 0.0f;
    unknown78.unknown04 = unknown78.unknown00 * unknown78.unknown08;
    for (u32 i = 0; i < LAYER_UNKNOWN_32; i++) {
      unknown98[i].unknown04 = 0.0f;
    }
  } else {
    f32 speed = unknown8c;
    if (__builtin_fabsf(speed - unknown78.unknown08) > 0.000001f) {
      unknown78.unknown08 = speed;
      unknown78.unknown00 = 1.0f / unknown10.unknown04;
      unknown78.unknown04 = speed * unknown78.unknown00;
    }
    for (u32 i = 0; i < LAYER_UNKNOWN_32; i++) {
      unknown98[i].unknown08 = unknown98[i].unknown00;
      unknown98[i].unknown04 = unknown98[i].unknown00 * unknown78.unknown08;
      unknown98[i].unknown0d = unknown98[i].unknown0c;
    }
  }

  if (isUpdating() && SoundManager::get() != nullptr) {
    SoundManager::get()->update(unknown78);
  }
}

void Framework::endFrame(const UpdateState &updateState) {}

void Framework::preUpdate() {
  if (isUpdating() && m_applet != nullptr) {
    m_applet->preUpdate(unknown78);
  }
}

void Framework::update() {
  if (!isUpdating()) {
    return;
  }

  if (ResourceManager::get() != nullptr) {
    ResourceManager::get()->update(unknown78);
  }
  if (ScriptManager::get() != nullptr) {
    ScriptManager::get()->update(unknown78);
  }
  if (BdatManager::get() != nullptr) {
    BdatManager::get()->update(unknown78);
  }
  if (m_applet != nullptr && canUpdate()) {
    m_applet->update(unknown78);
  }
  if (ColiManager::get() != nullptr) {
    ColiManager::get()->update();
  }
  if (NaviManager::get() != nullptr) {
    NaviManager::get()->update();
  }
  if (WindManager::get() != nullptr) {
    WindManager::get()->update(unknown78);
  }

  for (u32 layer = 0; layer < unknown001; layer++) {
    u32 layerMask = 1 << layer;
    UpdateInfo info;
    info.unknown08 = unknown98[layer].unknown04;
    info.unknown00 = unknown78.unknown00;
    info.unknown04 = unknown78.unknown00 * unknown98[layer].unknown04;
    if (unknown98[layer].unknown0d) {
      if (AnimationManager::get() != nullptr) {
        AnimationManager::get()->applyPose(layerMask);
      }
    } else {
      if (AnimationManager::get() != nullptr) {
        AnimationManager::get()->updateControls(info, layerMask);
      }
      if (SensorManager::get() != nullptr) {
        SensorManager::get()->flushBeforeGame(info, layerMask);
      }
      if (UpdatableObjectManager::get() != nullptr) {
        UpdatableObjectManager::get()->update(info, layerMask);
      }
      if (AnimationManager::get() != nullptr) {
        AnimationManager::get()->samplePose(layerMask);
      }
      if (SensorManager::get() != nullptr) {
        SensorManager::get()->flushAfterAnimation(info, layerMask);
      }
      if (AnimationManager::get() != nullptr) {
        AnimationManager::get()->solveIK(info, layerMask);
      }
      DyanmicsManager *dynamicsManager = DyanmicsManager::get();
      if (dynamicsManager != nullptr) {
        dynamicsManager->updateColObjects(layerMask);
        dynamicsManager->updateDynamics(info, layerMask);
      }
      AnimationManager *animationManager = AnimationManager::get();
      if (animationManager != nullptr) {
        animationManager->applyPose(layerMask);
        animationManager->applyAfterModifyPose(layerMask);
      }
      if (TransformManager::get() != nullptr) {
        TransformManager::get()->update(layerMask);
      }
      if (ModelManager::get() != nullptr) {
        ModelManager::get()->update(info, layerMask);
      }
      if (EffectManager::get() != nullptr) {
        EffectManager::get()->updateLayer(info, layerMask);
      }
      if (SoundLayerManager::get() != nullptr) {
        SoundLayerManager::get()->update(layerMask);
      }
    }
  }

  for (u32 layer = 0; layer < unknown001; layer++) {
    u32 layerMask = 1 << layer;
    UpdateInfo info;
    info.unknown08 = unknown98[layer].unknown04;
    info.unknown00 = unknown78.unknown00;
    info.unknown04 = unknown78.unknown00 * unknown98[layer].unknown04;
    if (unknown98[layer].unknown0d) {
      info.unknown08 = 0.0f;
    }
    if (EffectManager::get() != nullptr) {
      EffectManager::get()->updateLayerPost(info, layerMask);
    }
  }

  if (UpdatableObjectManager::get() != nullptr) {
    ObjectEvent event = {OBJECT_EVENT_UNKNOWN_0};
    UpdatableObjectManager::get()->execEvent(event, (1 << unknown001) - 1);
  }
  if (EffectManager::get() != nullptr) {
    EffectManager::get()->update(unknown78);
  }
  if (CameraManager::get() != nullptr) {
    CameraManager::get()->update(unknown78);
  }
  if (MovieManager::get() != nullptr) {
    MovieManager::get()->update();
  }
  if (MessageManager::get() != nullptr) {
    MessageManager::get()->update(unknown78);
  }
  unknown8a = true;
}

bool Framework::canUpdate() {
  Framework *framework = get();
  if (framework == nullptr) {
    return false;
  }

  return framework->unknown84 == STATE_UNKNOWN_3;
}

void Framework::tail(const UpdateState &updateState) {
  if (!isUpdating()) {
    return;
  }

  if (m_applet != nullptr && canUpdate() && !updateState.isPause) {
    m_applet->tail(unknown78);
  }
  UpdatableObjectManager *updatableManager = UpdatableObjectManager::get();
  if (updatableManager != nullptr && !updateState.isPause) {
    updatableManager->tail(unknown78);
  }
  if (ColiManager::get() != nullptr) {
    ColiManager::get()->tail();
  }
  if (NaviManager::get() != nullptr) {
    NaviManager::get()->tail();
  }
  if (LayerSetManager::get() != nullptr) {
    LayerSetManager::get()->tail();
  }
  EffectManager *effectManager = EffectManager::get();
  if (effectManager != nullptr) {
    effectManager->tail(unknown78, updateState.isPause);
  }
}

void Framework::render() {}

Applet *Framework::getApplet() const { return m_applet; }

bool Framework::isAppletClosed() {
  if (m_applet == nullptr) {
    return false;
  }

  return m_applet->unknown08;
}

void Framework::destroyApplet() {
  if (m_applet != nullptr) {
    m_applet->finalize(*this);
    if (m_applet != nullptr) {
      delete m_applet;
      m_applet = nullptr;
    }
  }
}

void Framework::enterFinalizeApplet() { ManagerRegister::get()->enterFinalizeApplet(); }

bool Framework::isInitialized() {
  Framework *framework = get();
  if (framework == nullptr) {
    return false;
  }

  return framework->unknown84 >= STATE_UNKNOWN_2 && framework->unknown84 <= STATE_UNKNOWN_3;
}

mtl::ALLOC_HANDLE Framework::getMemHandle() {
  Framework *framework = get();
  if (framework == nullptr) {
    return mtl::ALLOC_HANDLE();
  }

  if (framework->unknown68.isValid()) {
    return framework->unknown68;
  }

  return FrameworkMemory::getMem(5);
}

void Framework::setPause(bool isPause) {
  Framework *framework = get();
  if (framework != nullptr && framework->unknown70 != nullptr) {
    framework->unknown70->setDebugPause(isPause);
  }
}

bool Framework::isPause() {
  Framework *framework = get();
  if (framework != nullptr && framework->unknown70 != nullptr) {
    return framework->unknown70->isDebugPause();
  }

  return false;
}

void Framework::stepPause() {
  Framework *framework = get();
  if (framework != nullptr && framework->unknown70 != nullptr) {
    framework->unknown70->stepDebugPause();
  }
}

bool Framework::reqSoftReset() {
  Framework *framework = get();
  if (framework != nullptr && framework->unknown70 != nullptr) {
    return framework->unknown70->resetApp();
  }

  return false;
}

void Framework::setUpdateSpeed(f32 speed) {
  Framework *framework = get();
  if (framework != nullptr) {
    framework->unknown8c = speed;
  }
}

void Framework::setLayerUpdateSpeed(u32 layer, f32 speed) {
  Framework *framework = get();
  if (framework != nullptr) {
    framework->unknown98[layer].unknown00 = speed;
  }
}

f32 Framework::getLayerUpdateSpeed(u32 layer) {
  Framework *framework = get();
  if (framework != nullptr) {
    return framework->unknown98[layer].unknown08;
  }

  return 1.0f;
}

void Framework::setLayerPause(u32 layer, bool isPause) {
  Framework *framework = get();
  if (framework != nullptr) {
    framework->unknown98[layer].unknown0c = isPause;
  }
}

bool Framework::isLayerPause(u32 layer) {
  Framework *framework = get();
  if (framework != nullptr) {
    return framework->unknown98[layer].unknown0d;
  }

  return false;
}

u32 Framework::getFrameCount() { return ml::WorkCpu::getFrameCount(); }

const UpdateInfo *Framework::getUpdateInfo() {
  Framework *framework = get();
  return framework == nullptr ? nullptr : &framework->unknown78;
}

void Framework::addPauseCallback(IPauseTrigger *trigger) {
  if (trigger == nullptr) {
    return;
  }

  Framework *framework = get();
  if (framework == nullptr) {
    return;
  }

  if (mm::mtl::find(framework->unknown298.begin(), framework->unknown298.end(), trigger) != framework->unknown298.end()) {
    return;
  }

  framework->unknown298.push_back(trigger);
}

void Framework::removePauseCallback(IPauseTrigger *trigger) {
  Framework *framework = get();
  if (framework == nullptr) {
    return;
  }

  IPauseTrigger **found = mm::mtl::find(framework->unknown298.begin(), framework->unknown298.end(), trigger);
  if (found != framework->unknown298.end()) {
    framework->unknown298.erase(found);
  }
}

IPauseTrigger::IPauseTrigger() { Framework::addPauseCallback(this); }

IPauseTrigger::~IPauseTrigger() { Framework::removePauseCallback(this); }

} // namespace fw
