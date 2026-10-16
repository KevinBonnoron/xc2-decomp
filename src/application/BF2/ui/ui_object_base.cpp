#include "ui/ui_object_base.h"

namespace ui {

UIObjectBase::UIObjectBase(const mm::mtl::FixStr<32> &name) : flags(), duplicateIndex(0), name(name.c_str()) { flags.clear(); }

UIObjectBase::~UIObjectBase() {}

void UIObjectBase::update() {
  transform.syncParent();
  displayInfo.syncParent();
}

void UIObjectBase::setInitialize() { flags.set(UI_OBJECT_FLAG_TERM, false); }

void UIObjectBase::setTerm() {
  flags.set(UI_OBJECT_FLAG_TERM, true);
  flags.set(UI_OBJECT_FLAG_SUSPEND, false);
}

void UIObjectBase::setSuspend(bool suspend) {
  if (isTerm()) {
    flags.set(UI_OBJECT_FLAG_SUSPEND, false);
  } else {
    flags.set(UI_OBJECT_FLAG_SUSPEND, suspend);
  }
}

} // namespace ui
