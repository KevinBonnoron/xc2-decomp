#include "event/model_obj.h"

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

bool ModelObj::isSame() {
  if (unknown0c != MODEL_TYPE_NONE) {
    return false;
  }
  return (unknown08 & FLAG_SAME) != 0;
}

} // namespace event
