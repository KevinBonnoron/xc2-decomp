#include "gf/object/gf_append.h"

#include "gf/util/gf_util.h"

namespace gf {

const char *GfAppend::getBone(OPTMNT mount) const {
  for (const MOUNT_INFO *it = unknown00.begin(); it != unknown00.end(); ++it) {
    if (it->unknown14 == mount) {
      return it->unknown00.c_str();
    }
  }

  return "";
}

const char *GfAppend::getModelName() const { return m_modelName; }

const char *GfAppend::getMotionName() const { return m_motionName; }

const char *GfAppend::getResourceName() const { return util::getFilePtrFromPath(m_modelName); }

const char *GfAppend::getAsmFileName() const { return util::getFilePtrFromPath(m_motionName); }

u16 GfAppend::getMountIndex() const { return m_mountIndex; }

u16 GfAppend::getRscID() const { return m_rscID; }

} // namespace gf
