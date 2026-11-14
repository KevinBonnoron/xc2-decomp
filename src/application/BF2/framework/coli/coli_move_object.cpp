#include "framework/coli/coli_manager.h"
#include "framework/coli/coli_object.h"
#include "framework/memory/framework_memory.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "idcoli/idcoli.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"

namespace fw {

ColiObject *ColiMoveObject::createColiCharacter(const ColiCharacterInfo &info, const mm::mtl::IntrusivePtr<ReferenceFrame> &frame) {
  idcoli::IDColiAccMan accMan;
  idcoli::IDColiObj *coliObject = accMan.createColiCharacter();
#line 29
  ColiObject *object = new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) ColiMoveObject();
  object->addRef();
  object->setColiObject(coliObject);
  object->setHitMaterialFlag(0xfffffffa);
  ColiManager::get()->registObject(object);
  if (object != nullptr) {
    setupColiCharacter(object, info, frame);
  }

  return object;
}

ColiObject *ColiMoveObject::createColiPhantom(const ColiPhantomInfo &info, const mm::mtl::IntrusivePtr<ReferenceFrame> &frame) {
  idcoli::IDColiAccMan accMan;
  idcoli::IDColiObj *coliObject = accMan.createColiPhantom();
#line 55
  ColiObject *object = new (FrameworkMemory::getAllocator(5), 16, __FILE__, __LINE__) ColiMoveObject();
  object->addRef();
  object->setColiObject(coliObject);
  ColiManager::get()->registObject(object);
  if (object != nullptr) {
    setupColiPhantom(object, info, frame);
  }

  return object;
}

ColiMoveObject::ColiMoveObject() : m_dir(mm::Vec3::zero), unknown110(0) {}

const mm::mtl::RTTI *ColiMoveObject::getRTTI() const { return &m_rtti; }

void ColiMoveObject::setDir(const mm::Vec3 &direction) { m_dir = direction; }

void ColiMoveObject::postUpdate() {
  ColiObject::postUpdate();
  if (unknown30 != COLI_TYPE_UNKNOWN_0) {
    if (m_coliObject != nullptr) {
      idcoli::IDColiMove move;
      if (unknown110 & FLAG_UNKNOWN_1) {
        move.setAccuracy(true);
        unknown110 &= ~FLAG_UNKNOWN_1;
      }
      move.moveColi(m_coliObject, m_dir);
      mm::Mat44 matrix(getMatrix());
      mm::Vec3 delta = move.unknown130;
      matrix.rows[3][0] = delta.x + matrix.rows[3][0];
      matrix.rows[3][1] = delta.y + matrix.rows[3][1];
      matrix.rows[3][2] = delta.z + matrix.rows[3][2];
      setMatrix(matrix);
      ReferenceFrame *frame = unknown28.get();
      if (frame != nullptr) {
        frame->invalidateLocal();
        frame->unknown40.unknown00 += move.unknown130;
      }
    }
    m_dir = mm::Vec3::zero;
  }
}

} // namespace fw
