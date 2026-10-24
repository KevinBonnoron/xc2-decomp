#include "idcoli/idcoli.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace idcoli {

IDColiParmsCharacter::IDColiParmsCharacter(IDColiObj *object) : IDColiParmsBase(object), m_character(static_cast<IDColiObjChar *>(object)) {}

void IDColiParmsCharacter::createSphere(f32 radius) {
  m_character->m_size = mm::Vec3(radius, radius, radius);
  m_character->unknownc0 = SHAPE_TYPE_SPHERE;
  m_character->unknown1c |= IDColiObj::UPDATE_SIZE;
}

void IDColiParmsCharacter::createCapsule(f32 radius, f32 height, bool isRotate) {
  m_character->m_size = mm::Vec3(height, radius, height);
  if (isRotate) {
    m_character->unknownc0 = SHAPE_TYPE_CAPSULE_ROTATE;
    m_character->unknown1c |= IDColiObj::UPDATE_ROTATE;
  } else {
    m_character->unknownc0 = SHAPE_TYPE_CAPSULE;
    m_character->unknown1c &= ~IDColiObj::UPDATE_ROTATE;
  }
  m_character->unknown1c |= IDColiObj::UPDATE_SIZE;
}

void IDColiParmsCharacter::createBox(const mm::Vec3 &size, bool isRotate) {
  m_character->m_size = size;
  if (isRotate) {
    m_character->unknownc0 = SHAPE_TYPE_BOX_ROTATE;
    m_character->unknown1c |= IDColiObj::UPDATE_ROTATE;
  } else {
    m_character->unknownc0 = SHAPE_TYPE_BOX;
    m_character->unknown1c &= ~IDColiObj::UPDATE_ROTATE;
  }
  m_character->unknown1c |= IDColiObj::UPDATE_SIZE;
}

void IDColiParmsCharacter::createCharacter(f32 radius, f32 height) {
  m_character->m_size = mm::Vec3(height, radius, height);
  m_character->unknownc0 = SHAPE_TYPE_CHARACTER;
  m_character->unknown1c |= IDColiObj::UPDATE_SIZE;
}

void IDColiParmsCharacter::createData(const void *binary) { m_character->createBinary(binary); }

void IDColiParmsCharacter::setAdsorption(f32 adsorption) { m_character->unknown220 = adsorption; }

f32 IDColiParmsCharacter::getAdsorption() const { return m_character->unknown220; }

} // namespace idcoli
