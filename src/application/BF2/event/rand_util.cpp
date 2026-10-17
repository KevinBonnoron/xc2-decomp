#include "event/rand_util.h"

#include "event/object.h"
#include "event/object_chara.h"

namespace event {

mm::Vec3 RandUtil::getEyePos(int id) {
  if (id > 0) {
    Object *object = searchByID(id);
    if (object != nullptr && object->getType() == OBJTYPE_CHARA) {
      return static_cast<ObjectChara *>(object)->getEyePos();
    }
  }
  return mm::Vec3::zero;
}

mm::Vec3 RandUtil::getCurentTarPos(int id, bool &isFound) {
  if (id > 0) {
    Object *object = searchByID(id);
    if (object != nullptr && object->getType() == OBJTYPE_CHARA) {
      isFound = static_cast<ObjectChara *>(object)->isTar();
      return static_cast<ObjectChara *>(object)->getTar();
    }
  }
  isFound = false;
  return mm::Vec3::zero;
}

} // namespace event
