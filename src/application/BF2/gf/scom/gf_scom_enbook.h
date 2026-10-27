#pragma once
#include "gf/request/gf_scom.h"
#include "types.h"

namespace gf {

struct GF_SCOM_HANDLE;
struct GF_OBJ_HANDLE;

class SCOM_ENBOOK_IN_BATTLE : public SCOM {
public:
  SCOM_ENBOOK_IN_BATTLE(GF_SCOM_HANDLE *handle, u32 enemy) : SCOM(handle, SCOM_TYPE_UNKNOWN_69, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(enemy) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *handle);

  u32 unknown1c; // Inferred role: enemy bdat id; original member name unknown.
};

class SCOM_ENBOOK_BOSS_TIME : public SCOM {
public:
  SCOM_ENBOOK_BOSS_TIME(GF_SCOM_HANDLE *handle, u32 enemy, u32 time) : SCOM(handle, SCOM_TYPE_UNKNOWN_71, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(enemy), unknown20(time) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *handle, u32 time);

  u32 unknown1c; // Inferred role: enemy bdat id; original member name unknown.
  u32 unknown20; // Inferred role: clear time; original member name unknown.
};

class SCOM_ENBOOK_DEFEAT_ENEMY : public SCOM {
public:
  SCOM_ENBOOK_DEFEAT_ENEMY(GF_SCOM_HANDLE *handle, u32 enemy) : SCOM(handle, SCOM_TYPE_UNKNOWN_72, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(enemy) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *handle);

  u32 unknown1c; // Inferred role: enemy bdat id; original member name unknown.
};

class SCOM_ENBOOK_DEAD_PLAYER : public SCOM {
public:
  SCOM_ENBOOK_DEAD_PLAYER(GF_SCOM_HANDLE *handle, u32 enemy) : SCOM(handle, SCOM_TYPE_UNKNOWN_73, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(enemy) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(GF_OBJ_HANDLE *handle);

  u32 unknown1c; // Inferred role: enemy bdat id; original member name unknown.
};

static_assert(sizeof(SCOM_ENBOOK_IN_BATTLE) == 0x20, "");
static_assert(sizeof(SCOM_ENBOOK_BOSS_TIME) == 0x28, "");
static_assert(sizeof(SCOM_ENBOOK_DEFEAT_ENEMY) == 0x20, "");
static_assert(sizeof(SCOM_ENBOOK_DEAD_PLAYER) == 0x20, "");

} // namespace gf
