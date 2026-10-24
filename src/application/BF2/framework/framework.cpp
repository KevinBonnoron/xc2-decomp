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
  return framework == nullptr ? nullptr : &framework->unknown3a0;
}

bool Framework::finalizeManager() {
  bool isFinalized = ManagerRegister::get()->finalize();
  unknown84 = isFinalized ? STATE_FINALIZED : STATE_FINALIZING;
  return isFinalized;
}

void Framework::prepareEnter() { unknown84 = STATE_ENTERED; }

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

void Framework::endFrame(const UpdateState &updateState) {}

void Framework::preUpdate() {
  if (isUpdating() && m_applet != nullptr) {
    m_applet->preUpdate(unknown78);
  }
}

bool Framework::canUpdate() {
  Framework *framework = get();
  if (framework == nullptr) {
    return false;
  }

  return framework->unknown84 == STATE_ENTERED;
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

  return framework->unknown84 >= STATE_MANAGER_INITIALIZED && framework->unknown84 <= STATE_ENTERED;
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
