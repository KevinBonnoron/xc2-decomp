#include "event/mdlstm_manager.h"

#include "event/mdlstm_data.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

bool MdlstmManager::isReuseEnable() const { return (unknown14 & REUSE_FLAG_UNKNOWN_0) != 0; }

bool MdlstmManager::isLoadingPrio(f32 priority) const {
  for (MdlstmObj *const *it = unknown3c020.begin(); it != unknown3c020.end(); ++it) {
    if ((*it)->isLoading(priority))
      return true;
  }
  return false;
}

bool MdlstmManager::searchByHandle(gf::GF_OBJ_HANDLE *handle) const {
  for (MdlstmObj *const *it = unknown3c020.begin(); it != unknown3c020.end(); ++it) {
    if ((*it)->checkByHandle(handle))
      return true;
  }
  return false;
}

MdlstmManager::MdlstmManager() : unknown10(0), unknown14(0), unknown3c018(0) {}

void MdlstmManager::clear() {
  mm::mtl::Singleton<MdlstmData>::getPtr()->clear();
  for (u32 i = 0; i < unknown3c020.size(); i++) {
    unknown3c020[i]->dispose();
  }
  for (u32 i = 0; i < unknown3c020.size(); i++) {
    unknown3c020[i]->finishFree();
  }
  unknown3c020.clear();
  unknown3c018 = 0;
  _3e028 = 0;
  _3e02c = 0;
  unknown3e030 = 0;
  unknown10 = 0;
  unknown14 = 0;
}

void MdlstmManager::dispose(ModelObj *model) {
  if (model == nullptr) {
    return;
  }
  for (u32 i = 0; i < _3e028; i++) {
    if (unknown3c020[i]->isDisposeable(model)) {
      unknown3c020[i]->dispose();
      return;
    }
  }
}

f32 MdlstmManager::getNextCutFrame(f32 frame) {
  f32 next = frame;
  if (unknown3c018 != 0) {
    next = unknown18[unknown3c018 - 1].unknown10;
    for (u32 i = 0; i < unknown3c018; i++) {
      if (frame < unknown3c020[i]->unknown10) {
        if (unknown3c020[i]->unknown10 < next) {
          next = unknown3c020[i]->unknown10;
        }
      }
    }
  }
  return next;
}

void MdlstmManager::create(mtl::ALLOC_HANDLE handle) {
  unknown10 = FLAG_UNKNOWN_2;
  unknown3c018 = 0;
  _3e028 = 0;
  _3e02c = 0;
  unknown3e030 = 0;
  mm::mtl::Singleton<MdlstmData>::getPtr()->clear();
  unknown10 |= FLAG_UNKNOWN_0;
}

void MdlstmManager::render() {}

void MdlstmManager::addReplaceInfo(const MdlstmData::Info &info) { mm::mtl::Singleton<MdlstmData>::getPtr()->addReplaceInfo(info); }

void MdlstmManager::start() {
  if (unknown10 & FLAG_UNKNOWN_0) {
    unknown10 |= FLAG_UNKNOWN_1;
  }
}

void MdlstmManager::setReuseEnable(bool isReuseEnable) {
  if (isReuseEnable) {
    unknown14 |= REUSE_FLAG_UNKNOWN_0;
  } else {
    unknown14 &= ~REUSE_FLAG_UNKNOWN_0;
  }
}

void MdlstmManager::setReuseFlag(int reuseFlag) { unknown3e030 = reuseFlag; }

void MdlstmManager::load(f32 frame, const char *path, u32 value, bool isActive) {
  if (unknown10 & FLAG_UNKNOWN_0) {
    MdlstmObj *obj = &unknown18[unknown3c018++];
    obj->init(frame, path, value, isActive, unknown3e030);
    unknown001(obj);
  }
}

void MdlstmManager::load(f32 frame, MODEL_TYPE type, u32 id, u32 value, bool isActive) {
  if (unknown10 & FLAG_UNKNOWN_0) {
    MdlstmObj *obj = &unknown18[unknown3c018++];
    obj->init(frame, type, id, value, isActive, unknown3e030);
    unknown001(obj);
  }
}

ModelObj *MdlstmManager::build(const char *path, u32 value) {
  for (u32 i = 0; i < _3e028; i++) {
    if (unknown3c020[i]->isBuildable(path, value)) {
      return unknown3c020[i]->build();
    }
  }
  return nullptr;
}

ModelObj *MdlstmManager::build(MODEL_TYPE type, u32 id, u32 value) {
  for (u32 i = 0; i < _3e028; i++) {
    if (unknown3c020[i]->isBuildable(type, id, value)) {
      return unknown3c020[i]->build();
    }
  }
  return nullptr;
}

void MdlstmManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_14:
    update();
    break;
  case MSG_TYPE_UNKNOWN_12:
    clear();
    break;
  default:
    break;
  }
}

} // namespace event
