#include "dr/dr_env_coli_obj.h"

#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_env_coli_man.h"
#include "dr/dr_env_coli_parameter.h"
#include "dr/dr_environment_man.h"
#include "dr/dr_ini_sys.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_res_list.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

namespace {

// Inferred role: collision sphere data; original type name unknown.
struct unknown001 {
  u8 _00[0x0c];
  f32 unknown0c; // Inferred role: radius; original member name unknown.
};

// Inferred role: collision data of a non rotated cylinder; original type name unknown.
struct unknown002 {
  u8 _00[0x0c];
  f32 unknown0c; // Inferred role: radius; original member name unknown.
  f32 unknown10; // Inferred role: half height; original member name unknown.
};

// Inferred role: collision data of a non rotated box; original type name unknown.
struct unknown003 {
  u8 _00[0x0c];
  f32 unknown0c;    // Inferred role: radius; original member name unknown.
  f32 unknown10[3]; // Inferred role: half extents; original member name unknown.
};

// Inferred role: collision data of a rotated box or cylinder; original type name unknown.
struct unknown004 {
  u8 _00[0x30];
  f32 unknown30[3]; // Inferred role: center; original member name unknown.
  f32 unknown3c;    // Inferred role: radius; original member name unknown.
  f32 unknown40[3]; // Inferred role: half extents; original member name unknown.
};

// Inferred role: env coli data header; original type name unknown.
struct unknown006 {
  u8 _00[0x04];
  s32 unknown04; // Inferred role: post parameter index; original member name unknown.
  u8 _08[0x18 - 0x08];
  u32 unknown18; // Inferred role: post parameters offset; original member name unknown.
};

// Inferred role: post parameters header; original type name unknown.
struct unknown007 {
  u8 _00[0x04];
  u32 unknown04; // Inferred role: post parameter index list offset; original member name unknown.
  u8 _08[0x0c - 0x08];
  u32 unknown0c; // Inferred role: post data list offset; original member name unknown.
};

// Inferred role: post parameter index; original type name unknown.
struct unknown008 {
  u8 _00[0x04];
  u32 unknown04; // Inferred role: first post data index; original member name unknown.
  s32 unknown08; // Inferred role: post data num; original member name unknown.
  u8 _0c[0x18 - 0x0c];
};

// Inferred role: deletes every object of a list; original name unknown.
void unknown010(DrEnvColiObj *&first, DrEnvColiObj *&last) {
  DrEnvColiObj *object = first;
  while (object != nullptr) {
    DrEnvColiObj *next = object->unknown08;
    delete object;
    object = next;
  }
  first = nullptr;
  last = nullptr;
}

} // namespace

DrEnvColiObj::COLITEST DrEnvColiObj::s_pColiTest[5] = {
    &DrEnvColiObj::envcoli_box,
    &DrEnvColiObj::envcoli_sphere,
    &DrEnvColiObj::envcoli_cylinder,
    &DrEnvColiObj::envcoli_notrot_box,
    &DrEnvColiObj::envcoli_notrot_cylinder,
};

DrEnvColiObj *DrEnvColiMan::createObj(const void *data) {
  DrEnvColiObj *object = new (unknown30->unknown10) DrEnvColiObj(unknown30, data);
  unknown101(unknown10[DrMan::s_nDblStockIdx][0], unknown10[DrMan::s_nDblStockIdx][1], object);
  return object;
}

DrEnvColiObj::DrEnvColiObj(DrMan *man, const void *data) : unknown00(nullptr), unknown08(nullptr), unknown10(nullptr), unknown28(nullptr), unknown30(man), unknown38(0) { setDataAdd(data); }

void DrEnvColiMan::update() {
  bool isChanged = false;
  DrEnvColiObj *object = unknown10[DrMan::s_nDblIdx][0];
  while (object != nullptr) {
    DrEnvColiObj *next = object->unknown08;
    unknown101(unknown00, unknown08, object);
    object = next;
    isChanged = true;
  }
  unknown10[DrMan::s_nDblIdx][0] = nullptr;
  unknown10[DrMan::s_nDblIdx][1] = nullptr;
  object = unknown00;
  while (object != nullptr) {
    DrEnvColiObj *next = object->unknown08;
    if (object->isDeleteCall()) {
      if (object->unknown00 == nullptr) {
        if (object->unknown08 == nullptr) {
          unknown00 = nullptr;
          unknown08 = nullptr;
        } else {
          unknown00 = object->unknown08;
          unknown00->unknown00 = nullptr;
        }
      } else if (object->unknown08 == nullptr) {
        unknown08 = object->unknown00;
        unknown08->unknown08 = nullptr;
      } else {
        object->unknown00->unknown08 = object->unknown08;
        object->unknown08->unknown00 = object->unknown00;
      }
      object->unknown00 = nullptr;
      object->unknown08 = nullptr;
      delete object;
      isChanged = true;
    }
    object = next;
  }
  DrPixlPostParm *postParm = unknown30->unknown120[unknown30->unknown1c98];
  postParm->unknown1104 = postParm->unknown1105[DrMan::s_nDblIdx];
  postParm->unknown1105[DrMan::s_nDblIdx] = false;
  if (!unknown30->unknown1d8e) {
    DrEnvColiObj *selected = unknown00;
    if (selected != nullptr) {
      DrEnvColiResult result;
      mm::Vec3 position(unknown30->unknown580->unknown10->unknown400);
      DrEnvColiObj *hitObject = nullptr;
      DrEnvColiObj *next = selected;
      for (DrEnvColiObj *current = next; current != nullptr; current = next) {
        next = current->unknown08;
        if (!current->isDeleteAll() && current->testEnvColi(&result, position, 0.0f)) {
          hitObject = current;
        }
      }
      if (hitObject != nullptr) {
        selected = hitObject;
      }
      if (unknown38 != selected || unknown8c != result.unknown1c) {
        unknown70 = unknown30->unknown120[unknown30->unknown1c98]->getWeatherFrame();
      }
      DrPixlPostParm *currentParm = unknown30->unknown120[unknown30->unknown1c98];
      s32 weather = currentParm->unknown1084;
      bool isReset = unknown74 != weather;
      updateTime(isReset);
      updateCloudFade(isReset, isChanged);
      unknown74 = weather;
      DrEnvColiParameter parameter(selected, &result, unknown30, this);
      parameter.calcPostEffectParams(isReset);
      unknown38 = selected;
      unknown8c = result.unknown1c;
      return;
    }
    unknown38 = nullptr;
    unknown8c = -1;
  }
  DrEnvColiParameter::updateBloomParams();
}

DrEnvColiParameter::DrEnvColiParameter(DrEnvColiObj *object, DrEnvColiResult *result, DrMan *man, DrEnvColiMan *coliMan) {
  unknown10 = result;
  unknown18 = object;
  unknown00 = man;
  unknown08 = coliMan;
  unknown20 = object->getPostParams();
  unknown28 = reinterpret_cast<const unknown006 *>(object->unknown10)->unknown04;
}

DrEnvColiParameter::~DrEnvColiParameter() {}

void DrEnvColiParameter::calcPostEffectParams(bool isReset) {
  const unknown008 *postIndexList = reinterpret_cast<const unknown008 *>(unknown20 + reinterpret_cast<const unknown007 *>(unknown20)->unknown04);
  const unknown008 *postIndex = &postIndexList[unknown10->unknown1c];
  calcParams(postIndex->unknown04, postIndex->unknown08, isReset);
}

void DrEnvColiParameter::updateBloomParams() {
  DrMan *man = DrMan::getIns();
  DrPixlPostParm *postParm = man->unknown120[man->unknown1c98];
  const DrPixlPostParm &defaultParm = DrMan::getIns()->unknown70->unknown970;
  postParm->unknown40 = defaultParm.unknown40;
  postParm->m_borderBlmMul = defaultParm.m_borderBlmMul;
  postParm->unknown48 = defaultParm.unknown48;
  postParm->unknown4c = defaultParm.unknown4c;
  postParm->unknown50 = defaultParm.unknown50;
  for (int i = 0; i < 3; i++) {
    postParm->unknown54[i] = defaultParm.unknown54[i];
  }
  for (int i = 0; i < 7; i++) {
    postParm->unknown60[i] = defaultParm.unknown60[i];
  }
  for (int i = 0; i < 3; i++) {
    postParm->unknown7c[i] = defaultParm.unknown7c[i];
  }
  for (int i = 0; i < 2; i++) {
    postParm->unknown88[i] = defaultParm.unknown88[i];
  }
  for (int i = 0; i < 3; i++) {
    postParm->unknown90[i] = defaultParm.unknown90[i];
  }
  for (int i = 0; i < 7; i++) {
    postParm->unknown9c[i] = defaultParm.unknown9c[i];
  }
  for (int i = 0; i < 2; i++) {
    postParm->unknownc0[i] = defaultParm.unknownc0[i];
  }
  postParm->unknownc8 = defaultParm.unknownc8;
  postParm->unknowncc = defaultParm.unknowncc;
  postParm->unknownd0 = defaultParm.unknownd0;
  postParm->unknownd4 = defaultParm.unknownd4;
  postParm->unknownd8 = defaultParm.unknownd8;
  postParm->unknowndc = defaultParm.unknowndc;
  postParm->unknowne0 = defaultParm.unknowne0;
  postParm->unknowne4 = defaultParm.unknowne4;
  postParm->unknowne8 = defaultParm.unknowne8;
}

void DrEnvColiParameter::resetToneMapParams(const EnvColiPostParameterVer<10006> *from, const EnvColiPostParameterVer<10006> *to, f32 ratio) {
  DrPixlPostParm *postParm = unknown00->unknown120[unknown00->unknown1c98];
  if (ratio != 0.0f) {
    f32 inverse = 1.0f - ratio;
    postParm->unknown08 = from->unknown00 * ratio + inverse * to->unknown00;
    postParm->unknown0c = from->unknown04 * ratio + inverse * to->unknown04;
    postParm->unknown10 = from->unknown08 * ratio + inverse * to->unknown08;
    postParm->unknown14 = from->unknown0c * ratio + inverse * to->unknown0c;
    postParm->unknown18 = from->unknown10 * ratio + inverse * to->unknown10;
    postParm->unknown1c = from->unknown14 * ratio + inverse * to->unknown14;
    postParm->unknown20 = from->unknown18 * ratio + inverse * to->unknown18;
    postParm->unknown24 = from->unknown1c * ratio + inverse * to->unknown1c;
    postParm->unknown28 = from->unknown20 * ratio + inverse * to->unknown20;
    postParm->unknown2c = from->unknown24 * ratio + inverse * to->unknown24;
    postParm->unknown30 = from->unknown28 * ratio + inverse * to->unknown28;
  } else {
    postParm->unknown08 = from->unknown00;
    postParm->unknown0c = from->unknown04;
    postParm->unknown10 = from->unknown08;
    postParm->unknown14 = from->unknown0c;
    postParm->unknown18 = from->unknown10;
    postParm->unknown1c = from->unknown14;
    postParm->unknown20 = from->unknown18;
    postParm->unknown24 = from->unknown1c;
    postParm->unknown28 = from->unknown20;
    postParm->unknown2c = from->unknown24;
    postParm->unknown30 = from->unknown28;
  }
}

bool DrEnvColiMan::testEnvColi(DrEnvColiResult *result, const mm::Vec3 &position, f32 radius) {
  if (result == nullptr) {
    result = &unknown40;
    result->unknown001();
  }
  bool isHit = false;
  DrEnvColiObj *next = unknown00;
  for (DrEnvColiObj *object = next; object != nullptr; object = next) {
    next = object->unknown08;
    if (!object->isDeleteAll()) {
      isHit |= object->testEnvColi(result, position, radius);
    }
  }
  return isHit;
}

bool DrEnvColiObj::testEnvColi(DrEnvColiResult *result, const mm::Vec3 &position, f32 radius) {
  if (!isPause() && unknown10 != nullptr) {
    return testTreeColi(result, unknown20, position, radius);
  }
  return false;
}

const u8 *DrEnvColiObj::getPostParams() const { return unknown10 + reinterpret_cast<const unknown006 *>(unknown10)->unknown18; }

bool DrEnvColiObj::testTreeColi(DrEnvColiResult *result, const EnvColiListTreeData *tree, const mm::Vec3 &position, f32 radius) {
  bool isHit = false;
  if (!(tree->unknown00[0] + radius < position.x || tree->unknown0c[0] - radius > position.x || tree->unknown00[2] + radius < position.z || tree->unknown0c[2] - radius > position.z ||
        tree->unknown00[1] + radius < position.y || tree->unknown0c[1] - radius > position.y)) {
    u32 childCount = tree->unknown20;
    u32 primCount;
    if (childCount != 0) {
      u8 childHit = 0;
      const u16 *children = reinterpret_cast<const u16 *>(unknown10 + tree->unknown18);
      for (u32 i = 0; i < childCount; i++) {
        const EnvColiListTreeData *base = unknown20;
        childHit |= testTreeColi(result, base + children[i], position, radius) & 1;
      }
      primCount = tree->unknown22;
      isHit = childHit != 0;
    } else {
      primCount = tree->unknown22;
    }
    if (primCount != 0) {
      const u16 *primitives = reinterpret_cast<const u16 *>(unknown10 + tree->unknown1c);
      for (u32 i = 0; i < primCount; i++, primitives++) {
        const unknown005 *base = unknown18;
        u16 index = *primitives;
        const unknown005 *primitive = base + index;
        if (result->unknown00 > primitive->unknown08 || (result->unknown00 == primitive->unknown08 && result->unknown04 > primitive->unknown0a)) {
          continue;
        }
        u16 gblId = primitive->unknown0c;
        if (gblId != 0 && unknown30->isGblIdx(gblId)) {
          continue;
        }
        if (!(this->*s_pColiTest[primitive->unknown04])(unknown10 + primitive->unknown00, position, radius, unknown28[index])) {
          continue;
        }
        result->unknown00 = primitive->unknown08;
        result->unknown04 = primitive->unknown0a;
        result->unknown24 |= primitive->unknown06;
        if (primitive->unknown06 & 2) {
          result->unknown08 = primitive->unknown0e;
        }
        result->unknown0c = primitive->unknown10;
        result->unknown10 = primitive->unknown11;
        result->unknown14 = primitive->unknown12;
        result->unknown18 = primitive->unknown14;
        result->unknown1c = primitive->unknown16;
        result->unknown20 = 0;
        DrEnvColiMan *coliMan = unknown30->unknown100[0]->unknown18;
        const u8 *postParams = getPostParams();
        const unknown007 *header = reinterpret_cast<const unknown007 *>(postParams);
        const unknown008 *postIndex = &reinterpret_cast<const unknown008 *>(postParams + header->unknown04)[result->unknown1c];
        const EnvColiPostData *postData = &reinterpret_cast<const EnvColiPostData *>(postParams + header->unknown0c)[postIndex->unknown04];
        u32 weatherBit = 1 << coliMan->unknown74;
        u32 time = static_cast<s32>(coliMan->unknown68 * 1440.0f);
        const EnvColiPostData *current = nullptr;
        const EnvColiPostData *latest = nullptr;
        s32 count = postIndex->unknown08;
        for (s32 j = 0; j < count; j++, postData++) {
          if (postData->unknown04 & weatherBit) {
            if (latest == nullptr) {
              latest = postData;
            } else if (latest->unknown10 <= postData->unknown10) {
              latest = postData;
            }
            if (postData->unknown10 < time) {
              current = postData;
            }
          }
        }
        if (current != nullptr) {
          latest = current;
        }
        if (latest != nullptr) {
          result->unknown20 = latest->unknown26;
        }
        isHit = true;
      }
    }
  }
  return isHit;
}

DrEnvColiObj::DrEnvColiObj(DrMan *man) : unknown00(nullptr), unknown08(nullptr), unknown10(nullptr), unknown28(nullptr), unknown30(man), unknown38(0) {}

DrEnvColiObj::~DrEnvColiObj() {
  if (unknown28 != nullptr) {
    mtl::MemManager::deallocate(unknown28, 0, false);
    unknown28 = nullptr;
  }
}

DrEnvColiMan::~DrEnvColiMan() { clear(); }

void DrEnvColiMan::clear() {
  for (s32 i = 0; i < 2; i++) {
    unknown010(unknown10[i][0], unknown10[i][1]);
  }
  unknown010(unknown00, unknown08);
}

void DrEnvColiMan::updateTime(bool isReset) {
  if (isReset) {
    unknown70 = unknown30->unknown120[unknown30->unknown1c98]->getWeatherFrame();
  } else {
    unknown70 -= unknown30->unknown1c8c;
    if (unknown70 < 0.0f) {
      unknown70 = 0.0f;
    }
  }
  if (unknown70 != 0.0f) {
    unknown6c = 1.0f / unknown70;
    if (unknown6c > 1.0f) {
      unknown6c = 1.0f;
    }
  } else {
    unknown6c = 1.0f;
  }
  unknown68 = unknown30->unknown1cac;
}

void DrEnvColiMan::updateCloudFade(bool isReset, bool isForce) {
  unknown88 = 1.0f;
  if (isReset) {
    unknown84 = 600.0f;
    unknown88 = 0.0f;
  } else {
    unknown84 -= unknown30->unknown1c8c;
    if (unknown84 < 0.0f) {
      unknown84 = 0.0f;
    } else {
      unknown88 = mm::clamp(1.0f / unknown84, 0.0f, 1.0f);
    }
  }
  if (unknown30->unknown120[unknown30->unknown1c98]->unknown1104 || isForce || unknown30->unknown580->unknown10->unknown9ac) {
    unknown84 = 0.0f;
    unknown88 = 1.0f;
  }
}

void DrEnvColiMan::updateRainDropFade(bool isReset) {
  if (isReset) {
    unknown7c = unknown30->unknown120[unknown30->unknown1c98]->unknown10c0;
  } else {
    unknown7c -= unknown30->unknown1c8c;
    if (unknown7c < 0.0f) {
      unknown7c = 0.0f;
    }
  }
  if (unknown7c != 0.0f) {
    unknown78 = 1.0f / unknown7c;
    if (unknown78 > 1.0f) {
      unknown78 = 1.0f;
    }
  } else {
    unknown78 = 1.0f;
  }
}

void DrEnvColiObj::release() { unknown38 |= 1 << DrMan::s_nDblStockIdx; }

void DrEnvColiObj::setPause(bool isPause) {
  if (isPause) {
    unknown38 |= 4;
  } else {
    unknown38 &= ~4;
  }
}

bool DrEnvColiObj::isPause() const { return (unknown38 >> 2 & 1) != 0; }

u32 DrEnvColiObj::isDeleteCall() const { return unknown38 & (1 << DrMan::s_nDblIdx); }

u32 DrEnvColiObj::isDeleteAll() const { return unknown38 & 3; }

bool DrEnvColiObj::envcoli_box(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *axes) {
  const struct unknown004 *box = reinterpret_cast<const struct unknown004 *>(data);
  f32 cx = box->unknown30[0];
  f32 cy = box->unknown30[1];
  f32 cz = box->unknown30[2];
  f32 dx = position.x - cx;
  f32 dy = position.y - cy;
  f32 dz = position.z - cz;
  f32 radius = box->unknown3c + margin;
  if (!(dx * dx + dy * dy + dz * dz <= radius * radius)) {
    return false;
  }
  f32 a = dx * axes[0].x + dy * axes[0].y + dz * axes[0].z;
  if (!(box->unknown40[0] + margin >= a)) {
    return false;
  }
  if (!(-box->unknown40[0] - margin <= a)) {
    return false;
  }
  f32 c = dx * axes[2].x + dy * axes[2].y + dz * axes[2].z;
  if (!(box->unknown40[2] + margin >= c)) {
    return false;
  }
  if (!(-box->unknown40[2] - margin <= c)) {
    return false;
  }
  f32 b = dx * axes[1].x + dy * axes[1].y + dz * axes[1].z;
  if (!(box->unknown40[1] + margin >= b)) {
    return false;
  }
  return -box->unknown40[1] - margin <= b;
}

bool DrEnvColiObj::envcoli_sphere(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *center) {
  const struct unknown001 *sphere = reinterpret_cast<const struct unknown001 *>(data);
  f32 dx = position.x - center->x;
  f32 dy = position.y - center->y;
  f32 dz = position.z - center->z;
  f32 radius = sphere->unknown0c + margin;
  return dx * dx + dy * dy + dz * dz <= radius * radius;
}

bool DrEnvColiObj::envcoli_cylinder(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *axes) {
  const struct unknown004 *cylinder = reinterpret_cast<const struct unknown004 *>(data);
  f32 cx = cylinder->unknown30[0];
  f32 cy = cylinder->unknown30[1];
  f32 cz = cylinder->unknown30[2];
  f32 dx = position.x - cx;
  f32 dy = position.y - cy;
  f32 dz = position.z - cz;
  f32 radius = cylinder->unknown3c + margin;
  if (!(dx * dx + dy * dy + dz * dz <= radius * radius)) {
    return false;
  }
  f32 height = dx * axes[1].x + dy * axes[1].y + dz * axes[1].z;
  if (!(cylinder->unknown40[1] + margin >= height)) {
    return false;
  }
  if (!(-cylinder->unknown40[1] - margin <= height)) {
    return false;
  }
  f32 a = dx * axes[0].x + dy * axes[0].y + dz * axes[0].z;
  f32 b = dx * axes[2].x + dy * axes[2].y + dz * axes[2].z;
  f32 limit = cylinder->unknown40[0] + margin;
  return a * a + b * b <= limit * limit;
}

bool DrEnvColiObj::envcoli_notrot_box(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *center) {
  const struct unknown003 *box = reinterpret_cast<const struct unknown003 *>(data);
  f32 dx = position.x - center->x;
  f32 dy = position.y - center->y;
  f32 dz = position.z - center->z;
  f32 radius = box->unknown0c + margin;
  if (!(dx * dx + dy * dy + dz * dz <= radius * radius)) {
    return false;
  }
  if (!(box->unknown10[0] + margin >= dx)) {
    return false;
  }
  if (!(-box->unknown10[0] - margin <= dx)) {
    return false;
  }
  if (!(box->unknown10[2] + margin >= dz)) {
    return false;
  }
  if (!(-box->unknown10[2] - margin <= dz)) {
    return false;
  }
  if (!(box->unknown10[1] + margin >= dy)) {
    return false;
  }
  return -box->unknown10[1] - margin <= dy;
}

bool DrEnvColiObj::envcoli_notrot_cylinder(const u8 *data, const mm::Vec3 &position, f32 margin, const mm::Vec3 *center) {
  const unknown002 *cylinder = reinterpret_cast<const unknown002 *>(data);
  f32 dy = position.y - center->y;
  if (!(cylinder->unknown10 + margin >= dy)) {
    return false;
  }
  if (!(-cylinder->unknown10 - margin <= dy)) {
    return false;
  }
  f32 dx = position.x - center->x;
  f32 dz = position.z - center->z;
  f32 radius = cylinder->unknown0c + margin;
  return dx * dx + dz * dz <= radius * radius;
}

} // namespace ml
