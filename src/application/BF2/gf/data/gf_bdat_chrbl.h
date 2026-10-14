#pragma once
#include "gf/data/gf_bdat_wrapper.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

class GfBdatChrBl : public mm::mtl::PtrSingleton<GfBdatChrBl>, public GfBdatRefresh {
public:
  u32 getChrBlStart() const;
  u32 getChrBlName(u32 id) const;
  const char *getChrBlDebugName(u32 id) const;
  u32 getChrBlRace(u32 id) const;
  u32 getChrBlRotateLimitPitch(u32 id) const;
  u32 getChrBlRotateLimitRoll(u32 id) const;
  u32 getChrBlGender(u32 id) const;
  u32 getChrBlQuestRace(u32 id) const;
  const char *getChrBlModel(u32 id) const;
  const char *getChrBlMotion(u32 id) const;
  const char *getChrBlAddMotion(u32 id) const;
  u32 getChrBlCondition(u32 id) const;
  const char *getChrBlModel2(u32 id) const;
  const char *getChrBlMotion2(u32 id) const;
  u32 getChrBlStill(u32 id) const;
  const char *getChrBlVoice(u32 id) const;
  const char *getChrBlClipEvent(u32 id) const;
  const char *getChrBlCom_SE(u32 id) const;
  const char *getChrBlSePack(u32 id) const;
  const char *getChrBlCom_Eff(u32 id) const;
  const char *getChrBlCom_Vo(u32 id) const;
  u32 getChrBlOffsetID(u32 id) const;
  u32 getChrBlEyeRot(u32 id) const;
  u32 getChrBlChestHeight(u32 id) const;
  u32 getChrBlLandingHeight(u32 id) const;
  u32 getChrBlFootStep(u32 id) const;
  u32 getChrBlFootStepEffect(u32 id) const;
  u32 getChrBlWeaponType(u32 id) const;
  u32 getChrBlScale(u32 id) const;
  u32 getChrBlWpnScale(u32 id) const;
  bool isChrBlFlagOnlyWpn(u32 id) const;
  u32 getChrBlPrivateWpnR(u32 id) const;
  u32 getChrBlPrivateWpnL(u32 id) const;
  u32 getChrBlPrivateWpnR_Driver(u32 id) const;
  u32 getChrBlPrivateWpnL_Driver(u32 id) const;
  const char *getChrBlWpnrOut(u32 id) const;
  const char *getChrBlWpnlOut(u32 id) const;
  u32 getChrBlOrbNum(u32 id) const;
  u32 getChrBlAtr(u32 id) const;
  u32 getChrBlPersonality(u32 id) const;
  u32 getChrBlCoolTime(u32 id) const;
  u32 getChrBlDefWeapon(u32 id) const;
  u32 getChrBlBArts1(u32 id) const;
  u32 getChrBlBArts2(u32 id) const;
  u32 getChrBlBArts3(u32 id) const;
  u32 getChrBlBartsEx(u32 id) const;
  u32 getChrBlBartsEx2(u32 id) const;
  u32 getChrBlNArts1(u32 id) const;
  u32 getChrBlNArtsRecastRev1(u32 id) const;
  u32 getChrBlNArts2(u32 id) const;
  u32 getChrBlNArtsRecastRev2(u32 id) const;
  u32 getChrBlNArts3(u32 id) const;
  u32 getChrBlNArtsRecastRev3(u32 id) const;
  u32 getChrBlBSkill1(u32 id) const;
  u32 getChrBlBSkill2(u32 id) const;
  u32 getChrBlBSkill3(u32 id) const;
  u32 getChrBlPArmor(u32 id) const;
  u32 getChrBlEArmor(u32 id) const;
  u32 getChrBlHpMaxRev(u32 id) const;
  u32 getChrBlStrengthRev(u32 id) const;
  u32 getChrBlPowEtherRev(u32 id) const;
  u32 getChrBlDexRev(u32 id) const;
  u32 getChrBlAgilityRev(u32 id) const;
  u32 getChrBlLuckRev(u32 id) const;
  u32 getChrBlBKLSet(u32 id) const;
  u32 getChrBlFSkill1(u32 id) const;
  u32 getChrBlFSkill2(u32 id) const;
  u32 getChrBlFSkill3(u32 id) const;
  u32 getChrBlArtsAchievement1(u32 id) const;
  u32 getChrBlArtsAchievement2(u32 id) const;
  u32 getChrBlArtsAchievement3(u32 id) const;
  u32 getChrBlSkillAchievement1(u32 id) const;
  u32 getChrBlSkillAchievement2(u32 id) const;
  u32 getChrBlSkillAchievement3(u32 id) const;
  u32 getChrBlFskillAchivement1(u32 id) const;
  u32 getChrBlFskillAchivement2(u32 id) const;
  u32 getChrBlFskillAchivement3(u32 id) const;
  u32 getChrBlKeyAchievement(u32 id) const;
  u32 getChrBlIdeaBlue(u32 id) const;
  u32 getChrBlIdeaRed(u32 id) const;
  u32 getChrBlIdeaWhite(u32 id) const;
  u32 getChrBlIdeaBlack(u32 id) const;
  u32 getChrBlFavoriteCategory1(u32 id) const;
  u32 getChrBlFavoriteCategory2(u32 id) const;
  u32 getChrBlFavoriteItem1(u32 id) const;
  u32 getChrBlFavoriteItem2(u32 id) const;
  u32 getChrBlCreateEventID(u32 id) const;
  u32 getChrBlNormalTalk(u32 id) const;
  u32 getChrBlCollisionId(u32 id) const;
  u32 getChrBlBladeSize(u32 id) const;
  u32 getChrBlMemorySlot(u32 id) const;
  u32 getChrBlEventAsset(u32 id) const;
  const char *getChrBlCenterBone(u32 id) const;
  const char *getChrBlCamBone(u32 id) const;
  u32 getChrBlMerceName(u32 id) const;
  u32 getChrBlReleaseLock(u32 id) const;
  u32 getChrBlCreateInfo(u32 id) const;
  u32 getChrBlExtraParts1(u32 id) const;
  u32 getChrBlExtraParts2(u32 id) const;
  u32 getChrBlExtraParts3(u32 id) const;
  u32 getChrBlExtraParts4(u32 id) const;
  u32 getChrBlMnuCastName(u32 id) const;
  u32 getChrBlMnuIlustName(u32 id) const;
  const char *getChrBlMnuVoice1(u32 id) const;
  const char *getChrBlMnuVoice2(u32 id) const;
  const char *getChrBlMnuVoice3(u32 id) const;

  u32 getChrBlEnd() const;

private:
  CBdatWrapper *unknown10; // Inferred label: mChrBl; original member name unknown.
};

} // namespace gf
