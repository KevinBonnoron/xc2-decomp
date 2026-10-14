#pragma once
#include "fw/fw_pad.h"
#include "gf/event/gf_event.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

enum DWPAD {};

class GfGamePad : public mm::mtl::PtrSingleton<GfGamePad>, public IGfEvent {
public:
  static const u32 INTERRUPT_PAD_MAX = 64;

  GfGamePad(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfGamePad();
  void clear();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  void changePadInputMode();
  static bool isInitialized();
  static void update(const fw::UpdateInfo &info);
  void clearUniqParams();
  static u32 getPlayerPadId();
  void checkEmergencyEscape();
  void updateInterruptPadOnForDebug();
  static const fw::PadData *getPadPlayer();
  static bool isEventPause();
  static void setInterruptPadOnForDebug(DWPAD pad);
  void eventInGameEventPause();
  void eventInGameOpenMainMenu();
  void eventInGameOpenSystemMenu();
  void eventInGameOpenSkipTravelMenu();
  void gevExecState(EXEC_STATE state) override;
  void gevGameState(GF_STATE state, GF_STATE oldState) override;
  void eventInGameOpenQuestListMenu();

private:
  bool mInitialized;
  bool mIsEventPause;
  fw::PadRelay mPadRelay;
  fw::PadData mPadData;
  mm::mtl::FixedVector<DWPAD, INTERRUPT_PAD_MAX> mInterruptPads;
  u8 mEmergencyEscapeFrame;
};

static_assert(sizeof(GfGamePad) == 0x1a8, "");

} // namespace gf
