#include "event/rand_util.h"

#include "event/object.h"
#include "event/object_chara.h"
#include "event/object_manager.h"
#include "mm_mtl/singleton.h"

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

Object *RandUtil::searchByID(int id) {
  Object *object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(3, id);
  if (object != nullptr) {
    return object;
  }
  object = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByID(4, id);
  if (object != nullptr) {
    return object;
  }
  return nullptr;
}

mm::Vec3 RandUtil::getEyePos(gf::GF_OBJ_HANDLE *handle) {
  ObjectChara *chara = mm::mtl::Singleton<ObjectManager>::getPtr()->searchByHandle(handle);
  if (chara != nullptr) {
    return chara->getEyePos();
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
