#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

constexpr u32 EVENT_UNKNOWN_16777264 = 0x1000030; // Inferred role: msg game ride event; original name unknown.

enum {
  RIDE_EVENT_UNKNOWN_0 = 0, // Inferred role: ride event ride on; original name unknown.
  RIDE_EVENT_UNKNOWN_1 = 1, // Inferred role: ride event get down; original name unknown.
  RIDE_EVENT_UNKNOWN_2 = 2, // Inferred role: ride event get down force; original name unknown.
};

struct MsgGameRideEvent : fw::Message {
  explicit MsgGameRideEvent(u32 event) : fw::Message(EVENT_UNKNOWN_16777264, 0), unknown08(event) {}

  u32 unknown08; // Inferred role: ride event type; original member name unknown.
};

class GfGameRide : public mm::mtl::PtrSingleton<GfGameRide>, public IGfEvent, public fw::MessageObject {
public:
  GfGameRide();
  ~GfGameRide();
  static void build(const GfSetupParam &param);
  void setup();
  static void destroy();
  void cleanup();
  static void setRideOn(bool isRide);
  void rideOn();
  void getDown(GF_OBJ_HANDLE *handle);
  static bool isRideOnPair();
  static bool testRideOn();
  static bool isRider(GF_OBJ_HANDLE *handle);
  void resetHandles();
  static bool isVehicle(GF_OBJ_HANDLE *handle);
  // The order of the overrides follows the game's vtable (0x710118b510).
  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void gevPartyReturnFieldState(u32 state) override;
  void procMsgGameRideEvent(fw::MessageObject *sender, MsgGameRideEvent &message);

  GF_OBJ_HANDLE *unknown28; // Inferred role: vehicle; original member name unknown.
  GF_OBJ_HANDLE *unknown30; // Inferred role: rider; original member name unknown.
};

static_assert(offsetof(GfGameRide, unknown28) == 0x28, "");
static_assert(offsetof(GfGameRide, unknown30) == 0x30, "");
static_assert(sizeof(GfGameRide) == 0x38, "");

} // namespace gf
