#include "gf/field/gf_field_pitch_roll_controller.h"

#include "framework/anim/anim_manager.h"
#include "framework/ik/ik_rotate_solver.h"
#include "framework/ik/ik_solver.h"
#include "gf/object/component/gf_com_ik.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

namespace gf {

void GfFieldPitchRollController::create(const CreateInfo &info) {
  dispose();
  unknown0a = info.unknown0a;
  unknown08 = info.unknown08;
  unknown00 = info.unknown00;
  unknown18 = &GfFieldPitchRollController::seqInit;
}

void GfFieldPitchRollController::dispose() {
  unknown00 = INVALID_HANDLE;
  unknown18 = nullptr;
  unknown08 = unknown001();
  unknown10 = nullptr;
  unknown0a = true;
}

void GfFieldPitchRollController::seqInit(const gmk::GmkRouteNavi &navi) {
  GfObjAcc acc(unknown00);
  GfObj *obj = acc.getObj();
  if (obj == nullptr) {
    dispose();
    return;
  }

  GfComIK *comIK = obj->getComponent<GfComIK>();
  if (comIK != nullptr) {
    fw::IkSolver *ikSolver = comIK->unknown10.unknown10[0].get();
    if (ikSolver != nullptr) {
      fw::RotateIkSolver *solver = mm::mtl::dynamicCast<fw::RotateIkSolver>(ikSolver);
      if (solver != nullptr) {
        unknown10 = solver;
        solver->fadeIn(0.0f);
        unknown18 = &GfFieldPitchRollController::seqUpdate;
        return;
      }
    }

    unknown10 = nullptr;
  }
}

void GfFieldPitchRollController::update(const gmk::GmkRouteNavi &navi) {
  if (unknown00 != INVALID_HANDLE) {
    if (unknown18) {
      (this->*unknown18)(navi);
    }
  }
}

} // namespace gf
