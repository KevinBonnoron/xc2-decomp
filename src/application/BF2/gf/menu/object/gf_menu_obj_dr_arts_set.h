#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UIObjectAcc;
class UICtrlCursorSelect;
class UICtrlSlideSelect;
class UISelectObjList;
} // namespace ui

namespace gf {
class GfMenuCallContext;
class GfMenuReferenceNumber;

class GfMenuObjDrArtsSet : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjDrArtsSet *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];           // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjDrArtsSet *unknown20; // Inferred role: owner; original member name unknown.
  };

  class WpnTypeListener : public ui::UIObjectListener {
  public:
    WpnTypeListener(GfMenuObjDrArtsSet *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];           // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjDrArtsSet *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ArtsListListener : public ui::UIObjectListener {
  public:
    ArtsListListener(GfMenuObjDrArtsSet *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];           // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjDrArtsSet *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ArtsDetailListener : public ui::UIObjectListener {
  public:
    ArtsDetailListener(GfMenuObjDrArtsSet *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];           // Actively zero-initialized unknown byte range, NOT padding; original name/role unknown.
    GfMenuObjDrArtsSet *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjDrArtsSet(u32 handle);
  ~GfMenuObjDrArtsSet() override;
  static bool attach(GfMenuCallContext *context);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  static void setupWpnType(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number);
  static void setupSlideSelect(ui::UIObjectAcc &acc, mm::mtl::FixedVector<u32, 27> &weaponTypes, ui::UISelectObjList *list);
  static void setupArtsList(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number);
  static void setupArtsDetail(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> wpnType, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> artsIndex);
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x28 - 0x24];
  ui::UISelectObjList *unknown28;                         // Inferred role: arts objects; original member name unknown.
  ui::UICtrlSlideSelect *unknown30;                       // Inferred role: weapon type slider; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown38; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown40; // Inferred role: reference number; original member name unknown.
  ui::UICtrlCursorSelect *unknown48;                      // Inferred role: arts cursor; original member name unknown.
  mm::mtl::FixedVector<u32, 27> unknown50;                // Inferred role: weapon types; original member name unknown.
  GfMenuCallContext *unknownc8;                           // Inferred role: call context; original member name unknown.
};

static_assert(offsetof(GfMenuObjDrArtsSet, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjDrArtsSet, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjDrArtsSet, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjDrArtsSet, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjDrArtsSet, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjDrArtsSet, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjDrArtsSet, unknownc8) == 0xc8, "");
static_assert(offsetof(GfMenuObjDrArtsSet::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjDrArtsSet::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjDrArtsSet::WpnTypeListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjDrArtsSet::WpnTypeListener) == 0x28, "");
static_assert(offsetof(GfMenuObjDrArtsSet::ArtsListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjDrArtsSet::ArtsListListener) == 0x28, "");
static_assert(offsetof(GfMenuObjDrArtsSet::ArtsDetailListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjDrArtsSet::ArtsDetailListener) == 0x28, "");

} // namespace gf
