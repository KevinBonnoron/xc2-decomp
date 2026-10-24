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

  CharaObj *getTalker() const { return unknown5d0; }

private:
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown10 |= flag;
    } else {
      unknown10 &= ~flag;
    }
  }

  void setDispFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown14 |= flag;
    } else {
      unknown14 &= ~flag;
    }
  }

  u32 unknown10;                   // Inferred role: flags; original member name unknown.
  u32 unknown14;                   // Inferred role: disp flags; original member name unknown.
  TextCaption unknown18;           // Inferred role: caption; original member name unknown.
  TextWindow unknown128;           // Inferred role: window; original member name unknown.
  f32 unknown358;                  // Inferred role: life; original member name unknown.
  f32 unknown35c;                  // Inferred role: delay; original member name unknown.
  f32 unknown360;                  // Inferred role: delay back; original member name unknown.
  f32 unknown364;                  // Inferred role: life count; original member name unknown.
  f32 unknown368;                  // Inferred role: delay count; original member name unknown.
  f32 unknown36c;                  // Inferred role: delay back count; original member name unknown.
  int unknown370;                  // Inferred role: caption type; original member name unknown.
  f32 unknown374;                  // Inferred role: start frame; original member name unknown.
  u8 *unknown378;                  // Inferred role: bdat; original member name unknown.
  int unknown380;                  // Inferred role: text id; original member name unknown.
  mm::mtl::FixStr<64> unknown384;  // Inferred role: label; original member name unknown.
  mm::mtl::FixStr<512> unknown3c8; // Inferred role: text; original member name unknown.
  CharaObj *unknown5d0;            // Inferred role: talker; original member name unknown.
  CharaObj *unknown5d8;            // Inferred role: default talker; original member name unknown.
  mm::mtl::FixStr<32> unknown5e0;  // Inferred role: replace name; original member name unknown.
};

static_assert(sizeof(TextManager) == 0x608, "");

} // namespace event
