#include "gf/object/component/gf_com_sound.h"

#include <string.h>

namespace gf {

namespace {

const char *const unknown001[] = {"material", "attribute", "wall", "water_depth", "move_status"}; // Inferred role: names of SoundVariable; original name unknown.
const char *const unknown002[] = {"MAT_NONE",
                                  "MAT_WOOD",
                                  "MAT_GRASS",
                                  "MAT_SAND",
                                  "MAT_IRON",
                                  "MAT_SNOW",
                                  "MAT_SOIL",
                                  "MAT_WIRE_MESH",
                                  "MAT_GEL",
                                  "MAT_CARPET",
                                  "MAT_WATER",
                                  "MAT_CLOUD",
                                  "MAT_ICE"};                             // Inferred role: names of the material variable; original name unknown.
const char *const unknown003[] = {"WALL_NORMAL", "WALL_LADER"};           // Inferred role: names of SoundVariableWall; original name unknown.
const char *const unknown004[] = {"WATER_DEPTH_LOW", "WATER_DEPTH_HIGH"}; // Inferred role: names of SoundVariableWaterDepth; original name unknown.
const char *const unknown005[] = {"MOVE_NORMAL", "MOVE_RUN"};             // Inferred role: names of SoundVarMoveStatus; original name unknown.

struct unknown006 {
  s32 unknown00;
  const char *unknown08;
};

const unknown006 unknown007[] = {
    {0, "ATR_NONE"},
    {1, "ATR_FIRE"},
    {2, "ATR_AQUA"},
    {3, "ATR_WIND"},
    {4, "ATR_EARTH"},
    {5, "ATR_VOLT"},
    {6, "ATR_ICE"},
    {7, "ATR_LIGHT"},
    {8, "ATR_DARK"},
}; // Inferred role: attribute variable values and names; original name unknown.

} // namespace

const char *getSoundVariableName(SoundVariable variable) { return unknown001[variable]; }

const char *getMaterialVariableName(int variable) {
  if (variable < 13) {
    return unknown002[variable];
  }

  return "invalid";
}

const char *getWallVariableName(SoundVariableWall variable) {
  if (variable >= 0) {
    return unknown003[variable];
  }

  return "invalid";
}

const char *getWaterDepthVariableName(SoundVariableWaterDepth variable) {
  if (variable >= 0) {
    return unknown004[variable];
  }

  return "invalid";
}

const char *getMoveStatusVariableName(SoundVarMoveStatus variable) {
  if (variable >= 0) {
    return unknown005[variable];
  }

  return "invalid";
}

int getMaterialVariable(const char *name) {
  for (int i = 0; i < 13; i++) {
    if (strcmp(unknown002[i], name) == 0) {
      return i;
    }
  }

  return -1;
}

const char *getAttributeVariableName(int variable) {
  for (u32 i = 0; i < 9; i++) {
    if (variable == unknown007[i].unknown00) {
      return unknown007[i].unknown08;
    }
  }

  return "invalid";
}

int getAttrbiteVariable(const char *name) {
  for (u32 i = 0; i < 9; i++) {
    if (strcmp(unknown007[i].unknown08, name) == 0) {
      return unknown007[i].unknown00;
    }
  }

  return -1;
}

int getWallVariable(const char *name) {
  if (strcmp(unknown003[0], name) == 0) {
    return 0;
  }
  if (strcmp(unknown003[1], name) == 0) {
    return 1;
  }

  return -1;
}

int getWaterDepthVariable(const char *name) {
  if (strcmp(unknown004[0], name) == 0) {
    return 0;
  }
  if (strcmp(unknown004[1], name) == 0) {
    return 1;
  }

  return -1;
}

int getMoveStatusVariable(const char *name) {
  if (strcmp(unknown005[0], name) == 0) {
    return 0;
  }
  if (strcmp(unknown005[1], name) == 0) {
    return 1;
  }

  return -1;
}

} // namespace gf
