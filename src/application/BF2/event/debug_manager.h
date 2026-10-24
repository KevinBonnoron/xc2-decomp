#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class DebugManager : public IManager, public mm::mtl::Singleton<DebugManager> {
public:
  static constexpr u32 EQUIP_SLOT_COUNT = 16;

  enum {
    FLAG_DISP = 1 << 0,
    FLAG_MESSAGE = 1 << 1,
    FLAG_WARNING = 1 << 2,
    FLAG_PLAY_ONETIME = 1 << 3,
    FLAG_PLAY_CANCEL = 1 << 4,
    FLAG_FAST_SKIP_DISABLE = 1 << 5,
    FLAG_FAST_SKIP_ENABLE_ONE_TIME = 1 << 6,
    FLAG_AGEING_SKIP_ENABLE = 1 << 7,
    FLAG_FAILURE_SKIP = 1 << 8,
    FLAG_DISABLE_BGM = 1 << 9,
    FLAG_REPLACE_MAXIMUM_EQUIP = 1 << 10,
    FLAG_REPLACE_MAXIMUM_BLADE = 1 << 11,
    FLAG_DISABLE_NEW_GAME_WAIT = 1 << 12,
    FLAG_SYNC_FREE_CAM = 1 << 13,
    FLAG_SYNC_FREE_CAM_ONE_TIME = 1 << 14,
    FLAG_DISABLE_REUSE = 1 << 15,
    FLAG_MOVIE_DEBUG = 1 << 16,
  };

  enum {
    SIGHT_NONE,
    SIGHT_CROSS,
    SIGHT_THIRDS,
  };

  DebugManager();
  virtual ~DebugManager() {}
  void update();
  void render();
  void tail();
  void playMessage(const char *format, ...);
  void playWarning(const char *format, ...);
  void setPlayOnetime(bool isPlayOnetime);
  bool isPlayOnetime() const;
  void setPlayCancel(bool isPlayCancel);
  bool isPlayCancel() const;
  void setFastSkipDisable(bool isDisable);
  bool isFastSkipDisable() const;
  void setFastSkipEnableOneTime(bool isEnable);
  bool isFastSkipEnableOneTime() const;
  void setAgeingSkipEnable(bool isEnable);
  bool isAgeingSkip() const;
  void failureSkip();
  bool isFailureSkip() const;
  void setDisableBgm(bool isDisable);
  bool isDisableBgm() const;
  void setReplaceDefaultEquip(bool isReplace, u32 slot, u32 item);
  bool isReplaceDefaultEquip(u32 slot, u32 *item);
  void setReplaceMaximumEquip(bool isReplace);
  bool isReplaceMaximumEquip() const;
  void setReplaceMaximumBlade(bool isReplace);
  bool isReplaceMaximumBlade() const;
  void setDisableNewGameWait(bool isDisable);
  bool isDisableNewGameWait() const;
  void setSyncFreeCam(bool isSync, bool isOneTime);
  bool isSyncFreeCam() const;
  void setDisp(bool isDisp);
  bool isDisp() const;
  void setDispSight(int sight);
  int getDispSight() const;
  void setDisableReuse(bool isDisable);
  bool isDisableReuse() const;
  void setMovieDebug(bool isMovieDebug);
  bool isMovieDebug() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown10 |= flag;
    } else {
      unknown10 &= ~flag;
    }
  }

  u32 unknown10;                   // Inferred role: flags; original member name unknown.
  mm::mtl::FixStr<256> unknown14;  // Inferred role: message; original member name unknown.
  s32 unknown118;                  // Inferred role: message timer; original member name unknown.
  mm::mtl::FixStr<256> unknown11c; // Inferred role: warning; original member name unknown.
  s32 unknown220;                  // Inferred role: warning timer; original member name unknown.
  int m_dispSight;
  u32 unknown228[EQUIP_SLOT_COUNT]; // Inferred role: replace default equips; original member name unknown.
};

static_assert(sizeof(DebugManager) == 0x268, "");

} // namespace event
