#pragma once
#include "dr/dr_mdo_mat.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrResMdoMat;

class DrMdoAnim : public DrMdoMat {
public:
  void setMatAnmFrme(f32 frame);
  static void animcall_UV_Scr_U(DrResMdoMat *mat, f32 *work, f32 value);
  static void animcall_UV_Scr_V(DrResMdoMat *mat, f32 *work, f32 value);
  static void animcall_UV_Trans_U(DrResMdoMat *mat, f32 *work, f32 value);
  static void animcall_UV_Trans_V(DrResMdoMat *mat, f32 *work, f32 value);
  static void animcall_WorkFloat1(DrResMdoMat *mat, f32 *work, f32 value);
  static void animcall_MatAlpha(DrResMdoMat *mat, f32 *work, f32 value);
  static void animcall_MatColorR(DrResMdoMat *mat, f32 *work, f32 value);
  static void animcall_MatColorG(DrResMdoMat *mat, f32 *work, f32 value);
  static void animcall_MatColorB(DrResMdoMat *mat, f32 *work, f32 value);
  static void anmNodeParm_TranX(mm::Vec3 *transform, f32 value);
  static void anmNodeParm_TranY(mm::Vec3 *transform, f32 value);
  static void anmNodeParm_TranZ(mm::Vec3 *transform, f32 value);
  static void anmNodeParm_RotX(mm::Vec3 *transform, f32 value);
  static void anmNodeParm_RotY(mm::Vec3 *transform, f32 value);
  static void anmNodeParm_RotZ(mm::Vec3 *transform, f32 value);
  static void anmNodeParm_SclX(mm::Vec3 *transform, f32 value);
  static void anmNodeParm_SclY(mm::Vec3 *transform, f32 value);
  static void anmNodeParm_SclZ(mm::Vec3 *transform, f32 value);
};

} // namespace ml
