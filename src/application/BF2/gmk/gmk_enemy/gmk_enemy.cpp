#include "gmk/gmk_enemy/gmk_enemy.h"

#include "bdat.h"
#include "framework/debug/debug_draw.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gmk/gmk_bdat.h"
#include "gmk/gmk_list_impl.h" // IWYU pragma: keep
#include "gmk/gmk_squad.h"
#include "ml/rand.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec2.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mm_mtl/vector.h"

namespace gmk {

template bool TGmkList<GmkEnemy, GmkEnemy::BdatInfo, 1296387653u, 5u, GmkEnemyGob>::initGmkBdatInfo(GmkEnemy::BdatInfo &, int &, const AGmkBase &);

static u32 getU8OrU16(const CBdatWrapper &bdat, const char *name, int id) {
  if (Bdat::getVarType(bdat.unknown00, name) == BDAT_TYPE_U16) {
    return static_cast<u16>(bdat.getValCheck(name, id, BDAT_TYPE_U16));
  }
  return static_cast<u8>(bdat.getValCheck(name, id, BDAT_TYPE_U8));
}

void GmkEnemyInsts::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown0e = ScenarioFlagCond(bdat.getValCheck("ScenarioFlagMin", id, BDAT_TYPE_U16), bdat.getValCheck("ScenarioFlagMax", id, BDAT_TYPE_U16));
  unknown12 = QuestFlagCond(bdat.getValCheck("QuestFlag", id, BDAT_TYPE_U16), bdat.getValCheck("QuestFlagMin", id, BDAT_TYPE_U8), bdat.getValCheck("QuestFlagMax", id, BDAT_TYPE_U8));
  unknown00 = bdat.getValCheck("Condition", id, BDAT_TYPE_U16);
  unknown18.unknown08 = bdat.getValCheck("POP_TIME", id, BDAT_TYPE_U32);
  unknown28.unknown08 = bdat.getValCheck("popWeather", id, BDAT_TYPE_U8);
  if (Bdat::getFlagVal(bdat.unknown00, "flag", id, "popCloud") != 0) {
    unknown38.unknown08 = CloudCond::TYPE_CLOUD_SEA;
  }
  unknown02 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "ene_priority") != 0;
  unknown03 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "pop_smn") != 0;
  unknown04 = bdat.getValCheck("squadId", id, BDAT_TYPE_U16);
  s16 squadScale = bdat.getValCheck("squadScale", id, BDAT_TYPE_U16);
  unknown06 = squadScale == 0 ? 100 : squadScale;
  unknown08 = bdat.getValCheck("form", id, BDAT_TYPE_U8);
  unknown09 = bdat.getValCheck("form_range", id, BDAT_TYPE_U8);
  u16 mutekiQuest = bdat.getValCheck("muteki_QuestFlag", id, BDAT_TYPE_U16);
  u8 mutekiQuestMin = bdat.getValCheck("muteki_QuestFlagMin", id, BDAT_TYPE_U8);
  u8 mutekiQuestMax = bdat.getValCheck("muteki_QuestFlagMax", id, BDAT_TYPE_U8);
  if (mutekiQuestMax >= mutekiQuestMin) {
    unknown48 = QuestFlagCond(mutekiQuest, mutekiQuestMin, mutekiQuestMax);
  }
  unknown0a = bdat.getValCheck("muteki_Condition", id, BDAT_TYPE_U16);
  const char *name = reinterpret_cast<const char *>(bdat.getValCheck("name", id, BDAT_TYPE_STRING));
  if (name != nullptr && (__builtin_strcmp("ma20a_b05_23", name) == 0 || __builtin_strcmp("ma20a_b05_24", name) == 0)) {
    unknown0c = true;
  }
}

bool GmkEnemyInsts::BdatInfo::isInvincibleCondMatched() const {
  bool isMatched = false;
  if (unknown0a != 0) {
    if (!gf::GfGameCond::isGameCond(unknown0a)) {
      return false;
    }
    isMatched = true;
  }
  if (unknown48.isEnable()) {
    if (!unknown48.isMatch()) {
      return false;
    }
    isMatched = true;
  }
  return isMatched;
}

bool GmkEnemyInsts::BdatInfo::isPopCondMatchedOfSmn() const {
  if (unknown0e.isEnable() && !unknown0e.isMatch()) {
    return false;
  }
  return true;
}

void GmkEnemy::debugDraw() const {
  if (!isValid()) {
    return;
  }
  {
    mm::Vec3 position = AGmkBase::unknown08.unknown08->unknown00;
    mm::Mat44 matrix;
    unknown001(matrix, position);
    fw::debug::drawCircleLine(matrix, getData()->unknown00, mm::Col4::cyan);
  }
  mm::Vec2 screen;
  if (toScreenPos(screen, AGmkBase::unknown08.unknown08->unknown00)) {
    mm::mtl::FixStr<128> text;
    int offset;
    if (unknown48.unknown170 > 0.0f) {
      text.format("repop-time=%.1f", unknown48.unknown170);
      fw::debug::drawFont(static_cast<int>(screen.x), static_cast<int>(screen.y) + 24, mm::Col4::green, text.c_str());
      offset = 48;
    } else {
      offset = 24;
    }
    if (reinterpret_cast<const BdatInfo *>(unknown20.unknown10)->unknown02) {
      text.format("summon");
      fw::debug::drawFont(static_cast<int>(screen.x), static_cast<int>(screen.y) + offset, mm::Col4::red, text.c_str());
    }
  }
}

void GmkEnemy::BdatInfo::create(CBdatWrapper bdat, int id, const AGmkBase &gmk) {
  unknown00 = bdat.getValCheck("tagetpoint_name", id, BDAT_TYPE_U16);
  unknown02 = Bdat::getFlagVal(bdat.unknown00, "flag", id, "pop_smn") != 0;
  unknown04 = getU8OrU16(bdat, "ene_disp_r", id);
  unknown06 = getU8OrU16(bdat, "ene_disp_h", id);
}

bool GmkEnemyList::BdatInfo::create() {
  u8 *mapList = gf::GfDataBdat::getFP(gf::BDAT_FLD_MAPLIST);
  if (mapList == nullptr) {
    unknown00 = -1;
    return false;
  }
  unknown00 = gf::GfGameManager::getMapID();
  if (unknown00 < Bdat::getIdTop(mapList) || Bdat::getIdTop(mapList) + Bdat::getIdCount(mapList) <= unknown00) {
    unknown00 = -1;
    return false;
  }
  unknown04 = Bdat::getValCheck(mapList, "ene_disp_r", unknown00, BDAT_TYPE_U8);
  unknown05 = Bdat::getValCheck(mapList, "ene_disp_h", unknown00, BDAT_TYPE_U8);
  unknown06 = Bdat::getValCheck(mapList, "ene_release_r", unknown00, BDAT_TYPE_U8);
  unknown07 = Bdat::getValCheck(mapList, "ene_release_h", unknown00, BDAT_TYPE_U8);
  unknown08 = Bdat::getValCheck(mapList, "e_repoptime", unknown00, BDAT_TYPE_U8);
  return true;
}

// Inferred helper: deletes a vector of game objects; original name unknown.
static void unknown003(mm::mtl::Vector<gf::GF_OBJ_HANDLE *> *&vector) {
  if (vector != nullptr) {
    delete vector;
    vector = nullptr;
  }
}

void GmkEnemyInsts::PopInfo::PopEnemyInfo::dispose() {
  unknown003(unknown10);
  unknown003(unknown18);
  unknown24 = 0;
}

void GmkEnemyInsts::PopInfo::dispose() {
  unknown08[0].dispose();
  unknown08[1].dispose();
  unknown08[2].dispose();
  unknown08[3].dispose();
  unknown02 = 0;
}

int GmkEnemyInsts::PopInfo::getGobInstNum() const {
  int num = 0;
  for (u32 i = 0; i < 4; i++) {
    num += unknown08[i].unknown001();
  }
  return num;
}

bool GmkEnemyInsts::PopInfo::isPopFinished() const {
  u8 *arrange = gf::GfDataBdat::getFP(gf::BDAT_CHR_EN_ARRANGE);
  for (u32 i = 0; i < 4; i++) {
    const PopEnemyInfo &info = unknown08[i];
    if (info.unknown00 != 0 && Bdat::getFlagVal(arrange, "Flag", info.unknown00, "Named") != 0 && gf::GfDataEnemy::getEnemySuppress(info.unknown00) != 0) {
      continue;
    }
    if (info.unknown04 != info.unknown001() + (info.unknown20 & 0xff) + (info.unknown20 >> 8)) {
      return false;
    }
  }
  return true;
}

void GmkEnemyInsts::PopInfo::removeDefeatedNamedEnemyInfo() {
  u8 *arrange = gf::GfDataBdat::getFP(gf::BDAT_CHR_EN_ARRANGE);
  for (u32 i = 0; i < 4; i++) {
    PopEnemyInfo &info = unknown08[i];
    if (info.unknown10 != nullptr && info.unknown18 != nullptr) {
      if (Bdat::getFlagVal(arrange, "Flag", info.unknown00, "Named") != 0 && gf::GfDataEnemy::getEnemySuppress(info.unknown00) != 0) {
        info.dispose();
      }
    }
  }
}

bool GmkEnemyInsts::PopInfo::hasEneID(u16 eneId, bool flag) const {
  for (u32 i = 0; i < 4; i++) {
    const PopEnemyInfo &info = unknown08[i];
    if (info.unknown10 == nullptr || info.unknown18 == nullptr) {
      continue;
    }
    if (flag && info.unknown03 < 100) {
      continue;
    }
    if (info.unknown00 == eneId) {
      return true;
    }
  }
  return false;
}

bool GmkEnemyInsts::PopInfo::hasTypeGenus(u8 genus, bool flag) const {
  for (u32 i = 0; i < 4; i++) {
    const PopEnemyInfo &info = unknown08[i];
    if (info.unknown10 == nullptr || info.unknown18 == nullptr) {
      continue;
    }
    if (flag && info.unknown03 < 100) {
      continue;
    }
    if (info.unknown07 == genus) {
      return true;
    }
  }
  return false;
}

bool GmkEnemyInsts::isPopFinished() const {
  if (!isGfObjNumFull(gf::OBJECT_TYPE_ENEMY) && (unknown178 & MATCHED_UNKNOWN_0) && (unknown178 & MATCHED_UNKNOWN_1)) {
    return unknown98.isPopFinished();
  }
  return true;
}

void GmkEnemyInsts::validateDisp(gf::GF_OBJ_HANDLE *handle) const {
  AGmkBase *gmk = getBindedGmkInst(handle);
  if (gmk == nullptr) {
    return;
  }
  bool isDisp = debugIsDispGmkType(gmk->getGmkType()) && unknown140;
  setEventDisp(handle, isDisp);
}

bool GmkEnemyInsts::isQuestDead() const {
  for (u32 i = 0; i < 4; i++) {
    if (unknown98.unknown08[i].unknown002() != unknown98.unknown08[i].unknown04) {
      return false;
    }
  }
  return true;
}

int GmkEnemyInsts::getGobInstCapa() const {
  int capacity = 0;
  for (u32 i = 0; i < 4; i++) {
    capacity += unknown98.unknown08[i].unknown04;
  }
  return capacity;
}

void GmkEnemyInsts::disposeSquad() { mm::mtl::safeRelease(unknown150); }

void GmkEnemyInsts::dispose() {
  unknown178 &= ~(MATCHED_UNKNOWN_0 | MATCHED_UNKNOWN_1 | MATCHED_UNKNOWN_2);
  disposeGobInsts(false, false);
  disposeSquad();
  unknown00 = CreateInfo();
}

void GmkEnemyInsts::validateDisp() const {
  u32 num = unknown98.getGobInstNum();
  for (u32 i = 0; i < num; i++) {
    validateDisp(getGobInst(i));
  }
}

bool GmkEnemyInsts::reqForcePopGobInst(const ForcePopEnemyInfo &info) const {
  if (unknown98.getGobInstNum() == 0) {
    if (unknown38.unknown03 && !(unknown178 & MATCHED_UNKNOWN_2)) {
      return false;
    }
    unknown141 = true;
    unknown144 = info;
    return true;
  }
  return false;
}

bool GmkEnemy::PopXformFinder::isYSnap() const { return unknown08->getData()->unknown04; }

bool GmkEnemy::PopXformFinder::onPopGob(gf::GF_OBJ_HANDLE *handle) const { return true; }

void GmkEnemy::PopXformFinder::onCreateGobInsts(u32 num) const {}

void GmkEnemy::update(f32 deltaTime) {
  debugUpdateMmf();
  if (!isValid()) {
    return;
  }
  GmkEnemyInsts::UpdateInfo info;
  PopXformFinder finder;
  finder.unknown08 = this;
  info.unknown00 = deltaTime;
  info.unknown08 = &unknown08.unknown08->unknown00;
  info.unknown10 = &finder;
  unknown48.update(info);
}

void GmkEnemy::dispose() {
  unknown48.dispose();
  AGmkBase::dispose();
}

GmkType GmkEnemy::getGmkType() const { return GMK_TYPE; }

IGmkList *GmkEnemy::getOwnerGmkEnemyList() const { return unknown08.unknown00; }

bool GmkEnemy::isPointInsideRandomWalk(const mm::Vec3 &position) const {
  const mm::Vec3 &center = unknown08.unknown08->unknown00;
  f32 x = center.x - position.x;
  f32 y = center.y - position.y;
  f32 z = center.z - position.z;
  return x * x + y * y + z * z <= getData()->unknown00 * getData()->unknown00;
}

mm::Vec3 &GmkEnemy::getPositionInRandomWalk(mm::Vec3 &result, f32 angleMin, f32 angleMax, f32 distanceMin, f32 distanceMax) const {
  mm::Mat44 rotation;
  rotation.setRotY(ml::mtRandf1(angleMin, angleMax));
  f32 distance = getData()->unknown00 * ml::mtRandf1(distanceMin, distanceMax);
  mm::Vec3 offset(0.0f, 0.0f, distance);
  result.x = offset.x * rotation.rows[0][0] + offset.y * rotation.rows[1][0] + offset.z * rotation.rows[2][0];
  result.y = offset.x * rotation.rows[0][1] + offset.y * rotation.rows[1][1] + offset.z * rotation.rows[2][1];
  result.z = offset.x * rotation.rows[0][2] + offset.y * rotation.rows[1][2] + offset.z * rotation.rows[2][2];
  result += unknown08.unknown08->unknown00;
  return result;
}

bool GmkEnemy::isValid() const {
  if (unknown08.unknown00 == nullptr || unknown20.unknown08 == nullptr || unknown20.unknown10 == nullptr) {
    return false;
  }
  if (unknown48.unknown00.unknown00 == nullptr || unknown48.unknown00.unknown08 == nullptr) {
    return false;
  }
  return unknown48.unknown00.unknown10 > 0;
}

GmkEnemyList::GmkEnemyList(u32 updateGmkNumPerFrame) : TGmkList(updateGmkNumPerFrame), unknown240(0xffffffff) {}

void GmkEnemyList::create(const CreateInfo &info) {
  if (!unknown228.create()) {
    dispose();
    return;
  }
  TGmkList::create(info);
}

void GmkEnemyList::createGmk(void *data) {
  TGmkList::createGmk(data);
  unknown001(unknown240, getCreateInfo());
}

void GmkEnemyList::dispose() {
  unknown240.dispose();
  TGmkList::dispose();
}

void GmkEnemyList::update(f32 deltaTime) {
  unknown240.update(deltaTime);
  TGmkList::update(deltaTime);
}

const AGmkBase *GmkEnemyList::getInst(u32 index) const { return &gmkInsts[index]; }

void GmkEnemyList::setUpdateGmkNumPerFrame(u32 num) {
  TGmkList::setUpdateGmkNumPerFrame(num);
  unknown240.setUpdateGmkNumPerFrame(num);
}

void GmkEnemyList::debugDraw() const {
  TGmkList::debugDraw();
  unknown240.debugDraw();
}

void GmkEnemyList::debugUpdateMmf() {
  TGmkList::debugUpdateMmf();
  unknown240.debugUpdateMmf();
}

} // namespace gmk

template void mm::mtl::Vector<gmk::GmkEnemy::BdatInfo>::expand(size_t, size_t);

template void mm::mtl::Vector<gmk::GmkEnemy::BdatInfo>::extend(size_t, size_t);
template void mm::mtl::Vector<gmk::GmkEnemy::BdatInfo>::resize(size_t);
