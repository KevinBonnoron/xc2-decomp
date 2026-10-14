#pragma once
#include "types.h"

namespace gf {

class GfDataNpc {
public:
  static const char *getName(u32 npc);
  static bool getName(u8 *&bdat, u32 &textId, u32 npc);
  static u8 *getNameBdatFp(int npc);
  static u32 getRscRelativeID(u32 npc);
  static u32 getRace(u32 npc);
  static u32 getGender(u32 npc);
  static const char *getModelName(u32 npc);
  static const char *getMotionName(u32 npc);
  static const char *getAddMotionName(u32 npc);
  static const char *getEffectName(u32 npc);
  static f32 getScale(u32 npc);
  static u32 getCollisionId(u32 npc);
  static u32 getOffsetID(u32 npc);
  static u8 *getRscBdatFp(int npc);
  static bool getExtraParts(u32 npc, u32 part);
  static bool isNeedResourceEvent(u32 npc);
  static u32 getFootStep(u32 npc);
  static u32 getFootStepEffect(u32 npc);
  static u32 getEyeRotControl(u32 npc);
};

} // namespace gf
