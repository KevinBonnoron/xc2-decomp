#include "apps/framework_launcher.h"

#include "framework/applet.h"
#include "framework/effect/effect_manager.h"
#include "framework/framework.h"
#include "framework/resource/resource_manager.h"
#include "ml/dev_keyboard.h"
#include "ml/micro_thread.h"
#include "ml/reslist.h"
#include "ml/scn.h"
#include "ml/win_view.h"
#include "mm_mtl/reference_object.h"
#include "scn/scn_render_dr_sys.h"

namespace nn {
namespace os {
struct FiberType;
} // namespace os
} // namespace nn

namespace apps {

void FrameworkLauncher::updatePause() {}

void FrameworkLauncher::rdkReaded(const char *name, void *data, int size) {}

bool FrameworkLauncher::wkStandbyLogin() { return WorkObj::wkStandbyLogin(); }

bool FrameworkLauncher::isDebugPause() const { return m_debugPause; }

ml::Scn *FrameworkLauncher::getScn() {
  FrameworkLauncher *launcher = get();
  if (launcher != nullptr) {
    return launcher->m_scn;
  }
  return nullptr;
}

ml::WinView *FrameworkLauncher::getView() {
  FrameworkLauncher *launcher = get();
  if (launcher != nullptr) {
    return launcher->m_view;
  }
  return nullptr;
}

fw::Applet *FrameworkLauncher::getApplet() {
  fw::Framework *framework = fw::Framework::get();
  if (framework != nullptr) {
    return framework->getApplet();
  }
  return nullptr;
}

SceneBuildInfo *FrameworkLauncher::getBuildInfo() {
  FrameworkLauncher *launcher = get();
  if (launcher != nullptr) {
    return &launcher->m_buildInfo;
  }
  return nullptr;
}

bool FrameworkLauncher::isInitialized() {
  FrameworkLauncher *launcher = get();
  if (launcher != nullptr) {
    return (launcher->unknown1c8 & FLAG_UNKNOWN_1) != 0;
  }
  return false;
}

bool FrameworkLauncher::isInitializing() {
  FrameworkLauncher *launcher = get();
  if (launcher != nullptr) {
    return (launcher->unknown1c8 & FLAG_UNKNOWN_7) != 0;
  }
  return false;
}

bool FrameworkLauncher::isInitializedSound() {
  FrameworkLauncher *launcher = get();
  if (launcher != nullptr) {
    return (launcher->unknown1c8 & FLAG_UNKNOWN_6) != 0;
  }
  return false;
}

void FrameworkLauncher::reqSoftReset() {
  FrameworkLauncher *launcher = get();
  if (launcher != nullptr) {
    launcher->resetApp();
  }
}

bool FrameworkLauncher::resetApp() {
  if ((unknown1c8 & (FLAG_UNKNOWN_28 | FLAG_UNKNOWN_29 | FLAG_UNKNOWN_30)) != 0) {
    return false;
  }
  unknown1c8 |= FLAG_UNKNOWN_28 | FLAG_UNKNOWN_30;
  return true;
}

void FrameworkLauncher::stepDebugPause() {
  if (unknown419) {
    unknown1c8 |= FLAG_UNKNOWN_21;
  }
}

void FrameworkLauncher::wkUpdate() {
  if (unknown418) {
    return;
  }
  update();
  mm::mtl::PtrSingleton<ml::MicroThread>::get()->update(unknown1d0);
}

void FrameworkLauncher::wkTail() {
  if (!unknown418) {
    fw::UpdateState state;
    state.isPause = m_debugPause;
    fw::Framework *framework = fw::Framework::get();
    if (framework != nullptr && (unknown1c8 & (FLAG_UNKNOWN_4 | FLAG_UNKNOWN_7)) == 0) {
      framework->tail(state);
    }
    ml::Scn *scn = getScn();
    if (scn != nullptr) {
      scn->tail();
    }
    mm::mtl::PtrSingleton<ml::MicroThread>::get()->update(unknown1d8);
  }
}

void FrameworkLauncher::cbRenderAfter(ml::Scn *scn, ml::SCNPRIO_CB priority) {
  ml::WinView *view = ml::WinView::getView(true);
  if (view == getView() && priority != ml::SCNPRIO_CB_UNKNOWN_19 && fw::Framework::get() != nullptr) {
    fw::Framework::get()->render();
  }
}

void FrameworkLauncher::drawTask() {
  if (get() != nullptr) {
    ml::WinView *view = ml::WinView::getView(true);
    if (view == getView()) {
      ml::Scn *scn = getScn();
      if (scn != nullptr) {
        scn->draw();
      }
    }
  }
}

void FrameworkLauncher::destroyScn() { mm::mtl::safeRelease(m_scn); }

void FrameworkLauncher::setDebugPause(bool isPause) {
  ml::Scn *scn = ml::Scn::get();
  if (scn != nullptr && scn->unknown38 != nullptr) {
    scn->unknown38->setMdlDblPause(isPause);
  }
  fw::EffectManager::get()->setMasterPause(isPause);
}

void FrameworkLauncher::bkgHomeMenu(bool isOpen) {
  if (unknown418 != isOpen) {
    unknown418 = isOpen;
    setDebugPause(isOpen);
  }
  fw::Framework *framework = fw::Framework::get();
  if (framework != nullptr) {
    if (isOpen) {
      framework->deactivate();
    } else {
      framework->activate();
    }
  }
}

bool FrameworkLauncher::createWaitLoadResourceThread() {
  FrameworkLauncher *launcher = get();
  if (launcher == nullptr) {
    return true;
  }
  if (launcher->unknown1f8 == -1 && launcher->unknown1f0 == -1 && launcher->unknown1e8 == -1 && (launcher->unknown1c8 & FLAG_UNKNOWN_11) == 0) {
    launcher->unknown1f8 = mm::mtl::PtrSingleton<ml::MicroThread>::get()->createThread(launcher->unknown1d0, mlthFnLoadResource, launcher);
  }
  return (launcher->unknown1c8 & FLAG_UNKNOWN_11) != 0;
}

bool FrameworkLauncher::createAppletInitializeThread() {
  FrameworkLauncher *launcher = get();
  if (launcher == nullptr) {
    return true;
  }
  if (launcher->unknown1f0 == -1 && launcher->unknown1f8 == -1 && launcher->unknown1e8 == -1 && (launcher->unknown1c8 & FLAG_UNKNOWN_10) == 0) {
    launcher->unknown1f0 = mm::mtl::PtrSingleton<ml::MicroThread>::get()->createThread(launcher->unknown1d0, mlthFnAppletInitialize, launcher);
  }
  return (launcher->unknown1c8 & FLAG_UNKNOWN_10) != 0;
}

nn::os::FiberType *FrameworkLauncher::mlthFnLoadResource(void *argument) {
  FrameworkLauncher *launcher = get();
  fw::Applet *applet = getApplet();
  fw::Framework *framework = fw::Framework::get();
  if (applet != nullptr && framework != nullptr) {
    applet->initializeResource(*framework);
  }
  fw::ResourceManager *resourceManager = fw::ResourceManager::get();
  if (resourceManager != nullptr) {
    while (!resourceManager->isLoaded()) {
      mm::mtl::PtrSingleton<ml::MicroThread>::get()->sleep(0, true);
    }
  }
  launcher->unknown1c8 |= FLAG_UNKNOWN_11;
  launcher->unknown1f8 = -1;
  mm::mtl::PtrSingleton<ml::MicroThread>::get()->exit();
  return nullptr;
}

nn::os::FiberType *FrameworkLauncher::mlthFnAppletInitialize(void *argument) {
  FrameworkLauncher *launcher = get();
  fw::Applet *applet = getApplet();
  fw::Framework *framework = fw::Framework::get();
  if (applet != nullptr && framework != nullptr) {
    applet->initialize(*framework);
    while (!getApplet()->isInitialized()) {
      mm::mtl::PtrSingleton<ml::MicroThread>::get()->sleep(0, true);
    }
    getApplet()->enter();
    fw::Framework::get()->prepareEnter();
  }
  launcher->unknown1c8 |= FLAG_UNKNOWN_10;
  launcher->unknown1f0 = -1;
  mm::mtl::PtrSingleton<ml::MicroThread>::get()->exit();
  return nullptr;
}

bool FrameworkLauncher::destroy() {
  FrameworkLauncher *launcher = get();
  if (launcher != nullptr) {
    if (launcher->unknown1e0 == -1 && launcher->unknown1e8 == -1 && launcher->unknown1f0 == -1 && launcher->unknown1f8 == -1 && (launcher->unknown1c8 & FLAG_UNKNOWN_4) == 0) {
      launcher->unknown1c8 |= FLAG_UNKNOWN_29;
      launcher->unknown1e0 = mm::mtl::PtrSingleton<ml::MicroThread>::get()->createThread(launcher->unknown1d8, mlthFnTermUpdate, launcher);
    }
    if ((launcher->unknown1c8 & FLAG_UNKNOWN_4) == 0) {
      return false;
    }
    ml::DevKeyboard::clearKey();
  }
  return true;
}

bool FrameworkLauncher::wkStandbyLogout() {
  if (unknown60.size() == 0) {
    if (!destroy()) {
      return false;
    }
    if ((unknown1c8 & FLAG_UNKNOWN_4) != 0) {
      return WorkObj::wkStandbyLogout();
    }
  }
  return false;
}

} // namespace apps
