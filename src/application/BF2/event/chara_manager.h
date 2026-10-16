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
  bool isStreamMode() const { return (flags & FLAG_STREAM_MODE) != 0; }
  bool isOffscrMode() const { return (flags & FLAG_OFFSCR_MODE) != 0; }
  u32 getOffscrID() const { return mOffscrID; }
  bool isAutoTalkMode() const { return (flags & FLAG_AUTO_TALK_MODE) != 0; }
  bool isSeamlessAction() const { return (flags & FLAG_SEAMLESS_ACTION) != 0; }
  bool isSystemTicket960() const { return (flags & FLAG_SYSTEM_TICKET960) != 0; }
  bool isUseHood() const { return (flags & FLAG_USE_HOOD) != 0; }
  int getReuseFlag() const { return mReuseFlag; }
  void clear();
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
  u32 mOffscrID;
  int mReuseFlag;
};

static_assert(sizeof(CharaManager) == 0x20, "");

} // namespace event
