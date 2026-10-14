#include "gf/data/gf_data_field.h"
#include "bdat.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"

namespace gf {

enum {
  BDAT_TIME_RANGE = 0x4f,
  BDAT_WEATHER = 0x50,
};

constexpr u32 VOICE_DRIVER_COUNT = 6;
constexpr u32 VOICE_BLADE_FIRST = 1001;
constexpr u32 VOICE_BLADE_COUNT = 11;
constexpr u32 VOICE_RARE_BLADE_FIRST = 1014;
constexpr u32 VOICE_RARE_BLADE_COUNT = 37;
constexpr u32 VOICE_COMMON_BLADE_FIRST = 1197;
constexpr u32 VOICE_COMMON_BLADE_COUNT = 200;
constexpr u32 PERSONALITY_VOICE_FIRST = 61;
constexpr u32 PERSONALITY_VOICE_COUNT = 32;

const char *GfDataField::getFieldSkillVoice(u32 chara, u32 voice) {
  if (voice == 0) {
    return nullptr;
  }

  GfBdatRsc *bdatResource = GfBdatRsc::get();
  const char *voiceName;
  if (chara - 1 < VOICE_DRIVER_COUNT) {
    voiceName = bdatResource->getVoiceTableDriver(voice, chara - 1);
  } else if (chara - VOICE_BLADE_FIRST < VOICE_BLADE_COUNT) {
    voiceName = bdatResource->getVoiceTableBladeBlade(voice, chara - VOICE_BLADE_FIRST);
  } else if (chara - VOICE_RARE_BLADE_FIRST < VOICE_RARE_BLADE_COUNT) {
    voiceName = bdatResource->getVoiceTableRareBlade(voice, chara - VOICE_RARE_BLADE_FIRST);
  } else {
    if (chara - VOICE_COMMON_BLADE_FIRST >= VOICE_COMMON_BLADE_COUNT) {
      return nullptr;
    }

    u32 personality = GfDataBlade::getSDataBlade(chara)->personality;
    u32 personalityVoice = GfBdatBtl::get()->getBTL_Bl_PersonalityVoiceID(personality);
    if (personalityVoice - PERSONALITY_VOICE_FIRST >= PERSONALITY_VOICE_COUNT) {
      return nullptr;
    }

    voiceName = bdatResource->getVoiceTableCommonCommonBlade(voice, personalityVoice - PERSONALITY_VOICE_FIRST);
  }

  if (voiceName == nullptr || voiceName[0] == '\0') {
    return nullptr;
  }

  return voiceName;
}

bool GfDataField::getLandmarkName(u8 *&bdat, u32 &textId, u32 landmark) {
  textId = static_cast<u16>(Bdat::getValCheck(Bdat::getFP("FLD_LandmarkPop"), "MSGID", landmark, 2));
  bdat = GfBdatMsg::getFpLandmark();
  return textId != 0;
}

bool GfDataField::getTimeRangeName(u8 *&bdat, u32 &textId, u32 time) {
  u16 msg = Bdat::getValCheck(GfDataBdat::getFP(BDAT_TIME_RANGE), "msg", time, 2);
  textId = msg;
  if (msg == 0) {
    return false;
  }

  bdat = GfBdatMsg::getFpMapInfo();
  return true;
}

bool GfDataField::getWeatherName(u8 *&bdat, u32 &textId, u32 weather) {
  u16 msg = Bdat::getValCheck(GfDataBdat::getFP(BDAT_WEATHER), "msg", weather, 2);
  textId = msg;
  if (msg == 0) {
    return false;
  }

  bdat = GfBdatMsg::getFpMapInfo();
  return true;
}

} // namespace gf
