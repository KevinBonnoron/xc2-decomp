#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

constexpr u32 MSG_GAME_RIDE_EVENT = 0x1000030;

enum {
  RIDE_EVENT_RIDE_ON = 0,
  RIDE_EVENT_GET_DOWN = 1,
  RIDE_EVENT_GET_DOWN_FORCE = 2,
};

struct MsgGameRideEvent : fw::Message {
  explicit MsgGameRideEvent(u32 event) : fw::Message(MSG_GAME_RIDE_EVENT, 0), unknown08(event) {}

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
  void gevPartyReturnFieldState(u32 state) override;
  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void procMsgGameRideEvent(fw::MessageObject *sender, MsgGameRideEvent &message);

  GF_OBJ_HANDLE *unknown28; // Inferred role: vehicle; original member name unknown.
  GF_OBJ_HANDLE *unknown30; // Inferred role: rider; original member name unknown.
};

static_assert(offsetof(GfGameRide, unknown28) == 0x28, "");
static_assert(offsetof(GfGameRide, unknown30) == 0x30, "");
static_assert(sizeof(GfGameRide) == 0x38, "");

} // namespace gf
