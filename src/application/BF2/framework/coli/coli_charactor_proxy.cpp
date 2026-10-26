#include "framework/coli/coli_charactor_proxy.h"

#include "framework/coli/coli_object.h"
#include "idcoli/idcoli.h"
#include "mm_math/mm_vec3.h"

namespace fw {

ColiCharactorProxy::ColiCharactorProxy() : unknown00(nullptr), unknown08(0.4f) {}

void ColiCharactorProxy::integrate(const mm::Vec3 &position, const mm::Vec3 &move, mm::Vec3 *result) {
  mm::Vec3 target = position + move;
  idcoli::IDColiMove coliMove;
  coliMove.setFloor(unknown08);
  coliMove.setAccuracy(true);
  coliMove.moveColi(unknown00->m_coliObject, target);
  *result = coliMove.unknown130;
}

} // namespace fw
