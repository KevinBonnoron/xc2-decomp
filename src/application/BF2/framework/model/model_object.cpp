#include "fw/fw_model_object.h"
#include "mm_math/mm_vec3.h"

namespace ml {
class ScnObjModel;
} // namespace ml

namespace fw {

ml::ScnObjModel *ModelObject::getInterface() { return model; }

void ModelObject::setActive(bool isActive) { active = isActive; }

bool ModelObject::isActive() const { return active; }

void ModelObject::setAddOffsetPos(const mm::Vec3 &offset) { addOffsetPos = offset; }

} // namespace fw
