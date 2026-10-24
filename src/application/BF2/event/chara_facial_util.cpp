#include "event/chara_facial_util.h"

#include "bdat.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_vec2.h"

namespace event {

namespace {

bool isInBdat(unsigned char *bdat, int id) { return Bdat::getIdTop(bdat) <= id && id < Bdat::getIdTop(bdat) + Bdat::getIdCount(bdat); }

} // namespace

const char *CharaFacialUtil::getFacialBdat(gf::GfObj *obj) {
  gf::GfObjAcc acc(obj->unknownf8);
  int id = acc.getBdatId();
  int asset;
  switch (transferGroup(id, obj->type)) {
  case gf::OBJECT_TYPE_DRIVER:
    asset = static_cast<u16>(Bdat::getValCheck(Bdat::getFP("CHR_Dr"), "EventAsset", id, 2));
    break;
  case gf::OBJECT_TYPE_BLADE: {
    unsigned char *bdat = Bdat::getFP("CHR_Bl");
    if (Bdat::getIdTop(bdat) + Bdat::getIdCount(bdat) > id) {
      asset = static_cast<u16>(Bdat::getValCheck(bdat, "EventAsset", id, 2));
      break;
    }
  }
  default: {
    unsigned char *assetList = Bdat::getFP("EVT_assetList");
    return reinterpret_cast<const char *>(Bdat::getValCheck(assetList, "facialSeat", Bdat::getIdTop(assetList), 7));
  }
  case gf::OBJECT_TYPE_NPC:
    asset = static_cast<u16>(Bdat::getValCheck(Bdat::getFP("RSC_NpcList"), "EventAsset", id, 2));
    break;
  }

  return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_assetList"), "facialSeat", asset, 7));
}

u32 CharaFacialUtil::transferGroup(int id, u32 type) {
  switch (type) {
  case gf::OBJECT_TYPE_DRIVER:
    if (isInBdat(Bdat::getFP("CHR_Dr"), id)) {
      return gf::OBJECT_TYPE_DRIVER;
    }
    return transferGroupSub(id, gf::OBJECT_TYPE_DRIVER);
  case gf::OBJECT_TYPE_BLADE:
    if (isInBdat(Bdat::getFP("CHR_Bl"), id)) {
      return gf::OBJECT_TYPE_BLADE;
    }
    return transferGroupSub(id, gf::OBJECT_TYPE_BLADE);
  case gf::OBJECT_TYPE_NPC:
    if (isInBdat(Bdat::getFP("RSC_NpcList"), id)) {
      return gf::OBJECT_TYPE_NPC;
    }
    return transferGroupSub(id, gf::OBJECT_TYPE_NPC);
  }
  return type;
}

void CharaFacialUtil::getLensLimit(mm::Vec2 &translateMin, mm::Vec2 &translateMax, mm::Vec2 &rotateMin, mm::Vec2 &rotateMax, gf::GfObj *obj) {
  translateMin = mm::Vec2::zero;
  translateMax = mm::Vec2::zero;
  rotateMin = mm::Vec2::zero;
  rotateMax = mm::Vec2::zero;

  gf::GfObjAcc acc(obj->unknownf8);
  int id = acc.getBdatId();
  unsigned char *bdat;
  int asset;
  switch (transferGroup(id, obj->type)) {
  case gf::OBJECT_TYPE_DRIVER:
    asset = static_cast<u16>(Bdat::getValCheck(Bdat::getFP("CHR_Dr"), "EventAsset", id, 2));
    break;
  case gf::OBJECT_TYPE_BLADE:
    bdat = Bdat::getFP("CHR_Bl");
    if (id < Bdat::getIdTop(bdat) || Bdat::getIdTop(bdat) + Bdat::getIdCount(bdat) <= id) {
      return;
    }
    asset = static_cast<u16>(Bdat::getValCheck(bdat, "EventAsset", id, 2));
    break;
  case gf::OBJECT_TYPE_NPC:
    bdat = Bdat::getFP("RSC_NpcList");
    if (id < Bdat::getIdTop(bdat) || Bdat::getIdTop(bdat) + Bdat::getIdCount(bdat) <= id) {
      return;
    }
    asset = static_cast<u16>(Bdat::getValCheck(bdat, "EventAsset", id, 2));
    break;
  default:
    return;
  }

  int lens = static_cast<s16>(Bdat::getValCheck(Bdat::getFP("EVT_assetList"), "lensID", asset, 5));
  unsigned char *lensBdat = Bdat::getFP("EVT_lens");
  translateMin.x = static_cast<s16>(Bdat::getValCheck(lensBdat, "thMin", lens, 5)) * 0.001f;
  translateMin.y = static_cast<s16>(Bdat::getValCheck(lensBdat, "tvMin", lens, 5)) * 0.001f;
  translateMax.x = static_cast<s16>(Bdat::getValCheck(lensBdat, "thMax", lens, 5)) * 0.001f;
  translateMax.y = static_cast<s16>(Bdat::getValCheck(lensBdat, "tvMax", lens, 5)) * 0.001f;
  rotateMin.x = static_cast<s16>(Bdat::getValCheck(lensBdat, "rhMin", lens, 5)) * 0.017453292f;
  rotateMin.y = static_cast<s16>(Bdat::getValCheck(lensBdat, "rvMin", lens, 5)) * 0.017453292f;
  rotateMax.x = static_cast<s16>(Bdat::getValCheck(lensBdat, "rhMax", lens, 5)) * 0.017453292f;
  rotateMax.y = static_cast<s16>(Bdat::getValCheck(lensBdat, "rvMax", lens, 5)) * 0.017453292f;
}

const char *CharaFacialUtil::headType2stat(int type) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_headtype"), "stat", type, 7)); }

const char *CharaFacialUtil::headType2name(int type) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_headtype"), "name", type, 7)); }

f32 CharaFacialUtil::headType2bld(int type) { return static_cast<s16>(Bdat::getValCheck(Bdat::getFP("EVT_headtype"), "blend", type, 5)); }

f32 CharaFacialUtil::headType2weight(int type) {
  Bdat::Value weight;
  weight.valueU32 = Bdat::getValCheck(Bdat::getFP("EVT_headtype"), "weight", type, 8);
  f32 value = weight.valueF32;
  if (value < 0.0f) {
    value = 0.0f;
  } else if (value > 1.0f) {
    value = 1.0f;
  }
  return value;
}

const char *CharaFacialUtil::browType2stat(int type) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_browtype"), "stat", type, 7)); }

const char *CharaFacialUtil::browType2name(int type) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_browtype"), "name", type, 7)); }

const char *CharaFacialUtil::eyeType2stat(int type) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_eyetype"), "stat", type, 7)); }

const char *CharaFacialUtil::eyeType2name(int type) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_eyetype"), "name", type, 7)); }

bool CharaFacialUtil::lipType2disableWink(int type) { return static_cast<s8>(Bdat::getValCheck(Bdat::getFP("EVT_eyetype"), "disableWink", type, 4)) > 0; }

const char *CharaFacialUtil::lipType2stat(int type) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_liptype"), "stat", type, 7)); }

const char *CharaFacialUtil::lipType2name(int type) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_liptype"), "name", type, 7)); }

bool CharaFacialUtil::lipType2disableTalkLip(int type) { return static_cast<s8>(Bdat::getValCheck(Bdat::getFP("EVT_liptype"), "disableTalkLip", type, 4)) > 0; }

const char *CharaFacialUtil::talkHeadStat() { return "S_headtalk"; }

const char *CharaFacialUtil::talkLipStat() { return "S_lip_talk"; }

const char *CharaFacialUtil::winkType2name(int type) { return reinterpret_cast<const char *>(Bdat::getValCheck(Bdat::getFP("EVT_winktype"), "name", type, 7)); }

bool CharaFacialUtil::checkBdatID(gf::GF_OBJ_HANDLE *handle, int id) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return false;
  }

  gf::GfObjAcc acc(handle);
  u32 type = obj->type;
  return transferGroup(acc.getBdatId(), type) == gf::OBJECT_TYPE_DRIVER && acc.getBdatId() == id;
}

u32 CharaFacialUtil::transferGroupSub(int id, u32 type) {
  unsigned char *bdat = Bdat::getFP("CHR_Dr");
  if (Bdat::getIdTop(bdat) <= id && id < Bdat::getIdTop(bdat) + Bdat::getIdCount(bdat)) {
    return gf::OBJECT_TYPE_DRIVER;
  }
  bdat = Bdat::getFP("CHR_Bl");
  if (Bdat::getIdTop(bdat) <= id && id < Bdat::getIdTop(bdat) + Bdat::getIdCount(bdat)) {
    return gf::OBJECT_TYPE_BLADE;
  }
  bdat = Bdat::getFP("RSC_NpcList");
  if (Bdat::getIdTop(bdat) <= id && id < Bdat::getIdTop(bdat) + Bdat::getIdCount(bdat)) {
    return gf::OBJECT_TYPE_NPC;
  }
  return type;
}

} // namespace event
