#include "event/text_manager.h"

#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"

namespace event {

bool TextManager::isReplying() const {
  if ((flags & FLAG_PLAY) != 0) {
    if ((flags & FLAG_WRITE) == 0) {
      return true;
    }
    if (window.isWriting()) {
      return true;
    }
  }
  return false;
}

bool TextManager::isCutChangeFrame() const { return (flags & FLAG_CUT_CHANGE_FRAME) != 0; }

TextManager::TextManager() : flags(0), dispFlags(0), bdat(nullptr), talker(nullptr) {}

void TextManager::clear() {
  caption.clear();
  window.clear();
  init();
}

void TextManager::init() {
  flags = 0;
  life = 0.0f;
  delay = 0.0f;
  delayBack = 0.0f;
  lifeCount = 0.0f;
  delayCount = 0.0f;
  delayBackCount = 0.0f;
  captionType = 0;
  startFrame = 0.0f;
  bdat = nullptr;
  textId = 0;
  label = "";
  text = "";
  talker = nullptr;
  defaultTalker = nullptr;
  replaceName = "";
}

void TextManager::write(const char *text, u8 *bdat, u32 textId, const char *name, gf::GF_OBJ_HANDLE *handle) {
  if ((flags & FLAG_CAPTION) != 0) {
    caption.write(text, bdat, textId, captionType);
  } else {
    window.write(text, name, bdat, textId, handle);
  }
}

void TextManager::stop() {
  if ((flags & FLAG_CAPTION) != 0) {
    caption.hide();
  } else {
    window.hide();
  }
  flags &= ~(FLAG_LOCK_FRAME | FLAG_PLAY | FLAG_WRITE | FLAG_ERASE);
}

void TextManager::render() {
  if (!isDisp()) {
    return;
  }
  caption.render();
  window.render();
  if ((flags & FLAG_PLAY) == 0) {
    return;
  }
  s32 height = ml::DevGraph::getRootHeight();
  fw::debug::drawSquare2D(mm::Rect<s32>(250, height - 230, 530, 25), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(250, height - 230, 530, 25), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  s32 y = height - 225;
  if (delayCount >= 0.0f) {
    fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 1.0f, 1.0f));
  } else {
    fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 0.5f, 1.0f));
  }
  fw::debug::drawFont(260, y, "delay(%.1f / %.1f)", delayCount > 0.0f ? delayCount : 0.0f, delay > 0.0f ? delay : 0.0f);
  if (delayCount >= 0.0f || lifeCount < -delayBackCount) {
    fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 0.5f, 1.0f));
  } else {
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  }
  fw::debug::drawFont(410, y, "life(%.1f / %.1f)", lifeCount > 0.0f ? lifeCount : 0.0f, life > 0.0f ? life : 0.0f);
  if (delayBackCount < 0.0f && lifeCount < -delayBackCount) {
    fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 1.0f, 1.0f));
  } else if (delayBackCount > 0.0f && lifeCount < 0.0f) {
    fw::debug::drawFontColor(mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
  } else {
    fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 0.5f, 1.0f));
  }
  fw::debug::drawFont(560, y, "delayBack(%.1f)", delayBackCount);
}

void TextManager::setup(bool isCaption) {
  caption.hide();
  window.hide();
  setFlag(FLAG_CAPTION, isCaption);
  update();
}

void TextManager::setDefaultTalkerMode(bool isDefault, CharaObj *chara) { defaultTalker = isDefault ? chara : nullptr; }

void TextManager::setAutoTalkMode(bool isAutoTalkMode) { setFlag(FLAG_AUTO_TALK_MODE, isAutoTalkMode); }

void TextManager::setAutoVoiceMode(bool isAutoVoiceMode) { setFlag(FLAG_AUTO_VOICE_MODE, isAutoVoiceMode); }

void TextManager::setBladeNameMode(bool isBladeNameMode) { setFlag(FLAG_BLADE_NAME_MODE, isBladeNameMode); }

void TextManager::setReplaceMode(bool isReplaceMode, const char *name) {
  if (isReplaceMode) {
    flags |= FLAG_REPLACE_MODE;
    replaceName = name;
  } else {
    flags &= ~FLAG_REPLACE_MODE;
    replaceName = "";
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
