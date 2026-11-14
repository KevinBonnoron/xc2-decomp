#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace mm {
struct Col4;
} // namespace mm

namespace gf {

class GfMenuObjFade : public GfMenuObject {
public:
  class FadeListener : public ui::UIObjectListener {
  public:
    FadeListener(GfMenuObjFade *owner) : unknown0c(0), unknown10(0), _14(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u32 unknown0c; // Inferred role: fade layer index, sent back as the parameter of the finish event; original member name unknown.
    int unknown10; // Inferred role: running alpha control, -1 when none; original member name unknown.
    u8 _14[0x20 - 0x14];
    GfMenuObjFade *unknown20; // Inferred role: owner; original member name unknown.
  };

  class LoadingListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjFade *unknown20; // Inferred role: owner; original member name unknown.
  };

  struct StartParam {
    u8 unknown00;  // Inferred role: fade layer index (IMG_fade%02d); original member name unknown.
    u16 unknown02; // Inferred role: event parameter, copied as is; original member name unknown.
    f32 unknown04; // Inferred role: scaled by 255 into an event parameter; original member name unknown.
    f32 unknown08; // Inferred role: scaled by 255 into an event parameter; original member name unknown.
    f32 unknown0c; // Inferred role: scaled by 255 into an event parameter; original member name unknown.
    f32 unknown10; // Inferred role: scaled by 255 into an event parameter; original member name unknown.
  };

  GfMenuObjFade(u32 handle);
  ~GfMenuObjFade() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void dispLoading(bool disp, u16 type);
  static void dispSaving(bool disp, u16 type);
  static void start(const StartParam &param);
  static void getFadeColor(u8 type, mm::Col4 &color);

  u32 unknown24; // Role and original member name unknown, zeroed by the constructor.
  s8 unknown28;  // Inferred role: loading display count; original member name unknown.
};

static_assert(offsetof(GfMenuObjFade::FadeListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjFade::FadeListener, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjFade::FadeListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjFade::FadeListener) == 0x28, "");
static_assert(offsetof(GfMenuObjFade::LoadingListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjFade::StartParam, unknown02) == 0x02, "");
static_assert(offsetof(GfMenuObjFade::StartParam, unknown04) == 0x04, "");
static_assert(offsetof(GfMenuObjFade::StartParam, unknown10) == 0x10, "");
static_assert(sizeof(GfMenuObjFade::StartParam) == 0x14, "");

static_assert(offsetof(GfMenuObjFade, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjFade, unknown28) == 0x28, "");
static_assert(sizeof(GfMenuObjFade) == 0x30, "");

} // namespace gf
