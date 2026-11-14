#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuCallContext;

class GfMenuObjButtonChallenge : public GfMenuObject {
public:
  // Layout from the start function (0x710041fe5c) that reads it; original member names unknown.
  struct ChallengeParam {
    u16 unknown00; // Role and original member name unknown.
    u16 unknown02; // Role and original member name unknown.
    u16 unknown04; // Role and original member name unknown.
    u16 unknown06; // Role and original member name unknown.
  };

  // Inferred role: running challenge data kept in m_ChallengeData and copied by the main listener; original type name unknown.
  struct unknown003 {
    f32 unknown00; // Inferred role: speed of the ring; original member name unknown.
    u16 unknown04; // Inferred role: ring size; original member name unknown.
    u16 unknown06; // Inferred role: size of the success range; original member name unknown.
    u16 unknown08; // Inferred role: size of the perfect range; original member name unknown.
    u8 _0a[0x0c - 0x0a];
  };

  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjButtonChallenge *owner) : unknown0c(0), unknown10(0), unknown14(0), unknown18(0), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u32 unknown0c; // Inferred role: state; original member name unknown.
    int unknown10; // Inferred role: running control; original member name unknown.
    u32 unknown14; // Inferred role: timer; original member name unknown.
    int unknown18; // Inferred role: result, 0 miss, 1 good and 2 perfect; original member name unknown.
    u8 _1c[0x20 - 0x1c];
    GfMenuObjButtonChallenge *unknown20; // Inferred role: owner; original member name unknown.
    unknown003 unknown28;                // Inferred role: copy of the challenge data; original member name unknown.
    u8 _34[0x38 - 0x34];                 // Not initialized by the constructor; original members unknown.
  };

  GfMenuObjButtonChallenge(u32 handle);
  ~GfMenuObjButtonChallenge() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static bool start(GfMenuCallContext *context, const ChallengeParam &param);
  static void cancel(GfMenuCallContext *context);

  static unknown003 m_ChallengeData;
};

static_assert(sizeof(GfMenuObjButtonChallenge::unknown003) == 0xc, "");
static_assert(offsetof(GfMenuObjButtonChallenge::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjButtonChallenge::MainListener, unknown28) == 0x28, "");
static_assert(sizeof(GfMenuObjButtonChallenge::MainListener) == 0x38, "");

} // namespace gf
