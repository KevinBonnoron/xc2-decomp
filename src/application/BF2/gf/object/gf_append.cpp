#include "gf/object/gf_append.h"

#include "framework/message/message_object.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gf/util/gf_util.h"

namespace gf {
enum OPTMNT : u32;

void GfAppendHandles::sendMessage(fw::MessageObject *sender, fw::Message &message) const {
  for (u32 index = 0; index < 10; index++) {
    GfObj *obj = GfObjUtil::getObj(getCurrentHandles()[index]);
    if (obj != nullptr) {
      static_cast<fw::MessageObject *>(obj)->recieveMessage(sender, message);
    }
  }
}

void GfAppendHandles::setAlpha(f32 alpha) {
  for (u32 index = 0; index < 10; index++) {
    GfObjAcc acc(getCurrentHandles()[index]);
    acc.setAlphaNormal(alpha);
  }
}

void GfAppendHandles::destroy(mm::mtl::FixedArray<GF_OBJ_HANDLE *, 10> &handles) {
  for (u32 index = 0; index < 10; index++) {
    GF_OBJ_HANDLE *handle = handles[index];
    if (handle != INVALID_HANDLE) {
      handles[index] = INVALID_HANDLE;
      GfObjUtil::destroy(handle);
    }
  }
}

void GfAppendHandles::destroy() {
  destroy(unknown08);
  destroy(unknown58);
}

void GfAppendHandles::eraseHandle(mm::mtl::FixedArray<GF_OBJ_HANDLE *, 10> &handles, GF_OBJ_HANDLE *handle) {
  for (u32 index = 0; index < 10; index++) {
    if (handles[index] == handle) {
      handles[index] = INVALID_HANDLE;
      return;
    }
  }
}

void GfAppendHandles::eraseHandle(GF_OBJ_HANDLE *handle) {
  eraseHandle(unknown08, handle);
  eraseHandle(unknown58, handle);
}

GfAppend::GfAppend() : unknown00(), m_modelName(nullptr), m_motionName(nullptr), m_mountIndex(0xffff), m_rscID(0), unknown7c(1.0f), unknown80(false) {}

GfAppend::GfAppend(const char *modelName, const char *motionName, u16 mountIndex, u16 rscID, f32 scale, bool multiMount)
    : unknown00(), m_modelName(modelName), m_motionName(motionName), m_mountIndex(mountIndex), m_rscID(rscID), unknown7c(scale), unknown80(multiMount) {}

const char *GfAppend::getBone(OPTMNT mount) const {
  for (const MOUNT_INFO *it = unknown00.begin(); it != unknown00.end(); ++it) {
    if (it->unknown14 == mount) {
      return it->unknown00.c_str();
    }
  }

  return "";
}

void GfAppend::addMount(MOUNT_INFO &info) { unknown00.push_back(info); }

const char *GfAppend::getModelName() const { return m_modelName; }

const char *GfAppend::getMotionName() const { return m_motionName; }

const char *GfAppend::getResourceName() const { return util::getFilePtrFromPath(m_modelName); }

const char *GfAppend::getAsmFileName() const { return util::getFilePtrFromPath(m_motionName); }

u16 GfAppend::getMountIndex() const { return m_mountIndex; }

u16 GfAppend::getRscID() const { return m_rscID; }

void GfAppendWire::startWire(GF_OBJ_HANDLE *target, f32 time) { startWireWithClose(target, time, 0.0f, 0.0f); }

} // namespace gf
