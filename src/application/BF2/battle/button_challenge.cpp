#include "battle/button_challenge.h"

#include "battle/battle_global.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_button_challenge2.h"

namespace btl {

constexpr int CHALLENGE_SEQUENCE = 223;

static void unknown001(gf::GfMenuCallContext *&context) { // Inferred role: releaseContext; original function name unknown.
  if (context != nullptr) {
    context->release();
    context = nullptr;
  }
}

ButtonChallenge::ButtonChallenge()
    : unknown08(nullptr), unknown10(nullptr), unknown28(1), unknown2c(0), unknown30(0), unknown34(0), unknown35(false), unknown36(true),
      unknown37(false) {}

ButtonChallenge::~ButtonChallenge() {
  unknown001(unknown08);
  unknown001(unknown10);
}

void ButtonChallenge::OpenButtonChallenge(int id, int challenge) {
  if (unknown08 == nullptr) {
    unknown08 = gf::GfMenuCallContext::create();
  } else {
    unknown08->reset();
  }

  if (id == CHALLENGE_SEQUENCE) {
    gf::GfMenuObjButtonChallenge2::openSequence(unknown08, challenge, false, true);
  } else {
    gf::GfMenuObjButtonChallenge2::open(unknown08, challenge, false, true);
  }
  unknown35 = true;
  unknown36 = false;
}

int ButtonChallenge::Start(const BUTTON_CHALLENGE_PARAM &param) {
  if (unknown35) {
    if (param.unknown0d < this->unknown18.unknown0d) {
      return 0;
    }
    if (!unknown36 && this->unknown18.unknown03_4 == TYPE_DRIVER) {
      ResultProc(3);
    }
    CancelProc();
  }

  this->unknown18 = param;
  OpenButtonChallenge(param.unknown00_0, param.unknown01_6);
  FinalizeExProc();
  if (param.unknown03_4 == TYPE_ENEMY) {
    BattleGlobal::get()->SetPause(BattleGlobal::PAUSE_BUTTON_CHALLENGE, true);
  }
  this->unknown18 = param;
  int id = unknown28;
  unknown28 = id == -1 ? 1 : id + 1;
  unknown2c = id;
  return id;
}

void ButtonChallenge::CancelProc() {
  gf::GfMenuCallContext *closing = unknown08;
  if (closing != nullptr) {
    unknown001(unknown10);
    unknown08 = nullptr;
    unknown10 = closing;
    gf::GfMenuObjButtonChallenge2::close(closing);
  }
  unknown18 = BUTTON_CHALLENGE_PARAM();
  unknown2c = 0;
  unknown35 = false;
  unknown36 = true;
  unknown37 = false;
}

void ButtonChallenge::FinalizeExProc() {
  DeleteSlow();
  BattleGlobal::get()->SetPause(BattleGlobal::PAUSE_BUTTON_CHALLENGE, false);
}

void ButtonChallenge::Cancel(u32 id) {
  if (unknown2c == id && !unknown36) {
    CancelProc();
  }
}

void ButtonChallenge::ProgressSeparately() {
  if (unknown08 != nullptr) {
    gf::GfMenuObjButtonChallenge2::resume(unknown08);
  }
}

bool ButtonChallenge::IsProc() const { return unknown35 || unknown18.unknown03_4 != TYPE_NONE; }

void ButtonChallenge::DeleteSlow() {
  if (unknown30 != 0) {
    BattleGlobal::get()->DeleteSlow(unknown30);
    unknown30 = 0;
  }
}

bool ButtonChallenge::IsEnemyChallengeSuccess() {
  bool isSuccess = unknown37;
  unknown37 = false;
  return isSuccess;
}

} // namespace btl
