#pragma once
#include "event/i_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class CharaManager : public IManager, public mm::mtl::Singleton<CharaManager> {
public:
  enum {
    FLAG_STREAM_MODE = 1 << 0,
    FLAG_OFFSCR_MODE = 1 << 1,
    FLAG_AUTO_TALK_MODE = 1 << 2,
    FLAG_SEAMLESS_ACTION = 1 << 3,
    FLAG_SYSTEM_TICKET960 = 1 << 4,
    FLAG_USE_HOOD = 1 << 5,
  };

  enum {
    DISP_FLAG_CHARA = 1 << 0,
    DISP_FLAG_FACIAL = 1 << 1,
    DISP_FLAG_BONE = 1 << 2,
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
