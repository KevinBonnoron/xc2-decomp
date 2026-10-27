#pragma once
#include "gf/data/gf_data_bdat.h"
#include "mm_mtl/singleton.h"
#include "types.h"

struct CBdatWrapper;

namespace gf {

class GfBdatChrDr : public mm::mtl::PtrSingleton<GfBdatChrDr>, public IDataBdat {
public:
  GfBdatChrDr();
  virtual ~GfBdatChrDr();
  void destroyFP();
  void createFP();
  void bdatRefresh() override;
  u32 getChrDrStart() const;
  u32 getChrDrEnd() const;
  u32 getChrDrName(u32 id) const;
  const char *getChrDrDebugName(u32 id) const;
  u32 getChrDrRace(u32 id) const;
  u32 getChrDrRotateLimitPitch(u32 id) const;
  u32 getChrDrRotateLimitRoll(u32 id) const;
  u32 getChrDrGender(u32 id) const;
  const char *getChrDrModel(u32 id) const;
  u32 getChrDrCondition(u32 id) const;
  const char *getChrDrModel2(u32 id) const;
  const char *getChrDrMotion(u32 id) const;
  u32 getChrDrStill(u32 id) const;
  u32 getChrDrOffsetID(u32 id) const;
  u32 getChrDrEyeRot(u32 id) const;
  const char *getChrDrVoice(u32 id) const;
  const char *getChrDrClipEvent(u32 id) const;
  const char *getChrDrCom_SE(u32 id) const;
  const char *getChrDrCom_Eff(u32 id) const;
  const char *getChrDrCom_Vo(u32 id) const;
  u32 getChrDrAiID(u32 id) const;
  u32 getChrDrChestHeight(u32 id) const;
  u32 getChrDrLandingHeight(u32 id) const;
  u32 getChrDrFootStep(u32 id) const;
  u32 getChrDrFootStepEffect(u32 id) const;
  u32 getChrDrDefBlade1(u32 id) const;
  u32 getChrDrDefBlade2(u32 id) const;
  u32 getChrDrDefBlade3(u32 id) const;
  u32 getChrDrDefLvType(u32 id) const;
  u32 getChrDrDefLv(u32 id) const;
  u32 getChrDrDefWPType(u32 id) const;
  u32 getChrDrDefWP(u32 id) const;
  u32 getChrDrDefSPType(u32 id) const;
  u32 getChrDrDefSP(u32 id) const;
  u32 getChrDrDefAcce(u32 id) const;
  u32 getChrDrDefIdeaBlue(u32 id) const;
  u32 getChrDrDefIdeaRed(u32 id) const;
  u32 getChrDrDefIdeaWhite(u32 id) const;
  u32 getChrDrDefIdeaBlack(u32 id) const;
  u32 getChrDrHpMaxLv1(u32 id) const;
  u32 getChrDrStrengthLv1(u32 id) const;
  u32 getChrDrPowEtherLv1(u32 id) const;
  u32 getChrDrDexLv1(u32 id) const;
  u32 getChrDrAgilityLv1(u32 id) const;
  u32 getChrDrLuckLv1(u32 id) const;
  u32 getChrDrHpMaxLv99(u32 id) const;
  u32 getChrDrStrengthLv99(u32 id) const;
  u32 getChrDrPowEtherLv99(u32 id) const;
  u32 getChrDrDexLv99(u32 id) const;
  u32 getChrDrAgilityLv99(u32 id) const;
  u32 getChrDrLuckLv99(u32 id) const;
  u32 getChrDrFavoriteCategory1(u32 id) const;
  u32 getChrDrFavoriteCategory2(u32 id) const;
  u32 getChrDrFavoriteItem1(u32 id) const;
  u32 getChrDrFavoriteItem2(u32 id) const;
  u32 getChrDrCollisionId(u32 id) const;
  const char *getChrDrCenterBone(u32 id) const;
  const char *getChrDrCamBone(u32 id) const;
  u32 getChrDrWpnType(u32 driver, u32 slot) const;
  u32 getChrDrWpRate(u32 id, u32 index) const;
  u32 getChrDrDefBlade(u32 driver, u32 slot) const;
  u32 getChrDrFavoriteCategory(u32 driver, u32 favorite) const;
  u32 getChrDrFavoriteItem(u32 driver, u32 favorite) const;

private:
  CBdatWrapper *m_chrDr;
};

} // namespace gf
