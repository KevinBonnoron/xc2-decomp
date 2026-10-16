#pragma once
#include "event/i_manager.h"
#include "event/text_caption.h"
#include "event/text_window.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace event {

class CharaObj;

class TextManager : public IManager, public mm::mtl::Singleton<TextManager> {
public:
  enum {
    FLAG_CAPTION = 1 << 0,
    FLAG_AUTO_TALK_MODE = 1 << 1,
    FLAG_AUTO_VOICE_MODE = 1 << 2,
    FLAG_BLADE_NAME_MODE = 1 << 3,
    FLAG_REPLACE_MODE = 1 << 4,
    FLAG_CUT_CHANGE_FRAME = 1 << 5,
    FLAG_LOCK_FRAME = 1 << 6,
    FLAG_PLAY = 1 << 7,
    FLAG_WRITE = 1 << 8,
    FLAG_ERASE = 1 << 9,
  };

  enum {
    DISP_FLAG_DISP = 1 << 0,
    DISP_FLAG_USE_SKIP = 1 << 1,
  };

  TextManager();
  virtual ~TextManager() {}
  void reply(const char *label, int textId, CharaObj *chara);
  bool isReplying() const;
  void replyEnd(CharaObj *chara);
  bool isCutChangeFrame() const;
  void clear();
  void init();
  void update();
  void write(const char *text, u8 *bdat, u32 textId, const char *name, gf::GF_OBJ_HANDLE *handle);
  void stop();
  void render();
  void setup(bool isCaption);
  void setDefaultTalkerMode(bool isDefault, CharaObj *chara);
  void setAutoTalkMode(bool isAutoTalkMode);
  void setAutoVoiceMode(bool isAutoVoiceMode);
  void setBladeNameMode(bool isBladeNameMode);
  void setReplaceMode(bool isReplaceMode, const char *name);
  void play(const char *label, CharaObj *chara, f32 life, f32 delay, f32 delayBack, int captionType);
  void setCutChangeFrame();
  void setDisp(bool isDisp);
  bool isDisp() const;
  void setUseSkip(bool isUse);
  virtual void OnEventProc(MSG_TYPE type);

private:
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      flags |= flag;
    } else {
      flags &= ~flag;
    }
  }

  void setDispFlag(u32 flag, bool isSet) {
    if (isSet) {
      dispFlags |= flag;
    } else {
      dispFlags &= ~flag;
    }
  }

  u32 flags;
  u32 dispFlags;
  TextCaption caption;
  TextWindow window;
  f32 life;
  f32 delay;
  f32 delayBack;
  f32 lifeCount;
  f32 delayCount;
  f32 delayBackCount;
  int captionType;
  f32 startFrame;
  u8 *bdat;
  int textId;
  mm::mtl::FixStr<64> label;
  mm::mtl::FixStr<512> text;
  CharaObj *talker;
  CharaObj *defaultTalker;
  mm::mtl::FixStr<32> replaceName;
};

static_assert(sizeof(TextManager) == 0x608, "");

} // namespace event
