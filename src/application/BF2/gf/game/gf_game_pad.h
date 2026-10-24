#pragma once
#include "fw/fw_pad.h"
#include "gf/event/gf_event.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

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
  void gevGameState(GF_STATE previousState, GF_STATE state) override;
  void eventInGameOpenQuestListMenu();

private:
  bool unknown10;                                           // Inferred role: initialized; original member name unknown.
  bool unknown11;                                           // Inferred role: event pause; original member name unknown.
  fw::PadRelay unknown18;                                   // Inferred role: pad relay; original member name unknown.
  fw::PadData unknown50;                                    // Inferred role: pad data; original member name unknown.
  mm::mtl::FixedVector<DWPAD, INTERRUPT_PAD_MAX> unknown98; // Inferred role: interrupt pads; original member name unknown.
  u8 unknown1a0;                                            // Inferred role: emergency escape frame; original member name unknown.
};

static_assert(sizeof(GfGamePad) == 0x1a8, "");

} // namespace gf
