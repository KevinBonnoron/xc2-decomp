#include "gf/object/gf_append.h"

#include "gf/util/gf_util.h"

namespace gf {

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
