#include "gf/camera/gimmick/gf_camera_gimmick_params.h"

namespace gf {

namespace {

struct unknown001 {
  u32 unknown00; // Inferred role: magic checked by setup; original name unknown.
  u32 unknown04; // Inferred role: parameter count; original name unknown.
  s32 unknown08; // Inferred role: version checked by setup; original name unknown.
  u32 unknown0c; // Inferred role: padding; original name unknown.
};

const GimmickCameraParams::Param unknown002 = {};

} // namespace

GimmickCameraParams::GimmickCameraParams() : m_size(0), unknown10(NULL) {}

GimmickCameraParams::GimmickCameraParams(void *data, int version) : m_size(0), unknown10(NULL) { setup(data, version); }

void GimmickCameraParams::setup(void *data, int version) {
  unknown001 *header = static_cast<unknown001 *>(data);
  if (header->unknown00 == 0x504347 && header->unknown08 == version) {
    m_size = header->unknown04;
    unknown10 = reinterpret_cast<const Param *>(header + 1);
  }
}

int GimmickCameraParams::getSize() const { return m_size; }

const GimmickCameraParams::Param &GimmickCameraParams::getParam(int index) const {
  if (index < static_cast<int>(m_size)) {
    return unknown10[index];
  }
  return unknown002;
}

mm::mtl::FixStr<128> GimmickCameraParams::getPath(const char *name) {
  mm::mtl::FixStr<128> path;
  path.format("%s%s%s", "/camera/", name, ".gcp");
  return path;
}

} // namespace gf
