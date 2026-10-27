#pragma once
#include <math.h>

#include "gmk/gmk_form.h"
#include "gmk/gmk_form_pc.h"
#include "gmk/gmk_list.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gmk {

template <typename FORM_PC, typename FORM_PCNPC> bool GmkForm::create(const FORM_PC &formPc) {
  dispose();
  unknown00 = formPc.getData()->unknown14 - formPc.getData()->unknown10 + 1;
  if (unknown00 > MAX_NUM) {
    unknown00 = MAX_NUM;
  } else if (unknown00 == 0) {
    return false;
  }
  const typename FORM_PC::Data *data = formPc.getData();
  unknown10[0] = data->unknown001();
  unknown70[0] = data->unknown0c;
  for (u32 i = 1; i < unknown00; i++) {
    const IGmkList *list = formPc.getBindedFormPcnpcList();
    u32 index = formPc.getData()->unknown10 + i - 1;
    list->getInstNum();
    const typename FORM_PCNPC::Data *memberData = static_cast<const FORM_PCNPC *>(list->getInst(index))->getData();
    unknown10[i] = memberData->unknown001();
    unknown70[i] = memberData->unknown0c;
  }
  validatePosRotY();
  return true;
}

template <typename T, typename BASE> void TGmkFormPcnpcList<T, BASE>::createGmk(void *data) {
  BASE::createGmk(data);
  const IGmkList::CreateInfo &info = this->getCreateInfo();
  const mm::Vec3 &position = info.unknown140;
  mm::Mat44 matrix;
  if (info.unknown150 == 0.0f && fabsf(position.x) <= 1e-6f && fabsf(position.y) <= 1e-6f && fabsf(position.z) <= 1e-6f) {
    return;
  }
  if (info.unknown150 == 0.0f && fabsf(position.x) <= 1e-6f && fabsf(position.y) <= 1e-6f && fabsf(position.z) <= 1e-6f) {
    matrix = mm::Mat44::identity;
  } else {
    matrix.setRotY(info.unknown150);
    mm::Vec3 translation = info.unknown140;
    matrix.rows[3][0] += translation.x;
    matrix.rows[3][1] += translation.y;
    matrix.rows[3][2] += translation.z;
  }
  u32 num = this->getInstNum();
  for (u32 i = 0; i < num; i++) {
    T &gmk = this->gmkInsts[i];
    typename T::Data *gmkData = gmk.getData();
    mm::Vec3 point(gmkData->unknown00, gmkData->unknown04, gmkData->unknown08);
    f32 z0 = matrix.rows[2][0] * point.z;
    gmkData->unknown00 = matrix.rows[3][0] + ((matrix.rows[0][0] * point.x + matrix.rows[1][0] * point.y) + z0);
    f32 z1 = matrix.rows[2][1] * point.z;
    gmkData->unknown04 = matrix.rows[3][1] + ((matrix.rows[0][1] * point.x + matrix.rows[1][1] * point.y) + z1);
    f32 z2 = matrix.rows[2][2] * point.z;
    gmkData->unknown08 = matrix.rows[3][2] + ((matrix.rows[0][2] * point.x + matrix.rows[1][2] * point.y) + z2);
  }
}

template <typename T, typename BASE> void TGmkFormPcList<T, BASE>::createGmk(void *data) {
  BASE::createGmk(data);
  const IGmkList::CreateInfo &info = this->getCreateInfo();
  const mm::Vec3 &position = info.unknown140;
  mm::Mat44 matrix;
  if (info.unknown150 == 0.0f && fabsf(position.x) <= 1e-6f && fabsf(position.y) <= 1e-6f && fabsf(position.z) <= 1e-6f) {
    return;
  }
  if (info.unknown150 == 0.0f && fabsf(position.x) <= 1e-6f && fabsf(position.y) <= 1e-6f && fabsf(position.z) <= 1e-6f) {
    matrix = mm::Mat44::identity;
  } else {
    matrix.setRotY(info.unknown150);
    mm::Vec3 translation = info.unknown140;
    matrix.rows[3][0] += translation.x;
    matrix.rows[3][1] += translation.y;
    matrix.rows[3][2] += translation.z;
  }
  u32 num = this->getInstNum();
  for (u32 i = 0; i < num; i++) {
    T &gmk = this->gmkInsts[i];
    typename T::Data *gmkData = gmk.getData();
    mm::Vec3 point(gmkData->unknown00, gmkData->unknown04, gmkData->unknown08);
    f32 z0 = matrix.rows[2][0] * point.z;
    gmkData->unknown00 = matrix.rows[3][0] + ((matrix.rows[0][0] * point.x + matrix.rows[1][0] * point.y) + z0);
    f32 z1 = matrix.rows[2][1] * point.z;
    gmkData->unknown04 = matrix.rows[3][1] + ((matrix.rows[0][1] * point.x + matrix.rows[1][1] * point.y) + z1);
    f32 z2 = matrix.rows[2][2] * point.z;
    gmkData->unknown08 = matrix.rows[3][2] + ((matrix.rows[0][2] * point.x + matrix.rows[1][2] * point.y) + z2);
    gmkData->unknown0c = info.unknown150 + gmkData->unknown0c;
  }
}

} // namespace gmk
