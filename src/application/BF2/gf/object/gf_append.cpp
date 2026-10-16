#include "gf/object/gf_append.h"

#include "gf/util/gf_util.h"

namespace gf {

const char *GfAppend::getBone(OPTMNT mount) const {
  for (const MOUNT_INFO *it = mounts.begin(); it != mounts.end(); ++it) {
    if (it->mount == mount) {
      return it->bone.c_str();
    }
  }

  return "";
}

const char *GfAppend::getModelName() const { return modelName; }

const char *GfAppend::getMotionName() const { return motionName; }

const char *GfAppend::getResourceName() const { return util::getFilePtrFromPath(modelName); }

const char *GfAppend::getAsmFileName() const { return util::getFilePtrFromPath(motionName); }

u16 GfAppend::getMountIndex() const { return mountIndex; }

u16 GfAppend::getRscID() const { return rscId; }

} // namespace gf
