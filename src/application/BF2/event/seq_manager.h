#pragma once
#include <stddef.h>

#include "event/cmd_queue.h"
#include "event/i_cmd.h"
#include "event/i_manager.h"
#include "event/seq_info.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class SeqManager : public IManager, public mm::mtl::Singleton<SeqManager> {
public:
  static constexpr size_t QUEUE_COUNT = 32;

  enum {
    FLAG_SCRIPT_ERROR = 1 << 0,
    FLAG_END = 1 << 1,
    FLAG_NEXT = 1 << 2,
    FLAG_LOGIN = 1 << 3,
  };

  enum {
    DISP_FLAG_DISP = 1 << 0,
  };

  class play_start : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class play_next : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class start : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class start_fadeout : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class start_notice : public ICmd {
  public:
    virtual RESULT update(const Param &param);

  private:
    u8 _08[0x10 - 0x08];
  };

  class start_areajump : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class start_loading : public ICmd {
  public:
    virtual RESULT update(const Param &param);

  private:
    u8 _08[0x10 - 0x08];
  };

  class start_other : public ICmd {
  public:
    virtual RESULT update(const Param &param);

  private:
    u8 _08[0x50 - 0x08];
  };

  class start_form : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class start_change : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class start_env_seam : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class start_weather : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class start_streaming0 : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class start_capture_wait : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class start_streaming1 : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class exec : public ICmd {
  public:
    virtual RESULT update(const Param &param);

  private:
    u8 _08[0x18 - 0x08];
  };

  class exec_fadeout : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class exec_grass : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class end_change : public ICmd {
  public:
    virtual RESULT update(const Param &param);

  private:
    u8 _08[0x10 - 0x08];
  };

  class end_eff : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class end_stream : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class end_wait : public ICmd {
  public:
    virtual RESULT update(const Param &param);

  private:
    u8 _08[0x10 - 0x08];
  };

  class end_areajump : public ICmd {
  public:
    virtual RESULT update(const Param &param);

  private:
    u8 _08[0x10 - 0x08];
  };

  class end_env_seam : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class end_fadewait : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class end_fadein : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class end_notice : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  class end : public ICmd {
  public:
    virtual RESULT update(const Param &param);
  };

  SeqManager();
  virtual ~SeqManager();
  void clear();
  void login();
  void logout();
  static bool checkWaitSeam(const SeqInfo &info, bool isSeamless);
  static bool checkWait3D(const SeqInfo &info);
  static bool checkSkipClear(const SeqInfo &info);
  static bool checkSyncBgm(const SeqInfo &info, bool isSync);
  static bool checkCapture(const SeqInfo &info);
  void update();
  void nextEvent(int next);
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  play_start cmdPlayStart;
  play_next cmdPlayNext;
  start cmdStart;
  start_fadeout cmdStartFadeout;
  start_notice cmdStartNotice;
  start_areajump cmdStartAreajump;
  start_loading cmdStartLoading;
  start_other cmdStartOther;
  start_form cmdStartForm;
  start_change cmdStartChange;
  start_env_seam cmdStartEnvSeam;
  start_weather cmdStartWeather;
  start_streaming0 cmdStartStreaming0;
  start_capture_wait cmdStartCaptureWait;
  start_streaming1 cmdStartStreaming1;
  exec cmdExec;
  exec_fadeout cmdExecFadeout;
  exec_grass cmdExecGrass;
  end_change cmdEndChange;
  end_eff cmdEndEff;
  end_stream cmdEndStream;
  end_wait cmdEndWait;
  end_areajump cmdEndAreajump;
  end_env_seam cmdEndEnvSeam;
  end_fadewait cmdEndFadewait;
  end_fadein cmdEndFadein;
  end_notice cmdEndNotice;
  end cmdEnd;
  u32 flags;
  u32 dispFlags;
  mm::mtl::FixStr<128> mStateName;
  CmdQueue<QUEUE_COUNT, 0> queue;
  SeqInfo mInfo;
  int mNextEvent;
  u8 _2844[0x2850 - 0x2844];
  u32 loginState;
  u8 _2854[0x2858 - 0x2854];
};

static_assert(sizeof(SeqManager) == 0x2858, "");

} // namespace event
