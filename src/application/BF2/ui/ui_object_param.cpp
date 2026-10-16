#include "ui/ui_object_param.h"

#include "ui/ui_object.h"
#include "ui/ui_util.h"

namespace ui {

UIObjectParam::UIObjectParam(u32 handle) {
  this->handle = handle;
  UIUtil::getObject(handle)->registAdditionalParam(this);
}

UIObjectParam::~UIObjectParam() {
  if (handle != 0) {
    UIObject *object = UIUtil::getObject(handle);
    if (object != nullptr) {
      object->registAdditionalParam(this);
    }
  }
}

} // namespace ui
