#include "dr/dr_env_coli_obj.h"

#include "cloud/cloud_calc_params.h"
#include "cloud/cloud_man.h"
#include "cloud/cloud_obj_man.h"
#include "dr/dr_calc_man.h"
#include "dr/dr_calc_view_work.h"
#include "dr/dr_env_coli_man.h"
#include "dr/dr_env_coli_parameter.h"
#include "dr/dr_environment_man.h"
#include "dr/dr_ini_sys.h"
#include "dr/dr_man.h"
#include "dr/dr_pixl_post_parm.h"
#include "dr/dr_res_list.h"
#include "mm_math/mm_col3.h"
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
  u8 _10[0x1c - 0x10];
  u32 unknown1c; // Inferred role: cloud sky parameter list offset; original member name unknown.
  u8 _20[0x24 - 0x20];
  u32 unknown24; // Inferred role: cloud plane parameter list offset; original member name unknown.
  u8 _28[0x2c - 0x28];
  u32 unknown2c; // Inferred role: cloud parameter list offset; original member name unknown.
  u8 _30[0x34 - 0x30];
  u32 unknown34; // Inferred role: cloud model parameter list offset; original member name unknown.
  u32 unknown38; // Inferred role: version, 0x1001 has the longer parameter records; original member name unknown.
  u8 _3c[0x40 - 0x3c];
  u32 unknown40; // Inferred role: cloud light parameter list offset; original member name unknown.
};

// Inferred role: cloud parameter record; original type name unknown.
struct unknown011 {
  f32 unknown00[2]; // Inferred role: cloud height; original member name unknown.
  u16 unknown08[2]; // Inferred role: sky parameter index; original member name unknown.
  u16 unknown0c[2]; // Inferred role: plane parameter index; original member name unknown.
  u16 unknown10[2]; // Inferred role: model parameter index; original member name unknown.
  u16 unknown14;    // Inferred role: light parameter index; original member name unknown.
};

// Inferred role: cloud plane parameters; original type name unknown.
struct unknown012 {
  f32 unknown00[0x27];
};

// Inferred role: cloud sky parameters; original type name unknown.
struct unknown013 {
  f32 unknown00[0x19];
};

// Inferred role: cloud light parameters; original type name unknown.
struct unknown014 {
  f32 unknown00[0x22];
};

// Inferred role: cloud model parameters; original type name unknown.
struct unknown015 {
  f32 unknown00[10];
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

// Inferred role: copies the leading parameters (0x00 to 0x53: tone map, border blm and blm parameter groups) of a post parameter record, the same in the versions 10003 to 10006; original name
// unknown.
template <int From, int To> void unknown020(const EnvColiPostParameterVer<From> &from, EnvColiPostParameterVer<To> &to) {
  to.unknown00 = from.unknown00;
  to.unknown04 = from.unknown04;
  to.unknown08 = from.unknown08;
  to.unknown0c = from.unknown0c;
  to.unknown10 = from.unknown10;
  to.unknown14 = from.unknown14;
  to.unknown18 = from.unknown18;
  to.unknown1c = from.unknown1c;
  to.unknown20 = from.unknown20;
  to.unknown24 = from.unknown24;
  to.unknown28 = from.unknown28;
  for (int i = 0; i < 5; i++) {
    to.unknown2c[i] = from.unknown2c[i];
  }
  for (int i = 0; i < 5; i++) {
    to.unknown40[i] = from.unknown40[i];
  }
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
  DrEnvColiObj *object = new (m_drMan->unknown10) DrEnvColiObj(m_drMan, data);
  unknown101(unknown10[DrMan::s_nDblStockIdx][0], unknown10[DrMan::s_nDblStockIdx][1], object);
  return object;
}

DrEnvColiObj::DrEnvColiObj(DrMan *man, const void *data) : unknown00(nullptr), unknown08(nullptr), unknown10(nullptr), unknown28(nullptr), m_drMan(man), unknown38(0) { setDataAdd(data); }

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
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  postParm->unknown1104 = postParm->unknown1105[DrMan::s_nDblIdx];
  postParm->unknown1105[DrMan::s_nDblIdx] = false;
  if (!m_drMan->unknown1d8e) {
    DrEnvColiObj *selected = unknown00;
    if (selected != nullptr) {
      DrEnvColiResult result;
      mm::Vec3 position(m_drMan->m_drCalcMan->m_drCalcViewWork->unknown400);
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
        unknown70 = m_drMan->unknown120[m_drMan->unknown1c98]->getWeatherFrame();
      }
      DrPixlPostParm *currentParm = m_drMan->unknown120[m_drMan->unknown1c98];
      s32 weather = currentParm->m_weather;
      bool isReset = unknown74 != weather;
      updateTime(isReset);
      updateCloudFade(isReset, isChanged);
      unknown74 = weather;
      DrEnvColiParameter parameter(selected, &result, m_drMan, this);
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
  m_drEnvColiResult = result;
  m_drEnvColiObj = object;
  m_drMan = man;
  m_drEnvColiMan = coliMan;
  unknown20 = object->getPostParams();
  unknown28 = reinterpret_cast<const unknown006 *>(object->unknown10)->unknown04;
}

DrEnvColiParameter::~DrEnvColiParameter() {}

void DrEnvColiParameter::calcPostEffectParams(bool isReset) {
  const unknown008 *postIndexList = reinterpret_cast<const unknown008 *>(unknown20 + reinterpret_cast<const unknown007 *>(unknown20)->unknown04);
  const unknown008 *postIndex = &postIndexList[m_drEnvColiResult->unknown1c];
  calcParams(postIndex->unknown04, postIndex->unknown08, isReset);
}

void DrEnvColiParameter::updateBloomParams() {
  DrMan *man = DrMan::getIns();
  DrPixlPostParm *postParm = man->unknown120[man->unknown1c98];
  const DrPixlPostParm &defaultParm = DrMan::getIns()->m_drIniSys->m_drPixlPostParm;
  postParm->m_borderBlmSub = defaultParm.m_borderBlmSub;
  postParm->m_borderBlmMul = defaultParm.m_borderBlmMul;
  postParm->m_borderBlmSecSub = defaultParm.m_borderBlmSecSub;
  postParm->m_borderBlmSecMul = defaultParm.m_borderBlmSecMul;
  postParm->m_borderBlmMax = defaultParm.m_borderBlmMax;
  for (int i = 0; i < 10; i++) {
    postParm->m_blmWeight[i] = defaultParm.m_blmWeight[i];
  }
  for (int i = 0; i < 15; i++) {
    postParm->m_blmStr[i] = defaultParm.m_blmStr[i];
  }
  postParm->unknownc0[0] = defaultParm.unknownc0[0];
  postParm->unknownc4 = defaultParm.unknownc4;
  postParm->m_blmLensSub = defaultParm.m_blmLensSub;
  postParm->m_blmLensMul = defaultParm.m_blmLensMul;
  postParm->m_blmLensMax = defaultParm.m_blmLensMax;
  postParm->m_blmLensRot = defaultParm.m_blmLensRot;
  postParm->m_blmLensWeight = defaultParm.m_blmLensWeight;
  postParm->m_blmLensDecay = defaultParm.m_blmLensDecay;
  postParm->m_blmLensStrength = defaultParm.m_blmLensStrength;
  postParm->m_blmLensParmMax = defaultParm.m_blmLensParmMax;
  postParm->m_blmLensUVDecay = defaultParm.m_blmLensUVDecay;
}

// Written statement by statement as in the original (0x71007d5770): the game's code is straight-line, one blend or fade statement per parameter, in the order of the destination members (source
// indices 7, 8, 6 for the plane and light groups). Checked with Clang 3.9.1: a loop over a run of up to 14 elements (6 or 10 elements, or the 3-entry index table 7, 8, 6) is fully unrolled and gives
// the same code, but the runs of 20, 22 or 29 elements (a loop over the 29-entry index table of the plane group included) stay rolled loops (1172 to 1243 instructions against 1328), and the fade
// statements write distinct members of CloudCalcParams. So the blocks cannot be loops; the statements the game holds are written out (decisions of 2026-11-13 ruling 8 and 2026-11-14 P3).
void DrEnvColiParameter::updateCloudParams(f32 ratio, bool, const EnvColiPostData *from, const EnvColiPostData *to) {
  unknown012 blendPlane;
  unknown013 blendSky;
  unknown015 blendModel;
  unknown014 blendLight;
  cloud::CloudMan *cloudMan = m_drMan->unknown1e00;
  u32 cldNum = cloudMan->getCldNum();
  const unknown007 *header = reinterpret_cast<const unknown007 *>(unknown20);
  u32 sizeCloud = header->unknown38 == 0x1001 ? 0x20 : 0x14;
  u32 sizePlane = header->unknown38 == 0x1001 ? 0x9c : 0x78;
  u32 sizeSky = header->unknown38 == 0x1001 ? 100 : 0x60;
  const u8 *clouds = unknown20 + header->unknown2c;
  const u8 *listPlane = unknown20 + header->unknown24;
  const u8 *listSky = unknown20 + header->unknown1c;
  const u8 *listModel = unknown20 + header->unknown34;
  const u8 *listLight = unknown20 + header->unknown40;
  const unknown011 *other = reinterpret_cast<const unknown011 *>(clouds + to->unknown2c * sizeCloud);
  const unknown011 *cloud = reinterpret_cast<const unknown011 *>(clouds + from->unknown2c * sizeCloud);
  const unknown012 *paramPlane = reinterpret_cast<const unknown012 *>(listPlane + cloud->unknown0c[cldNum] * sizePlane);
  const unknown013 *paramSky = reinterpret_cast<const unknown013 *>(listSky + cloud->unknown08[cldNum] * sizeSky);
  const unknown015 *paramModel = reinterpret_cast<const unknown015 *>(listModel + cloud->unknown10[cldNum] * 0x28);
  const unknown014 *paramLight = reinterpret_cast<const unknown014 *>(listLight + cloud->unknown14 * 0x88);
  cloudMan->setHeight(cloud->unknown00[cldNum]);
  if (ratio != 0.0f) {
    f32 inverse = 1.0f - ratio;
    if ((from->unknown08 & EnvColiPostData::FLAG_UNKNOWN_1) != 0 && (to->unknown08 & EnvColiPostData::FLAG_UNKNOWN_1) != 0) {
      const unknown012 *otherPlane = reinterpret_cast<const unknown012 *>(listPlane + other->unknown0c[cldNum] * sizePlane);
      blendPlane.unknown00[0] = paramPlane->unknown00[0] * ratio + inverse * otherPlane->unknown00[0];
      blendPlane.unknown00[1] = paramPlane->unknown00[1] * ratio + inverse * otherPlane->unknown00[1];
      blendPlane.unknown00[2] = paramPlane->unknown00[2] * ratio + inverse * otherPlane->unknown00[2];
      blendPlane.unknown00[3] = paramPlane->unknown00[3] * ratio + inverse * otherPlane->unknown00[3];
      blendPlane.unknown00[4] = paramPlane->unknown00[4] * ratio + inverse * otherPlane->unknown00[4];
      blendPlane.unknown00[5] = paramPlane->unknown00[5] * ratio + inverse * otherPlane->unknown00[5];
      blendPlane.unknown00[7] = paramPlane->unknown00[7] * ratio + inverse * otherPlane->unknown00[7];
      blendPlane.unknown00[8] = paramPlane->unknown00[8] * ratio + inverse * otherPlane->unknown00[8];
      blendPlane.unknown00[6] = paramPlane->unknown00[6] * ratio + inverse * otherPlane->unknown00[6];
      blendPlane.unknown00[9] = paramPlane->unknown00[9] * ratio + inverse * otherPlane->unknown00[9];
      blendPlane.unknown00[10] = paramPlane->unknown00[10] * ratio + inverse * otherPlane->unknown00[10];
      blendPlane.unknown00[11] = paramPlane->unknown00[11] * ratio + inverse * otherPlane->unknown00[11];
      blendPlane.unknown00[12] = paramPlane->unknown00[12] * ratio + inverse * otherPlane->unknown00[12];
      blendPlane.unknown00[13] = paramPlane->unknown00[13] * ratio + inverse * otherPlane->unknown00[13];
      blendPlane.unknown00[14] = paramPlane->unknown00[14] * ratio + inverse * otherPlane->unknown00[14];
      blendPlane.unknown00[15] = paramPlane->unknown00[15] * ratio + inverse * otherPlane->unknown00[15];
      blendPlane.unknown00[16] = paramPlane->unknown00[16] * ratio + inverse * otherPlane->unknown00[16];
      blendPlane.unknown00[17] = paramPlane->unknown00[17] * ratio + inverse * otherPlane->unknown00[17];
      blendPlane.unknown00[18] = paramPlane->unknown00[18] * ratio + inverse * otherPlane->unknown00[18];
      blendPlane.unknown00[19] = paramPlane->unknown00[19] * ratio + inverse * otherPlane->unknown00[19];
      blendPlane.unknown00[20] = paramPlane->unknown00[20] * ratio + inverse * otherPlane->unknown00[20];
      blendPlane.unknown00[21] = paramPlane->unknown00[21] * ratio + inverse * otherPlane->unknown00[21];
      blendPlane.unknown00[22] = paramPlane->unknown00[22] * ratio + inverse * otherPlane->unknown00[22];
      blendPlane.unknown00[23] = paramPlane->unknown00[23] * ratio + inverse * otherPlane->unknown00[23];
      blendPlane.unknown00[24] = paramPlane->unknown00[24] * ratio + inverse * otherPlane->unknown00[24];
      blendPlane.unknown00[25] = paramPlane->unknown00[25] * ratio + inverse * otherPlane->unknown00[25];
      blendPlane.unknown00[26] = paramPlane->unknown00[26] * ratio + inverse * otherPlane->unknown00[26];
      blendPlane.unknown00[27] = paramPlane->unknown00[27] * ratio + inverse * otherPlane->unknown00[27];
      blendPlane.unknown00[28] = paramPlane->unknown00[28] * ratio + inverse * otherPlane->unknown00[28];
      if (header->unknown38 == 0x1001) {
        blendPlane.unknown00[0x1e] = paramPlane->unknown00[0x1e];
        blendPlane.unknown00[0x1f] = paramPlane->unknown00[0x1f];
        blendPlane.unknown00[0x20] = paramPlane->unknown00[0x20];
        blendPlane.unknown00[0x21] = paramPlane->unknown00[0x21];
        blendPlane.unknown00[0x22] = paramPlane->unknown00[0x22];
        blendPlane.unknown00[0x23] = paramPlane->unknown00[0x23];
        blendPlane.unknown00[0x24] = paramPlane->unknown00[0x24];
        blendPlane.unknown00[0x25] = paramPlane->unknown00[0x25];
        blendPlane.unknown00[0x26] = paramPlane->unknown00[0x26];
      }
      paramPlane = &blendPlane;
    }
    if ((from->unknown08 & EnvColiPostData::FLAG_UNKNOWN_5) != 0 && (to->unknown08 & EnvColiPostData::FLAG_UNKNOWN_5) != 0) {
      const unknown014 *otherLight = reinterpret_cast<const unknown014 *>(listLight + other->unknown14 * 0x88);
      blendLight.unknown00[0] = paramLight->unknown00[0] * ratio + inverse * otherLight->unknown00[0];
      blendLight.unknown00[1] = paramLight->unknown00[1] * ratio + inverse * otherLight->unknown00[1];
      blendLight.unknown00[2] = paramLight->unknown00[2] * ratio + inverse * otherLight->unknown00[2];
      blendLight.unknown00[3] = paramLight->unknown00[3] * ratio + inverse * otherLight->unknown00[3];
      blendLight.unknown00[4] = paramLight->unknown00[4] * ratio + inverse * otherLight->unknown00[4];
      blendLight.unknown00[5] = paramLight->unknown00[5] * ratio + inverse * otherLight->unknown00[5];
      blendLight.unknown00[7] = paramLight->unknown00[7] * ratio + inverse * otherLight->unknown00[7];
      blendLight.unknown00[8] = paramLight->unknown00[8] * ratio + inverse * otherLight->unknown00[8];
      blendLight.unknown00[6] = paramLight->unknown00[6] * ratio + inverse * otherLight->unknown00[6];
      blendLight.unknown00[9] = paramLight->unknown00[9] * ratio + inverse * otherLight->unknown00[9];
      blendLight.unknown00[10] = paramLight->unknown00[10] * ratio + inverse * otherLight->unknown00[10];
      blendLight.unknown00[11] = paramLight->unknown00[11] * ratio + inverse * otherLight->unknown00[11];
      blendLight.unknown00[12] = paramLight->unknown00[12] * ratio + inverse * otherLight->unknown00[12];
      blendLight.unknown00[13] = paramLight->unknown00[13] * ratio + inverse * otherLight->unknown00[13];
      blendLight.unknown00[14] = paramLight->unknown00[14] * ratio + inverse * otherLight->unknown00[14];
      blendLight.unknown00[15] = paramLight->unknown00[15] * ratio + inverse * otherLight->unknown00[15];
      blendLight.unknown00[16] = paramLight->unknown00[16] * ratio + inverse * otherLight->unknown00[16];
      blendLight.unknown00[17] = paramLight->unknown00[17] * ratio + inverse * otherLight->unknown00[17];
      blendLight.unknown00[18] = paramLight->unknown00[18] * ratio + inverse * otherLight->unknown00[18];
      blendLight.unknown00[19] = paramLight->unknown00[19] * ratio + inverse * otherLight->unknown00[19];
      blendLight.unknown00[20] = paramLight->unknown00[20] * ratio + inverse * otherLight->unknown00[20];
      blendLight.unknown00[21] = paramLight->unknown00[21] * ratio + inverse * otherLight->unknown00[21];
      blendLight.unknown00[22] = paramLight->unknown00[22] * ratio + inverse * otherLight->unknown00[22];
      blendLight.unknown00[23] = paramLight->unknown00[23] * ratio + inverse * otherLight->unknown00[23];
      blendLight.unknown00[24] = paramLight->unknown00[24] * ratio + inverse * otherLight->unknown00[24];
      blendLight.unknown00[25] = paramLight->unknown00[25] * ratio + inverse * otherLight->unknown00[25];
      blendLight.unknown00[26] = paramLight->unknown00[26] * ratio + inverse * otherLight->unknown00[26];
      blendLight.unknown00[27] = paramLight->unknown00[27] * ratio + inverse * otherLight->unknown00[27];
      blendLight.unknown00[28] = paramLight->unknown00[28] * ratio + inverse * otherLight->unknown00[28];
      blendLight.unknown00[0x1f] = paramLight->unknown00[0x1f] * ratio + inverse * otherLight->unknown00[0x1f];
      blendLight.unknown00[0x20] = paramLight->unknown00[0x20] * ratio + inverse * otherLight->unknown00[0x20];
      blendLight.unknown00[0x21] = paramLight->unknown00[0x21] * ratio + inverse * otherLight->unknown00[0x21];
      blendLight.unknown00[0x1e] = paramLight->unknown00[0x1e];
      paramLight = &blendLight;
    }
    if ((from->unknown08 & EnvColiPostData::FLAG_UNKNOWN_3) != 0 && (to->unknown08 & EnvColiPostData::FLAG_UNKNOWN_3) != 0) {
      const unknown013 *otherSky = reinterpret_cast<const unknown013 *>(listSky + other->unknown08[cldNum] * sizeSky);
      blendSky.unknown00[0] = paramSky->unknown00[0] * ratio + inverse * otherSky->unknown00[0];
      blendSky.unknown00[1] = paramSky->unknown00[1] * ratio + inverse * otherSky->unknown00[1];
      blendSky.unknown00[2] = paramSky->unknown00[2] * ratio + inverse * otherSky->unknown00[2];
      blendSky.unknown00[3] = paramSky->unknown00[3] * ratio + inverse * otherSky->unknown00[3];
      blendSky.unknown00[4] = paramSky->unknown00[4] * ratio + inverse * otherSky->unknown00[4];
      blendSky.unknown00[5] = paramSky->unknown00[5] * ratio + inverse * otherSky->unknown00[5];
      blendSky.unknown00[6] = paramSky->unknown00[6] * ratio + inverse * otherSky->unknown00[6];
      blendSky.unknown00[7] = paramSky->unknown00[7] * ratio + inverse * otherSky->unknown00[7];
      blendSky.unknown00[8] = paramSky->unknown00[8] * ratio + inverse * otherSky->unknown00[8];
      blendSky.unknown00[9] = paramSky->unknown00[9] * ratio + inverse * otherSky->unknown00[9];
      blendSky.unknown00[10] = paramSky->unknown00[10] * ratio + inverse * otherSky->unknown00[10];
      blendSky.unknown00[11] = paramSky->unknown00[11] * ratio + inverse * otherSky->unknown00[11];
      blendSky.unknown00[12] = paramSky->unknown00[12] * ratio + inverse * otherSky->unknown00[12];
      blendSky.unknown00[13] = paramSky->unknown00[13] * ratio + inverse * otherSky->unknown00[13];
      blendSky.unknown00[14] = paramSky->unknown00[14] * ratio + inverse * otherSky->unknown00[14];
      blendSky.unknown00[15] = paramSky->unknown00[15] * ratio + inverse * otherSky->unknown00[15];
      blendSky.unknown00[16] = paramSky->unknown00[16] * ratio + inverse * otherSky->unknown00[16];
      blendSky.unknown00[17] = paramSky->unknown00[17] * ratio + inverse * otherSky->unknown00[17];
      blendSky.unknown00[18] = paramSky->unknown00[18] * ratio + inverse * otherSky->unknown00[18];
      blendSky.unknown00[19] = paramSky->unknown00[19] * ratio + inverse * otherSky->unknown00[19];
      blendSky.unknown00[20] = paramSky->unknown00[20] * ratio + inverse * otherSky->unknown00[20];
      blendSky.unknown00[21] = paramSky->unknown00[21] * ratio + inverse * otherSky->unknown00[21];
      if (header->unknown38 == 0x1001) {
        blendSky.unknown00[0x18] = paramSky->unknown00[0x18];
      }
      paramSky = &blendSky;
    }
    if ((from->unknown08 & EnvColiPostData::FLAG_UNKNOWN_4) != 0 && (to->unknown08 & EnvColiPostData::FLAG_UNKNOWN_4) != 0) {
      const unknown015 *otherModel = reinterpret_cast<const unknown015 *>(listModel + other->unknown10[cldNum] * 0x28);
      blendModel.unknown00[0] = paramModel->unknown00[0] * ratio + inverse * otherModel->unknown00[0];
      blendModel.unknown00[1] = paramModel->unknown00[1] * ratio + inverse * otherModel->unknown00[1];
      blendModel.unknown00[2] = paramModel->unknown00[2] * ratio + inverse * otherModel->unknown00[2];
      blendModel.unknown00[3] = paramModel->unknown00[3] * ratio + inverse * otherModel->unknown00[3];
      blendModel.unknown00[4] = paramModel->unknown00[4] * ratio + inverse * otherModel->unknown00[4];
      blendModel.unknown00[5] = paramModel->unknown00[5] * ratio + inverse * otherModel->unknown00[5];
      blendModel.unknown00[6] = paramModel->unknown00[6] * ratio + inverse * otherModel->unknown00[6];
      blendModel.unknown00[7] = paramModel->unknown00[7] * ratio + inverse * otherModel->unknown00[7];
      blendModel.unknown00[8] = paramModel->unknown00[8] * ratio + inverse * otherModel->unknown00[8];
      blendModel.unknown00[9] = paramModel->unknown00[9] * ratio + inverse * otherModel->unknown00[9];
      paramModel = &blendModel;
    }
  }
  f32 fade = m_drEnvColiMan->unknown88;
  if ((from->unknown08 & EnvColiPostData::FLAG_UNKNOWN_1) != 0) {
    cloud::CloudCalcParams *params = cloudMan->unknown50->unknown38;
    params->unknown1b8[0].r += fade * (paramPlane->unknown00[0] - params->unknown1b8[0].r);
    params->unknown1b8[0].g += fade * (paramPlane->unknown00[1] - params->unknown1b8[0].g);
    params->unknown1b8[0].b += fade * (paramPlane->unknown00[2] - params->unknown1b8[0].b);
    params->unknown1b8[1].r += fade * (paramPlane->unknown00[3] - params->unknown1b8[1].r);
    params->unknown1b8[1].g += fade * (paramPlane->unknown00[4] - params->unknown1b8[1].g);
    params->unknown1b8[1].b += fade * (paramPlane->unknown00[5] - params->unknown1b8[1].b);
    params->unknown1d0 += fade * (paramPlane->unknown00[7] - params->unknown1d0);
    params->unknown1d4 += fade * (paramPlane->unknown00[8] - params->unknown1d4);
    params->unknown1dc += fade * (paramPlane->unknown00[6] - params->unknown1dc);
    params->unknown1e0[0] += fade * (paramPlane->unknown00[9] - params->unknown1e0[0]);
    params->unknown1e0[1] += fade * (paramPlane->unknown00[10] - params->unknown1e0[1]);
    params->unknown1e0[2] += fade * (paramPlane->unknown00[11] - params->unknown1e0[2]);
    params->unknown1e0[3] += fade * (paramPlane->unknown00[12] - params->unknown1e0[3]);
    params->unknown1e0[4] += fade * (paramPlane->unknown00[13] - params->unknown1e0[4]);
    params->unknown1e0[5] += fade * (paramPlane->unknown00[14] - params->unknown1e0[5]);
    params->unknown1e0[6] += fade * (paramPlane->unknown00[15] - params->unknown1e0[6]);
    params->unknown1e0[7] += fade * (paramPlane->unknown00[16] - params->unknown1e0[7]);
    params->unknown1e0[8] += fade * (paramPlane->unknown00[17] - params->unknown1e0[8]);
    params->unknown1e0[9] += fade * (paramPlane->unknown00[18] - params->unknown1e0[9]);
    params->unknown1e0[10] += fade * (paramPlane->unknown00[19] - params->unknown1e0[10]);
    params->unknown1e0[11] += fade * (paramPlane->unknown00[20] - params->unknown1e0[11]);
    params->unknown1e0[12] += fade * (paramPlane->unknown00[21] - params->unknown1e0[12]);
    params->unknown1e0[13] += fade * (paramPlane->unknown00[22] - params->unknown1e0[13]);
    params->unknown1e0[14] += fade * (paramPlane->unknown00[23] - params->unknown1e0[14]);
    params->unknown1e0[15] += fade * (paramPlane->unknown00[24] - params->unknown1e0[15]);
    params->unknown1e0[16] += fade * (paramPlane->unknown00[25] - params->unknown1e0[16]);
    params->unknown1e0[17] += fade * (paramPlane->unknown00[26] - params->unknown1e0[17]);
    params->unknown1e0[18] += fade * (paramPlane->unknown00[27] - params->unknown1e0[18]);
    params->unknown1e0[19] += fade * (paramPlane->unknown00[28] - params->unknown1e0[19]);
    if (header->unknown38 == 0x1001) {
      params->unknown1d8 = paramPlane->unknown00[0x1e];
      params->unknown230[0] = paramPlane->unknown00[0x1f];
      params->unknown230[1] = paramPlane->unknown00[0x20];
      params->unknown230[2] = paramPlane->unknown00[0x21];
      params->unknown230[3] = paramPlane->unknown00[0x22];
      params->unknown230[4] = paramPlane->unknown00[0x23];
      params->unknown230[5] = paramPlane->unknown00[0x24];
      params->unknown230[6] = paramPlane->unknown00[0x25];
      params->unknown230[7] = paramPlane->unknown00[0x26];
    }
  }
  if ((from->unknown08 & EnvColiPostData::FLAG_UNKNOWN_5) != 0) {
    cloud::CloudCalcParams *params = cloudMan->unknown50->unknown38;
    params->unknown254[0] += fade * (paramLight->unknown00[0] - params->unknown254[0]);
    params->unknown254[1] += fade * (paramLight->unknown00[1] - params->unknown254[1]);
    params->unknown254[2] += fade * (paramLight->unknown00[2] - params->unknown254[2]);
    params->unknown254[3] += fade * (paramLight->unknown00[3] - params->unknown254[3]);
    params->unknown254[4] += fade * (paramLight->unknown00[4] - params->unknown254[4]);
    params->unknown254[5] += fade * (paramLight->unknown00[5] - params->unknown254[5]);
    params->unknown26c += fade * (paramLight->unknown00[7] - params->unknown26c);
    params->unknown270 += fade * (paramLight->unknown00[8] - params->unknown270);
    params->unknown278 += fade * (paramLight->unknown00[6] - params->unknown278);
    params->unknown27c[0] += fade * (paramLight->unknown00[9] - params->unknown27c[0]);
    params->unknown27c[1] += fade * (paramLight->unknown00[10] - params->unknown27c[1]);
    params->unknown27c[2] += fade * (paramLight->unknown00[11] - params->unknown27c[2]);
    params->unknown27c[3] += fade * (paramLight->unknown00[12] - params->unknown27c[3]);
    params->unknown27c[4] += fade * (paramLight->unknown00[13] - params->unknown27c[4]);
    params->unknown27c[5] += fade * (paramLight->unknown00[14] - params->unknown27c[5]);
    params->unknown27c[6] += fade * (paramLight->unknown00[15] - params->unknown27c[6]);
    params->unknown27c[7] += fade * (paramLight->unknown00[16] - params->unknown27c[7]);
    params->unknown27c[8] += fade * (paramLight->unknown00[17] - params->unknown27c[8]);
    params->unknown27c[9] += fade * (paramLight->unknown00[18] - params->unknown27c[9]);
    params->unknown27c[10] += fade * (paramLight->unknown00[19] - params->unknown27c[10]);
    params->unknown27c[11] += fade * (paramLight->unknown00[20] - params->unknown27c[11]);
    params->unknown27c[12] += fade * (paramLight->unknown00[21] - params->unknown27c[12]);
    params->unknown27c[13] += fade * (paramLight->unknown00[22] - params->unknown27c[13]);
    params->unknown27c[14] += fade * (paramLight->unknown00[23] - params->unknown27c[14]);
    params->unknown27c[15] += fade * (paramLight->unknown00[24] - params->unknown27c[15]);
    params->unknown27c[16] += fade * (paramLight->unknown00[25] - params->unknown27c[16]);
    params->unknown27c[17] += fade * (paramLight->unknown00[26] - params->unknown27c[17]);
    params->unknown27c[18] += fade * (paramLight->unknown00[27] - params->unknown27c[18]);
    params->unknown27c[19] += fade * (paramLight->unknown00[28] - params->unknown27c[19]);
    params->unknown274 = paramLight->unknown00[0x1e];
    params->unknown2f0[0] += fade * (paramLight->unknown00[0x1f] - params->unknown2f0[0]);
    params->unknown2f0[1] += fade * (paramLight->unknown00[0x20] - params->unknown2f0[1]);
    params->unknown2f0[2] += fade * (paramLight->unknown00[0x21] - params->unknown2f0[2]);
  }
  if ((from->unknown08 & EnvColiPostData::FLAG_UNKNOWN_3) != 0) {
    cloud::CloudCalcParams *params = cloudMan->unknown50->unknown38;
    params->unknown2fc += fade * (paramSky->unknown00[0] - params->unknown2fc);
    params->unknown300 += fade * (paramSky->unknown00[1] - params->unknown300);
    params->unknown304 += fade * (paramSky->unknown00[2] - params->unknown304);
    params->unknown308 += fade * (paramSky->unknown00[3] - params->unknown308);
    params->unknown30c += fade * (paramSky->unknown00[4] - params->unknown30c);
    params->unknown310 += fade * (paramSky->unknown00[5] - params->unknown310);
    params->unknown318 += fade * (paramSky->unknown00[6] - params->unknown318);
    params->unknown31c += fade * (paramSky->unknown00[7] - params->unknown31c);
    params->unknown320 += fade * (paramSky->unknown00[8] - params->unknown320);
    params->unknown324 += fade * (paramSky->unknown00[9] - params->unknown324);
    params->unknown328 += fade * (paramSky->unknown00[10] - params->unknown328);
    params->unknown32c += fade * (paramSky->unknown00[11] - params->unknown32c);
    params->unknown330 += fade * (paramSky->unknown00[12] - params->unknown330);
    params->unknown334 += fade * (paramSky->unknown00[13] - params->unknown334);
    params->unknown338 += fade * (paramSky->unknown00[14] - params->unknown338);
    params->unknown33c += fade * (paramSky->unknown00[15] - params->unknown33c);
    params->unknown340 += fade * (paramSky->unknown00[16] - params->unknown340);
    params->unknown344 += fade * (paramSky->unknown00[17] - params->unknown344);
    params->unknown348 += fade * (paramSky->unknown00[18] - params->unknown348);
    params->unknown34c += fade * (paramSky->unknown00[19] - params->unknown34c);
    params->unknown350 += fade * (paramSky->unknown00[20] - params->unknown350);
    params->unknown354 += fade * (paramSky->unknown00[21] - params->unknown354);
    if (header->unknown38 == 0x1001) {
      params->unknown314 = paramSky->unknown00[0x18];
    }
  }
  if ((from->unknown08 & EnvColiPostData::FLAG_UNKNOWN_4) != 0) {
    cloud::CloudCalcParams *params = cloudMan->unknown50->unknown38;
    params->unknown360 += fade * (paramModel->unknown00[0] - params->unknown360);
    params->unknown364 += fade * (paramModel->unknown00[1] - params->unknown364);
    params->unknown368 += fade * (paramModel->unknown00[2] - params->unknown368);
    params->unknown36c += fade * (paramModel->unknown00[3] - params->unknown36c);
    params->unknown370 += fade * (paramModel->unknown00[4] - params->unknown370);
    params->unknown374 += fade * (paramModel->unknown00[5] - params->unknown374);
    params->unknown378 += fade * (paramModel->unknown00[6] - params->unknown378);
    params->unknown37c += fade * (paramModel->unknown00[7] - params->unknown37c);
    params->unknown380 += fade * (paramModel->unknown00[8] - params->unknown380);
    params->unknown384 += fade * (paramModel->unknown00[9] - params->unknown384);
  }
}

void DrEnvColiParameter::resetToneMapParams(const EnvColiPostParameterVer<10006> *from, const EnvColiPostParameterVer<10006> *to, f32 ratio) {
  DrPixlPostParm *postParm = m_drMan->unknown120[m_drMan->unknown1c98];
  if (ratio != 0.0f) {
    f32 inverse = 1.0f - ratio;
    postParm->m_toneMax = from->unknown00 * ratio + inverse * to->unknown00;
    postParm->m_toneMin = from->unknown04 * ratio + inverse * to->unknown04;
    postParm->m_toneRatio = from->unknown08 * ratio + inverse * to->unknown08;
    postParm->m_toneRatioLast = from->unknown0c * ratio + inverse * to->unknown0c;
    postParm->m_toneBlmMax = from->unknown10 * ratio + inverse * to->unknown10;
    postParm->m_toneBlmMin = from->unknown14 * ratio + inverse * to->unknown14;
    postParm->m_toneBlmRatio = from->unknown18 * ratio + inverse * to->unknown18;
    postParm->m_toneBlmRatioLast = from->unknown1c * ratio + inverse * to->unknown1c;
    postParm->unknown28 = from->unknown20 * ratio + inverse * to->unknown20;
    postParm->unknown2c = from->unknown24 * ratio + inverse * to->unknown24;
    postParm->unknown30 = from->unknown28 * ratio + inverse * to->unknown28;
  } else {
    postParm->m_toneMax = from->unknown00;
    postParm->m_toneMin = from->unknown04;
    postParm->m_toneRatio = from->unknown08;
    postParm->m_toneRatioLast = from->unknown0c;
    postParm->m_toneBlmMax = from->unknown10;
    postParm->m_toneBlmMin = from->unknown14;
    postParm->m_toneBlmRatio = from->unknown18;
    postParm->m_toneBlmRatioLast = from->unknown1c;
    postParm->unknown28 = from->unknown20;
    postParm->unknown2c = from->unknown24;
    postParm->unknown30 = from->unknown28;
  }
}

bool DrEnvColiMan::testEnvColi(DrEnvColiResult *result, const mm::Vec3 &position, f32 radius) {
  if (result == nullptr) {
    result = &m_drEnvColiResult;
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
    return testTreeColi(result, m_envColiListTreeData, position, radius);
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
        const EnvColiListTreeData *base = m_envColiListTreeData;
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
        if (gblId != 0 && m_drMan->isGblIdx(gblId)) {
          continue;
        }
        if (!(this->*s_pColiTest[primitive->unknown04])(unknown10 + primitive->unknown00, position, radius, unknown28[index])) {
          continue;
        }
        result->unknown00 = primitive->unknown08;
        result->unknown04 = primitive->unknown0a;
        result->unknown24 |= primitive->unknown06;
        if (primitive->unknown06 & 2) {
          result->m_bgmId = primitive->unknown0e;
        }
        result->m_layerId = primitive->unknown10;
        result->m_reverbId = primitive->unknown11;
        result->m_caveId = primitive->unknown12;
        result->m_areaId = primitive->unknown14;
        result->unknown1c = primitive->unknown16;
        result->m_windId = 0;
        DrEnvColiMan *coliMan = m_drMan->unknown100[0]->m_drEnvColiMan;
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
          result->m_windId = latest->unknown26;
        }
        isHit = true;
      }
    }
  }
  return isHit;
}

DrEnvColiObj::DrEnvColiObj(DrMan *man) : unknown00(nullptr), unknown08(nullptr), unknown10(nullptr), unknown28(nullptr), m_drMan(man), unknown38(0) {}

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
    unknown70 = m_drMan->unknown120[m_drMan->unknown1c98]->getWeatherFrame();
  } else {
    unknown70 -= m_drMan->unknown1c8c;
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
  unknown68 = m_drMan->m_timerVal;
}

void DrEnvColiMan::updateCloudFade(bool isReset, bool isForce) {
  unknown88 = 1.0f;
  if (isReset) {
    unknown84 = 600.0f;
    unknown88 = 0.0f;
  } else {
    unknown84 -= m_drMan->unknown1c8c;
    if (unknown84 < 0.0f) {
      unknown84 = 0.0f;
    } else {
      unknown88 = mm::clamp(1.0f / unknown84, 0.0f, 1.0f);
    }
  }
  if (m_drMan->unknown120[m_drMan->unknown1c98]->unknown1104 || isForce || m_drMan->m_drCalcMan->m_drCalcViewWork->unknown9ac) {
    unknown84 = 0.0f;
    unknown88 = 1.0f;
  }
}

void DrEnvColiMan::updateRainDropFade(bool isReset) {
  if (isReset) {
    unknown7c = m_drMan->unknown120[m_drMan->unknown1c98]->unknown10c0;
  } else {
    unknown7c -= m_drMan->unknown1c8c;
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

template <> void convertEnvColiPostParameterVer<10003, 10004>(const EnvColiPostParameterVer<10003> &from, EnvColiPostParameterVer<10004> &to) {
  unknown020(from, to);
  to.unknowna4 = from.unknowna4;
  to.unknowna8 = from.unknownb0;
  to.unknownac[0] = from.unknownb4[0];
  to.unknownac[1] = from.unknownb4[1];
  to.unknownb4 = from.unknownbc;
  for (int i = 0; i < 6; i++) {
    to.unknownb8[i] = from.unknownc0[i];
  }
  to.unknownd0[0] = from.unknownd8[0];
  to.unknownd0[1] = from.unknownd8[1];
  to.unknownd0[2] = from.unknownd8[2];
  for (int i = 0; i < 6; i++) {
    to.unknowndc[i] = from.unknowne4[i];
  }
  for (int i = 0; i < 8; i++) {
    to.unknownf4[i] = from.unknownfc[i];
  }
  for (int i = 0; i < 6; i++) {
    to.unknown114[i] = from.unknown11c[i];
  }
  to.unknown12c[0] = from.unknown134[0];
  to.unknown12c[1] = from.unknown134[1];
  to.unknown134[0] = from.unknown13c[0];
  to.unknown134[1] = from.unknown13c[1];
  to.unknown13c[0] = from.unknown144[0];
  to.unknown13c[1] = from.unknown144[1];
  to.unknown154 = from.unknown15c;
  to.unknown158[0] = from.unknown160[0];
  to.unknown158[1] = from.unknown160[1];
  to.unknown158[2] = from.unknown160[2];
  to.unknown17c = 0.0f;
  to.unknown180[0] = 0.69f;
  to.unknown180[1] = 2.49f;
  to.unknown180[2] = 28.88f;
  to.unknown180[3] = -0.000004f;
  to.unknown190.unknown00[0] = 0.675f;
  to.unknown190.unknown00[1] = 0.7005f;
  to.unknown190.unknown00[2] = 0.75f;
  to.unknown190.unknown00[3] = 0.6f;
  to.unknown190.unknown00[4] = 0.630588f;
  to.unknown190.unknown00[5] = 0.660147f;
  to.unknown190.unknown00[6] = 0.67f;
  to.unknown190.unknown00[7] = 0.76f;
  to.unknown190.unknown00[8] = 0.506479f;
  to.unknown190.unknown00[9] = 0.567606f;
  to.unknown190.unknown00[10] = 0.62f;
  to.unknown190.unknown00[11] = 0.88f;
  to.unknown1c0[0].unknown00[0] = 0.94f;
  to.unknown1c0[0].unknown00[1] = 12.69f;
  to.unknown1c0[0].unknown00[2] = 15.67f;
  to.unknown1c0[1].unknown00[0] = 9.7f;
  to.unknown1c0[1].unknown00[1] = 22.39f;
  to.unknown1c0[1].unknown00[2] = 25.37f;
  to.unknown1c0[2].unknown00[0] = 6.64f;
  to.unknown1c0[2].unknown00[1] = 7.31f;
  to.unknown1c0[2].unknown00[2] = 10.0f;
  to.unknown1c0[3].unknown00[0] = -3.36f;
  to.unknown1c0[3].unknown00[1] = -2.69f;
  to.unknown1c0[3].unknown00[2] = 3.36f;
  to.unknown1c0[4].unknown00[0] = 2.25f;
  to.unknown1c0[4].unknown00[1] = 0.9f;
  to.unknown1c0[4].unknown00[2] = 0.47f;
}

template <> void convertEnvColiPostParameterVer<10004, 10005>(const EnvColiPostParameterVer<10004> &from, EnvColiPostParameterVer<10005> &to) {
  unknown020(from, to);
  to.unknowna4 = from.unknowna4;
  to.unknowna8 = from.unknowna8;
  to.unknownac[0] = from.unknownac[0];
  to.unknownac[1] = from.unknownac[1];
  to.unknownb4 = from.unknownb4;
  for (int i = 0; i < 6; i++) {
    to.unknownb8[i] = from.unknownb8[i];
  }
  to.unknownd0[0] = from.unknownd0[0];
  to.unknownd0[1] = from.unknownd0[1];
  to.unknownd0[2] = from.unknownd0[2];
  for (int i = 0; i < 6; i++) {
    to.unknowndc[i] = from.unknowndc[i];
  }
  to.unknown1ec &= ~(EnvColiPostParameterVer<10005>::FLAG_UNKNOWN_0 | EnvColiPostParameterVer<10005>::FLAG_UNKNOWN_1 | EnvColiPostParameterVer<10005>::FLAG_UNKNOWN_2);
  for (int i = 0; i < 6; i++) {
    to.unknownf4[i] = from.unknown114[i];
  }
  to.unknown10c[0] = from.unknown12c[0];
  to.unknown10c[1] = from.unknown12c[1];
  to.unknown114[0] = from.unknown134[0];
  to.unknown114[1] = from.unknown134[1];
  // The game stores the two default pairs as two 64-bit immediates (0x71007d22e0). Written as four float stores in any of the 24 orders
  // (and interleaved with the neighbouring copies, 840 orders measured), the stores merge differently (best: 6 differing lines); the
  // copy of a constant pair is what gives the two immediates.
  const unknown303 first = {{8.0f, 50.0f}};
  const unknown303 second = {{1.0f, 1.0f}};
  to.unknown11c[0] = first;
  to.unknown11c[1] = second;
  to.unknown12c[0] = from.unknown13c[0];
  to.unknown12c[1] = from.unknown13c[1];
  to.unknown144 = from.unknown154;
  to.unknown148[0] = from.unknown158[0];
  to.unknown148[1] = from.unknown158[1];
  to.unknown148[2] = from.unknown158[2];
  to.unknown16c[0] = from.unknown17c;
  for (int i = 0; i < 4; i++) {
    to.unknown16c[i + 1] = from.unknown180[i];
  }
  to.unknown180 = from.unknown190;
  for (int i = 0; i < 5; i++) {
    to.unknown1b0[i] = from.unknown1c0[i];
  }
}

template <> void convertEnvColiPostParameterVer<10005, 10006>(const EnvColiPostParameterVer<10005> &from, EnvColiPostParameterVer<10006> &to) {
  unknown020(from, to);
  to.unknowna4 = from.unknowna4;
  to.unknowna8 = from.unknowna8;
  to.unknownac[0] = from.unknownac[0];
  to.unknownac[1] = from.unknownac[1];
  to.unknownb4 = from.unknownb4;
  for (int i = 0; i < 6; i++) {
    to.unknownb8[i] = from.unknownb8[i];
  }
  to.unknownd0[0] = from.unknownd0[0];
  to.unknownd0[1] = from.unknownd0[1];
  to.unknownd0[2] = from.unknownd0[2];
  for (int i = 0; i < 6; i++) {
    to.unknowndc[i] = from.unknowndc[i];
  }
  // The game loads the destination flag word before the source (`ldr w8, [x19, #496]; ldr w9, [x20, #492]; bfxil`, 0x71007d25b8), which
  // the bit-field assignments `to.f = from.f` (source loaded first) do not give: 215 instructions, first difference at 0x71007d25b8.
  to.unknown1f0 = (to.unknown1f0 & ~EnvColiPostParameterVer<10006>::FLAG_UNKNOWN_0) | (from.unknown1ec & EnvColiPostParameterVer<10005>::FLAG_UNKNOWN_0);
  to.unknown1f0 = (to.unknown1f0 & ~EnvColiPostParameterVer<10006>::FLAG_UNKNOWN_1) | (from.unknown1ec & EnvColiPostParameterVer<10005>::FLAG_UNKNOWN_1);
  to.unknown1f0 = (to.unknown1f0 & ~EnvColiPostParameterVer<10006>::FLAG_UNKNOWN_2) | (from.unknown1ec & EnvColiPostParameterVer<10005>::FLAG_UNKNOWN_2);
  for (int i = 0; i < 6; i++) {
    to.unknownf4[i] = from.unknownf4[i];
  }
  to.unknown10c[0] = from.unknown10c[0];
  to.unknown10c[1] = from.unknown10c[1];
  to.unknown114[0] = from.unknown114[0];
  to.unknown114[1] = from.unknown114[1];
  for (int i = 0; i < 4; i++) {
    to.unknown11c[i] = from.unknown11c[i / 2].unknown00[i % 2];
  }
  to.unknown12c[0] = from.unknown12c[0];
  to.unknown12c[1] = from.unknown12c[1];
  to.unknown144 = from.unknown144;
  to.unknown148[0] = from.unknown148[0];
  to.unknown148[1] = from.unknown148[1];
  to.unknown148[2] = from.unknown148[2];
  for (int i = 0; i < 5; i++) {
    to.unknown16c[i] = from.unknown16c[i];
  }
  to.unknown180 = from.unknown180;
  for (int i = 0; i < 5; i++) {
    to.unknown1b0[i] = from.unknown1b0[i];
  }
  to.unknown1ec = 0.0f;
}

} // namespace ml
