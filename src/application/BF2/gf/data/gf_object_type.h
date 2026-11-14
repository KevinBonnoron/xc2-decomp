#pragma once

namespace gf {

// The enumerators are the entries of the game's GfObj::getTypeName table, in value order, each prefixed with OBJECT_TYPE_: "NONE", "MAP", "MAP_LOD", "PC", "BLADE", "ENEMY", "NPC", "MOB", "GIMMICK",
// "FIELD_OBJ", "PC_WEAPON", "EVENT_OBJ", "EN_WEAPON", "OPTION", "EXTRA", "UI_OBJ".
enum {
  OBJECT_TYPE_NONE = 0,
  OBJECT_TYPE_MAP = 1,
  OBJECT_TYPE_MAP_LOD = 2,
  OBJECT_TYPE_PC = 3,
  OBJECT_TYPE_BLADE = 4,
  OBJECT_TYPE_ENEMY = 5,
  OBJECT_TYPE_NPC = 6,
  OBJECT_TYPE_MOB = 7,
  OBJECT_TYPE_GIMMICK = 8,
  OBJECT_TYPE_FIELD_OBJ = 9,
  OBJECT_TYPE_PC_WEAPON = 10,
  OBJECT_TYPE_EVENT_OBJ = 11,
  OBJECT_TYPE_EN_WEAPON = 12,
  OBJECT_TYPE_OPTION = 13,
  OBJECT_TYPE_EXTRA = 14,
  OBJECT_TYPE_UI_OBJ = 15,
};

} // namespace gf
