#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuObjPartyForm : public GfMenuObject {
public:
  // Inferred role: one party member row, the member id and the adapters that show its data; original type name unknown.
  // Evidence: initialize (0x71004a64f8) builds it in a local (id at 0, GfMenuCharDataAdapter::create results stored at +0x30 into the vector at 8, size at 0x20)
  // and copies it to the context, 0x28 bytes per row.
  struct unknown004 {
    u32 unknown00;                                         // Inferred role: member id; original member name unknown.
    mm::mtl::FixedVector<class unknown140 *, 3> unknown08; // Inferred role: adapters; original member name unknown.
  };

  // Original type name from the mangled symbol _ZN2gf18GfMenuObjPartyForm10swapDriverEPNS0_13PtFormContextEjj (0x71004a74b0); original member names unknown.
  // Evidence: the listeners keep a pointer to the data at 0x28 of the object (initialize stores this + 0x28 at 0x71004a6570) and swapDriver takes it: driver rows at 0x00 (size at 0xc8),
  // the selected driver row at 0xd0 (DriverFormListener writes 0xffffffff there), gauge adapters at 0xe0 (size at 0xf8) and blade rows at 0x100 (size at 0x178; the constructor,
  // 0x71004a63b4 to 0x71004a63bc, clears the three sizes at the object offsets 0xf0, 0x120 and 0x1a0). The context goes on after 0x180 (BladeFormListener reads 0x180).
  struct PtFormContext {
    mm::mtl::FixedVector<unknown004, 5> unknown00; // Inferred role: driver rows; original member name unknown.
    int unknownd0;                                 // Inferred role: selected driver row, -1 when none (read sign-extended at 0x71004a78c8); original member name unknown.
    u8 _d4[0xd8 - 0xd4];
    u32 unknownd8; // Inferred role: driver whose blades are shown, set by the BladeFormListener event 0x21 (0x71004a7904); original member name unknown.
    u8 _dc[0xe0 - 0xdc];
    mm::mtl::FixedVector<class unknown140 *, 3> unknowne0; // Inferred role: gauge adapters; original member name unknown.
    mm::mtl::FixedVector<unknown004, 3> unknown100;        // Inferred role: blade rows; original member name unknown.
    u32 unknown180;                                        // Inferred role: selected blade row, 0xffffffff when none (BladeFormListener, 0x71004a7818); original member name unknown.
  };

  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;
  };

  class DriverFormListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u32 unknown0c; // Inferred role: state, 0 while no driver is picked and 1 while one is held for a swap; original member name unknown.
    u8 _10[0x20 - 0x10];
    GfMenuObjPartyForm *unknown20; // Inferred role: owner; original member name unknown.
    PtFormContext *unknown28;      // Inferred role: data of the owner; original member name unknown.
  };

  class BladeFormListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u32 unknown0c; // Inferred role: state, 0 while no blade is picked, 1 while one is held for a swap and 2 after the driver list was left; original member name unknown.
    int unknown10; // Inferred role: control that fades the blade list; original member name unknown.
    u8 _14[0x20 - 0x14];
    GfMenuObjPartyForm *unknown20; // Inferred role: owner; original member name unknown.
    PtFormContext *unknown28;      // Inferred role: data of the owner; original member name unknown.
  };

  GfMenuObjPartyForm(u32 handle);
  ~GfMenuObjPartyForm() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void selectDriver(u32 handle, u32 index, u32 state);
  static void selectBlade(u32 handle, u32 index, u32 state);
  static void swapDriver(PtFormContext *, u32, u32);
  static void swapBlade(PtFormContext *, u32, u32);

  u8 _24[0x28 - 0x24];
  PtFormContext unknown28; // Inferred role: party form data; original member name unknown.
};

static_assert(offsetof(GfMenuObjPartyForm::unknown004, unknown08) == 0x08, "");
static_assert(sizeof(GfMenuObjPartyForm::unknown004) == 0x28, "");
static_assert(offsetof(GfMenuObjPartyForm::PtFormContext, unknownd0) == 0xd0, "");
static_assert(offsetof(GfMenuObjPartyForm::PtFormContext, unknowne0) == 0xe0, "");
static_assert(offsetof(GfMenuObjPartyForm::PtFormContext, unknown100) == 0x100, "");
static_assert(offsetof(GfMenuObjPartyForm::DriverFormListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjPartyForm::DriverFormListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjPartyForm::DriverFormListener, unknown28) == 0x28, "");
static_assert(sizeof(GfMenuObjPartyForm::DriverFormListener) == 0x30, "");
static_assert(offsetof(GfMenuObjPartyForm::PtFormContext, unknownd8) == 0xd8, "");
static_assert(offsetof(GfMenuObjPartyForm::PtFormContext, unknown180) == 0x180, "");
static_assert(offsetof(GfMenuObjPartyForm::BladeFormListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjPartyForm::BladeFormListener, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuObjPartyForm::BladeFormListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjPartyForm::BladeFormListener, unknown28) == 0x28, "");
static_assert(sizeof(GfMenuObjPartyForm::BladeFormListener) == 0x30, "");
static_assert(offsetof(GfMenuObjPartyForm, unknown28) == 0x28, "");

} // namespace gf
