#pragma once
#include "battle/character/character_manager_battle.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {
class GfMenuCallContext;
}

namespace btl {

class ButtonChallenge {
public:
  enum TYPE {
    TYPE_DRIVER,
    TYPE_BLADE,
    TYPE_ENEMY,
    TYPE_NONE,
  };

  struct BUTTON_CHALLENGE_PARAM {
    BUTTON_CHALLENGE_PARAM()
        : unknown00_0(0), unknown01_6(0), unknown03_4(TYPE_NONE), unknown04_0(0), unknown06_0(0), unknown08(0), unknown0c(CHARACTER_COUNT),
          unknown0d(0) {}

    u32 unknown00_0 : 14; // Inferred role: id; original member name unknown.
    u32 unknown01_6 : 14; // Inferred role: challenge; original member name unknown.
    u32 unknown03_4 : 4;  // Inferred role: type; original member name unknown.
    u32 : 0;
    u32 unknown04_0 : 16; // Inferred role: weapon attack flag; original member name unknown.
    u32 unknown06_0 : 16; // Inferred role: attack type; original member name unknown.
    int unknown08;        // Inferred role: target; original member name unknown.
    u8 unknown0c;         // Inferred role: character id; original member name unknown.
    u8 unknown0d;         // Inferred role: priority; original member name unknown.
  };

  ButtonChallenge();
  virtual ~ButtonChallenge();
  void OpenButtonChallenge(int id, int challenge);
  int Start(const BUTTON_CHALLENGE_PARAM &param);
  void ResultProc(int result);
  void CancelProc();
  void FinalizeExProc();
  void Cancel(u32 id);
  void ProgressSeparately();
  bool IsProc() const;
  void Update(const fw::UpdateInfo &updateInfo);
  void DeleteSlow();
  bool IsEnemyChallengeSuccess();

  gf::GfMenuCallContext *unknown08; // Inferred role: menu call context; original member name unknown.
  gf::GfMenuCallContext *unknown10; // Inferred role: closing menu call context; original member name unknown.
  BUTTON_CHALLENGE_PARAM unknown18; // Inferred role: param; original member name unknown.
  int unknown28;                    // Inferred role: next id; original member name unknown.
  u32 unknown2c;                    // Inferred role: current id; original member name unknown.
  u32 unknown30;                    // Inferred role: slow id; original member name unknown.
  u8 unknown34;                     // Inferred role: success count; original member name unknown.
  bool unknown35;                   // Inferred role: open flag; original member name unknown.
  bool unknown36;                   // Inferred role: end flag; original member name unknown.
  bool unknown37;                   // Inferred role: enemy success flag; original member name unknown.
};

static_assert(offsetof(ButtonChallenge, unknown08) == 0x08, "");
static_assert(offsetof(ButtonChallenge, unknown10) == 0x10, "");
static_assert(offsetof(ButtonChallenge, unknown18) == 0x18, "");
static_assert(offsetof(ButtonChallenge, unknown28) == 0x28, "");
static_assert(offsetof(ButtonChallenge, unknown2c) == 0x2c, "");
static_assert(offsetof(ButtonChallenge, unknown30) == 0x30, "");
static_assert(offsetof(ButtonChallenge, unknown34) == 0x34, "");
static_assert(offsetof(ButtonChallenge, unknown35) == 0x35, "");
static_assert(offsetof(ButtonChallenge, unknown36) == 0x36, "");
static_assert(offsetof(ButtonChallenge, unknown37) == 0x37, "");
static_assert(sizeof(ButtonChallenge) == 0x38, "");

} // namespace btl
