#include "idcoli/idcoli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

IDColiParmsPhantom::IDColiParmsPhantom(IDColiObj *object) : IDColiParmsBase(object), m_phantom(static_cast<IDColiObjPhantom *>(object)) {}

void IDColiParmsPhantom::createSphere(f32 radius) {
  m_phantom->m_size = mm::Vec3(radius, radius, radius);
  m_phantom->m_shapeType = SHAPE_TYPE_SPHERE;
  m_phantom->m_updateFlags |= IDColiObj::UPDATE_SIZE;
}

void IDColiParmsPhantom::createCapsule(f32 radius, f32 height) {
  m_phantom->m_size = mm::Vec3(height, radius, height);
  m_phantom->m_shapeType = SHAPE_TYPE_CAPSULE;
  m_phantom->m_updateFlags |= IDColiObj::UPDATE_SIZE;
}

void IDColiParmsPhantom::createBox(const mm::Vec3 &size) {
  m_phantom->m_size = size;
  m_phantom->m_shapeType = SHAPE_TYPE_BOX;
  m_phantom->m_updateFlags |= IDColiObj::UPDATE_SIZE;
}

void IDColiParmsPhantom::createCharacter(f32 radius, f32 height) {
  m_phantom->m_size = mm::Vec3(height, radius, height);
  m_phantom->m_shapeType = SHAPE_TYPE_CHARACTER;
  m_phantom->m_updateFlags |= IDColiObj::UPDATE_SIZE;
}

void IDColiParmsPhantom::createData(const void *binary) {}

} // namespace idcoli
