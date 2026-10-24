#include "ui/plugin/ui_object_disp_plugin.h"

#include "framework/memory/framework_memory.h"
#include "ui/ctrl/ui_ctrl_manager.h"
#include "ui/plugin/ui_object_plugin_util.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectDispPlugin::UIObjectDispPlugin() : unknown1c(true), unknown1d(true), unknown20(), m_followObjHandle(0), unknown28(nullptr), unknown78(0.0f) {}

UIObjectDispPlugin::~UIObjectDispPlugin() {
  if (unknown58.ctrl != nullptr) {
    UICtrlManager::get()->delUpdater(unknown58);
  }
  unknown58.ctrl = nullptr;
  if (unknown28 != nullptr) {
    delete unknown28;
    unknown28 = nullptr;
  }
}

void UIObjectDispPlugin::setAlphaMode(bool alphaMode) {
  if (unknown20.test(MODE_ALPHA) != alphaMode) {
    unknown20.set(MODE_ALPHA, alphaMode);
    unknown18 |= true;
  }
}

void UIObjectDispPlugin::setReverseMode(bool reverseMode) {
  if (unknown20.test(MODE_REVERSE) != reverseMode) {
    unknown20.set(MODE_REVERSE, reverseMode);
    unknown18 |= true;
  }
}

void UIObjectDispPlugin::setSuspendMode(bool suspendMode) {
  if (unknown20.test(MODE_SUSPEND) != suspendMode) {
    unknown20.set(MODE_SUSPEND, suspendMode);
    unknown18 |= true;
  }
}

void UIObjectDispPlugin::setDispControl(bool dispControl) { this->unknown1c = dispControl; }

void UIObjectDispPlugin::setFollowObjHandle(u32 handle) { m_followObjHandle = handle; }

void UIObjectDispPlugin::setFadeMode(f32 fadeTime) {
  this->unknown78 = fadeTime;
  unknown20.set(MODE_ALPHA);
  unknown20.set(MODE_FADE);
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

void UIObjectDispPlugin::init(u32 handle) { unknown1d = UIObjectAcc(handle).isDisp(); }

void UIObjectDispPlugin::execute(UIObjectAcc &acc) {
  if (unknown1c) {
    bool visible = unknown1d;
    if (m_followObjHandle != 0) {
      visible = UIObjectAcc(m_followObjHandle).isDisp();
    }
    visible ^= unknown20.test(MODE_REVERSE);
    if (!unknown20.test(MODE_ALPHA)) {
      if (unknown20.test(MODE_SUSPEND)) {
        acc.setSuspend(!visible);
      }
      acc.setDisp(visible);
    } else {
      acc.setDisp(true);
      if (!unknown20.test(MODE_FADE)) {
        acc.setAlpha(visible ? 1.0f : 0.0f);
        if (unknown20.test(MODE_SUSPEND)) {
          acc.setSuspend(!visible);
        }
      } else if (unknown28 == nullptr) {
// __LINE__ is the line argument of the operator new call.
#line 221
        unknown28 = new (UIUtil::getProgAllocator(), 16, __FILE__, __LINE__) UIObjectAlphaParam(acc.unknown10);
        unknown28->unknown1c = visible ? 1.0f : 0.0f;
      } else if (unknown58.ctrl != nullptr) {
        f32 alpha = unknown30.values[0];
        unknown28->unknown1c = alpha;
        if (!unknown30.isBusy()) {
          if (unknown58.ctrl != nullptr) {
            UICtrlManager::get()->delUpdater(unknown58);
          }
          unknown58.ctrl = nullptr;
        }
        if (unknown20.test(MODE_SUSPEND)) {
          acc.setSuspend(alpha == 0.0f);
        }
      } else if (unknown20.test(MODE_SUSPEND)) {
        acc.setSuspend(unknown28->unknown1c == 0.0f);
      }
    }
  }
  UIObjectPlugin::execute(acc);
}

const mm::mtl::RTTI *UIObjectDispPlugin::getRTTI() const { return &m_rtti; }

bool UIObjectDispPlugin::isNeedUpdate(UIObjectAcc &acc) { return (unknown18 & 1) || acc.isDisp() != unknown1d || unknown58.ctrl != nullptr || m_followObjHandle != 0; }

void UIObjectAlphaParam::apply(AdditionalParam &param) const { param.alpha *= unknown1c; }

} // namespace ui
