#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {
class GfMenuCallContext;
class GfMenuDriverList;
class GfMenuReferenceNumber;

class GfMenuObjPartyForm3 : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjPartyForm3 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjPartyForm3 *unknown20; // Inferred role: owner; original member name unknown.
  };

  class BGListener : public ui::UIObjectListener {
  public:
    BGListener(GfMenuObjPartyForm3 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];            // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjPartyForm3 *unknown20; // Inferred role: owner; original member name unknown.
  };

  class DriverSelectListener : public ui::UIObjectListener {
  public:
    DriverSelectListener(GfMenuObjPartyForm3 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];            // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjPartyForm3 *unknown20; // Inferred role: owner; original member name unknown.
  };

  bool seqWaitOpenEnd();
  struct OpenParam {
    u16 unknown00; // Role and original member name unknown.
  };

  GfMenuObjPartyForm3(u32 handle);
  ~GfMenuObjPartyForm3() override;
  static void registOpenParam(const OpenParam &param);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;
  static void setupBGLayout(ui::UIObjectAcc &, u32, bool);
  static void setupDriverSelect(ui::UIObjectAcc &acc, GfMenuDriverList *list, u32 first, u32 second, mm::mtl::FixedArray<mm::mtl::IntrusivePtr<GfMenuReferenceNumber>, 7> &numbers);
  static void setupDriverLayout(ui::UIObjectAcc &acc, u32 first, u32 second, mm::mtl::FixedArray<mm::mtl::IntrusivePtr<GfMenuReferenceNumber>, 7> &numbers, u32 mode);
  void refreshRemoveAddOperation(u32 handle, int index);
  bool seqAnnounceChange();

  u8 _24[0x28 - 0x24];
  GfMenuDriverList *unknown28; // Inferred role: drivers; original member name unknown.
  u16 unknown30;               // Role and original member name unknown, cleared by the constructor.
  u8 _32[0x34 - 0x32];
  u32 unknown34;  // Inferred role: party member count; original member name unknown.
  u32 unknown38;  // Role and original member name unknown, cleared by the constructor.
  u32 unknown3c;  // Role and original member name unknown, cleared by the constructor.
  int unknown40;  // Inferred role: pending slot, -1 when none; original member name unknown.
  bool unknown44; // Role and original member name unknown, cleared by the constructor.
  u8 _45[0x48 - 0x45];
  mm::mtl::FixedArray<mm::mtl::IntrusivePtr<GfMenuReferenceNumber>, 7> unknown48; // Inferred role: party member numbers; original member name unknown.
  GfMenuSequence<GfMenuObjPartyForm3, 8> unknown80;                               // Inferred role: queued steps; original member name unknown.
  GfMenuCallContext *unknown310;                                                  // Inferred role: announce call context; original member name unknown.
  bool unknown318;                                                                // Inferred role: unused, true at start; original member name unknown.
  bool unknown319;                                                                // Role and original member name unknown, cleared by the constructor.
  u8 _31a[0x320 - 0x31a];
};

static_assert(offsetof(GfMenuObjPartyForm3, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown34) == 0x34, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown44) == 0x44, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuObjPartyForm3::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjPartyForm3::BGListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjPartyForm3::MainListener) == 0x28, "");
static_assert(sizeof(GfMenuObjPartyForm3::BGListener) == 0x28, "");
static_assert(offsetof(GfMenuObjPartyForm3::DriverSelectListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjPartyForm3::DriverSelectListener) == 0x28, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown310) == 0x310, "");
static_assert(offsetof(GfMenuObjPartyForm3, unknown318) == 0x318, "");
static_assert(sizeof(GfMenuObjPartyForm3) == 0x320, "");

} // namespace gf
