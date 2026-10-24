#include "dr/dr_mdo_anim.h"

#include "dr/dr_res_mdo_mat.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_vec3.h"

namespace ml {

void DrMdoAnim::animcall_UV_Scr_U(DrResMdoMat *mat, f32 *work, f32 value) { work[0] = value; }

void DrMdoAnim::animcall_UV_Scr_V(DrResMdoMat *mat, f32 *work, f32 value) { work[5] = value; }

void DrMdoAnim::animcall_UV_Trans_U(DrResMdoMat *mat, f32 *work, f32 value) { work[3] = value; }

void DrMdoAnim::animcall_UV_Trans_V(DrResMdoMat *mat, f32 *work, f32 value) { work[7] = value; }

void DrMdoAnim::animcall_WorkFloat1(DrResMdoMat *mat, f32 *work, f32 value) { work[0] = value; }

void DrMdoAnim::animcall_MatAlpha(DrResMdoMat *mat, f32 *work, f32 value) { mat->setAlpha(value); }

void DrMdoAnim::animcall_MatColorR(DrResMdoMat *mat, f32 *work, f32 value) { mat->unknown08.r = value; }

void DrMdoAnim::animcall_MatColorG(DrResMdoMat *mat, f32 *work, f32 value) { mat->unknown08.g = value; }

void DrMdoAnim::animcall_MatColorB(DrResMdoMat *mat, f32 *work, f32 value) { mat->unknown08.b = value; }

void DrMdoAnim::anmNodeParm_TranX(mm::Vec3 *transform, f32 value) { transform[0].x = value; }

void DrMdoAnim::anmNodeParm_TranY(mm::Vec3 *transform, f32 value) { transform[0].y = value; }

void DrMdoAnim::anmNodeParm_TranZ(mm::Vec3 *transform, f32 value) { transform[0].z = value; }

void DrMdoAnim::anmNodeParm_RotX(mm::Vec3 *transform, f32 value) { transform[1].x = value; }

void DrMdoAnim::anmNodeParm_RotY(mm::Vec3 *transform, f32 value) { transform[1].y = value; }

void DrMdoAnim::anmNodeParm_RotZ(mm::Vec3 *transform, f32 value) { transform[1].z = value; }

void DrMdoAnim::anmNodeParm_SclX(mm::Vec3 *transform, f32 value) { transform[2].x = value; }

void DrMdoAnim::anmNodeParm_SclY(mm::Vec3 *transform, f32 value) { transform[2].y = value; }

void DrMdoAnim::anmNodeParm_SclZ(mm::Vec3 *transform, f32 value) { transform[2].z = value; }

} // namespace ml
