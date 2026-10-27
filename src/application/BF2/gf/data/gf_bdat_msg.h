#pragma once
#include "gf/data/gf_data_bdat.h"
#include "mm_mtl/singleton.h"
#include "types.h"

struct CBdatWrapper;

namespace gf {
struct QuestID;

class GfBdatMsg : public mm::mtl::PtrSingleton<GfBdatMsg>, public IDataBdat {
public:
  GfBdatMsg();
  virtual ~GfBdatMsg();
  static void destroyFP();
  static void createFP();
  void bdatRefresh() override;
  static const char *getNameEnemy(u32 id);
  static u8 *getFpEnemy();
  static const char *getNameNpc(u32 id);
  static u8 *getFpNpc();
  static const char *getNameQuest(QuestID quest, u32 line);
  static u8 *getFpQuest(QuestID quest);
  static u8 *getFpQuest(u32 quest);
  static const char *getNameMapInfo(u32 id);
  static u8 *getFpMapInfo();
  static const char *getNameLandmark(u32 id);
  static u8 *getFpLandmark();
  static const char *getNameCollection(u32 id);
  static u8 *getFpCollection();
  static const char *getNameCrystal(u32 id);
  static u8 *getFpCrystal();
  static const char *getNamePrecious(u32 id);
  static u8 *getFpPrecious();
  static const char *getNameInfo(u32 id);
  static u8 *getFpInfo();
  static const char *getNameEvent(u32 id);
  static u8 *getFpEvent();
  static u8 *getFpPcWpn();
  static u8 *getFpPcWpnChip();
  static u8 *getFpPcWpnType();
  static u8 *getFpSalvage();
  static u8 *getFpTresure();
  static u8 *getFpBooster();
  static u8 *getFpFavorite();
  static u8 *getFpOrb();
  static u8 *getFpPcEquip();
  static const char *getNameBladeName(u32 id);
  static u8 *getFpCommonBladeName();
  static u8 *getFpMerceName();
  static const char *getNameFieldSkill(u32 id);
  static u8 *getFpFieldSkill();
  static u8 *getFpAchievement();
  static const char *getNameChrDr(u32 id);
  static u8 *getFpChrDr();
  static const char *getNameChrBl(u32 id);
  static u8 *getFpChrBl();
  static const char *getNameEnGenus(u32 id);
  static u8 *getFpBtlClass();
  static u8 *getFpBlArtsMs();
  static u8 *getFpBlSpArtsMs();
  static u8 *getFpBlSkill();
  static u8 *getFpDrArtsMs();
  static u8 *getFpBtlEnhanceCap();
  static u8 *getFpBlBuffMs();
  static u8 *getFpBlBuffCap();
  static u8 *getFpBtlHanaRole();
  static u8 *getFpBtlHanaNArts();
  static u8 *getFpBtlHanaArts();
  static u8 *getFpBtlHanaAtr();
  static u8 *getFpBtlHanaAssist();
  static u8 *getFpBtlSkillDr();
  static u8 *getFpRscEnGenus();

private:
  static CBdatWrapper *m_fpBldBladeName;
  static CBdatWrapper *m_fpBldMerceName;
  static CBdatWrapper *m_fpFldEnemyName;
  static CBdatWrapper *m_fpFldNpcName;
  static CBdatWrapper *m_fpFldQuest;
  static CBdatWrapper *m_fpFldMapInfo;
  static CBdatWrapper *m_fpFldLandmark;
  static CBdatWrapper *m_fpFldFieldSkill;
  static CBdatWrapper *m_fpItmCollection;
  static CBdatWrapper *m_fpItmCrystal;
  static CBdatWrapper *m_fpItmPrecious;
  static CBdatWrapper *m_fpItmInfo;
  static CBdatWrapper *m_fpItmEvent;
  static CBdatWrapper *m_fpItmPcWpn;
  static CBdatWrapper *m_fpItmPcWpnChip;
  static CBdatWrapper *m_fpItmPcWpnType;
  static CBdatWrapper *m_fpItmSalvage;
  static CBdatWrapper *m_fpItmTresure;
  static CBdatWrapper *m_fpItmFavorite;
  static CBdatWrapper *m_fpItmBooster;
  static CBdatWrapper *m_fpItmOrb;
  static CBdatWrapper *m_fpItmPcEquip;
  static CBdatWrapper *m_fpChrDr;
  static CBdatWrapper *m_fpChrBl;
  static CBdatWrapper *m_fpBtlClass;
  static CBdatWrapper *m_fpBlArtsMs;
  static CBdatWrapper *m_fpBlSpArtsMs;
  static CBdatWrapper *m_fpBlSkill;
  static CBdatWrapper *m_fpDrArtsMs;
  static CBdatWrapper *m_fpBtlEnhanceCap;
  static CBdatWrapper *m_fpFldQuestNormal;
  static CBdatWrapper *m_fpFldQuestMini;
  static CBdatWrapper *m_fpFldQuestBlade;
  static CBdatWrapper *m_fpFldQuestAchievement;
  static CBdatWrapper *m_fpFldQuestMercenaries;
  static CBdatWrapper *m_fpBtlBuffMs;
  static CBdatWrapper *m_fpBtlBuffCap;
  static CBdatWrapper *m_fpFldAchievement;
  static CBdatWrapper *m_fpBtlHanaRole;
  static CBdatWrapper *m_fpBtlHanaNArts;
  static CBdatWrapper *m_fpBtlHanaArts;
  static CBdatWrapper *m_fpBtlHanaAtr;
  static CBdatWrapper *m_fpBtlHanaAssist;
  static CBdatWrapper *m_fpBtlSkillDr;
  static CBdatWrapper *m_fpBtlEnGenus;
};

} // namespace gf
