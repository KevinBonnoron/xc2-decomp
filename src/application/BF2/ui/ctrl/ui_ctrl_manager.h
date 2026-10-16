#pragma once
#include "mm_mtl/intrusive_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace ui {

class IUICtrlUpdater : public mm::mtl::IntrusiveListNodeBase {
public:
  virtual bool updateCtrl(const fw::UpdateInfo &info) = 0;
};

class UICtrlManager : public mm::mtl::PtrSingleton<UICtrlManager> {
public:
  void addUpdater(IUICtrlUpdater &updater);
  void delUpdater(IUICtrlUpdater &updater);
  void changeEventHandleObject(int ctrl, u32 handler);
};

} // namespace ui
