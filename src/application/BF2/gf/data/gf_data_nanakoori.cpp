#include "gf/data/gf_data_nanakoori.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_item_id.h"
#include "types.h"

namespace gf {

enum {
  FLAG_NANAKOORI_VOCAL_LEVEL = 0x84f,
  FLAG_NANAKOORI_VISUAL_LEVEL = 0x850,
  FLAG_NANAKOORI_SOUL_LEVEL = 0x851,
  FLAG_NANAKOORI_FAN = 0x60e,
};

enum {
  MISSION_VOCAL_LESSON_1 = 0xb2,
  MISSION_VOCAL_LESSON_2 = 0xb3,
  MISSION_VOCAL_LESSON_3 = 0xb4,
  MISSION_VOCAL_LESSON_4 = 0xb5,
  MISSION_VOCAL_LESSON_5 = 0xb6,
  MISSION_LOOKS_LESSON_1 = 0xb7,
  MISSION_LOOKS_LESSON_2 = 0xb8,
  MISSION_LOOKS_LESSON_3 = 0xb9,
  MISSION_LOOKS_LESSON_4 = 0xba,
  MISSION_LOOKS_LESSON_5 = 0xbb,
  MISSION_SOUL_LESSON_1 = 0xbc,
  MISSION_SOUL_LESSON_2 = 0xbd,
  MISSION_SOUL_LESSON_3 = 0xbe,
  MISSION_SOUL_LESSON_4 = 0xbf,
  MISSION_SOUL_LESSON_5 = 0xc0,
  MISSION_SPARKLY_COSTUMES = 0xc1,
  MISSION_SONG_SELECTION = 0xc2,
  MISSION_LUXURY_STAGE = 0xc3,
  MISSION_REHEARSAL = 0xc4,
  MISSION_HOLY_CHOIR = 0xc5,
  MISSION_FASHION_SHOW = 0xc6,
  MISSION_MEET_AND_GREET = 0xc7,
  MISSION_CONCERT_IN_ARGENTUM = 0xc8,
  MISSION_CONCERT_IN_URAYA = 0xc9,
  MISSION_CONCERT_IN_MOR_ARDAIN = 0xca,
  MISSION_NOPON_POP_STARS = 0xcb,
  MISSION_LOCAL_POP_STAR = 0xcc,
  MISSION_STAGE_STAR = 0xcd,
  MISSION_SUMMER_CONCERT = 0xce,
  MISSION_BENEFIT_CONCERT = 0xcf,
  MISSION_INVITATION_FROM_QUEEN = 0xd0,
  MISSION_INVITATION_FROM_EMPEROR = 0xd1,
  MISSION_SPECIAL_CONCERT = 0xd2,
};

bool GfDataNanakoori::setVocalLevel(u32 vocalLevel) {
  u32 oldVocalLevel = GfGameFlag::getLocal(8, FLAG_NANAKOORI_VOCAL_LEVEL);
  GfGameFlag::setLocal(8, FLAG_NANAKOORI_VOCAL_LEVEL, vocalLevel);
  return oldVocalLevel != vocalLevel;
}

u32 GfDataNanakoori::getVocalLevel() { return GfGameFlag::getLocal(8, FLAG_NANAKOORI_VOCAL_LEVEL); }

bool GfDataNanakoori::setVisualLevel(u32 visualLevel) {
  u32 oldVisualLevel = GfGameFlag::getLocal(8, FLAG_NANAKOORI_VISUAL_LEVEL);
  GfGameFlag::setLocal(8, FLAG_NANAKOORI_VISUAL_LEVEL, visualLevel);
  return oldVisualLevel != visualLevel;
}

u32 GfDataNanakoori::getVisualLevel() { return GfGameFlag::getLocal(8, FLAG_NANAKOORI_VISUAL_LEVEL); }

bool GfDataNanakoori::setSoulLevel(u32 soulLevel) {
  u32 oldSoulLevel = GfGameFlag::getLocal(8, FLAG_NANAKOORI_SOUL_LEVEL);
  GfGameFlag::setLocal(8, FLAG_NANAKOORI_SOUL_LEVEL, soulLevel);
  return oldSoulLevel != soulLevel;
}

u32 GfDataNanakoori::getSoulLevel() { return GfGameFlag::getLocal(8, FLAG_NANAKOORI_SOUL_LEVEL); }

bool GfDataNanakoori::setFan(u32 fan) {
  u32 oldFan = GfGameFlag::getLocal(0x10, FLAG_NANAKOORI_FAN);
  GfGameFlag::setLocal(0x10, FLAG_NANAKOORI_FAN, fan);
  return oldFan != fan;
}

u32 GfDataNanakoori::getFan() { return GfGameFlag::getLocal(0x10, FLAG_NANAKOORI_FAN); }

u32 GfDataNanakoori::getNanakooriMissionClearFlg1Offset(u32 mission) {
  return mission == MISSION_HOLY_CHOIR                ? 1
         : mission == MISSION_FASHION_SHOW            ? 2
         : mission == MISSION_MEET_AND_GREET          ? 3
         : mission == MISSION_INVITATION_FROM_QUEEN   ? 4
         : mission == MISSION_INVITATION_FROM_EMPEROR ? 5
         : mission == MISSION_SPECIAL_CONCERT         ? 6
         : mission == MISSION_SPARKLY_COSTUMES        ? 0x15
         : mission == MISSION_SONG_SELECTION          ? 0x16
         : mission == MISSION_LUXURY_STAGE            ? 0x17
         : mission == MISSION_REHEARSAL               ? 0x18
         : mission == MISSION_NOPON_POP_STARS         ? 0x19
         : mission == MISSION_LOCAL_POP_STAR          ? 0x1a
         : mission == MISSION_STAGE_STAR              ? 0x1b
         : mission == MISSION_SUMMER_CONCERT          ? 0x1c
         : mission == MISSION_BENEFIT_CONCERT         ? 0x1d
         : mission == MISSION_VOCAL_LESSON_1          ? 0x29
         : mission == MISSION_VOCAL_LESSON_2          ? 0x2a
         : mission == MISSION_VOCAL_LESSON_3          ? 0x2b
         : mission == MISSION_VOCAL_LESSON_4          ? 0x2c
         : mission == MISSION_VOCAL_LESSON_5          ? 0x2d
         : mission == MISSION_LOOKS_LESSON_1          ? 0x2e
         : mission == MISSION_LOOKS_LESSON_2          ? 0x2f
         : mission == MISSION_LOOKS_LESSON_3          ? 0x30
         : mission == MISSION_LOOKS_LESSON_4          ? 0x31
         : mission == MISSION_LOOKS_LESSON_5          ? 0x32
         : mission == MISSION_SOUL_LESSON_1           ? 0x33
         : mission == MISSION_SOUL_LESSON_2           ? 0x34
         : mission == MISSION_SOUL_LESSON_3           ? 0x35
         : mission == MISSION_SOUL_LESSON_4           ? 0x36
         : mission == MISSION_SOUL_LESSON_5           ? 0x37
                                                      : 0;
}

u32 GfDataNanakoori::getLevelForNanakoori(u32 stampCount) {
  return stampCount == 0     ? 1
         : stampCount < 3    ? 2
         : stampCount < 9    ? 3
         : stampCount < 0x11 ? 4
         : stampCount < 0x1e ? 5
         : stampCount < 0x32 ? 6
         : stampCount < 0x4b ? 7
         : stampCount < 0x63 ? 8
                             : 9;
}

u64 GfDataNanakoori::getItemForVocalLevelUp() { return ITEM_VOCALS_STAMP; }

u64 GfDataNanakoori::getItemForVisualLevelUp() { return ITEM_LOOKS_STAMP; }

u64 GfDataNanakoori::getItemForSoulLevelUp() { return ITEM_SOUL_STAMP; }

u32 GfDataNanakoori::getClearMissionForSpecial() {
  u32 clearMissionForSpecial = 0;

  constexpr static u16 missions[] = {
      MISSION_HOLY_CHOIR,
      MISSION_FASHION_SHOW,
      MISSION_MEET_AND_GREET,
      MISSION_INVITATION_FROM_QUEEN,
      MISSION_INVITATION_FROM_EMPEROR,
      MISSION_SPECIAL_CONCERT,
  };

  for (u32 i = 0; i < sizeof(missions) / sizeof(missions[0]); i++) {
    u32 offset = getNanakooriMissionClearFlg1Offset(missions[i]);
    if (offset != 0 && GfGameFlag::getLocal(1, offset) != 0) {
      clearMissionForSpecial += 1;
    }
  }

  return clearMissionForSpecial;
}

u32 GfDataNanakoori::getClearMissionForLive() {
  u32 clearMissionForLive = 0;

  constexpr static u16 missions[] = {
      MISSION_SPARKLY_COSTUMES,
      MISSION_SONG_SELECTION,
      MISSION_LUXURY_STAGE,
      MISSION_REHEARSAL,
      MISSION_NOPON_POP_STARS,
      MISSION_LOCAL_POP_STAR,
      MISSION_STAGE_STAR,
      MISSION_SUMMER_CONCERT,
      MISSION_BENEFIT_CONCERT,
  };

  for (u32 i = 0; i < sizeof(missions) / sizeof(missions[0]); i++) {
    u32 offset = getNanakooriMissionClearFlg1Offset(missions[i]);
    if (offset != 0 && GfGameFlag::getLocal(1, offset) != 0) {
      clearMissionForLive += 1;
    }
  }

  return clearMissionForLive;
}

u32 GfDataNanakoori::getClearMissionForLesson() {
  u32 clearMissionForLesson = 0;

  constexpr static u16 missions[] = {
      MISSION_VOCAL_LESSON_1,
      MISSION_VOCAL_LESSON_2,
      MISSION_VOCAL_LESSON_3,
      MISSION_VOCAL_LESSON_4,
      MISSION_VOCAL_LESSON_5,
      MISSION_LOOKS_LESSON_1,
      MISSION_LOOKS_LESSON_2,
      MISSION_LOOKS_LESSON_3,
      MISSION_LOOKS_LESSON_4,
      MISSION_LOOKS_LESSON_5,
      MISSION_SOUL_LESSON_1,
      MISSION_SOUL_LESSON_2,
      MISSION_SOUL_LESSON_3,
      MISSION_SOUL_LESSON_4,
      MISSION_SOUL_LESSON_5,
  };

  for (u32 i = 0; i < sizeof(missions) / sizeof(missions[0]); i++) {
    u32 offset = getNanakooriMissionClearFlg1Offset(missions[i]);
    if (offset != 0 && GfGameFlag::getLocal(1, offset) != 0) {
      clearMissionForLesson += 1;
    }
  }

  return clearMissionForLesson;
}

} // namespace gf
