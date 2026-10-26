#include "gf/field/gf_field_bgm.h"

#include "gf/data/gf_bdat_maplist.h"
#include "gf/event/gf_event.h"
#include "gf/game/gf_game_manager.h"

namespace gf {

namespace _gffsn {
bool s_bStopBGM;
} // namespace _gffsn

enum {
  MAPJUMP_TYPE_FIELD_DESTROY = 2,
};

u32 GfFieldBgm::getRscFieldBgmID() const {
  u32 map = GfGameManager::getMapID();
  if (map != 0) {
    return GfBdatMaplist::get()->getMaplistbgm_cndID(map);
  }
  return 0;
}

u32 GfFieldBgm::getRscBossBattleBgmID() const { return m_rscBossBattleBgmID; }

u32 GfFieldBgm::getRscBattleBgmID() const { return m_rscBattleBgmID; }

u32 GfFieldBgm::getRscGimmickBgmID() const { return m_rscGimmickBgmID; }

bool GfFieldBgm::isDisableFieldBgmChange() const { return m_disableFieldBgmChange; }

void GfFieldBgm::setGimmickBgmID(u32 id) {
  if (id == 0 && m_gimmickBgmID != 0) {
    unknowna4 = 30;
  }
  m_gimmickBgmID = id;
}

void GfFieldBgm::gevBattleEnd() { m_rscBossBattleBgmID = 0; }

void GfFieldBgm::gevMapjump(GEV gev, const MapjumpCallbackInfo &info) {
  switch (gev) {
  case GEV_MAPJUMP_START:
    applyMapJumpStart(info);
    break;
  case GEV_MAPJUMP_FADEIN:
    applyMapJumpFadein(info);
    break;
  default:
    break;
  }
}

void GfFieldBgm::applyMapJumpStart(const MapjumpCallbackInfo &info) {
  if (info.unknown10 == MAPJUMP_TYPE_FIELD_DESTROY) {
    unknowna9 = true;
  }
  m_disableFieldBgmChange = true;
}

void GfFieldBgm::applyMapJumpCleanup(const MapjumpCallbackInfo &) {}

void GfFieldBgm::applyMapJumpFadein(const MapjumpCallbackInfo &info) {
  if (info.unknown10 == MAPJUMP_TYPE_FIELD_DESTROY) {
    unknowna9 = false;
  }
  m_disableFieldBgmChange = false;
}

void GfFieldBgm::updateGimmickBgm(const fw::UpdateInfo &) {
  unknowna4--;
  if (unknowna4 <= 0 && m_gimmickBgmID != static_cast<u32>(-1)) {
    m_rscGimmickBgmID = m_gimmickBgmID;
    m_gimmickBgmID = -1;
  }
}

void GfFieldBgm::stopBgmForDebug(bool stop) { _gffsn::s_bStopBGM = stop; }

bool GfFieldBgm::isStopBgmForDebug() { return _gffsn::s_bStopBGM; }

} // namespace gf
