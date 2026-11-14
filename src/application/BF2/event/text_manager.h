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
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: caption flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: auto talk mode flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: auto voice mode flag; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3, // Inferred role: blade name mode flag; original name unknown.
    FLAG_UNKNOWN_4 = 1 << 4, // Inferred role: replace mode flag; original name unknown.
    FLAG_UNKNOWN_5 = 1 << 5, // Inferred role: cut change frame flag; original name unknown.
    FLAG_UNKNOWN_6 = 1 << 6, // Inferred role: lock frame flag; original name unknown.
    FLAG_UNKNOWN_7 = 1 << 7, // Inferred role: play flag; original name unknown.
    FLAG_UNKNOWN_8 = 1 << 8, // Inferred role: write flag; original name unknown.
    FLAG_UNKNOWN_9 = 1 << 9, // Inferred role: erase flag; original name unknown.
  };

  enum {
    DISP_FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: disp flag; original name unknown.
    DISP_FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: use skip flag; original name unknown.
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
  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md, decision 2026-11-14 #26): inline flag helper, no game symbol gives its name; rename if a sibling build gives a symbol.
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown10 |= flag;
    } else {
      unknown10 &= ~flag;
    }
  }

  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md, decision 2026-11-14 #26): inline flag helper, no game symbol gives its name; rename if a sibling build gives a symbol.
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
