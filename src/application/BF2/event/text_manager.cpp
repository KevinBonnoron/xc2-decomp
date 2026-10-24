#include "event/text_manager.h"

#include "bdat.h"
#include "event/chara_obj.h"
#include "event/debug_manager.h"
#include "event/frame_manager.h"
#include "event/skip_manager.h"
#include "fw/fw_bdat_manager.h"
#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/singleton.h"

namespace event {

void TextManager::reply(const char *label, int textId, CharaObj *chara) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (mm::mtl::Singleton<DebugManager>::getPtr()->isFailureSkip() || (unknown10 & FLAG_CAPTION) != 0) {
    return;
  }
  unknown10 = (unknown10 & ~(FLAG_PLAY | FLAG_WRITE | FLAG_ERASE)) | FLAG_PLAY;
  unknown378 = fw::BdatManager::getFp(label);
  this->unknown380 = textId;
  this->unknown384 = "";
  unknown3c8 = Bdat::getMSText(unknown378, textId);
  unknown35c = 0.0f;
  unknown360 = 0.0f;
  unknown358 = 1.0f;
  unknown364 = 1.0f;
  unknown368 = 0.0f;
  unknown370 = 0;
  unknown374 = mm::mtl::Singleton<FrameManager>::getPtr()->getFrame() + 1.0f;
  unknown5d0 = chara;
  if (chara == nullptr) {
    return;
  }
  if ((unknown10 & FLAG_AUTO_TALK_MODE) != 0 && chara->getActionLastFrame() <= 0.0f) {
    chara->playAutoAction(-1.0f);
  }
  unknown5d0->playAutoTalk(-1.0f);
  unknown5d0->playTalk(false, -1.0f, true, true, -1.0f, -1.0f, -1.0f, -1.0f);
}

bool TextManager::isReplying() const {
  if ((unknown10 & FLAG_PLAY) != 0) {
    if ((unknown10 & FLAG_WRITE) == 0) {
      return true;
    }
    if (unknown128.isWriting()) {
      return true;
    }
  }
  return false;
}

void TextManager::replyEnd(CharaObj *chara) {
  if ((unknown10 & FLAG_AUTO_TALK_MODE) != 0) {
    chara->playAutoAction(1.0f);
  }
  chara->playAutoTalk(1.0f);
  chara->playTalk(false, 1.0f, true, true, -1.0f, -1.0f, -1.0f, -1.0f);
}

bool TextManager::isCutChangeFrame() const { return (unknown10 & FLAG_CUT_CHANGE_FRAME) != 0; }

TextManager::TextManager() : unknown10(0), unknown14(0), unknown378(nullptr), unknown5d0(nullptr) {}

void TextManager::clear() {
  unknown18.clear();
  unknown128.clear();
  init();
}

void TextManager::init() {
  unknown10 = 0;
  unknown358 = 0.0f;
  unknown35c = 0.0f;
  unknown360 = 0.0f;
  unknown364 = 0.0f;
  unknown368 = 0.0f;
  unknown36c = 0.0f;
  unknown370 = 0;
  unknown374 = 0.0f;
  unknown378 = nullptr;
  unknown380 = 0;
  unknown384 = "";
  unknown3c8 = "";
  unknown5d0 = nullptr;
  unknown5d8 = nullptr;
  unknown5e0 = "";
}

void TextManager::write(const char *text, u8 *bdat, u32 textId, const char *name, gf::GF_OBJ_HANDLE *handle) {
  if ((unknown10 & FLAG_CAPTION) != 0) {
    unknown18.write(text, bdat, textId, unknown370);
  } else {
    unknown128.write(text, name, bdat, textId, handle);
  }
}

void TextManager::stop() {
  if ((unknown10 & FLAG_CAPTION) != 0) {
    unknown18.hide();
  } else {
    unknown128.hide();
  }
  unknown10 &= ~(FLAG_LOCK_FRAME | FLAG_PLAY | FLAG_WRITE | FLAG_ERASE);
}

void TextManager::render() {
  if (!isDisp()) {
    return;
  }
  unknown18.render();
  unknown128.render();
  if ((unknown10 & FLAG_PLAY) == 0) {
    return;
  }
  s32 height = ml::DevGraph::getRootHeight();
  fw::debug::drawSquare2D(mm::Rect<s32>(250, height - 230, 530, 25), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(250, height - 230, 530, 25), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  s32 y = height - 225;
  if (unknown368 >= 0.0f) {
    fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 1.0f, 1.0f));
  } else {
    fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 0.5f, 1.0f));
  }
  fw::debug::drawFont(260, y, "delay(%.1f / %.1f)", unknown368 > 0.0f ? unknown368 : 0.0f, unknown35c > 0.0f ? unknown35c : 0.0f);
  if (unknown368 >= 0.0f || unknown364 < -unknown36c) {
    fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 0.5f, 1.0f));
  } else {
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  }
  fw::debug::drawFont(410, y, "life(%.1f / %.1f)", unknown364 > 0.0f ? unknown364 : 0.0f, unknown358 > 0.0f ? unknown358 : 0.0f);
  if (unknown36c < 0.0f && unknown364 < -unknown36c) {
    fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 1.0f, 1.0f));
  } else if (unknown36c > 0.0f && unknown364 < 0.0f) {
    fw::debug::drawFontColor(mm::Col4(1.0f, 0.5f, 0.5f, 1.0f));
  } else {
    fw::debug::drawFontColor(mm::Col4(0.5f, 0.5f, 0.5f, 1.0f));
  }
  fw::debug::drawFont(560, y, "delayBack(%.1f)", unknown36c);
}

void TextManager::setup(bool isCaption) {
  unknown18.hide();
  unknown128.hide();
  setFlag(FLAG_CAPTION, isCaption);
  update();
}

void TextManager::setDefaultTalkerMode(bool isDefault, CharaObj *chara) { unknown5d8 = isDefault ? chara : nullptr; }

void TextManager::setAutoTalkMode(bool isAutoTalkMode) { setFlag(FLAG_AUTO_TALK_MODE, isAutoTalkMode); }

void TextManager::setAutoVoiceMode(bool isAutoVoiceMode) { setFlag(FLAG_AUTO_VOICE_MODE, isAutoVoiceMode); }

void TextManager::setBladeNameMode(bool isBladeNameMode) { setFlag(FLAG_BLADE_NAME_MODE, isBladeNameMode); }

void TextManager::setReplaceMode(bool isReplaceMode, const char *name) {
  if (isReplaceMode) {
    unknown10 |= FLAG_REPLACE_MODE;
    unknown5e0 = name;
  } else {
    unknown10 &= ~FLAG_REPLACE_MODE;
    unknown5e0 = "";
  }
}

void TextManager::setCutChangeFrame() { unknown10 |= FLAG_CUT_CHANGE_FRAME; }

void TextManager::setDisp(bool isDisp) { setDispFlag(DISP_FLAG_DISP, isDisp); }

bool TextManager::isDisp() const { return (unknown14 & DISP_FLAG_DISP) != 0; }

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
    unknown10 &= ~FLAG_CUT_CHANGE_FRAME;
    break;
  default:
    break;
  }
}

} // namespace event
