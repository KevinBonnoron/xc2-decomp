#pragma once
#include "event/i_manager.h"
#include "event/seq_info.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class SeqManager : public IManager, public mm::mtl::Singleton<SeqManager> {
public:
  enum {
    DISP_FLAG_DISP = 1 << 0,
  };

  SeqManager();
  virtual ~SeqManager();
  static bool checkWaitSeam(const SeqInfo &info, bool isSeamless);
  static bool checkWait3D(const SeqInfo &info);
  static bool checkSkipClear(const SeqInfo &info);
  static bool checkSyncBgm(const SeqInfo &info, bool isSync);
  static bool checkCapture(const SeqInfo &info);
  void nextEvent(int next);
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  u8 _10[0x170 - 0x10];
  u32 flags;
  u32 dispFlags;
  mm::mtl::FixStr<128> mStateName;
  u8 _1fc[0x2710 - 0x1fc];
  SeqInfo mInfo;
  int mNextEvent;
  u8 _2844[0x2858 - 0x2844];
};

static_assert(sizeof(SeqManager) == 0x2858, "");

} // namespace event
