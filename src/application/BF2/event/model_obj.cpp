#include "event/model_obj.h"

#include "gf/event/gf_evt_model.h"

namespace event {

void ModelObj::setReserve(u32 index, bool isReserve) {
  if (isReserve) {
    unknown134 |= 1 << index;
  } else {
    unknown134 &= ~(1 << index);
  }
}

bool ModelObj::isReserve(int index) { return (unknown134 & (index >= 0 ? 1 << index : 0x7fffffff)) != 0; }

bool ModelObj::isSame(const char *path, bool isPriority, u32 id) {
  if (unknown0c != MODEL_TYPE_PATH) {
    return false;
  }
  if (__builtin_strcmp(this->unknown18.c_str(), path) != 0) {
    return false;
  }
  if (((unknown08 & FLAG_PRIORITY) != 0) != isPriority) {
    return false;
  }
  return unknown5c == id;
}

bool ModelObj::isBusy() const {
  if ((unknown08 & 0xc) != 0) {
    return true;
  }
  if (unknown130 >= 0) {
    return true;
  }
  if (unknown128 != nullptr) {
    if (unknown128->isBusy(nullptr)) {
      return true;
    }
  }
  return false;
}

void ModelObj::update() {
  if (unknown128 != nullptr) {
    if (unknown130 >= 0) {
      unknown130--;
    }
    if (unknown128->isBusy(nullptr)) {
      unknown130 = 2;
    }
  }
}

bool ModelObj::isSame() {
  if (unknown0c != MODEL_TYPE_NONE) {
    return false;
  }
  return (unknown08 & FLAG_SAME) != 0;
}

} // namespace event
