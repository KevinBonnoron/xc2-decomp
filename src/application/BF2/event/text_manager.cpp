#include "event/text_manager.h"

#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"

namespace event {

TextManager::TextManager() : flags(0), dispFlags(0), mBdat(nullptr), mTalker(nullptr) {}

void TextManager::init() {
  flags = 0;
  mLife = 0.0f;
  mDelay = 0.0f;
  mDelayBack = 0.0f;
  mLifeCount = 0.0f;
  mDelayCount = 0.0f;
  mDelayBackCount = 0.0f;
  mCaptionType = 0;
  mStartFrame = 0.0f;
  mBdat = nullptr;
  mTextId = 0;
  mLabel = "";
  mText = "";
  mTalker = nullptr;
  mDefaultTalker = nullptr;
  mReplaceName = "";
}

void TextManager::render() {
  if (!isDisp()) {
    return;
  }
  mCaption.render();
  mWindow.render();
  if ((flags & FLAG_PLAY) == 0) {
    return;
  }
  s32 height = ml::DevGraph::getRootHeight();
  fw::debug::drawSquare2D(mm::Rect<s32>(250, height - 230, 530, 25), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(250, height - 230, 530, 25), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  s32 y = height - 225;
  if (mDelayCount >= 0.0f) {
    fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 1.0f, 1.0f));
  } else {
    fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 0.5f, 1.0f));
  }
  fw::debug::drawFont(260, y, "delay(%.1f / %.1f)", mDelayCount > 0.0f ? mDelayCount : 0.0f, mDelay > 0.0f ? mDelay : 0.0f);
  if (mDelayCount >= 0.0f || mLifeCount < -mDelayBackCount) {
    fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 0.5f, 1.0f));
  } else {
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  }
  fw::debug::drawFont(410, y, "life(%.1f / %.1f)", mLifeCount > 0.0f ? mLifeCount : 0.0f, mLife > 0.0f ? mLife : 0.0f);
  if (mDelayBackCount < 0.0f && mLifeCount < -mDelayBackCount) {
    fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 1.0f, 1.0f));
  } else if (mDelayBackCount > 0.0f && mLifeCount < 0.0f) {
    fw::debug::drawFontColor(mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
  } else {
    fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 0.5f, 1.0f));
  }
  fw::debug::drawFont(560, y, "delayBack(%.1f)", mDelayBackCount);
}

void TextManager::setDefaultTalkerMode(bool isDefault, CharaObj *chara) { mDefaultTalker = isDefault ? chara : nullptr; }

void TextManager::setAutoTalkMode(bool isAutoTalkMode) { setFlag(FLAG_AUTO_TALK_MODE, isAutoTalkMode); }

void TextManager::setAutoVoiceMode(bool isAutoVoiceMode) { setFlag(FLAG_AUTO_VOICE_MODE, isAutoVoiceMode); }

void TextManager::setBladeNameMode(bool isBladeNameMode) { setFlag(FLAG_BLADE_NAME_MODE, isBladeNameMode); }

void TextManager::setReplaceMode(bool isReplaceMode, const char *name) {
  if (isReplaceMode) {
    flags |= FLAG_REPLACE_MODE;
    mReplaceName = name;
  } else {
    flags &= ~FLAG_REPLACE_MODE;
    mReplaceName = "";
  }
}

void TextManager::setCutChangeFrame() { flags |= FLAG_CUT_CHANGE_FRAME; }

void TextManager::setDisp(bool isDisp) { setDispFlag(DISP_FLAG_DISP, isDisp); }

bool TextManager::isDisp() const { return (dispFlags & DISP_FLAG_DISP) != 0; }

void TextManager::setUseSkip(bool isUse) { setDispFlag(DISP_FLAG_USE_SKIP, isUse); }

void TextManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    init();
    break;
  case MSG_TYPE_CLEAR:
    clear();
    break;
  case MSG_TYPE_UPDATE:
    update();
    break;
  case MSG_TYPE_RENDER:
    render();
    break;
  case MSG_TYPE_TAIL:
    flags &= ~FLAG_CUT_CHANGE_FRAME;
    break;
  default:
    break;
  }
}

} // namespace event
