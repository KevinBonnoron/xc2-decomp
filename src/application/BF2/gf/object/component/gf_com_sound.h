#pragma once
#include "gf/object/component/gf_component.h"
#include "types.h"

namespace mm {
struct Vec3;

namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

enum SoundVariable : int {
  SOUND_VARIABLE_UNKNOWN_0,
  SOUND_VARIABLE_UNKNOWN_1,
  SOUND_VARIABLE_UNKNOWN_2,
  SOUND_VARIABLE_UNKNOWN_3,
  SOUND_VARIABLE_UNKNOWN_4,
};

enum SoundVariableWall : int {
  SOUND_VARIABLE_WALL_UNKNOWN_0,
  SOUND_VARIABLE_WALL_UNKNOWN_1,
};

enum SoundVariableWaterDepth : int {
  SOUND_VARIABLE_WATER_DEPTH_UNKNOWN_0,
  SOUND_VARIABLE_WATER_DEPTH_UNKNOWN_1,
};

enum SoundVarMoveStatus : int {
  SOUND_VAR_MOVE_STATUS_UNKNOWN_0,
  SOUND_VAR_MOVE_STATUS_UNKNOWN_1,
};

const char *getSoundVariableName(SoundVariable variable);
const char *getMaterialVariableName(int variable);
const char *getWallVariableName(SoundVariableWall variable);
const char *getWaterDepthVariableName(SoundVariableWaterDepth variable);
const char *getMoveStatusVariableName(SoundVarMoveStatus variable);
int getMaterialVariable(const char *name);
const char *getAttributeVariableName(int variable);
int getAttrbiteVariable(const char *name);
int getWallVariable(const char *name);
int getWaterDepthVariable(const char *name);
int getMoveStatusVariable(const char *name);

// Declaration rebuilt from the game's symbols (gf::GfComSound::stopSe, playSe2D); the component slot comes from the access offset 0x88.
class GfComSound : public GfComponent {
public:
  static mm::mtl::RTTI m_rtti;
  static const u32 COMPONENT_INDEX = 10;

  void stopSe(const char *name);
  bool playSe(const char *name, f32 volume, const mm::Vec3 &offset, bool isFollow);
  void playSe2D(const char *name, f32 volume, bool, bool);
  int getAttributeVariable() const;
  void setAttributeVariable(int attribute);
};

} // namespace gf
