#include "fw/fw_model_object.h"
#include "mm_math/mm_vec3.h"
#include "scn/scn_obj_acc.h"

namespace ml {
class ScnObjModel;
} // namespace ml

namespace fw {

void ModelObject::setup() { unknown3d = false; }

bool ModelObject::isRender() const {
  ml::ScnObjAccResMdlInfo info(m_interface);
  return info.isGpuRender() != 0;
}

ml::ScnObjModel *ModelObject::getInterface() { return m_interface; }

void ModelObject::setActive(bool isActive) { m_active = isActive; }

bool ModelObject::isActive() const { return m_active; }

void ModelObject::setAddOffsetPos(const mm::Vec3 &offset) { unknown50 = offset; }

} // namespace fw
