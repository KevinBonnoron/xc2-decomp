#include "event/text_manager.h"

#include "bdat.h"
#include "event/chara_obj.h"
#include "event/debug_manager.h"
#include "event/frame_manager.h"
#include "event/mstxt_manager.h"
#include "event/skip_manager.h"
#include "event/status_manager.h"
#include "event/ui_manager.h"
#include "event/voice_manager.h"
#include "event/voice_player.h"
#include "fw/fw_bdat_manager.h"
#include "fw/fw_debug.h"
#include "gf/object/gf_obj_handle.h"
#include "ml/dev_graph.h"
#include "ml/rand.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/singleton.h"

namespace event {

void TextManager::reply(const char *label, int textId, CharaObj *chara) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (mm::mtl::Singleton<DebugManager>::getPtr()->isFailureSkip() || (unknown10 & FLAG_UNKNOWN_0) != 0) {
    return;
  }
  unknown10 = (unknown10 & ~(FLAG_UNKNOWN_7 | FLAG_UNKNOWN_8 | FLAG_UNKNOWN_9)) | FLAG_UNKNOWN_7;
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
  if ((unknown10 & FLAG_UNKNOWN_1) != 0 && chara->getActionLastFrame() <= 0.0f) {
    chara->playAutoAction(-1.0f);
  }
  unknown5d0->playAutoTalk(-1.0f);
  unknown5d0->playTalk(false, -1.0f, true, true, -1.0f, -1.0f, -1.0f, -1.0f);
}

bool TextManager::isReplying() const {
  if ((unknown10 & FLAG_UNKNOWN_7) != 0) {
    if ((unknown10 & FLAG_UNKNOWN_8) == 0) {
      return true;
    }
    if (unknown128.isWriting()) {
      return true;
    }
  }
  return false;
}

void TextManager::replyEnd(CharaObj *chara) {
  if ((unknown10 & FLAG_UNKNOWN_1) != 0) {
    chara->playAutoAction(1.0f);
  }
  chara->playAutoTalk(1.0f);
  chara->playTalk(false, 1.0f, true, true, -1.0f, -1.0f, -1.0f, -1.0f);
}

bool TextManager::isCutChangeFrame() const { return (unknown10 & FLAG_UNKNOWN_5) != 0; }

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

void TextManager::update() {
  if ((unknown10 & FLAG_UNKNOWN_7) != 0) {
    const FrameInfo info = mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
    if ((unknown10 & FLAG_UNKNOWN_8) == 0) {
      unknown368 -= info.unknown0c;
      if (unknown368 < 0.0f) {
        if (!mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
          write(unknown3c8.c_str(), unknown378, unknown380, unknown5d0 != nullptr ? unknown5d0->getName() : "", unknown5d0 != nullptr ? unknown5d0->getHandle() : gf::unknown020);
        }
        unknown10 |= FLAG_UNKNOWN_8;
      }
    }
    if ((unknown10 & FLAG_UNKNOWN_8) != 0 && (unknown10 & FLAG_UNKNOWN_6) != 0 && !unknown128.isWriting()) {
      mm::mtl::Singleton<FrameManager>::getPtr()->requestFrame(unknown374);
      mm::mtl::Singleton<FrameManager>::getPtr()->setLockFrame(false, 0.0f);
      mm::mtl::Singleton<VoiceManager>::getPtr()->unknown001().stop(10.0f);
      unknown10 &= ~FLAG_UNKNOWN_6;
    }
    if ((unknown10 & FLAG_UNKNOWN_6) != 0 && mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
      mm::mtl::Singleton<FrameManager>::getPtr()->requestFrame(unknown374);
      mm::mtl::Singleton<FrameManager>::getPtr()->setLockFrame(false, 0.0f);
      mm::mtl::Singleton<VoiceManager>::getPtr()->unknown001().stop(10.0f);
      unknown10 &= ~FLAG_UNKNOWN_6;
    }
    unknown364 -= info.unknown04;
    if ((unknown10 & FLAG_UNKNOWN_9) == 0 && unknown36c < 0.0f && unknown364 < -unknown36c) {
      if ((unknown10 & FLAG_UNKNOWN_0) != 0) {
        unknown18.hide();
      } else {
        unknown128.hide();
      }
      unknown10 |= FLAG_UNKNOWN_9;
    }
    if (unknown36c > 0.0f) {
      if (unknown364 < -unknown36c) {
        stop();
      }
    } else if (unknown364 < 0.0f) {
      stop();
    }
    if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
      stop();
    }
  }
  unknown128.update();
}

void TextManager::write(const char *text, u8 *bdat, u32 textId, const char *name, gf::GF_OBJ_HANDLE *handle) {
  if ((unknown10 & FLAG_UNKNOWN_0) != 0) {
    unknown18.write(text, bdat, textId, unknown370);
  } else {
    unknown128.write(text, name, bdat, textId, handle);
  }
}

void TextManager::stop() {
  if ((unknown10 & FLAG_UNKNOWN_0) != 0) {
    unknown18.hide();
  } else {
    unknown128.hide();
  }
  unknown10 &= ~(FLAG_UNKNOWN_6 | FLAG_UNKNOWN_7 | FLAG_UNKNOWN_8 | FLAG_UNKNOWN_9);
}

void TextManager::render() {
  if (!isDisp()) {
    return;
  }
  unknown18.render();
  unknown128.render();
  if ((unknown10 & FLAG_UNKNOWN_7) == 0) {
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
  setFlag(FLAG_UNKNOWN_0, isCaption);
  update();
}

void TextManager::setDefaultTalkerMode(bool isDefault, CharaObj *chara) { unknown5d8 = isDefault ? chara : nullptr; }

void TextManager::setAutoTalkMode(bool isAutoTalkMode) { setFlag(FLAG_UNKNOWN_1, isAutoTalkMode); }

void TextManager::setAutoVoiceMode(bool isAutoVoiceMode) { setFlag(FLAG_UNKNOWN_2, isAutoVoiceMode); }

void TextManager::setBladeNameMode(bool isBladeNameMode) { setFlag(FLAG_UNKNOWN_3, isBladeNameMode); }

void TextManager::setReplaceMode(bool isReplaceMode, const char *name) {
  if (isReplaceMode) {
    unknown10 |= FLAG_UNKNOWN_4;
    unknown5e0 = name;
  } else {
    unknown10 &= ~FLAG_UNKNOWN_4;
    unknown5e0 = "";
  }
}

void TextManager::play(const char *label, CharaObj *chara, f32 life, f32 delay, f32 delayBack, int captionType) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  if (mm::mtl::Singleton<DebugManager>::getPtr()->isFailureSkip()) {
    return;
  }
  if (!mm::mtl::Singleton<MstxtManager>::getPtr()->isLoaded()) {
    return;
  }
  mm::mtl::FixStr<64> name(label);
  if ((unknown10 & FLAG_UNKNOWN_4) != 0) {
    char replace[256];
    __builtin_memset(replace, 0, sizeof(replace));
    __builtin_strcpy(replace, label);
    __builtin_memcpy(replace, unknown5e0.c_str(), 2);
    if (ml::mtRand(2) == 0) {
      replace[__builtin_strlen(replace) - 1] = '2';
    } else {
      replace[__builtin_strlen(replace) - 1] = '1';
    }
    if (mm::mtl::Singleton<MstxtManager>::getPtr()->getSeatID(replace) >= 0) {
      mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("text %s > %s", label, replace);
      name = replace;
    }
  }
  if (name.length() > 0 && name[name.length() - 1] == 'h') {
    if (mm::mtl::Singleton<StatusManager>::getPtr()->getHomuriFlag() == 0) {
      name[name.length() - 1] = 'h';
      mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("call HOMURA voice");
    } else {
      name[name.length() - 1] = 's';
      mm::mtl::Singleton<DebugManager>::getPtr()->playMessage("call HIKARI voice");
    }
  }
  unknown10 = (unknown10 & ~(FLAG_UNKNOWN_7 | FLAG_UNKNOWN_8 | FLAG_UNKNOWN_9)) | FLAG_UNKNOWN_7;
  delay = __builtin_fmaxf(delay, 0.0f);
  unknown378 = mm::mtl::Singleton<MstxtManager>::getPtr()->getFp();
  unknown380 = mm::mtl::Singleton<MstxtManager>::getPtr()->getSeatID(name.c_str());
  unknown384 = name;
  unknown3c8 = mm::mtl::Singleton<MstxtManager>::getPtr()->getText(name.c_str());
  unknown358 = life;
  unknown35c = delay;
  unknown360 = delayBack;
  unknown364 = life;
  unknown368 = delay;
  unknown36c = delayBack;
  unknown370 = captionType;
  unknown374 = mm::mtl::Singleton<FrameManager>::getPtr()->getFrame() + life;
  unknown5d0 = chara != nullptr ? chara : unknown5d8;
  if ((unknown10 & FLAG_UNKNOWN_0) == 0) {
    if (life >= 1.0f) {
      mm::mtl::Singleton<FrameManager>::getPtr()->setLockFrame(true, mm::mtl::Singleton<FrameManager>::getPtr()->getFrame() + life - 1.0f);
      unknown10 |= FLAG_UNKNOWN_6;
    } else {
      mm::mtl::Singleton<FrameManager>::getPtr()->setLockFrame(false, 0.0f);
      unknown10 &= ~FLAG_UNKNOWN_6;
    }
  }
  if (unknown5d0 != nullptr) {
    if ((unknown10 & FLAG_UNKNOWN_1) != 0 && unknown5d0->getActionLastFrame() <= 0.0f) {
      unknown5d0->playAutoAction(unknown364);
    }
    unknown5d0->playAutoTalk(unknown364);
    unknown5d0->playTalk(false, unknown364, true, true, -1.0f, -1.0f, -1.0f, -1.0f);
  }
  if ((unknown10 & FLAG_UNKNOWN_2) != 0) {
    mm::mtl::Singleton<VoiceManager>::getPtr()->playAuto(unknown384.c_str(), 0.0f, nullptr);
  }
  if ((unknown10 & FLAG_UNKNOWN_3) != 0) {
    if ((unknown10 & FLAG_UNKNOWN_4) != 0 || mm::mtl::Singleton<MstxtManager>::getPtr()->getTop() + mm::mtl::Singleton<MstxtManager>::getPtr()->getCount() - 1 <= unknown380) {
      mm::mtl::Singleton<UIManager>::getPtr()->openBladeNameUI();
      unknown10 &= ~FLAG_UNKNOWN_3;
    }
  }
}

void TextManager::setCutChangeFrame() { unknown10 |= FLAG_UNKNOWN_5; }

void TextManager::setDisp(bool isDisp) { setDispFlag(DISP_FLAG_UNKNOWN_0, isDisp); }

bool TextManager::isDisp() const { return (unknown14 & DISP_FLAG_UNKNOWN_0) != 0; }

void TextManager::setUseSkip(bool isUse) { setDispFlag(DISP_FLAG_UNKNOWN_1, isUse); }

void TextManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_4:
    init();
    break;
  case MSG_TYPE_UNKNOWN_12:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_14:
    update();
    break;
  case MSG_TYPE_UNKNOWN_16:
    render();
    break;
  case MSG_TYPE_UNKNOWN_18:
    unknown10 &= ~FLAG_UNKNOWN_5;
    break;
  default:
    break;
  }
}

} // namespace event
