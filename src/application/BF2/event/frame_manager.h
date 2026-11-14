#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {
struct GF_PAUSE_HANDLE;
}

namespace event {

enum ACC_TYPE {
  ACC_TYPE_UNKNOWN_0, // Inferred role: none; original name unknown.
  ACC_TYPE_UNKNOWN_1, // Inferred role: normal; original name unknown.
};

struct FrameInfo {
  f32 unknown00; // Inferred role: frame; original member name unknown.
  f32 unknown04; // Inferred role: delta; original member name unknown.
  f32 unknown08; // Inferred role: pause delta; original member name unknown.
  f32 unknown0c; // Inferred role: stream delta; original member name unknown.
  f32 unknown10; // Inferred role: acc frame; original member name unknown.
};

class FrameManager : public IManager, public mm::mtl::Singleton<FrameManager> {
public:
  static constexpr u32 KEY_FRAME_UNKNOWN_512 = 512; // Inferred role: key frame count; original name unknown.
  static constexpr f32 unknown003 = 1000.0f;        // Inferred role: default max frame; original name unknown.

  enum PAUSE_TYPE {
    PAUSE_TYPE_UNKNOWN_0 = 0,                        // Inferred role: wait; original name unknown.
    PAUSE_TYPE_UNKNOWN_1 = 1,                        // Inferred role: skip; original name unknown.
    PAUSE_TYPE_UNKNOWN_2 = 2,                        // Inferred role: select; original name unknown.
    PAUSE_TYPE_UNKNOWN_3 = 3,                        // Inferred role: quest; original name unknown.
    PAUSE_TYPE_UNKNOWN_4 = 4,                        // Inferred role: common ui; original name unknown.
    PAUSE_TYPE_UNKNOWN_5 = 5,                        // Inferred role: field skill; original name unknown.
    PAUSE_TYPE_UNKNOWN_6 = 6,                        // Inferred role: shop ui; original name unknown.
    PAUSE_TYPE_UNKNOWN_7 = 7,                        // Inferred role: payoff ui; original name unknown.
    PAUSE_TYPE_UNKNOWN_8 = 8,                        // Inferred role: reward ui; original name unknown.
    PAUSE_TYPE_UNKNOWN_9 = 9,                        // Inferred role: rand; original name unknown.
    PAUSE_TYPE_UNKNOWN_11 = 11,                      // Inferred role: homura hikari ui; original name unknown.
    PAUSE_TYPE_UNKNOWN_12 = 12,                      // Inferred role: minigame; original name unknown.
    PAUSE_TYPE_UNKNOWN_13 = 13,                      // Inferred role: new game wait; original name unknown.
    PAUSE_TYPE_UNKNOWN_14 = 14,                      // Inferred role: gf pause only while the stop3d display flag is set (PAUSE_PRESERVED_UNKNOWN_14 is its bit); original name unknown.
    PAUSE_TYPE_UNKNOWN_15 = 15,                      // Inferred role: gf pause only while the stop3d display flag is set; original name unknown.
    PAUSE_TYPE_UNKNOWN_16 = 16,                      // Inferred role: gf pause like the homura hikari ui; original name unknown.
    PAUSE_TYPE_UNKNOWN_17 = 17,                      // Inferred role: count; original name unknown.
    PAUSE_TYPE_UNKNOWN_17_2 = PAUSE_TYPE_UNKNOWN_17, // Inferred role: all; original name unknown.
  };

  enum {
    FLAG_UNKNOWN_0 = 1 << 0,   // Inferred role: stream mode flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1,   // Inferred role: cs snd acc enable flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2,   // Inferred role: cpu acc enable flag; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3,   // Inferred role: lock frame flag; original name unknown.
    FLAG_UNKNOWN_4 = 1 << 4,   // Inferred role: make capture frame flag; original name unknown.
    FLAG_UNKNOWN_5 = 1 << 5,   // Inferred role: capture frame set flag; original name unknown.
    FLAG_UNKNOWN_6 = 1 << 6,   // Inferred role: capture frame flag; original name unknown.
    FLAG_UNKNOWN_7 = 1 << 7,   // Inferred role: request frame flag; original name unknown.
    FLAG_UNKNOWN_8 = 1 << 8,   // Inferred role: page start flag; original name unknown.
    FLAG_UNKNOWN_9 = 1 << 9,   // Inferred role: waiting flag; original name unknown.
    FLAG_UNKNOWN_10 = 1 << 10, // Inferred role: backup frame flag; original name unknown.
    FLAG_UNKNOWN_11 = 1 << 11, // Inferred role: restore frame flag; original name unknown.
  };

  enum {
    DISP_FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: disp flag; original name unknown.
    DISP_FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: syncframe flag; original name unknown.
    DISP_FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: page flag; original name unknown.
    DISP_FLAG_UNKNOWN_3 = 1 << 3, // Inferred role: use skip flag; original name unknown.
    DISP_FLAG_UNKNOWN_4 = 1 << 4, // Inferred role: use stop3d flag; original name unknown.
    DISP_FLAG_UNKNOWN_5 = 1 << 5, // Inferred role: use acc print flag; original name unknown.
  };

  static constexpr u32 PAUSE_PRESERVED_UNKNOWN_14 = 1 << 14; // Inferred role: pause preserved bits; original name unknown.

  // Inferred role: key frame; original type name unknown.
  struct unknown001 {
    f32 unknown00;  // Inferred role: frame; original member name unknown.
    bool unknown04; // Inferred role: cut; original member name unknown.
  };

  f32 getFrame() const;
  bool isPause(PAUSE_TYPE type) const;
  const FrameInfo &frameInfo();
  f32 getTotalFrame() const;
  void pause(PAUSE_TYPE type, bool isPause);
  void requestFrame(f32 frame);
  void setLockFrame(bool isLock, f32 frame);
  FrameManager();
  virtual ~FrameManager() {}
  void login();
  void init();
  void end();
  void initPage();
  void update();
  void render();
  void tail();
  void tailAlways();
  void setStreamMode(bool isStreamMode);
  void setCsSndAccEnable(bool isEnable);
  void setCpuAccEnable(bool isEnable);
  void setInfomation(const char *pageName, int pageID, f32 maxFrame);
  const char *getPageName() const;
  int getPageID() const;
  void pauseClearAll();
  void koma(PAUSE_TYPE type);
  void setFrame(f32 frame);
  f32 getMaxFrame() const;
  void setMakeCaptureFrame(bool isMake);
  bool isCaptureFrame() const;
  void setSkipAbleFrame(f32 frame);
  void addKeyFrame(f32 frame, bool isCut);
  void shiftLeft(bool isCut, f32 frame);
  void shiftRight(bool isCut, f32 frame);
  void shiftFrame(f32 frame);
  void setAccframe(bool isAcc, ACC_TYPE type);
  ACC_TYPE getAccType() const;
  void queryCutList(mm::mtl::FixedVector<f32, KEY_FRAME_UNKNOWN_512> &cutList) const;
  void setDisp(bool isDisp);
  bool isDisp() const;
  void setUseSkip(bool isUse);
  void setUseStop3D(bool isUse);
  void setUseAccPrint(bool isUse);
  bool isUseAccPrint() const;
  void setSyncframe(bool isSync);
  bool isSyncframe() const;
  bool isWaiting() const;
  virtual void OnEventProc(MSG_TYPE type);

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

  void clearPage() {
    m_maxFrame = unknown003;
    unknown1188 = -1;
    m_pageName = "";
    m_pageID = 0;
    m_frame = 0.0f;
    unknown13c = 0.0f;
    unknown144 = 0.0f;
    unknown158 = 0.0f;
    unknown168.clear();
    unknown160 = 0.0f;
  }

  u32 unknown10;                                         // Inferred role: flags; original member name unknown.
  u32 unknown14;                                         // Inferred role: disp flags; original member name unknown.
  u32 unknown18;                                         // Inferred role: pause bits; original member name unknown.
  gf::GF_PAUSE_HANDLE *unknown20[PAUSE_TYPE_UNKNOWN_17]; // Inferred role: pause handles; original member name unknown.
  mm::mtl::FixStr<128> m_pageName;
  int m_pageID;
  f32 m_frame;
  f32 m_totalFrame;
  f32 unknown138; // Inferred role: skip start frame; original member name unknown.
  f32 unknown13c; // Inferred role: next frame; original member name unknown.
  f32 unknown140; // Inferred role: backup frame; original member name unknown.
  f32 unknown144; // Inferred role: reached frame; original member name unknown.
  f32 m_maxFrame;
  f32 unknown14c; // Inferred role: lock frame; original member name unknown.
  f32 unknown150; // Inferred role: capture frame; original member name unknown.
  f32 unknown154; // Inferred role: request frame; original member name unknown.
  f32 unknown158; // Inferred role: skip able frame; original member name unknown.
  ACC_TYPE m_accType;
  f32 unknown160; // Inferred role: acc frame; original member name unknown.
  u8 _164[0x168 - 0x164];
  mm::mtl::FixedVector<unknown001, KEY_FRAME_UNKNOWN_512> unknown168; // Inferred role: key frames; original member name unknown.
  FrameInfo unknown1170;                                              // Inferred role: frame info; original member name unknown.
  int unknown1184;                                                    // Inferred role: page disp count; original member name unknown.
  int unknown1188;                                                    // Inferred role: koma count; original member name unknown.
  PAUSE_TYPE unknown118c;                                             // Inferred role: koma type; original member name unknown.
};

static_assert(sizeof(FrameManager) == 0x1190, "");

} // namespace event
