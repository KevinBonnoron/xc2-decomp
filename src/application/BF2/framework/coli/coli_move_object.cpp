#include "framework/coli/coli_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "idcoli/idcoli.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"

namespace fw {

ColiMoveObject::ColiMoveObject() : unknown100(mm::Vec3::zero), unknown110(0) {}

const mm::mtl::RTTI *ColiMoveObject::getRTTI() const { return &m_rtti; }

void ColiMoveObject::setDir(const mm::Vec3 &direction) { unknown100 = direction; }

void ColiMoveObject::postUpdate() {
  ColiObject::postUpdate();
  if (unknown30 != COLI_TYPE_STATIC) {
    if (m_coliObject != nullptr) {
      idcoli::IDColiMove move;
      if (unknown110 & FLAG_ACCURACY) {
        move.setAccuracy(true);
        unknown110 &= ~FLAG_ACCURACY;
      }
      move.moveColi(m_coliObject, unknown100);
      mm::Mat44 matrix;
      matrix.unknown006(getMatrix());
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
    unknown100 = mm::Vec3::zero;
  }
}

} // namespace fw
