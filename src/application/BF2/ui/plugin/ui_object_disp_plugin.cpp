#include "ui/plugin/ui_object_disp_plugin.h"

#include "framework/memory/framework_memory.h"
#include "ui/ctrl/ui_ctrl_manager.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectDispPlugin::UIObjectDispPlugin() : dispControl(true), disp(true), modeFlags(), followObjHandle(0), alphaParam(nullptr), fadeTime(0.0f) {}

UIObjectDispPlugin::~UIObjectDispPlugin() {
  if (fadeUpdater.ctrl != nullptr) {
    UICtrlManager::get()->delUpdater(fadeUpdater);
  }
  fadeUpdater.ctrl = nullptr;
  if (alphaParam != nullptr) {
    delete alphaParam;
    alphaParam = nullptr;
  }
}

void UIObjectDispPlugin::setAlphaMode(bool alphaMode) {
  if (modeFlags.test(MODE_ALPHA) != alphaMode) {
    modeFlags.set(MODE_ALPHA, alphaMode);
    needUpdate |= true;
  }
}

void UIObjectDispPlugin::setReverseMode(bool reverseMode) {
  if (modeFlags.test(MODE_REVERSE) != reverseMode) {
    modeFlags.set(MODE_REVERSE, reverseMode);
    needUpdate |= true;
  }
}

void UIObjectDispPlugin::setSuspendMode(bool suspendMode) {
  if (modeFlags.test(MODE_SUSPEND) != suspendMode) {
    modeFlags.set(MODE_SUSPEND, suspendMode);
    needUpdate |= true;
  }
}

void UIObjectDispPlugin::setDispControl(bool dispControl) { this->dispControl = dispControl; }

void UIObjectDispPlugin::setFollowObjHandle(u32 handle) { followObjHandle = handle; }

void UIObjectDispPlugin::setFadeMode(f32 fadeTime) {
  this->fadeTime = fadeTime;
  modeFlags.set(MODE_ALPHA);
  modeFlags.set(MODE_FADE);
}

UIObjectDispPlugin *UIObjectDispPlugin::create(u32 handle) {
// __LINE__ is the line argument of the operator new call.
#line 168
  UIObjectDispPlugin *plugin = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectDispPlugin();
  plugin->addRef();
  if (UIObjectPluginUtil::attachPlugin(handle, plugin)) {
    plugin->init(handle);
  } else if (plugin != nullptr) {
    plugin->release();
    plugin = nullptr;
  }
  return plugin;
}

void UIObjectDispPlugin::init(u32 handle) { disp = UIObjectAcc(handle).isDisp(); }

void UIObjectDispPlugin::execute(UIObjectAcc &acc) {
  if (dispControl) {
    bool visible = disp;
    if (followObjHandle != 0) {
      visible = UIObjectAcc(followObjHandle).isDisp();
    }
    visible ^= modeFlags.test(MODE_REVERSE);
    if (!modeFlags.test(MODE_ALPHA)) {
      if (modeFlags.test(MODE_SUSPEND)) {
        acc.setSuspend(!visible);
      }
      acc.setDisp(visible);
    } else {
      acc.setDisp(true);
      if (!modeFlags.test(MODE_FADE)) {
        acc.setAlpha(visible ? 1.0f : 0.0f);
        if (modeFlags.test(MODE_SUSPEND)) {
          acc.setSuspend(!visible);
        }
      } else if (alphaParam == nullptr) {
// __LINE__ is the line argument of the operator new call.
#line 221
        alphaParam = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectAlphaParam(acc.handle);
        alphaParam->alpha = visible ? 1.0f : 0.0f;
      } else if (fadeUpdater.ctrl != nullptr) {
        f32 alpha = fade.values[0];
        alphaParam->alpha = alpha;
        if (!fade.isBusy()) {
          if (fadeUpdater.ctrl != nullptr) {
            UICtrlManager::get()->delUpdater(fadeUpdater);
          }
          fadeUpdater.ctrl = nullptr;
        }
        if (modeFlags.test(MODE_SUSPEND)) {
          acc.setSuspend(alpha == 0.0f);
        }
      } else if (modeFlags.test(MODE_SUSPEND)) {
        acc.setSuspend(alphaParam->alpha == 0.0f);
      }
    }
  }
  UIObjectPlugin::execute(acc);
}

const mm::mtl::RTTI *UIObjectDispPlugin::getRTTI() const { return &m_rtti; }

bool UIObjectDispPlugin::isNeedUpdate(UIObjectAcc &acc) {
  return (needUpdate & 1) || acc.isDisp() != disp || fadeUpdater.ctrl != nullptr || followObjHandle != 0;
}

void UIObjectAlphaParam::apply(AdditionalParam &param) const { param.alpha *= alpha; }

} // namespace ui
