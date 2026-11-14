#include "gf/field/gf_field_lod.h"

#include <string.h>

#include "bdat.h"
#include "framework/coli/coli_manager.h"
#include "framework/effect/effect_manager.h"
#include "fw/fw_debug.h"
#include "fw/fw_model_object.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_game_flag.h"
#include "gf/field/gf_field_manager.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/map/gf_map_manager.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"
#include "idcoli/idcoli.h"
#include "ml/dev_graph.h"
#include "ml/scn.h"
#include "ml/scn_cam_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/vector.h" // IWYU pragma: keep
#include "scn/scn_obj_acc.h"

namespace fw {
class EffectPack;
} // namespace fw

namespace gf {

constexpr int unknown002 = 0x9631; // Inferred role: first game flag of the anim reverse states; original name unknown.
constexpr int unknown003 = 0x9230; // Inferred role: first game flag of the fade states; original name unknown.

GfFieldLodEffect::GfFieldLodEffect() : unknown2a(false), unknown2c(0), unknown30(FIELD_LOD_STATE_UNKNOWN_5) {
  for (u32 i = 0; i < sizeof(unknown00) / sizeof(unknown00[0]); i++) {
    unknown00[i] = nullptr;
  }
}

void *GfFieldLodEffect::getAsset(GfFieldLodState state) const {
  if (state >= 0 && state < FIELD_LOD_STATE_UNKNOWN_5) {
    return unknown00[state];
  }
  return nullptr;
}

bool GfFieldLodEffect::isAssetExists() const {
  for (u32 i = 0; i < sizeof(unknown00) / sizeof(unknown00[0]); i++) {
    if (unknown00[i] != nullptr) {
      return true;
    }
  }
  return false;
}

bool GfFieldLodEffect::isAssetLoop(GfFieldLodState state) const {
  void *asset = getAsset(state);
  return asset != nullptr && fw::EffectManager::get()->isLoop(asset);
}

void GfFieldLodEffect::createAsset(int bdatId) {
  // Inferred role: lod list column of the effect of each lod state; original name unknown.
  static const char *const unknown004[] = {"effect_anime_normal", "effect_anime_reverse", "effect_visibleON", "effect_visibleOFF", "effect_fadeOUT"};
  disposeAsset();
  unknown2a = true;
  fw::EffectPack *pack = GfFieldManager::getEffectPack();
  if (pack == nullptr) {
    return;
  }
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_LODLIST);
  for (u32 i = 0; i < sizeof(unknown00) / sizeof(unknown00[0]); i++) {
    const char *name = reinterpret_cast<const char *>(Bdat::getValCheck(bdat, unknown004[i], bdatId, gmk::BDAT_TYPE_UNKNOWN_7));
    if (name != nullptr && name[0] != '\0') {
      void *asset = fw::EffectManager::get()->search(name, pack);
      if (asset != nullptr) {
        unknown00[i] = asset;
      }
    }
  }
  unknown28 = Bdat::getValCheck(bdat, "effect_skipframe", bdatId, gmk::BDAT_TYPE_UNKNOWN_2);
}

void GfFieldLodEffect::disposeAsset() {
  disposeInst(false);
  unknown2a = false;
  for (u32 i = 0; i < sizeof(unknown00) / sizeof(unknown00[0]); i++) {
    unknown00[i] = nullptr;
  }
}

void GfFieldLodEffect::disposeInst(bool isDead) {
  if (unknown2c != 0) {
    if (isDead) {
      fw::EffectManager::get()->dead(unknown2c);
    } else {
      fw::EffectManager::get()->remove(unknown2c);
    }
    unknown2c = 0;
  }
}

void GfFieldLodEffect::update(const ml::ScnObjAccPartsPos &partsPos) {
  if (unknown2c != 0 && partsPos.isPosAnm()) {
    mm::Mat44 matrix;
    partsPos.getAnmMatrix(&matrix);
    fw::EffectManager::get()->setMatrix(unknown2c, matrix);
  }
}

int GfFieldLod::findBdatIdByLodId(u16 lodId) const {
  for (u64 i = 0; i < 0x400; i++) {
    if (unknown08[i] == lodId) {
      return unknown808 + static_cast<int>(i);
    }
  }
  return unknown808 - 1;
}

const GfFieldLod::BdatInfo *GfFieldLod::findBdatInfo(int bdatId) const {
  if (unknown810.size() != 0) {
    for (const BdatInfo *info = unknown810.begin(); info != unknown810.end(); info++) {
      if (info->unknown0c == bdatId) {
        return info;
      }
    }
  }
  return nullptr;
}

GfFieldLod::BdatInfo *GfFieldLod::_findBdatInfo(int bdatId) {
  if (unknown810.size() != 0) {
    for (BdatInfo *info = unknown810.begin(); info != unknown810.end(); info++) {
      if (info->unknown0c == bdatId) {
        return info;
      }
    }
  }
  return nullptr;
}

bool GfFieldLod::findTransform(mm::Mat44 &matrix, int bdatId) const {
  if (unknown840.unknown00.unknown00 != nullptr && unknown840.unknown00.unknown10 != nullptr) {
    ml::ScnObjAccSeamPos seamPos(unknown840.unknown00.unknown00);
    int num = seamPos.getMax();
    u16 lodId = unknown08[bdatId - unknown808];
    for (int i = 0; i < num; i++) {
      ml::ScnObjAccPartsPos partsPos = seamPos.getObj(i);
      if (partsPos.isPosMatrix() && lodId == partsPos.getID()) {
        partsPos.getMatrix(matrix);
        return true;
      }
    }
  }
  return false;
}

void GfFieldLod::setLodSwitchId(int bdatId, u32 switchId) {
  if (unknown840.unknown00.unknown00 != nullptr && unknown840.unknown00.unknown10 != nullptr) {
    u16 lodId = unknown08[bdatId - unknown808];
    ml::ScnObjAccSeamPos seamPos(unknown840.unknown00.unknown00);
    int num = seamPos.getMax();
    for (int i = 0; i < num; i++) {
      ml::ScnObjAccPartsPos partsPos = seamPos.getObj(i);
      if (lodId == partsPos.getID()) {
        partsPos.setSwitchID(switchId);
      }
    }
  }
}

bool GfFieldLod::setAnimReverse(int bdatId, bool isReverse, bool isSkip) {
  GfGameFlag::setLocal(1, bdatId + unknown002 - unknown808, isReverse);
  if (unknown840.unknown00.unknown00 == nullptr || unknown840.unknown00.unknown10 == nullptr) {
    return false;
  }
  if (!unknown888) {
    BdatInfo *info = _findBdatInfo(bdatId);
    if (info != nullptr) {
      info->dirtyCache();
    }
  }
  return unknown840.play(unknown08[bdatId - unknown808], isReverse, isSkip);
}

void GfFieldLod::setPlaySpeed(int bdatId, f32 speed) {
  if (!unknown888) {
    BdatInfo *info = _findBdatInfo(bdatId);
    if (info != nullptr) {
      info->dirtyCache();
    }
  }
  u16 lodId = unknown08[bdatId - unknown808];
  unknown840.setPlaySpeed(lodId, speed);
}

f32 GfFieldLod::getPlaySpeed(int bdatId) const {
  u16 lodId = unknown08[bdatId - unknown808];
  return unknown840.getPlaySpeed(lodId);
}

bool GfFieldLod::isPlayAnimEnd(int bdatId) const {
  u16 lodId = unknown08[bdatId - unknown808];
  return unknown840.isPlayEnd(lodId);
}

bool GfFieldLod::isPlayAnimLoop(int bdatId) const {
  u16 lodId = unknown08[bdatId - unknown808];
  return unknown840.isPlayLoop(lodId);
}

f32 GfFieldLod::getAnimEndTime(int bdatId) const {
  u16 lodId = unknown08[bdatId - unknown808];
  return unknown840.getAnimEndTime(lodId);
}

void GfFieldLod::gevMapjump(GEV event, const MapjumpCallbackInfo &) {
  switch (event) {
  case GEV_UNKNOWN_2:
    updateBdatInfosImmidiate();
    break;
  case GEV_UNKNOWN_3:
    disposeColiAnim();
    break;
  case GEV_UNKNOWN_5: {
    validateBySaveData();
    fw::ModelObject *modelObject = GfMapManager::getModelObject();
    if (modelObject != nullptr) {
      ml::ScnObjModel *model = modelObject->getInterface();
      if (model != nullptr) {
        createColiAnim(model, false);
      }
    }
    validateVeSe();
    break;
  }
  default:
    break;
  }
}

void GfFieldLod::gevPlayEvent(GEV event, u32) {
  switch (event) {
  case GEV_UNKNOWN_9:
    unknown889 = true;
    break;
  case GEV_UNKNOWN_10:
    unknown889 = false;
    break;
  default:
    break;
  }
}

void GfFieldLod::createColiAnim(ml::ScnObjModel *model, bool isDebugDraw) {
  if (model == nullptr) {
    return;
  }
  disposeColiAnim();
  GfFieldLodColiAnim::CreateInfo info;
  info.unknown00 = model;
  fw::ColiObject *coliObject = GfMapManager::getColiObject();
  if (coliObject != nullptr) {
    info.unknown08 = coliObject->m_coliObject;
  }
  info.unknown10 = this;
  info.unknown18 = isDebugDraw;
  unknown840.create(info);
  createBdatInfos();
  unknown840.validateVeSe(*this);
}

void GfFieldLod::disposeColiAnim() {
  disposeBdatInfos();
  unknown840.dispose();
}

void GfFieldLod::finalize() {
  disposeColiAnim();
  unknown80c = false;
}

void GfFieldLod::destroy() {
  GfFieldLod *lod = get();
  lod->finalize();
  delete lod;
}

void GfFieldLod::setFade(int bdatId, bool isFadeIn, bool isImmediate) {
  GfGameFlag::setLocal(1, bdatId + unknown003 - unknown808, isFadeIn);
  // The lod id is read here, before the model test: the game loads it once before the search (1.0.0: 0x71002e4e34) and keeps it on the stack across the loop (str w1, [sp, #0xc] at
  // 0x71002e4e54). Read at the setFade call the load comes after the loop (93 instructions instead of 97); declared after the model test the id takes x22 and the address of unknown840 the stack slot.
  u16 lodId = unknown08[bdatId - unknown808];
  if (unknown840.unknown00.unknown00 == nullptr || unknown840.unknown00.unknown10 == nullptr) {
    return;
  }
  f32 fadeTime = 0.0f;
  BdatInfo *info = _findBdatInfo(bdatId);
  if (info != nullptr) {
    if (!unknown888) {
      info->dirtyCache();
    }
    if (!isImmediate) {
      fadeTime = isFadeIn ? info->unknown04 : info->unknown08;
    }
  }
  unknown840.setFade(lodId, isFadeIn, fadeTime);
}

void GfFieldLod::validateBySaveData() {
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_LODLIST);
  int top = Bdat::getIdTop(bdat);
  int count = Bdat::getIdCount(bdat);
  for (int i = 0; i < count; i++) {
    u32 isFadeIn = GfGameFlag::getLocal(1, unknown003 + i);
    get()->setFade(top + i, isFadeIn != 0, false);
    u32 isReverse = GfGameFlag::getLocal(1, unknown002 + i);
    get()->setAnimReverse(top + i, isReverse != 0, true);
  }
}

void GfFieldLod::disposeBdatInfos() { unknown810.destroy(); }

void GfFieldLod::updateBdatInfos() {
  if (!unknown889) {
    size_t size = unknown810.size();
    unknown888 = true;
    size_t count = size;
    if (count > 4) {
      count = 4;
    }
    for (size_t i = 0; i < count; i++, unknown838++) {
      if (size <= unknown838) {
        unknown838 = 0;
      }
      unknown810[unknown838].update();
    }
    unknown888 = false;
  }
}

void GfFieldLod::updateBdatInfosImmidiate() {
  size_t count = unknown810.size();
  for (size_t i = 0; i < count; i++) {
    unknown810[i].update();
  }
}

void GfFieldLod::validateVeSe() {
  size_t count = unknown810.size();
  for (int i = 0; i < count; i++) {
    BdatInfo &info = unknown810[i];
    unknown840.setFade(unknown08[info.unknown0c - unknown808], !isFadeOut(info.unknown0c), 0.0f);
  }
}

void GfFieldLod::validateByInitData() {
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_LODLIST);
  int top = Bdat::getIdTop(bdat);
  int count = Bdat::getIdCount(bdat);
  for (int i = 0; i < count; i++) {
    int bdatId = top + i;
    int visible = Bdat::getFlagVal(bdat, "flag", bdatId, "Visible");
    get()->setFade(bdatId, visible != 0, true);
    int animReverse = Bdat::getFlagVal(bdat, "flag", bdatId, "AnimReverse");
    get()->setAnimReverse(bdatId, animReverse != 0, true);
  }
}

void GfFieldLod::update(const fw::UpdateInfo &info) {
  GfFieldLod *lod = get();
  if (lod == nullptr || !lod->unknown80c) {
    return;
  }
  lod->updateBdatInfos();
  get()->unknown840.update(info);
}

bool GfFieldLod::isAnimReverse(int bdatId) const { return GfGameFlag::getLocal(1, bdatId + unknown002 - unknown808) != 0; }

bool GfFieldLod::isFadeOut(int bdatId) const {
  int top = unknown808;
  return GfGameFlag::getLocal(1, bdatId + unknown003 - top) == 0;
}

bool GfFieldLod::isAnimReverseOfInit(int bdatId) { return Bdat::getFlagVal(GfDataBdat::getFP(BDAT_FLD_LODLIST), "flag", bdatId, "AnimReverse") != 0; }

bool GfFieldLod::isVisibleOfInit(int bdatId) { return Bdat::getFlagVal(GfDataBdat::getFP(BDAT_FLD_LODLIST), "flag", bdatId, "Visible") != 0; }

void GfFieldLod::debugDraw() {
  GfFieldLod *lod = get();
  if (lod != nullptr && lod->unknown80c) {
    lod->unknown840.debugDraw();
  }
}

void GfFieldLod::build(const GfSetupParam &param) {
// __LINE__ must be 2054 as in the original file: its value changes the instruction order.
#line 2054
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfFieldLod(param);
}

GfFieldLod::BdatInfo::BdatInfo(u16 bdatId) : unknown00(0), unknown04(0.0f), unknown08(0.0f), unknown0c(0), unknown0e{CondInfo(), CondInfo(), CondInfo()} {
  if (bdatId != 0) {
    create(bdatId);
  }
}

void GfFieldLod::BdatInfo::create(u16 bdatId) {
  unknown0c = bdatId;
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_LODLIST);
  unknown00 = Bdat::getValCheck(bdat, "LODID", bdatId, gmk::BDAT_TYPE_UNKNOWN_2);
  unknown04 = gmk::toBdatF32(Bdat::getValCheck(bdat, "LOD_fadeIN_TIME", bdatId, gmk::BDAT_TYPE_UNKNOWN_8));
  unknown08 = gmk::toBdatF32(Bdat::getValCheck(bdat, "LOD_fadeOUT_TIME", bdatId, gmk::BDAT_TYPE_UNKNOWN_8));
  mm::mtl::FixStr<32> name;
  for (u64 i = 0; i < 3; i++) {
    CondInfo &cond = unknown0e[i];
    cond.unknown0a = false;
    name.format("ScenarioFlagMin%d", i + 1);
    u16 scenarioFlagMin = Bdat::getValCheck(bdat, name.c_str(), bdatId, gmk::BDAT_TYPE_UNKNOWN_2);
    name.format("ScenarioFlagMax%d", i + 1);
    u16 scenarioFlagMax = Bdat::getValCheck(bdat, name.c_str(), bdatId, gmk::BDAT_TYPE_UNKNOWN_2);
    gmk::ScenarioFlagCond scenarioCond(scenarioFlagMin, scenarioFlagMax);
    if (scenarioCond.unknown00 <= scenarioCond.unknown02) {
      cond.unknown00 = scenarioCond;
    }
    name.format("QuestFlag%d", i + 1);
    u16 questFlag = Bdat::getValCheck(bdat, name.c_str(), bdatId, gmk::BDAT_TYPE_UNKNOWN_2);
    name.format("QuestFlagMin%d", i + 1);
    u8 questFlagMin = Bdat::getValCheck(bdat, name.c_str(), bdatId, gmk::BDAT_TYPE_UNKNOWN_1);
    name.format("QuestFlagMax%d", i + 1);
    u8 questFlagMax = Bdat::getValCheck(bdat, name.c_str(), bdatId, gmk::BDAT_TYPE_UNKNOWN_1);
    gmk::QuestFlagCond questCond(questFlag, questFlagMin, questFlagMax);
    if (questCond.unknown02 > questCond.unknown03) {
      break;
    }
    cond.unknown04 = questCond;
    name.format("Condition%d", i + 1);
    cond.unknown08 = Bdat::getValCheck(bdat, name.c_str(), bdatId, gmk::BDAT_TYPE_UNKNOWN_2);
  }
}

void GfFieldLod::BdatInfo::dispose() { unknown0c = 0; }

void GfFieldLod::BdatInfo::dirtyCache() {
  if (unknown0c != 0) {
    for (int i = 0; i < 3; i++) {
      unknown0e[i].unknown0a = false;
    }
  }
}

GfFieldLod::GfFieldLod(const GfSetupParam &param) : unknown808(0), unknown80c(false), unknown838(0), unknown888(false), unknown889(false) {
  memset(unknown08, 0xff, sizeof(unknown08));
  initialize(param);
}

GfFieldLod::~GfFieldLod() {}

void GfFieldLod::initialize(const GfSetupParam &) {
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_LODLIST);
  unknown808 = Bdat::getIdTop(bdat);
  int count = Bdat::getIdCount(bdat);
  for (int i = 0; i < count; i++) {
    unknown08[i] = Bdat::getValCheck(bdat, "LODID", i + unknown808, gmk::BDAT_TYPE_UNKNOWN_2);
  }
  unknown80c = true;
  validateByInitData();
}

GfFieldLodColiAnim::GfFieldLodColiAnim(const CreateInfo *info) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfFieldLodColiAnim::create(const CreateInfo &info) {
  disposePosInfos();
  unknown00 = info;
  createPosInfos(info.unknown18);
}

void GfFieldLodColiAnim::dispose() {
  disposePosInfos();
  unknown00 = CreateInfo();
}

void GfFieldLodColiAnim::disposePosInfos() {
  clearEffectInsts();
  fw::ColiObject *coliObject = GfMapManager::getColiObject();
  size_t count = unknown20.size();
  for (int i = 0; i < count; i++) {
    PosInfo &posInfo = unknown20[i];
    if (posInfo.unknown50 != unknown020) {
      if (coliObject != nullptr && posInfo.unknown48 >= 0) {
        idcoli::IDColiParmsGrand coliParms(coliObject->m_coliObject);
        coliParms.getMoveObj(posInfo.unknown48).setUserData(nullptr);
      }
      unbindPosInfoToGfObj(posInfo);
      GfObjUtil::destroy(posInfo.unknown50);
    }
  }
  unknown20.destroy();
}

void GfFieldLodColiAnim::update(const fw::UpdateInfo &info) {
  if (unknown00.unknown00 != nullptr && unknown00.unknown10 != nullptr && !GfManager::isDestroyNow() && unknown20.size() != 0) {
    for (PosInfo &posInfo : unknown20) {
      if (posInfo.unknown50 == unknown020) {
        posInfo.update(info);
      }
    }
  }
}

GfFieldLodState GfFieldLodColiAnim::findStateOfAnimReverse(bool isReverse) { return isReverse ? FIELD_LOD_STATE_UNKNOWN_1 : FIELD_LOD_STATE_UNKNOWN_0; }

GfFieldLodState GfFieldLodColiAnim::findStateOfFade(bool isFadeIn, bool isImmediate) {
  if (isFadeIn) {
    return FIELD_LOD_STATE_UNKNOWN_2;
  }
  return isImmediate ? FIELD_LOD_STATE_UNKNOWN_3 : FIELD_LOD_STATE_UNKNOWN_4;
}

void GfFieldLodColiAnim::stop(u16 lodId) {
  ml::ScnObjAccSeamPos seamPos(unknown00.unknown00);
  int num = seamPos.getMax();
  for (int i = 0; i < num; i++) {
    ml::ScnObjAccPartsPos partsPos = seamPos.getObj(i);
    if (lodId == partsPos.getID()) {
      unknown20[i].unknown68 = false;
    }
  }
}

bool GfFieldLodColiAnim::isLodIdExist(u16 lodId) const {
  ml::ScnObjAccSeamPos seamPos(unknown00.unknown00);
  int num = seamPos.getMax();
  for (int i = 0; i < num; i++) {
    ml::ScnObjAccPartsPos partsPos = seamPos.getObj(i);
    if (lodId == partsPos.getID()) {
      return true;
    }
  }
  return false;
}

void GfFieldLodColiAnim::setPlaySpeed(u16 lodId, f32 speed) {
  ml::ScnObjAccSeamPos seamPos(unknown00.unknown00);
  int num = seamPos.getMax();
  for (int i = 0; i < num; i++) {
    ml::ScnObjAccPartsPos partsPos = seamPos.getObj(i);
    if (lodId == partsPos.getID()) {
      unknown20[i].unknown6c = speed;
    }
  }
}

bool GfFieldLodColiAnim::isPlayLoop(u16 lodId) const {
  ml::ScnObjAccSeamPos seamPos(unknown00.unknown00);
  int num = seamPos.getMax();
  for (int i = 0; i < num; i++) {
    ml::ScnObjAccPartsPos partsPos = seamPos.getObj(i);
    if (lodId != partsPos.getID()) {
      continue;
    }
    if (partsPos.isLoop()) {
      return true;
    }
  }
  return false;
}

f32 GfFieldLodColiAnim::getPlaySpeed(u16 lodId) const {
  ml::ScnObjAccSeamPos seamPos(unknown00.unknown00);
  int num = seamPos.getMax();
  for (int i = 0; i < num; i++) {
    ml::ScnObjAccPartsPos partsPos = seamPos.getObj(i);
    if (lodId == partsPos.getID()) {
      return unknown20[i].unknown6c;
    }
  }
  return 1.0f;
}

f32 GfFieldLodColiAnim::getAnimEndTime(u16 lodId) const {
  ml::ScnObjAccSeamPos seamPos(unknown00.unknown00);
  int num = seamPos.getMax();
  for (int i = 0; i < num; i++) {
    ml::ScnObjAccPartsPos partsPos = seamPos.getObj(i);
    if (lodId != partsPos.getID()) {
      continue;
    }
    if (partsPos.isPosAnm()) {
      return partsPos.getPosMaxFrame() * ml::DevGraph::getFrameSyncSec();
    }
    if (partsPos.isNodeAnm()) {
      return partsPos.getNodeMaxFrame() * ml::DevGraph::getFrameSyncSec();
    }
  }
  return 0.0f;
}

bool GfFieldLodColiAnim::isPlayEnd(u16 lodId) const {
  ml::ScnObjAccSeamPos seamPos(unknown00.unknown00);
  size_t count = unknown20.size();
  for (size_t i = 0; i < count; i++) {
    const PosInfo &posInfo = unknown20[i];
    ml::ScnObjAccPartsPos partsPos = seamPos.getObj(posInfo.unknown44);
    if (lodId != partsPos.getID() || partsPos.isLoop()) {
      continue;
    }
    if (partsPos.isPosAnm()) {
      if (posInfo.unknown69) {
        if (partsPos.getPosFrame() <= 0.0f) {
          return true;
        }
      }
      if (!posInfo.unknown69) {
        if (partsPos.getPosMaxFrame() <= partsPos.getPosFrame()) {
          return true;
        }
      }
    }
    if (partsPos.isNodeAnm()) {
      if (posInfo.unknown69) {
        if (partsPos.getNodeFrame() <= 0.0f) {
          return true;
        }
      }
      if (!posInfo.unknown69) {
        if (partsPos.getNodeMaxFrame() <= partsPos.getNodeFrame()) {
          return true;
        }
      }
    }
  }
  return false;
}

void GfFieldLodColiAnim::debugDraw() const {
  if (unknown00.unknown00 == nullptr || unknown00.unknown10 == nullptr) {
    return;
  }
  ml::ScnObjAccSeamPos seamPos(unknown00.unknown00);
  mm::Vec3 screenPos;
  mm::Mat44 matrix;
  mm::Col4 color;
  int max = seamPos.getMax();
  mm::mtl::FixStr<16> text;
  for (int i = 0; i < max; i++) {
    ml::ScnObjAccPartsPos partsPos = seamPos.getObj(i);
    if (partsPos.isPosMatrix()) {
      partsPos.getMatrix(matrix);
      mm::Vec3 position = matrix.unknown004();
      if (ml::ScnCamUtil::getScreenPos(screenPos, ml::Scn::get()->getCam(-1), position)) {
        color = unknown20[i].unknown08.unknown2c != 0 ? mm::Col4::red : mm::Col4::white;
        text.format("%d-%d", partsPos.getID(), partsPos.getSwitchID());
        fw::debug::drawFont(static_cast<int>(screenPos.x), static_cast<int>(screenPos.y), color, text.c_str());
      }
    }
  }
}

void GfFieldLodColiAnim::clearEffectInsts() {
  size_t count = unknown20.size();
  for (int i = 0; i < count; i++) {
    unknown20[i].unknown08.disposeInst(false);
  }
}

void GfFieldLodColiAnim::validateVeSe(const GfFieldLod &lod) {
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_LODLIST);
  size_t count = unknown20.size();
  for (int i = 0; i < count; i++) {
    PosInfo &posInfo = unknown20[i];
    int bdatId = lod.findBdatIdByLodId(posInfo.unknown40);
    if (bdatId > Bdat::getIdTop(bdat)) {
      posInfo.unknown08.createAsset(bdatId);
      f32 popDist = gmk::toBdatF32(Bdat::getValCheck(bdat, "effect_pop_dist", bdatId, gmk::BDAT_TYPE_UNKNOWN_8));
      f32 range = popDist;
      if (popDist == 0.0f) {
        for (u32 state = 0; state < 5; state++) {
          if (posInfo.unknown08.isAssetLoop(static_cast<GfFieldLodState>(state))) {
            range = 50.0f;
            break;
          }
        }
      }
      posInfo.unknown7c = range * range;
      posInfo.unknown80 = Bdat::getFlagVal(bdat, "flag", bdatId, "LOD_fadeIN_collision") != 0;
      posInfo.unknown81 = Bdat::getFlagVal(bdat, "flag", bdatId, "LOD_fadeOUT_collision") != 0;
    }
  }
}

void GfFieldLodColiAnim::bindPosInfoToGfObj(const PosInfo &posInfo) {
  GfObjAcc acc(posInfo.unknown50);
  acc.setUserData(OBJ_USER_DATA_UNKNOWN_1, reinterpret_cast<u64>(&posInfo));
}

void GfFieldLodColiAnim::unbindPosInfoToGfObj(const PosInfo &posInfo) {
  GfObjAcc acc(posInfo.unknown50);
  if (acc.isValid()) {
    acc.setUserData(OBJ_USER_DATA_UNKNOWN_1, 0);
  }
}

void GfFieldLodColiAnim::PosInfo::updateAnim(ml::ScnObjAccPartsPos &partsPos, f32 delta) {
  if (unknown68) {
    bool isLoop = partsPos.isLoop();
    f32 posFrame = partsPos.getPosFrame();
    f32 nodeFrame = partsPos.getNodeFrame();
    if (!unknown69) {
      posFrame += delta;
      nodeFrame += delta;
      if (partsPos.getPosMaxFrame() < posFrame) {
        posFrame = isLoop ? 0.0f : partsPos.getPosMaxFrame();
      }
      if (partsPos.getNodeMaxFrame() < nodeFrame) {
        nodeFrame = isLoop ? 0.0f : partsPos.getNodeMaxFrame();
      }
    } else {
      posFrame -= delta;
      nodeFrame -= delta;
      if (posFrame < 0.0f) {
        posFrame = isLoop ? partsPos.getPosMaxFrame() : 0.0f;
      }
      if (nodeFrame < 0.0f) {
        nodeFrame = isLoop ? partsPos.getNodeMaxFrame() : 0.0f;
      }
    }
    mm::Mat44 matrix;
    if (partsPos.isPosAnm()) {
      partsPos.getAnmMatrix(&matrix);
    }
    partsPos.setPosFrame(posFrame);
    partsPos.setNodeFrame(nodeFrame);
    if (partsPos.isPosAnm()) {
      partsPos.setMatrix(matrix);
      syncGfTransform(matrix);
      partsPos.getAnmMatrix(&matrix);
      if (unknown48 >= 0 && unknown00->unknown00.unknown08 != nullptr) {
        idcoli::IDColiParmsGrand grand(unknown00->unknown00.unknown08);
        grand.getMoveObj(unknown48).setMatrix(matrix);
      }
    }
  }
}

void GfFieldLodColiAnim::PosInfo::updateColiOff(ml::ScnObjAccPartsPos &partsPos) {
  if (partsPos.isColiSkipData()) {
    bool isColiOff = partsPos.isColiOff();
    u32 id = partsPos.getID();
    bool isGlobal = fw::ColiManager::get()->isGblId(id);
    if (isColiOff != !isGlobal) {
      fw::ColiManager::get()->setGblId(id, !isColiOff);
    }
  }
}

void GfFieldLodColiAnim::PosInfo::syncGfTransform(const mm::Mat44 &matrix) {
  GfObj *obj = GfObjUtil::getObj(unknown50);
  if (obj != nullptr) {
    GfComTransform *transform = obj->getComponent<GfComTransform>();
    mm::Quat rotation;
    mm::unknown004(rotation, matrix);
    transform->setPosition(matrix.unknown004());
    transform->setRotation(rotation);
    transform->syncFrame();
  }
}

const mm::mtl::RTTI *GfFieldLodColiAnim::ColiUserData::getRTTI() const { return &m_rtti; }

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfFieldLod>::~PtrSingleton();
template void mm::mtl::Vector<gf::GfFieldLodColiAnim::PosInfo>::push_back(const gf::GfFieldLodColiAnim::PosInfo &);
template void mm::mtl::Vector<gf::GfFieldLodColiAnim::PosInfo>::expand(size_t, size_t);
