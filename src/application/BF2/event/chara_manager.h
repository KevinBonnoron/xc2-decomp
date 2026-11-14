#pragma once
#include "event/chara_obj.h"
#include "event/i_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class CharaManager : public IManager, public mm::mtl::Singleton<CharaManager> {
public:
  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: stream mode flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: offscr mode flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: auto talk mode flag; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3, // Inferred role: seamless action flag; original name unknown.
    FLAG_UNKNOWN_4 = 1 << 4, // Inferred role: system ticket960 flag; original name unknown.
    FLAG_UNKNOWN_5 = 1 << 5, // Inferred role: use hood flag; original name unknown.
  };

  enum {
    DISP_FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: chara flag; original name unknown.
    DISP_FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: facial flag; original name unknown.
    DISP_FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: bone flag; original name unknown.
  };

  CharaManager();
  virtual ~CharaManager() {}
  bool isStreamMode() const;
  bool isOffscrMode() const;
  u32 getOffscrID() const;
  bool isAutoTalkMode() const;
  bool isSeamlessAction() const;
  bool isSystemTicket960() const;
  bool isUseHood() const;
  int getReuseFlag() const;
  void clear();
  void loadResource(const char *name);
  void loadMdlstream(f32 frame, const char *path, u32 value);
  void loadMdlstream(f32 frame, CHARA_TYPE type, u32 id, u32 value);
  void setStreamMode(bool isStreamMode);
  void setOffscrMode(bool isOffscrMode, u32 offscrID);
  void setAutoTalkMode(bool isAutoTalkMode);
  void setSeamlessAction(bool isSeamlessAction);
  void setSystemTicket960(bool isSystemTicket960);
  void setUseHood(bool isUseHood);
  void setCharaDisp(bool isDisp);
  bool isCharaDisp() const;
  void setFacialDisp(bool isDisp);
  bool isFacialDisp() const;
  void setBoneDisp(bool isDisp);
  bool isBoneDisp() const;
  void setReuseFlag(int reuseFlag);
  virtual void OnEventProc(MSG_TYPE type);

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

  u32 unknown10; // Inferred role: flags; original member name unknown.
  u32 unknown14; // Inferred role: disp flags; original member name unknown.
  u32 m_offscrID;
  int m_reuseFlag;
};

static_assert(sizeof(CharaManager) == 0x20, "");

} // namespace event
