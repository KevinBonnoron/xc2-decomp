#include "gf/data/gf_data_nanakoori.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_item_id.h"
#include "types.h"

namespace gf {

enum {
  FLAG_NANAKOORI_UNKNOWN_2127 = 0x84f, // Inferred role: flag nanakoori vocal level; original name unknown.
  FLAG_NANAKOORI_UNKNOWN_2128 = 0x850, // Inferred role: flag nanakoori visual level; original name unknown.
  FLAG_NANAKOORI_UNKNOWN_2129 = 0x851, // Inferred role: flag nanakoori soul level; original name unknown.
  FLAG_NANAKOORI_UNKNOWN_1550 = 0x60e, // Inferred role: flag nanakoori fan; original name unknown.
};

enum {
  MISSION_UNKNOWN_178 = 0xb2, // Inferred role: mission vocal lesson 1; original name unknown.
  MISSION_UNKNOWN_179 = 0xb3, // Inferred role: mission vocal lesson 2; original name unknown.
  MISSION_UNKNOWN_180 = 0xb4, // Inferred role: mission vocal lesson 3; original name unknown.
  MISSION_UNKNOWN_181 = 0xb5, // Inferred role: mission vocal lesson 4; original name unknown.
  MISSION_UNKNOWN_182 = 0xb6, // Inferred role: mission vocal lesson 5; original name unknown.
  MISSION_UNKNOWN_183 = 0xb7, // Inferred role: mission looks lesson 1; original name unknown.
  MISSION_UNKNOWN_184 = 0xb8, // Inferred role: mission looks lesson 2; original name unknown.
  MISSION_UNKNOWN_185 = 0xb9, // Inferred role: mission looks lesson 3; original name unknown.
  MISSION_UNKNOWN_186 = 0xba, // Inferred role: mission looks lesson 4; original name unknown.
  MISSION_UNKNOWN_187 = 0xbb, // Inferred role: mission looks lesson 5; original name unknown.
  MISSION_UNKNOWN_188 = 0xbc, // Inferred role: mission soul lesson 1; original name unknown.
  MISSION_UNKNOWN_189 = 0xbd, // Inferred role: mission soul lesson 2; original name unknown.
  MISSION_UNKNOWN_190 = 0xbe, // Inferred role: mission soul lesson 3; original name unknown.
  MISSION_UNKNOWN_191 = 0xbf, // Inferred role: mission soul lesson 4; original name unknown.
  MISSION_UNKNOWN_192 = 0xc0, // Inferred role: mission soul lesson 5; original name unknown.
  MISSION_UNKNOWN_193 = 0xc1, // Inferred role: mission sparkly costumes; original name unknown.
  MISSION_UNKNOWN_194 = 0xc2, // Inferred role: mission song selection; original name unknown.
  MISSION_UNKNOWN_195 = 0xc3, // Inferred role: mission luxury stage; original name unknown.
  MISSION_UNKNOWN_196 = 0xc4, // Inferred role: mission rehearsal; original name unknown.
  MISSION_UNKNOWN_197 = 0xc5, // Inferred role: mission holy choir; original name unknown.
  MISSION_UNKNOWN_198 = 0xc6, // Inferred role: mission fashion show; original name unknown.
  MISSION_UNKNOWN_199 = 0xc7, // Inferred role: mission meet and greet; original name unknown.
  MISSION_UNKNOWN_200 = 0xc8, // Inferred role: mission concert in argentum; original name unknown.
  MISSION_UNKNOWN_201 = 0xc9, // Inferred role: mission concert in uraya; original name unknown.
  MISSION_UNKNOWN_202 = 0xca, // Inferred role: mission concert in mor ardain; original name unknown.
  MISSION_UNKNOWN_203 = 0xcb, // Inferred role: mission nopon pop stars; original name unknown.
  MISSION_UNKNOWN_204 = 0xcc, // Inferred role: mission local pop star; original name unknown.
  MISSION_UNKNOWN_205 = 0xcd, // Inferred role: mission stage star; original name unknown.
  MISSION_UNKNOWN_206 = 0xce, // Inferred role: mission summer concert; original name unknown.
  MISSION_UNKNOWN_207 = 0xcf, // Inferred role: mission benefit concert; original name unknown.
  MISSION_UNKNOWN_208 = 0xd0, // Inferred role: mission invitation from queen; original name unknown.
  MISSION_UNKNOWN_209 = 0xd1, // Inferred role: mission invitation from emperor; original name unknown.
  MISSION_UNKNOWN_210 = 0xd2, // Inferred role: mission special concert; original name unknown.
};

bool GfDataNanakoori::setVocalLevel(u32 vocalLevel) {
  u32 oldVocalLevel = GfGameFlag::getLocal(8, FLAG_NANAKOORI_UNKNOWN_2127);
  GfGameFlag::setLocal(8, FLAG_NANAKOORI_UNKNOWN_2127, vocalLevel);
  return oldVocalLevel != vocalLevel;
}

u32 GfDataNanakoori::getVocalLevel() { return GfGameFlag::getLocal(8, FLAG_NANAKOORI_UNKNOWN_2127); }

bool GfDataNanakoori::setVisualLevel(u32 visualLevel) {
  u32 oldVisualLevel = GfGameFlag::getLocal(8, FLAG_NANAKOORI_UNKNOWN_2128);
  GfGameFlag::setLocal(8, FLAG_NANAKOORI_UNKNOWN_2128, visualLevel);
  return oldVisualLevel != visualLevel;
}

u32 GfDataNanakoori::getVisualLevel() { return GfGameFlag::getLocal(8, FLAG_NANAKOORI_UNKNOWN_2128); }

bool GfDataNanakoori::setSoulLevel(u32 soulLevel) {
  u32 oldSoulLevel = GfGameFlag::getLocal(8, FLAG_NANAKOORI_UNKNOWN_2129);
  GfGameFlag::setLocal(8, FLAG_NANAKOORI_UNKNOWN_2129, soulLevel);
  return oldSoulLevel != soulLevel;
}

u32 GfDataNanakoori::getSoulLevel() { return GfGameFlag::getLocal(8, FLAG_NANAKOORI_UNKNOWN_2129); }

bool GfDataNanakoori::setFan(u32 fan) {
  u32 oldFan = GfGameFlag::getLocal(0x10, FLAG_NANAKOORI_UNKNOWN_1550);
  GfGameFlag::setLocal(0x10, FLAG_NANAKOORI_UNKNOWN_1550, fan);
  return oldFan != fan;
}

u32 GfDataNanakoori::getFan() { return GfGameFlag::getLocal(0x10, FLAG_NANAKOORI_UNKNOWN_1550); }

u32 GfDataNanakoori::getNanakooriMissionClearFlg1Offset(u32 mission) {
  return mission == MISSION_UNKNOWN_197   ? 1
         : mission == MISSION_UNKNOWN_198 ? 2
         : mission == MISSION_UNKNOWN_199 ? 3
         : mission == MISSION_UNKNOWN_208 ? 4
         : mission == MISSION_UNKNOWN_209 ? 5
         : mission == MISSION_UNKNOWN_210 ? 6
         : mission == MISSION_UNKNOWN_193 ? 0x15
         : mission == MISSION_UNKNOWN_194 ? 0x16
         : mission == MISSION_UNKNOWN_195 ? 0x17
         : mission == MISSION_UNKNOWN_196 ? 0x18
         : mission == MISSION_UNKNOWN_203 ? 0x19
         : mission == MISSION_UNKNOWN_204 ? 0x1a
         : mission == MISSION_UNKNOWN_205 ? 0x1b
         : mission == MISSION_UNKNOWN_206 ? 0x1c
         : mission == MISSION_UNKNOWN_207 ? 0x1d
         : mission == MISSION_UNKNOWN_178 ? 0x29
         : mission == MISSION_UNKNOWN_179 ? 0x2a
         : mission == MISSION_UNKNOWN_180 ? 0x2b
         : mission == MISSION_UNKNOWN_181 ? 0x2c
         : mission == MISSION_UNKNOWN_182 ? 0x2d
         : mission == MISSION_UNKNOWN_183 ? 0x2e
         : mission == MISSION_UNKNOWN_184 ? 0x2f
         : mission == MISSION_UNKNOWN_185 ? 0x30
         : mission == MISSION_UNKNOWN_186 ? 0x31
         : mission == MISSION_UNKNOWN_187 ? 0x32
         : mission == MISSION_UNKNOWN_188 ? 0x33
         : mission == MISSION_UNKNOWN_189 ? 0x34
         : mission == MISSION_UNKNOWN_190 ? 0x35
         : mission == MISSION_UNKNOWN_191 ? 0x36
         : mission == MISSION_UNKNOWN_192 ? 0x37
                                          : 0;
}

u32 GfDataNanakoori::getLevelForNanakoori(u32 stampCount) {
  return stampCount == 0 ? 1 : stampCount < 3 ? 2 : stampCount < 9 ? 3 : stampCount < 0x11 ? 4 : stampCount < 0x1e ? 5 : stampCount < 0x32 ? 6 : stampCount < 0x4b ? 7 : stampCount < 0x63 ? 8 : 9;
}

u64 GfDataNanakoori::getItemForVocalLevelUp() { return ITEM_UNKNOWN_25175; }

u64 GfDataNanakoori::getItemForVisualLevelUp() { return ITEM_UNKNOWN_25176; }

u64 GfDataNanakoori::getItemForSoulLevelUp() { return ITEM_UNKNOWN_25177; }

u32 GfDataNanakoori::getClearMissionForSpecial() {
  u32 clearMissionForSpecial = 0;

  constexpr static u16 unknown006[] = {
      // Inferred role: missions; original name unknown.
      MISSION_UNKNOWN_197,
      MISSION_UNKNOWN_198,
      MISSION_UNKNOWN_199,
      MISSION_UNKNOWN_208,
      MISSION_UNKNOWN_209,
      MISSION_UNKNOWN_210,
  };

  for (u32 i = 0; i < sizeof(unknown006) / sizeof(unknown006[0]); i++) {
    u32 offset = getNanakooriMissionClearFlg1Offset(unknown006[i]);
    if (offset != 0 && GfGameFlag::getLocal(1, offset) != 0) {
      clearMissionForSpecial += 1;
    }
  }

  return clearMissionForSpecial;
}

u32 GfDataNanakoori::getClearMissionForLive() {
  u32 clearMissionForLive = 0;

  constexpr static u16 unknown007[] = {
      // Inferred role: missions; original name unknown.
      MISSION_UNKNOWN_193,
      MISSION_UNKNOWN_194,
      MISSION_UNKNOWN_195,
      MISSION_UNKNOWN_196,
      MISSION_UNKNOWN_203,
      MISSION_UNKNOWN_204,
      MISSION_UNKNOWN_205,
      MISSION_UNKNOWN_206,
      MISSION_UNKNOWN_207,
  };

  for (u32 i = 0; i < sizeof(unknown007) / sizeof(unknown007[0]); i++) {
    u32 offset = getNanakooriMissionClearFlg1Offset(unknown007[i]);
    if (offset != 0 && GfGameFlag::getLocal(1, offset) != 0) {
      clearMissionForLive += 1;
    }
  }

  return clearMissionForLive;
}

u32 GfDataNanakoori::getClearMissionForLesson() {
  u32 clearMissionForLesson = 0;

  constexpr static u16 unknown008[] = {
      // Inferred role: missions; original name unknown.
      MISSION_UNKNOWN_178,
      MISSION_UNKNOWN_179,
      MISSION_UNKNOWN_180,
      MISSION_UNKNOWN_181,
      MISSION_UNKNOWN_182,
      MISSION_UNKNOWN_183,
      MISSION_UNKNOWN_184,
      MISSION_UNKNOWN_185,
      MISSION_UNKNOWN_186,
      MISSION_UNKNOWN_187,
      MISSION_UNKNOWN_188,
      MISSION_UNKNOWN_189,
      MISSION_UNKNOWN_190,
      MISSION_UNKNOWN_191,
      MISSION_UNKNOWN_192,
  };

  for (u32 i = 0; i < sizeof(unknown008) / sizeof(unknown008[0]); i++) {
    u32 offset = getNanakooriMissionClearFlg1Offset(unknown008[i]);
    if (offset != 0 && GfGameFlag::getLocal(1, offset) != 0) {
      clearMissionForLesson += 1;
    }
  }

  return clearMissionForLesson;
}

} // namespace gf
