#include "event/model_obj.h"

namespace event {

void ModelObj::setReserve(u32 index, bool isReserve) {
  if (isReserve) {
    mReserve |= 1 << index;
  } else {
    mReserve &= ~(1 << index);
  }
}

bool ModelObj::isReserve(int index) { return (mReserve & (index >= 0 ? 1 << index : 0x7fffffff)) != 0; }

bool ModelObj::isSame(const char *path, bool isPriority, u32 id) {
  if (mType != MODEL_TYPE_PATH) {
    return false;
  }
  if (__builtin_strcmp(this->path.c_str(), path) != 0) {
    return false;
  }
  if (((flags & FLAG_PRIORITY) != 0) != isPriority) {
    return false;
  }
  return mId == id;
}

bool ModelObj::isSame() {
  if (mType != MODEL_TYPE_NONE) {
    return false;
  }
  return (flags & FLAG_SAME) != 0;
}

} // namespace event
