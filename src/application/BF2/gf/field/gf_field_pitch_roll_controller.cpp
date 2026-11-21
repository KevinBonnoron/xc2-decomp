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

GfFieldPitchRollController::GfFieldPitchRollController(const CreateInfo *info) {
  unknown00 = unknown020;
  unknown08 = unknown001();
  unknown0a = true;
  unknown10 = nullptr;
  unknown18 = nullptr;
  unknown28 = 0.0f;
  unknown2c = 0.0f;
  unknown30 = false;
  unknown31 = false;
  if (info != nullptr) {
    create(*info);
  }
}

void GfFieldPitchRollController::create(const CreateInfo &info) {
  dispose();
  unknown0a = info.unknown0a;
  unknown08 = info.unknown08;
  unknown00 = info.unknown00;
  unknown18 = &GfFieldPitchRollController::seqInit;
}

void GfFieldPitchRollController::dispose() {
  // Store order (game 0x7100340f3c, inlined into the constructor at 0x7100340e88 through create()): the two zero pointers come first.
  // MemCpyOpt then makes one 24-byte memset of the run unknown10/unknown18 from &unknown10, so the copy inlined in the constructor
  // uses unknown10 as its pre-indexed base (`str xzr, [x11, #0x10]!` in the first block, as in the game). The earlier order
  // 00, 18, 08, 10, 0a (the non-zero store 08 splits the run: 16-byte memset at unknown18 and a lone unknown10 store) also matches
  // the standalone dispose, create and seqInit but gives the constructor unknown18 as base; the declaration order matches none of them.
  unknown10 = nullptr;
  unknown18 = nullptr;
  unknown00 = unknown020;
  unknown08 = unknown001();
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
  if (unknown00 != unknown020) {
    if (unknown18) {
      (this->*unknown18)(navi);
    }
  }
}

} // namespace gf
