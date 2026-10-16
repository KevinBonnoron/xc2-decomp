#include "framework/framework.h"

#include "framework/applet.h"
#include "framework/manager_register.h"
#include "framework/memory/framework_memory.h"
#include "ml/work_cpu.h"
#include "mm_mtl/algorithm.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

Framework::~Framework() { destroyManager(); }

void Framework::finalize() { destroyManager(); }

mm::mtl::IAllocator *Framework::getAllocator() {
  Framework *framework = get();
  return framework == nullptr ? nullptr : &framework->allocator;
}

bool Framework::finalizeManager() {
  bool isFinalized = ManagerRegister::get()->finalize();
  state = isFinalized ? STATE_FINALIZED : STATE_FINALIZING;
  return isFinalized;
}

void Framework::prepareEnter() { state = STATE_ENTERED; }

void Framework::prepareExit() {}

void Framework::pauseEnter() {}

void Framework::pauseExit() {}

void Framework::activate() {
  for (IPauseTrigger *trigger : pauseTriggers) {
    trigger->activate();
  }
}

void Framework::deactivate() {
  for (IPauseTrigger *trigger : pauseTriggers) {
    trigger->deactivate();
  }
}

void Framework::endFrame(const UpdateState &updateState) {}

void Framework::preUpdate() {
  if (isUpdating() && applet != nullptr) {
    applet->preUpdate(updateInfo);
  }
}

bool Framework::canUpdate() {
  Framework *framework = get();
  if (framework == nullptr) {
    return false;
  }

  return framework->state == STATE_ENTERED;
}

void Framework::render() {}

Applet *Framework::getApplet() const { return applet; }

bool Framework::isAppletClosed() {
  if (applet == nullptr) {
    return false;
  }

  return applet->closed;
}

void Framework::destroyApplet() {
  if (applet != nullptr) {
    applet->finalize(*this);
    if (applet != nullptr) {
      delete applet;
      applet = nullptr;
    }
  }
}

void Framework::enterFinalizeApplet() { ManagerRegister::get()->enterFinalizeApplet(); }

bool Framework::isInitialized() {
  Framework *framework = get();
  if (framework == nullptr) {
    return false;
  }

  return framework->state >= STATE_MANAGER_INITIALIZED && framework->state <= STATE_ENTERED;
}

mtl::ALLOC_HANDLE Framework::getMemHandle() {
  Framework *framework = get();
  if (framework == nullptr) {
    return mtl::ALLOC_HANDLE();
  }

  if (framework->memHandle.isValid()) {
    return framework->memHandle;
  }

  return FrameworkMemory::getMem(5);
}

void Framework::setPause(bool isPause) {
  Framework *framework = get();
  if (framework != nullptr && framework->launcher != nullptr) {
    framework->launcher->setDebugPause(isPause);
  }
}

bool Framework::isPause() {
  Framework *framework = get();
  if (framework != nullptr && framework->launcher != nullptr) {
    return framework->launcher->isDebugPause();
  }

  return false;
}

void Framework::stepPause() {
  Framework *framework = get();
  if (framework != nullptr && framework->launcher != nullptr) {
    framework->launcher->stepDebugPause();
  }
}

bool Framework::reqSoftReset() {
  Framework *framework = get();
  if (framework != nullptr && framework->launcher != nullptr) {
    return framework->launcher->resetApp();
  }

  return false;
}

void Framework::setUpdateSpeed(f32 speed) {
  Framework *framework = get();
  if (framework != nullptr) {
    framework->updateSpeed = speed;
  }
}

void Framework::setLayerUpdateSpeed(u32 layer, f32 speed) {
  Framework *framework = get();
  if (framework != nullptr) {
    framework->layers[layer].speed = speed;
  }
}

f32 Framework::getLayerUpdateSpeed(u32 layer) {
  Framework *framework = get();
  if (framework != nullptr) {
    return framework->layers[layer].frameSpeed;
  }

  return 1.0f;
}

void Framework::setLayerPause(u32 layer, bool isPause) {
  Framework *framework = get();
  if (framework != nullptr) {
    framework->layers[layer].pause = isPause;
  }
}

bool Framework::isLayerPause(u32 layer) {
  Framework *framework = get();
  if (framework != nullptr) {
    return framework->layers[layer].framePause;
  }

  return false;
}

u32 Framework::getFrameCount() { return ml::WorkCpu::getFrameCount(); }

const UpdateInfo *Framework::getUpdateInfo() {
  Framework *framework = get();
  return framework == nullptr ? nullptr : &framework->updateInfo;
}

void Framework::addPauseCallback(IPauseTrigger *trigger) {
  if (trigger == nullptr) {
    return;
  }

  Framework *framework = get();
  if (framework == nullptr) {
    return;
  }

  if (mm::mtl::find(framework->pauseTriggers.begin(), framework->pauseTriggers.end(), trigger) != framework->pauseTriggers.end()) {
    return;
  }

  framework->pauseTriggers.push_back(trigger);
}

void Framework::removePauseCallback(IPauseTrigger *trigger) {
  Framework *framework = get();
  if (framework == nullptr) {
    return;
  }

  IPauseTrigger **found = mm::mtl::find(framework->pauseTriggers.begin(), framework->pauseTriggers.end(), trigger);
  if (found != framework->pauseTriggers.end()) {
    framework->pauseTriggers.erase(found);
  }
}

IPauseTrigger::IPauseTrigger() { Framework::addPauseCallback(this); }

IPauseTrigger::~IPauseTrigger() { Framework::removePauseCallback(this); }

} // namespace fw
