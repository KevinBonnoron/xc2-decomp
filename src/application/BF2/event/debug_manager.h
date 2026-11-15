#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class DebugManager : public IManager, public mm::mtl::Singleton<DebugManager> {
public:
  static constexpr u32 EQUIP_SLOT_UNKNOWN_16 = 16; // Inferred role: equip slot count; original name unknown.

  enum {
    FLAG_UNKNOWN_0 = 1 << 0,   // Inferred role: disp flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1,   // Inferred role: message flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2,   // Inferred role: warning flag; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3,   // Inferred role: play onetime flag; original name unknown.
    FLAG_UNKNOWN_4 = 1 << 4,   // Inferred role: play cancel flag; original name unknown.
    FLAG_UNKNOWN_5 = 1 << 5,   // Inferred role: fast skip disable flag; original name unknown.
    FLAG_UNKNOWN_6 = 1 << 6,   // Inferred role: fast skip enable one time flag; original name unknown.
    FLAG_UNKNOWN_7 = 1 << 7,   // Inferred role: ageing skip enable flag; original name unknown.
    FLAG_UNKNOWN_8 = 1 << 8,   // Inferred role: failure skip flag; original name unknown.
    FLAG_UNKNOWN_9 = 1 << 9,   // Inferred role: disable bgm flag; original name unknown.
    FLAG_UNKNOWN_10 = 1 << 10, // Inferred role: replace maximum equip flag; original name unknown.
    FLAG_UNKNOWN_11 = 1 << 11, // Inferred role: replace maximum blade flag; original name unknown.
    FLAG_UNKNOWN_12 = 1 << 12, // Inferred role: disable new game wait flag; original name unknown.
    FLAG_UNKNOWN_13 = 1 << 13, // Inferred role: sync free cam flag; original name unknown.
    FLAG_UNKNOWN_14 = 1 << 14, // Inferred role: sync free cam one time flag; original name unknown.
    FLAG_UNKNOWN_15 = 1 << 15, // Inferred role: disable reuse flag; original name unknown.
    FLAG_UNKNOWN_16 = 1 << 16, // Inferred role: movie debug flag; original name unknown.
  };

  enum {
    SIGHT_UNKNOWN_0, // Inferred role: none; original name unknown.
    SIGHT_UNKNOWN_1, // Inferred role: cross; original name unknown.
    SIGHT_UNKNOWN_2, // Inferred role: thirds; original name unknown.
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
  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md, decision 2026-11-14 #26): inline flag helper, no game symbol gives its name; rename if a sibling build gives a symbol.
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
  u32 unknown228[EQUIP_SLOT_UNKNOWN_16]; // Inferred role: replace default equips; original member name unknown.
};

static_assert(sizeof(DebugManager) == 0x268, "");

} // namespace event
