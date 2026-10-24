#include "fw/fw_model_object.h"
#include "mm_math/mm_vec3.h"

namespace ml {
class ScnObjModel;
} // namespace ml

namespace fw {

ml::ScnObjModel *ModelObject::getInterface() { return m_interface; }

void ModelObject::setActive(bool isActive) { m_active = isActive; }

bool ModelObject::isActive() const { return m_active; }

void ModelObject::setAddOffsetPos(const mm::Vec3 &offset) { unknown50 = offset; }

} // namespace fw
