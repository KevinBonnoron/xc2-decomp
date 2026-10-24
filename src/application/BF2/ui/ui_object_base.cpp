#include "ui/ui_object_base.h"

namespace ui {

UIObjectBase::UIObjectBase(const mm::mtl::FixStr<32> &name) : unknown98(), unknown9c(0), unknowna0(name.c_str()) { unknown98.clear(); }

UIObjectBase::~UIObjectBase() {}

void UIObjectBase::update() {
  unknown20.syncParent();
  unknown50.syncParent();
}

void UIObjectBase::setInitialize() { unknown98.set(UI_OBJECT_FLAG_TERM, false); }

void UIObjectBase::setTerm() {
  unknown98.set(UI_OBJECT_FLAG_TERM, true);
  unknown98.set(UI_OBJECT_FLAG_SUSPEND, false);
}

void UIObjectBase::setSuspend(bool suspend) {
  if (isTerm()) {
    unknown98.set(UI_OBJECT_FLAG_SUSPEND, false);
  } else {
    unknown98.set(UI_OBJECT_FLAG_SUSPEND, suspend);
  }
}

} // namespace ui
