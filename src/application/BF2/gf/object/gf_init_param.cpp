#include "gf/object/gf_init_param.h"

#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_bdat_chrenparam.h"
#include "gf/data/gf_data_blade.h"

namespace gf {

namespace {

// Original name unknown: common start of the GfInitParamEnemy setup functions.
void unknown001(GfInitParamEnemy &param, CharacterType type, u32 enArrange) {
  param.unknown08 = type;
  param.m_enArrangeID = enArrange;
  param.unknown98 = GfBdatChrEnArrange::get()->getChrEnArrangeParamID(enArrange);
  param.GfInitParam::m_bladeID = GfBdatChrEnParam::get()->getChrEnParamResourceID(param.unknown98);
}

} // namespace

u32 GfInitParam::getEnArrangeID() const { return 0; }

bool GfInitParamBlade::isAllWeapon() const { return m_allWeapon; }

void GfInitParamBlade::setupForParty(u32 blade, int slot, u32 driver, GF_OBJ_HANDLE *owner, bool isVirtual) {
  unknown08 = CHARACTER_TYPE_PARTY;
  unknown90 = true;
  unknown20 = blade;
  m_bladeID = driver;
  unknown98 = slot;
  unknown38 = owner;
  unknown91 = isVirtual;
  unknown4c = GfDataBlade::getScale(driver);
}

void GfInitParamBlade::setupForEvent(u32 blade, bool isFirst) {
  unknown08 = CHARACTER_TYPE_EVENT;
  m_bladeID = blade;
  unknown40 = 7;
  unknown4c = GfDataBlade::getScale(blade);
  unknowna4 = blade == 0x3e9 && isFirst;
  unknown81 = false;
  unknown82 = false;
}

void GfInitParamBlade::setupForEventWithWeapon(u32 blade) {
  unknown08 = CHARACTER_TYPE_EVENT;
  m_bladeID = blade;
  unknown40 = 7;
  unknown4c = GfDataBlade::getScale(blade);
  unknowna4 = false;
  unknown81 = false;
  unknown82 = false;
  unknown94 = GfDataBlade::getBladeWeapon(blade);
}

void GfInitParamBlade::setupForActViewer(u32 blade, u32 weapon) {
  unknown08 = CHARACTER_TYPE_UNKNOWN_10;
  m_bladeID = blade;
  unknown94 = weapon;
  unknown4c = GfDataBlade::getScale(blade);
  m_allWeapon = true;
}

void GfInitParamBlade::setupForActViewerEvent(u32 blade, u32 weapon) {
  unknown08 = CHARACTER_TYPE_ACT_VIEWER_EVENT;
  m_bladeID = blade;
  unknown94 = weapon;
  unknown40 = 7;
  unknown4c = GfDataBlade::getScale(blade);
}

void GfInitParamBlade::setupForActViewerUI(u32 blade, u32 weapon) {
  unknown08 = CHARACTER_TYPE_EVENT_NPC;
  m_bladeID = blade;
  unknown94 = weapon;
  unknown4c = GfDataBlade::getScale(blade);
}

void GfInitParamBlade::setupForUi(u32 blade, VIEWCAM camera) {
  unknown08 = CHARACTER_TYPE_EVENT_DRIVER;
  m_bladeID = blade;
  unknown24 = camera;
  unknown40 = 10;
  unknown4c = GfDataBlade::getScale(blade);
  unknown81 = false;
}

bool GfInitParamDriver::isAllWeapon() const { return m_allWeapon; }

u32 GfInitParamEnemy::getBladeID() const { return m_bladeID; }

u32 GfInitParamEnemy::getEnArrangeID() const { return m_enArrangeID; }

void GfInitParamEnemy::setupForEvent(u32 enArrange) {
  unknown001(*this, CHARACTER_TYPE_EVENT, enArrange);
  unknowna4 = GfBdatChrEnParam::get()->getChrEnParamResourceID(unknown98);
  unknown40 = 8;
  unknown81 = false;
  unknown82 = false;
}

void GfInitParamEnemy::setupEnArrangeId(u32 enArrange) {
  unknown001(*this, CHARACTER_TYPE_UNKNOWN_4, enArrange);
  unknowna4 = GfBdatChrEnParam::get()->getChrEnParamResourceID(unknown98);
  unknown40 = 5;
}

void GfInitParamEnemy::setupBlade(const GfInitParamEnemy &enemy) {
  GfBdatChrEnArrange *arrange = GfBdatChrEnArrange::get();
  unknown08 = CHARACTER_TYPE_ENEMY_BLADE;
  m_enArrangeID = arrange->getChrEnArrangeEnemyBladeID(enemy.m_enArrangeID);
  unknown98 = arrange->getChrEnArrangeParamID(m_enArrangeID);
  unknowna8 = 1;
  GfInitParam::m_bladeID = GfBdatChrEnParam::get()->getChrEnParamResourceID(unknown98);
  unknown40 = 5;
  m_bladeID = arrange->getChrEnArrangeBladeID(m_enArrangeID);
}

void GfInitParamEnemy::setupForUi(u32 enArrange, VIEWCAM camera) {
  unknown001(*this, CHARACTER_TYPE_EVENT_DRIVER, enArrange);
  unknown40 = 11;
  unknown24 = camera;
  unknown81 = false;
}

void GfInitParamEnemy::setupForActViewer(u32 resource, const CBdatWrapper *bdat) {
  unknown08 = CHARACTER_TYPE_UNKNOWN_10;
  GfInitParam::m_bladeID = resource;
  unknowna4 = resource;
  m_enArrangeID = 0;
  GfBdatChrEnArrange *arrange = GfBdatChrEnArrange::get();
  GfBdatChrEnParam *param = GfBdatChrEnParam::get();
  u32 start = arrange->getChrEnArrangeStart();
  u32 end = arrange->getChrEnArrangeEnd();
  for (u32 i = start; i < end; i++) {
    u32 paramId = arrange->getChrEnArrangeParamID(i);
    if (param->getChrEnParamResourceID(paramId) == resource) {
      if (arrange->getChrEnArrangeEnemyBladeID(i) != 0) {
        unknown98 = paramId;
        m_enArrangeID = i;
        break;
      }
      if (m_enArrangeID == 0) {
        unknown98 = paramId;
        m_enArrangeID = i;
      }
    }
  }
  unknown18 = bdat;
}

void GfInitParamEnemy::setupForActViewerEvent(u32 resource, const CBdatWrapper *bdat) {
  unknown08 = CHARACTER_TYPE_ACT_VIEWER_EVENT;
  GfInitParam::m_bladeID = resource;
  unknowna4 = resource;
  m_enArrangeID = 0;
  GfBdatChrEnArrange *arrange = GfBdatChrEnArrange::get();
  GfBdatChrEnParam *param = GfBdatChrEnParam::get();
  u32 start = arrange->getChrEnArrangeStart();
  u32 end = arrange->getChrEnArrangeEnd();
  for (u32 i = start; i < end; i++) {
    u32 paramId = arrange->getChrEnArrangeParamID(i);
    if (param->getChrEnParamResourceID(paramId) == resource) {
      if (arrange->getChrEnArrangeEnemyBladeID(i) != 0) {
        unknown98 = paramId;
        m_enArrangeID = i;
        break;
      }
      if (m_enArrangeID == 0) {
        unknown98 = paramId;
        m_enArrangeID = i;
      }
    }
  }
  unknown18 = bdat;
  unknown82 = false;
  unknown40 = 7;
}

u32 GfInitParamEnWeapon::getEnArrangeID() const { return m_enArrangeID; }

} // namespace gf
