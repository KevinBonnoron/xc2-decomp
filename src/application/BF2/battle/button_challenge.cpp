#include "battle/button_challenge.h"

#include "battle/battle_global.h"
#include "gf/menu/gf_menu_call_context.h"
#include "gf/menu/object/gf_menu_obj_button_challenge2.h"

namespace btl {

constexpr int CHALLENGE_SEQUENCE = 223;

static void ReleaseContext(gf::GfMenuCallContext *&context) {
  if (context != nullptr) {
    context->release();
    context = nullptr;
  }
}

ButtonChallenge::ButtonChallenge()
    : context(nullptr), closingContext(nullptr), nextId(1), currentId(0), slow(0), successCount(0), isOpen(false), isEnd(true),
      isEnemySuccess(false) {}

ButtonChallenge::~ButtonChallenge() {
  ReleaseContext(context);
  ReleaseContext(closingContext);
}

void ButtonChallenge::OpenButtonChallenge(int id, int challenge) {
  if (context == nullptr) {
    context = gf::GfMenuCallContext::create();
  } else {
    context->reset();
  }

  if (id == CHALLENGE_SEQUENCE) {
    gf::GfMenuObjButtonChallenge2::openSequence(context, challenge, false, true);
  } else {
    gf::GfMenuObjButtonChallenge2::open(context, challenge, false, true);
  }
  isOpen = true;
  isEnd = false;
}

int ButtonChallenge::Start(const BUTTON_CHALLENGE_PARAM &param) {
  if (isOpen) {
    if (param.priority < this->param.priority) {
      return 0;
    }
    if (!isEnd && this->param.type == TYPE_DRIVER) {
      ResultProc(3);
    }
    CancelProc();
  }

  this->param = param;
  OpenButtonChallenge(param.id, param.challenge);
  FinalizeExProc();
  if (param.type == TYPE_ENEMY) {
    BattleGlobal::get()->SetPause(BattleGlobal::PAUSE_BUTTON_CHALLENGE, true);
  }
  this->param = param;
  int id = nextId;
  nextId = id == -1 ? 1 : id + 1;
  currentId = id;
  return id;
}

void ButtonChallenge::CancelProc() {
  gf::GfMenuCallContext *closing = context;
  if (closing != nullptr) {
    ReleaseContext(closingContext);
    context = nullptr;
    closingContext = closing;
    gf::GfMenuObjButtonChallenge2::close(closing);
  }
  param = BUTTON_CHALLENGE_PARAM();
  currentId = 0;
  isOpen = false;
  isEnd = true;
  isEnemySuccess = false;
}

void ButtonChallenge::FinalizeExProc() {
  DeleteSlow();
  BattleGlobal::get()->SetPause(BattleGlobal::PAUSE_BUTTON_CHALLENGE, false);
}

void ButtonChallenge::Cancel(u32 id) {
  if (currentId == id && !isEnd) {
    CancelProc();
  }
}

void ButtonChallenge::ProgressSeparately() {
  if (context != nullptr) {
    gf::GfMenuObjButtonChallenge2::resume(context);
  }
}

bool ButtonChallenge::IsProc() const { return isOpen || param.type != TYPE_NONE; }

void ButtonChallenge::DeleteSlow() {
  if (slow != 0) {
    BattleGlobal::get()->DeleteSlow(slow);
    slow = 0;
  }
}

bool ButtonChallenge::IsEnemyChallengeSuccess() {
  bool isSuccess = isEnemySuccess;
  isEnemySuccess = false;
  return isSuccess;
}

} // namespace btl
