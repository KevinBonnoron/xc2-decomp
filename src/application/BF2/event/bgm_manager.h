#pragma once
#include "event/i_manager.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class BgmManager : public IManager, public mm::mtl::Singleton<BgmManager> {
public:
  static constexpr f32 TO_FR = 30.0f;         // Name given by the xc2 symbol _ZN5event10BgmManager5TO_FRE.
  static constexpr f32 TO_SEC = 1.0f / 30.0f; // Name given by the xc2 symbol _ZN5event10BgmManager6TO_SECE.

  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: hand over flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: play flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2, // Inferred role: delay flag; original name unknown.
    FLAG_UNKNOWN_3 = 1 << 3, // Inferred role: endless flag; original name unknown.
    FLAG_UNKNOWN_4 = 1 << 4, // Inferred role: keep flag; original name unknown.
    FLAG_UNKNOWN_5 = 1 << 5, // Inferred role: stop flag; original name unknown.
    FLAG_UNKNOWN_6 = 1 << 6, // Inferred role: sync flag; original name unknown.
  };

  enum {
    DISP_FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: disp flag; original name unknown.
  };

  BgmManager();
  virtual ~BgmManager() {}
  void clear();
  void update();
  void stop();
  void render();
  void setHandOver(bool isHandOver);
  void playDefaultBgm(f32 fadeFrame);
  void play(const char *name, f32 playFrame, f32 volume, f32 volumeFrame, f32 fadeFrame, f32 delayFrame, f32 fadeOutFrame, f32 startFrame, bool isKeep, f32 overTimeFrame);
  void changeVolume(f32 volume, f32 frame);
  void setSyncFrame(f32 frame);
  f32 getStartedTotalFrame() const;
  void cancelOverTime() const;
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  static const s32 unknown001[7]; // Inferred role: heights of the debug sound bars; original name unknown.

  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      unknown10 |= flag;
    } else {
      unknown10 &= ~flag;
    }
  }

  u32 unknown10;                 // Inferred role: flags; original member name unknown.
  u32 unknown14;                 // Inferred role: disp flags; original member name unknown.
  mm::mtl::FixStr<64> unknown18; // Inferred role: name; original member name unknown.
  f32 unknown5c;                 // Inferred role: volume; original member name unknown.
  f32 unknown60;                 // Inferred role: volume frame; original member name unknown.
  f32 unknown64;                 // Inferred role: fade frame; original member name unknown.
  f32 unknown68;                 // Inferred role: start frame; original member name unknown.
  f32 unknown6c;                 // Inferred role: delay frame; original member name unknown.
  f32 unknown70;                 // Inferred role: fade out frame; original member name unknown.
  f32 unknown74;                 // Inferred role: over time frame; original member name unknown.
  f32 m_startedTotalFrame;
  f32 unknown7c; // Inferred role: play frame; original member name unknown.
  f32 unknown80; // Inferred role: sync frame; original member name unknown.
  s32 unknown84; // Inferred role: sync wait; original member name unknown.
};

static_assert(sizeof(BgmManager) == 0x88, "");

} // namespace event
