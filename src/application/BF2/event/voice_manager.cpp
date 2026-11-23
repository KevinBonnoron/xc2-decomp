#include "event/voice_manager.h"

#include "event/extend.h"
#include "event/lipsync_manager.h"
#include "event/skip_manager.h"
#include "framework/lang_util.h"
#include "mm_mtl/fixstr.h"

namespace event {

VoiceManager::VoiceManager() : unknown10(0), unknown14(0) {}

void VoiceManager::clear() {
  m_voicePlayer.clear();
  m_voiceOneShoter.clear();
  unknown10 = 0;
}

void VoiceManager::startScene() { m_voicePlayer.clearPreload(); }

void VoiceManager::update() {
  m_voicePlayer.update();
  m_voiceOneShoter.update();
}

void VoiceManager::render() {
  if ((unknown14 & DISP_FLAG_UNKNOWN_0) != 0) {
    m_voicePlayer.draw();
  }
}

void VoiceManager::setAutoVoiceMode(bool isAutoVoiceMode, const char *directory, const char *name) {
  m_voiceMaker.create(isAutoVoiceMode, directory, name);
  setFlag(FLAG_UNKNOWN_0, isAutoVoiceMode);
}

void VoiceManager::setMultipleMode(bool isMultipleMode) { m_voicePlayer.setMultipleMode(isMultipleMode); }

// The original source repeats the statements of preload() here instead of calling it: with `preload(frame, path)`
// this function is 46 instructions against the game's 109 (0x71000fcaa4), and no call, unit grouping or flag
// gives the game's code.
void VoiceManager::preloadAuto(f32 frame, const char *name) {
  if ((unknown10 & FLAG_UNKNOWN_0) == 0) {
    return;
  }
  const char *path = m_voiceMaker.makePath(name);
  if (path == nullptr) {
    return;
  }
  m_voicePlayer.preload(frame, mm::mtl::Singleton<Extend>::getPtr()->wav(path));
}

void VoiceManager::preload(f32 frame, const char *name) {
  const char *path = mm::mtl::Singleton<Extend>::getPtr()->wav(name);
  m_voicePlayer.preload(frame, path);
}

// The original source repeats the statements of play() here instead of calling it: the game's playAuto
// (0x71000f517c, 159 instructions) holds them with Extend::wav inlined, which play() itself (0x71000fccec) calls.
// `return play(path, delay, event)` gives 26 instructions, and play() forced inline gives 123 (wav stays a call);
// no flag or inline threshold gives the game's code. Unit: this file is not the game's unit for playAuto: the game places it inside the TextManager block, right after
// TextManager::play (0x71000f46fc), its only caller (bl at 0x71000f503c), far from the VoiceManager block (0x71000fc854 to 0x71000fd264). A callee defined in this file therefore
// cannot be what the game inlines there; [INFERENCE] playAuto is emitted with TextManager, like a header function, and play() is visible in that unit (audit 2026-11-21).
bool VoiceManager::playAuto(const char *name, f32 delay, IVoiceEvent *event) {
  if ((unknown10 & FLAG_UNKNOWN_0) == 0) {
    return false;
  }
  const char *path = m_voiceMaker.makePath(name);
  if (path == nullptr) {
    return false;
  }
  bool isLipsync = mm::mtl::Singleton<LipsyncManager>::getPtr()->setTarget(path);
  setFlag(FLAG_UNKNOWN_1, isLipsync);
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    return isLipsync;
  }
  return m_voicePlayer.play(mm::mtl::Singleton<Extend>::getPtr()->wav(path), delay, event);
}

bool VoiceManager::play(const char *name, f32 delay, IVoiceEvent *event) {
  bool isLipsync = mm::mtl::Singleton<LipsyncManager>::getPtr()->setTarget(name);
  setFlag(FLAG_UNKNOWN_1, isLipsync);
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkip()) {
    return isLipsync;
  }
  return m_voicePlayer.play(mm::mtl::Singleton<Extend>::getPtr()->wav(name), delay, event);
}

bool VoiceManager::playOneshot(const char *name, f32 volume) {
  mm::mtl::FixStr<64> path("/stream/");
  path += name;
  if (fw::LangUtil::getVoiceType() != 0) {
    path = mm::mtl::Singleton<Extend>::getPtr()->replaceString(name, "jp", fw::LangUtil::getVoiceFolder().c_str());
  }
  return m_voiceOneShoter.play(mm::mtl::Singleton<Extend>::getPtr()->wav(path.c_str()), volume);
}

void VoiceManager::pause(bool isPause) {
  setFlag(FLAG_UNKNOWN_2, isPause);
  m_voicePlayer.pause(isPause);
  m_voiceOneShoter.pause(isPause);
}

void VoiceManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown14 |= DISP_FLAG_UNKNOWN_0;
  } else {
    unknown14 &= ~DISP_FLAG_UNKNOWN_0;
  }
}

bool VoiceManager::isDisp() const { return (unknown14 & DISP_FLAG_UNKNOWN_0) != 0; }

void VoiceManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_UNKNOWN_4:
    clear();
    break;
  case MSG_TYPE_UNKNOWN_7:
  case MSG_TYPE_UNKNOWN_8:
    startScene();
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
  default:
    break;
  }
}

} // namespace event

template event::VoiceManager *mm::mtl::Singleton<event::VoiceManager>::getPtr();
