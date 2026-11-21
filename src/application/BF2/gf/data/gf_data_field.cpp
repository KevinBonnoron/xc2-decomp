#include "gf/data/gf_data_field.h"
#include "bdat.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"

namespace gf {

constexpr u32 VOICE_UNKNOWN_6 = 6;       // Inferred role: voice driver count; original name unknown.
constexpr u32 VOICE_UNKNOWN_1001 = 1001; // Inferred role: voice blade first; original name unknown.
constexpr u32 VOICE_UNKNOWN_11 = 11;     // Inferred role: voice blade count; original name unknown.
constexpr u32 VOICE_UNKNOWN_1014 = 1014; // Inferred role: voice rare blade first; original name unknown.
constexpr u32 VOICE_UNKNOWN_37 = 37;     // Inferred role: voice rare blade count; original name unknown.
constexpr u32 VOICE_UNKNOWN_1197 = 1197; // Inferred role: voice common blade first; original name unknown.
constexpr u32 VOICE_UNKNOWN_200 = 200;   // Inferred role: voice common blade count; original name unknown.
constexpr u32 VOICE_UNKNOWN_32 = 32;     // Inferred role: personality voice count; original name unknown.

const char *GfDataField::getFieldSkillVoice(u32 chara, u32 voice) {
  if (voice == 0) {
    return nullptr;
  }

  GfBdatRsc *bdatResource = GfBdatRsc::get();
  const char *voiceName;
  if (chara - 1 < VOICE_UNKNOWN_6) {
    voiceName = bdatResource->getVoiceTableDriver(voice, chara - 1);
  } else if (chara - VOICE_UNKNOWN_1001 < VOICE_UNKNOWN_11) {
    voiceName = bdatResource->getVoiceTableBladeBlade(voice, chara - VOICE_UNKNOWN_1001);
  } else if (chara - VOICE_UNKNOWN_1014 < VOICE_UNKNOWN_37) {
    voiceName = bdatResource->getVoiceTableRareBlade(voice, chara - VOICE_UNKNOWN_1014);
  } else {
    if (chara - VOICE_UNKNOWN_1197 >= VOICE_UNKNOWN_200) {
      return nullptr;
    }

    u32 personality = GfDataBlade::getSDataBlade(chara).unknown824;
    u32 personalityVoice = GfBdatBtl::get()->getBTL_Bl_PersonalityVoiceID(personality);
    if (personalityVoice - VOICE_UNKNOWN_61 >= VOICE_UNKNOWN_32) {
      return nullptr;
    }

    voiceName = bdatResource->getVoiceTableCommonCommonBlade(voice, personalityVoice - VOICE_UNKNOWN_61);
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
  u16 msg = Bdat::getValCheck(GfDataBdat::getFP(BDAT_FLD_TIME_INFO), "msg", time, 2);
  textId = msg;
  if (msg == 0) {
    return false;
  }

  bdat = GfBdatMsg::getFpMapInfo();
  return true;
}

const char *GfDataField::getTimeRangeName(u32 time) {
  u16 msg = Bdat::getValCheck(GfDataBdat::getFP(BDAT_FLD_TIME_INFO), "msg", time, 2);
  const char *name = nullptr;
  if (msg) {
    // The game tests the u16 (and w8, w0, #0xffff at 0x71002b569c), then zero-extends the id (and w19, w0, #0xffff at 0x71002b56a4) before the call of getFpMapInfo;
    // passing msg to getMSText directly extends it after that call.
    u32 textId = msg;
    name = Bdat::getMSText(GfBdatMsg::getFpMapInfo(), textId);
  }
  if (name == nullptr) {
    name = "";
  }
  return name;
}

bool GfDataField::getWeatherName(u8 *&bdat, u32 &textId, u32 weather) {
  u16 msg = Bdat::getValCheck(GfDataBdat::getFP(BDAT_FLD_WEATHER_INFO), "msg", weather, 2);
  textId = msg;
  if (msg == 0) {
    return false;
  }

  bdat = GfBdatMsg::getFpMapInfo();
  return true;
}

} // namespace gf
