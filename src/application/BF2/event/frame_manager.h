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
  ACC_TYPE_NONE,
  ACC_TYPE_NORMAL,
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
  static constexpr u32 KEY_FRAME_COUNT = 512;
  static constexpr f32 DEFAULT_MAX_FRAME = 1000.0f;

  enum PAUSE_TYPE {
    PAUSE_TYPE_WAIT = 0,
    PAUSE_TYPE_SKIP = 1,
    PAUSE_TYPE_SELECT = 2,
    PAUSE_TYPE_QUEST = 3,
    PAUSE_TYPE_COMMON_UI = 4,
    PAUSE_TYPE_FIELD_SKILL = 5,
    PAUSE_TYPE_SHOP_UI = 6,
    PAUSE_TYPE_PAYOFF_UI = 7,
    PAUSE_TYPE_REWARD_UI = 8,
    PAUSE_TYPE_RAND = 9,
    PAUSE_TYPE_HOMURA_HIKARI_UI = 11,
    PAUSE_TYPE_MINIGAME = 12,
    PAUSE_TYPE_NEW_GAME_WAIT = 13,
    PAUSE_TYPE_COUNT = 17,
    PAUSE_TYPE_ALL = PAUSE_TYPE_COUNT,
  };

  enum {
    FLAG_STREAM_MODE = 1 << 0,
    FLAG_CS_SND_ACC_ENABLE = 1 << 1,
    FLAG_CPU_ACC_ENABLE = 1 << 2,
    FLAG_LOCK_FRAME = 1 << 3,
    FLAG_MAKE_CAPTURE_FRAME = 1 << 4,
    FLAG_CAPTURE_FRAME_SET = 1 << 5,
    FLAG_CAPTURE_FRAME = 1 << 6,
    FLAG_REQUEST_FRAME = 1 << 7,
    FLAG_PAGE_START = 1 << 8,
    FLAG_WAITING = 1 << 9,
    FLAG_BACKUP_FRAME = 1 << 10,
    FLAG_RESTORE_FRAME = 1 << 11,
  };

  enum {
    DISP_FLAG_DISP = 1 << 0,
    DISP_FLAG_SYNCFRAME = 1 << 1,
    DISP_FLAG_PAGE = 1 << 2,
    DISP_FLAG_USE_SKIP = 1 << 3,
    DISP_FLAG_USE_STOP3D = 1 << 4,
    DISP_FLAG_USE_ACC_PRINT = 1 << 5,
  };

  static constexpr u32 PAUSE_PRESERVED_BITS = 1 << 14;

  struct KeyFrame {
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
  void queryCutList(mm::mtl::FixedVector<f32, KEY_FRAME_COUNT> &cutList) const;
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

  void clearPage() {
    m_maxFrame = DEFAULT_MAX_FRAME;
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

  u32 unknown10;                                    // Inferred role: flags; original member name unknown.
  u32 unknown14;                                    // Inferred role: disp flags; original member name unknown.
  u32 unknown18;                                    // Inferred role: pause bits; original member name unknown.
  gf::GF_PAUSE_HANDLE *unknown20[PAUSE_TYPE_COUNT]; // Inferred role: pause handles; original member name unknown.
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
  mm::mtl::FixedVector<KeyFrame, KEY_FRAME_COUNT> unknown168; // Inferred role: key frames; original member name unknown.
  FrameInfo unknown1170;                                      // Inferred role: frame info; original member name unknown.
  int unknown1184;                                            // Inferred role: page disp count; original member name unknown.
  int unknown1188;                                            // Inferred role: koma count; original member name unknown.
  PAUSE_TYPE unknown118c;                                     // Inferred role: koma type; original member name unknown.
};

static_assert(sizeof(FrameManager) == 0x1190, "");

} // namespace event
