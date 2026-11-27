#include "gf/field/gf_field_pitch_roll_controller.h"

#include "framework/anim/anim_manager.h"
#include "framework/ik/ik_rotate_solver.h"
#include "framework/ik/ik_solver.h"
#include "fw/fw_transform.h"
#include "gf/object/component/gf_com_ik.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gmk/gmk_route_navi.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

namespace gf {

GfFieldPitchRollController::GfFieldPitchRollController(const CreateInfo *info) {
  m_GF_OBJ_HANDLE = unknown020;
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
  m_GF_OBJ_HANDLE = info.m_GF_OBJ_HANDLE;
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
  m_GF_OBJ_HANDLE = unknown020;
  unknown08 = unknown001();
  unknown0a = true;
}

void GfFieldPitchRollController::seqInit(const gmk::GmkRouteNavi &navi) {
  GfObjAcc acc(m_GF_OBJ_HANDLE);
  GfObj *obj = acc.getObj();
  if (obj == nullptr) {
    dispose();
    return;
  }

  GfComIK *comIK = obj->getComponent<GfComIK>();
  if (comIK != nullptr) {
    fw::IkSolver *ikSolver = comIK->m_ikResolver.unknown10[0].get();
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
  if (m_GF_OBJ_HANDLE != unknown020) {
    if (unknown18) {
      (this->*unknown18)(navi);
    }
  }
}

void GfFieldPitchRollController::seqUpdate(const gmk::GmkRouteNavi &navi) {
  f32 ratio = static_cast<f32>(navi.unknowna8) / static_cast<f32>(navi.m_createInfo.unknown18);
  if (ratio > 0.5f) {
    ratio = 1.0f - ratio;
  }

  if (unknown08.unknown00 || unknown08.unknown01) {
    GfObjAcc acc(m_GF_OBJ_HANDLE);
    GfObj *obj = acc.getObj();
    if (obj == nullptr) {
      dispose();
      return;
    }

    if (unknown30) {
      unknown28 = unknown28 + unknown28 * -0.1f;
    } else {
      const mm::Vec3 &position = acc.getWorldTransform().unknown00;
      mm::Vec3 direction(navi.unknown90.x - position.x, navi.unknown90.y - position.y, navi.unknown90.z - position.z);
      if (!direction.unknown003()) {
        direction.unknown001();
      }
      // Declared first and assigned after: the constructor form `horizontal(direction.x, 0.0f, direction.z)` orders the phis of the three components
      // (z, y, x) and Reassociate then swaps the operands of the last add of the dot product (`fadd s8, s1, s0`); the game has them as `fadd s8, s0, s1`.
      mm::Vec3 horizontal;
      horizontal = mm::Vec3(direction.x, 0.0f, direction.z);
      if (!horizontal.unknown003()) {
        horizontal.unknown001();
      }
      f32 angle = mm::acos(horizontal.x * direction.x + horizontal.y * direction.y + horizontal.z * direction.z);
      if (direction.y > 0.0f) {
        if (unknown08.unknown00) {
          angle = -angle;
        } else {
          angle = unknown28;
        }
      } else if (!unknown08.unknown01) {
        angle = unknown28;
      }
      unknown28 = unknown28 + (angle - unknown28) * 0.1f;
    }
  }

  if (unknown0a) {
    if (unknown31) {
      unknown2c = unknown2c + unknown2c * -0.1f;
    } else {
      f32 target = ratio * navi.unknownac;
      if (target < -1.5707964f) {
        target = 1.5707964f;
      } else if (target > 1.5707964f) {
        target = -1.5707964f;
      } else {
        target = -target;
      }
      unknown2c = unknown2c + (target - unknown2c) * 0.1f;
    }
  }

  unknown10->unknown40 = mm::Vec3(unknown28, 0.0f, unknown2c);
}

} // namespace gf
