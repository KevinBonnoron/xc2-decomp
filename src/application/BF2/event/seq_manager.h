#pragma once
#include <stddef.h>

#include "event/cmd_queue.h"
#include "event/i_cmd.h"
#include "event/i_manager.h"
#include "event/seq_info.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class ObjectChara;

class SeqManager : public IManager, public mm::mtl::Singleton<SeqManager> {
  friend class Manager;

public:
  static constexpr size_t QUEUE_UNKNOWN_32 = 32; // Inferred role: queue count; original name unknown.

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: script error flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: end flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: next flag; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3, // Inferred role: login flag; original name unknown.
    FLAG_UNKNOWN_9 = 1 << 9, // Inferred role: new game wait flag; original name unknown.
  };

  enum {
    DISP_FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: disp flag; original name unknown.
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
    friend class SeqManager;

  public:
    start_loading() : unknown08(false) {}
    virtual RESULT update(const Param &param);

  private:
    bool unknown08; // Role and original member name unknown.
  };

  class start_other : public ICmd {
  public:
    virtual RESULT update(const Param &param);

  private:
    mm::mtl::FixedVector<ObjectChara *, 8> unknown08; // Inferred role: created party characters; original member name unknown.
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
    friend class SeqManager;

  public:
    exec() : unknown08(false), unknown09(false), unknown0a(false), unknown0c(0.0f), unknown14(0) {}
    virtual RESULT update(const Param &param);

  private:
    bool unknown08; // Role and original member name unknown.
    bool unknown09; // Role and original member name unknown.
    bool unknown0a; // Role and original member name unknown.
    f32 unknown0c;  // Role and original member name unknown.
    int unknown10;  // Role and original member name unknown.
    int unknown14;  // Role and original member name unknown.
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
    friend class SeqManager;

  public:
    end_wait() : unknown08(false) {}
    virtual RESULT update(const Param &param);

  private:
    bool unknown08; // Role and original member name unknown.
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
  void clear();
  void play(const char *name);
  void login();
  void logout();
  static bool checkWaitSeam(const SeqInfo &info, bool isSeamless);
  static bool checkWait3D(const SeqInfo &info);
  static bool checkSkipClear(const SeqInfo &info);
  static bool checkSyncBgm(const SeqInfo &info, bool isSync);
  static bool checkCapture(const SeqInfo &info);
  void update();
  void render();
  void init();
  void setupScene();
  void startScene();
  void end();
  void nextEvent(int next);
  bool isSetupSceneEnd() const;
  void setDisp(bool isDisp);
  bool isDisp() const;
  // Inferred role: info of the current sequence; original name unknown.
  const SeqInfo &unknown001() const { return m_seqInfo; }
  virtual void OnEventProc(MSG_TYPE type);

private:
  play_start m_play_start;                  // Inferred role: cmd play start; original member name unknown.
  play_next m_play_next;                    // Inferred role: cmd play next; original member name unknown.
  start m_start;                            // Inferred role: cmd start; original member name unknown.
  start_fadeout m_start_fadeout;            // Inferred role: cmd start fadeout; original member name unknown.
  start_areajump m_start_areajump;          // Inferred role: cmd start areajump; original member name unknown.
  start_notice m_start_notice;              // Inferred role: cmd start notice; original member name unknown.
  start_loading m_start_loading;            // Inferred role: cmd start loading; original member name unknown.
  start_other m_start_other;                // Inferred role: cmd start other; original member name unknown.
  start_form m_start_form;                  // Inferred role: cmd start form; original member name unknown.
  start_change m_start_change;              // Inferred role: cmd start change; original member name unknown.
  start_env_seam m_start_env_seam;          // Inferred role: cmd start env seam; original member name unknown.
  start_weather m_start_weather;            // Inferred role: cmd start weather; original member name unknown.
  start_streaming0 m_start_streaming0;      // Inferred role: cmd start streaming0; original member name unknown.
  start_capture_wait m_start_capture_wait;  // Inferred role: cmd start capture wait; original member name unknown.
  start_streaming1 m_start_streaming1;      // Inferred role: cmd start streaming1; original member name unknown.
  exec m_exec;                              // Inferred role: cmd exec; original member name unknown.
  exec_fadeout m_exec_fadeout;              // Inferred role: cmd exec fadeout; original member name unknown.
  exec_grass m_exec_grass;                  // Inferred role: cmd exec grass; original member name unknown.
  end_change m_end_change;                  // Inferred role: cmd end change; original member name unknown.
  end_eff m_end_eff;                        // Inferred role: cmd end eff; original member name unknown.
  end_stream m_end_stream;                  // Inferred role: cmd end stream; original member name unknown.
  end_wait m_end_wait;                      // Inferred role: cmd end wait; original member name unknown.
  end_areajump m_end_areajump;              // Inferred role: cmd end areajump; original member name unknown.
  end_env_seam m_end_env_seam;              // Inferred role: cmd end env seam; original member name unknown.
  end_fadewait m_end_fadewait;              // Inferred role: cmd end fadewait; original member name unknown.
  end_fadein m_end_fadein;                  // Inferred role: cmd end fadein; original member name unknown.
  end_notice m_end_notice;                  // Inferred role: cmd end notice; original member name unknown.
  class end m_end;                          // Inferred role: cmd end; original member name unknown.
  u32 unknown170;                           // Inferred role: flags; original member name unknown.
  u32 unknown174;                           // Inferred role: disp flags; original member name unknown.
  mm::mtl::FixStr<128> unknown178;          // Inferred role: state name; original member name unknown.
  CmdQueue<QUEUE_UNKNOWN_32, 0> unknown200; // Inferred role: queue; original member name unknown.
  SeqInfo m_seqInfo;                        // Inferred role: info; original member name unknown.
  int unknown2840;                          // Inferred role: next event; original member name unknown.
  int unknown2844;                          // Inferred role: previous category; original member name unknown.
  u8 _2848[0x2850 - 0x2848];
  u32 unknown2850; // Inferred role: login state; original member name unknown.
  u8 _2854[0x2858 - 0x2854];
};

static_assert(sizeof(SeqManager) == 0x2858, "");

} // namespace event
