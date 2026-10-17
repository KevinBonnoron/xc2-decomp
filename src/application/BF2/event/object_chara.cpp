#include "event/object_chara.h"

#include "event/frame_manager.h"
#include "event/memory_manager.h"
#include "mtl/alloc_handle.h"

namespace event {

ObjectChara::ObjectChara(const char *name) : Object(OBJTYPE_CHARA, name), flags(0), mCharaObj(nullptr) {}

ObjectChara::~ObjectChara() {
  if (mCharaObj != nullptr) {
    delete mCharaObj;
    mCharaObj = nullptr;
  }
}

void ObjectChara::createGfObj(gf::GF_OBJ_HANDLE *handle) {
  mCharaObj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  mCharaObj->createGfObj(handle);
  flags |= FLAG_CREATED;
}

void ObjectChara::createGfObj(CHARA_TYPE type, u32 id, u32 param3, u32 param4) {
  mCharaObj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  mCharaObj->createGfObj(type, id, param3, param4);
  flags |= FLAG_CREATED;
}

void ObjectChara::createModel(const char *model, u32 param2, u32 param3) {
  mCharaObj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  mCharaObj->createModel(model, param2, param3);
  flags &= ~FLAG_CREATED;
}

void ObjectChara::createGhost() {
  mCharaObj = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CharaObj(getName());
  mCharaObj->createGhost();
  flags |= FLAG_CREATED;
}

void ObjectChara::clear() {
  if (mCharaObj != nullptr) {
    mCharaObj->clear();
  }
}

void ObjectChara::start() {
  if (mCharaObj != nullptr) {
    mCharaObj->start();
  }
}

void ObjectChara::end() {
  if (mCharaObj != nullptr) {
    mCharaObj->end();
  }
}

void ObjectChara::update() {
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  if (mCharaObj != nullptr) {
    mCharaObj->update(info);
  }
}

bool ObjectChara::isTar() const { return mCharaObj->isTar(); }

void ObjectChara::tail() {
  const FrameInfo &info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
  if (mCharaObj != nullptr) {
    mCharaObj->tail(info);
  }
}

bool ObjectChara::isLoading() const { return !mCharaObj->isReady(); }

mm::Vec3 ObjectChara::getTar() const { return mCharaObj->getTar(); }

} // namespace event
