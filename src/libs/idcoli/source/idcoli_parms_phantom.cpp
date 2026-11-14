#include "idcoli/idcoli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

IDColiParmsPhantom::IDColiParmsPhantom(IDColiObj *object) : IDColiParmsBase(object), m_phantom(static_cast<IDColiObjPhantom *>(object)) {}

void IDColiParmsPhantom::createSphere(f32 radius) {
  m_phantom->m_size = mm::Vec3(radius, radius, radius);
  m_phantom->unknownc0 = SHAPE_TYPE_UNKNOWN_0;
  m_phantom->unknown1c |= IDColiObj::UPDATE_UNKNOWN_5;
}

void IDColiParmsPhantom::createCapsule(f32 radius, f32 height) {
  m_phantom->m_size = mm::Vec3(height, radius, height);
  m_phantom->unknownc0 = SHAPE_TYPE_UNKNOWN_2;
  m_phantom->unknown1c |= IDColiObj::UPDATE_UNKNOWN_5;
}

void IDColiParmsPhantom::createBox(const mm::Vec3 &size) {
  m_phantom->m_size = size;
  m_phantom->unknownc0 = SHAPE_TYPE_UNKNOWN_1;
  m_phantom->unknown1c |= IDColiObj::UPDATE_UNKNOWN_5;
}

void IDColiParmsPhantom::createCharacter(f32 radius, f32 height) {
  m_phantom->m_size = mm::Vec3(height, radius, height);
  m_phantom->unknownc0 = SHAPE_TYPE_UNKNOWN_3;
  m_phantom->unknown1c |= IDColiObj::UPDATE_UNKNOWN_5;
}

void IDColiParmsPhantom::createData(const void *binary) {}

} // namespace idcoli
