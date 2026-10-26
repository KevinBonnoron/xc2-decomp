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
  };

  class start_areajump : public ICmd {
  public:
    virtual RESULT update(const Param &param);

  private:
    u32 unknown08; // Inferred role: request; original member name unknown.
    u8 _0c[0x10 - 0x0c];
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
    bool unknown08; // Inferred role: fade requested; original member name unknown.
    u8 _09[0x10 - 0x09];
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
    u32 unknown08; // Inferred role: request; original member name unknown.
    u8 _0c[0x10 - 0x0c];
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
  bool isSetupSceneEnd() const;
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  play_start unknown10;                // Inferred role: cmd play start; original member name unknown.
  play_next unknown18;                 // Inferred role: cmd play next; original member name unknown.
  start unknown20;                     // Inferred role: cmd start; original member name unknown.
  start_fadeout unknown28;             // Inferred role: cmd start fadeout; original member name unknown.
  start_areajump unknown30;            // Inferred role: cmd start areajump; original member name unknown.
  start_notice unknown40;              // Inferred role: cmd start notice; original member name unknown.
  start_loading unknown48;             // Inferred role: cmd start loading; original member name unknown.
  start_other unknown58;               // Inferred role: cmd start other; original member name unknown.
  start_form unknowna8;                // Inferred role: cmd start form; original member name unknown.
  start_change unknownb0;              // Inferred role: cmd start change; original member name unknown.
  start_env_seam unknownb8;            // Inferred role: cmd start env seam; original member name unknown.
  start_weather unknownc0;             // Inferred role: cmd start weather; original member name unknown.
  start_streaming0 unknownc8;          // Inferred role: cmd start streaming0; original member name unknown.
  start_capture_wait unknownd0;        // Inferred role: cmd start capture wait; original member name unknown.
  start_streaming1 unknownd8;          // Inferred role: cmd start streaming1; original member name unknown.
  exec unknowne0;                      // Inferred role: cmd exec; original member name unknown.
  exec_fadeout unknownf8;              // Inferred role: cmd exec fadeout; original member name unknown.
  exec_grass unknown100;               // Inferred role: cmd exec grass; original member name unknown.
  end_change unknown108;               // Inferred role: cmd end change; original member name unknown.
  end_eff unknown118;                  // Inferred role: cmd end eff; original member name unknown.
  end_stream unknown120;               // Inferred role: cmd end stream; original member name unknown.
  end_wait unknown128;                 // Inferred role: cmd end wait; original member name unknown.
  end_areajump unknown138;             // Inferred role: cmd end areajump; original member name unknown.
  end_env_seam unknown148;             // Inferred role: cmd end env seam; original member name unknown.
  end_fadewait unknown150;             // Inferred role: cmd end fadewait; original member name unknown.
  end_fadein unknown158;               // Inferred role: cmd end fadein; original member name unknown.
  end_notice unknown160;               // Inferred role: cmd end notice; original member name unknown.
  end unknown168;                      // Inferred role: cmd end; original member name unknown.
  u32 unknown170;                      // Inferred role: flags; original member name unknown.
  u32 unknown174;                      // Inferred role: disp flags; original member name unknown.
  mm::mtl::FixStr<128> unknown178;     // Inferred role: state name; original member name unknown.
  CmdQueue<QUEUE_COUNT, 0> unknown200; // Inferred role: queue; original member name unknown.
  SeqInfo unknown2710;                 // Inferred role: info; original member name unknown.
  int unknown2840;                     // Inferred role: next event; original member name unknown.
  u8 _2844[0x2850 - 0x2844];
  u32 unknown2850; // Inferred role: login state; original member name unknown.
  u8 _2854[0x2858 - 0x2854];
};

static_assert(sizeof(SeqManager) == 0x2858, "");

} // namespace event
