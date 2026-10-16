#include "battle/misc_battle.h"

#include <math.h>

#include "bdat.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "ml/rand.h"
#include "mm_math/mm_vec3.h"

namespace btl {

constexpr f32 NORMALIZE_LENGTH_MIN = 0.000001f;
constexpr int KIZUNA_STAGE_TO_ID = 7;

f32 Misc::CalcRotY(const mm::Vec3 &direction) { return CalcAngle(mm::Vec3::unitZ, direction, true); }

bool Misc::NormalizeXZ(mm::Vec3 &vector) {
  f32 length = sqrtf(vector.x * vector.x + vector.z * vector.z);
  if (length <= NORMALIZE_LENGTH_MIN) {
    vector = mm::Vec3::unitZ;
    return false;
  }

  f32 scale = 1.0f / length;
  vector.y = 0.0f;
  vector.x = scale * vector.x;
  vector.z = scale * vector.z;
  return true;
}

f32 Misc::CalcLength(const mm::Vec3 &from, const mm::Vec3 &to) {
  f32 x = to.x - from.x;
  f32 y = to.y - from.y;
  f32 z = to.z - from.z;
  return sqrtf(x * x + y * y + z * z);
}

f32 Misc::CalcSquareLength(const mm::Vec3 &from, const mm::Vec3 &to) {
  f32 x = to.x - from.x;
  f32 y = to.y - from.y;
  f32 z = to.z - from.z;
  return x * x + y * y + z * z;
}

f32 Misc::CalcLengthXZ(const mm::Vec3 &from, const mm::Vec3 &to) {
  f32 x = to.x - from.x;
  f32 z = to.z - from.z;
  return sqrtf(x * x + z * z);
}

f32 Misc::CalcSquareLengthXZ(const mm::Vec3 &from, const mm::Vec3 &to) {
  f32 x = to.x - from.x;
  f32 z = to.z - from.z;
  return x * x + z * z;
}

f32 Misc::CalcLengthXZ(const mm::Vec3 &vector) { return sqrtf(vector.x * vector.x + vector.z * vector.z); }

f32 Misc::CalcSquareLengthXZ(const mm::Vec3 &vector) { return vector.x * vector.x + vector.z * vector.z; }

bool Misc::CalcDirectionXZ(const mm::Vec3 &from, const mm::Vec3 &to, mm::Vec3 &direction) {
  direction.x = to.x - from.x;
  direction.z = to.z - from.z;
  return NormalizeXZ(direction);
}

f32 Misc::InnerProductXZ(const mm::Vec3 &left, const mm::Vec3 &right) { return left.x * right.x + left.z * right.z; }

f32 Misc::CalcOuterProductY(const mm::Vec3 &left, const mm::Vec3 &right) { return left.z * right.x - left.x * right.z; }

void Misc::RandomVector(mm::Vec3 &vector) {
  vector.x = 0.5f - ml::mtRandf1();
  vector.y = 0.5f - ml::mtRandf1();
  vector.z = 0.5f - ml::mtRandf1();
  Normalize(vector);
}

void Misc::RandomVectorXZ(mm::Vec3 &vector) {
  vector.x = 0.5f - ml::mtRandf1();
  vector.z = 0.5f - ml::mtRandf1();
  NormalizeXZ(vector);
}

bool Misc::GetObjectTransform(gf::GF_OBJ_HANDLE *handle, mm::Vec3 &transform, TRANS_TYPE type) {
  if (handle == gf::INVALID_HANDLE) {
    return false;
  }

  return GetObjectTransform(gf::GfObjUtil::getObj(handle), transform, type);
}

bool Misc::GetObjectDirection(const gf::GfObj *obj, mm::Vec3 &direction, bool isXZ) {
  if (!GetObjectTransform(obj, direction, TRANS_TYPE_DIRECTION)) {
    return false;
  }

  if (isXZ) {
    NormalizeXZ(direction);
  }

  return true;
}

bool Misc::GetNodePosition(gf::GF_OBJ_HANDLE *handle, const char *node, mm::Vec3 &position) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return false;
  }

  return GetNodePosition(obj, node, position);
}

bool Misc::GetNodePosition(gf::GfObj *obj, const char *node, mm::Vec3 &position) {
  gf::GfObjAcc acc(obj);
  int bone = acc.getBoneIdx(node);
  if (bone < 0) {
    return false;
  }

  fw::Transform transform;
  acc.getBoneTransform(transform, bone);
  position = transform.position;
  return true;
}

int Misc::GetPartyID(const gf::GfObj *obj) {
  if (obj == nullptr) {
    return -1;
  }

  return GetPartyID(obj->handle);
}

void Misc::GetKizunaMinMax(int stage, int &minimum, int &maximum) {
  int id = CovertKizunaStageToID(stage);
  u8 *bdat = gf::GfDataBdat::getFP(gf::BDAT_BTL_KIZUNA);
  minimum = static_cast<u16>(Bdat::getValCheck(bdat, "KizunaMin", id, 2));
  maximum = static_cast<u16>(Bdat::getValCheck(bdat, "KizunaMax", id, 2));
}

int Misc::CovertKizunaStageToID(int stage) { return KIZUNA_STAGE_TO_ID - stage; }

bool Misc::CheckInRange(const mm::Vec3 &position, const mm::Vec3 &target, f32 range, bool isXZ) {
  f32 length = isXZ ? CalcLengthXZ(position, target) : CalcLength(target, position);
  return length <= range;
}

const char *Misc::GetArtsTypeName(int) { return ""; }

} // namespace btl
