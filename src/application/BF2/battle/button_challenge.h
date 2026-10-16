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
        : id(0), challenge(0), type(TYPE_NONE), isWeaponAttack(0), attackType(0), target(0), characterId(CHARACTER_COUNT), priority(0) {}

    u32 id : 14;
    u32 challenge : 14;
    u32 type : 4;
    u32 : 0;
    u32 isWeaponAttack : 16;
    u32 attackType : 16;
    int target;
    u8 characterId;
    u8 priority;
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

  gf::GfMenuCallContext *context;
  gf::GfMenuCallContext *closingContext;
  BUTTON_CHALLENGE_PARAM param;
  int nextId;
  u32 currentId;
  u32 slow;
  u8 successCount;
  bool isOpen;
  bool isEnd;
  bool isEnemySuccess;
};

static_assert(offsetof(ButtonChallenge, context) == 0x08, "");
static_assert(offsetof(ButtonChallenge, closingContext) == 0x10, "");
static_assert(offsetof(ButtonChallenge, param) == 0x18, "");
static_assert(offsetof(ButtonChallenge, nextId) == 0x28, "");
static_assert(offsetof(ButtonChallenge, currentId) == 0x2c, "");
static_assert(offsetof(ButtonChallenge, slow) == 0x30, "");
static_assert(offsetof(ButtonChallenge, successCount) == 0x34, "");
static_assert(offsetof(ButtonChallenge, isOpen) == 0x35, "");
static_assert(offsetof(ButtonChallenge, isEnd) == 0x36, "");
static_assert(offsetof(ButtonChallenge, isEnemySuccess) == 0x37, "");
static_assert(sizeof(ButtonChallenge) == 0x38, "");

} // namespace btl
