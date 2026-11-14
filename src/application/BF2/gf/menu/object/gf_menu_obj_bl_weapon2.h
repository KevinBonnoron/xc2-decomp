#pragma once
#include <stddef.h>

#include "gf/menu/adapter/gf_menu_weapon_adapter.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace ui {
class UIObjectAcc;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuItemList;
class GfMenuReferenceNumber;

class GfMenuObjBlWeapon2 : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjBlWeapon2 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBlWeapon2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ItemSelectListener : public ui::UIObjectListener {
  public:
    ItemSelectListener(GfMenuObjBlWeapon2 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBlWeapon2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  class WeaponListener : public ui::UIObjectListener {
  public:
    WeaponListener(GfMenuObjBlWeapon2 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBlWeapon2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  class ChrChangeListener : public ui::UIObjectListener {
  public:
    ChrChangeListener(GfMenuObjBlWeapon2 *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjBlWeapon2 *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjBlWeapon2(u32 handle);
  ~GfMenuObjBlWeapon2() override;

  struct OpenParam {
    u16 unknown00; // Inferred role: open mode; original member name unknown.
    u32 unknown04; // Inferred role: weapon; original member name unknown.
  };

  // Inferred role: layer parameter built from OpenParam; original type name unknown.
  struct unknown002 {
    u16 unknown00; // Inferred role: open mode; original member name unknown.
    u16 unknown02; // Inferred role: weapon; original member name unknown.
  };

  static void registOpenParam(const OpenParam &param);
  static void openForShop(u32 weapon);
  static bool attach(GfMenuCallContext *context);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle);
  static int setFadeOut(u32 handle);
  static bool isSameWeapon(u32 blade, u32 chip);
  static bool isDownWeapon(u32 blade, u32 chip);
  void initialize() override;
  void finalize() override;
  void update() override;
  void closeCharChange();
  void openCharChange();
  bool seqStart();
  bool seqSrcLeave();
  bool seqSrcAppear();
  bool seqSrcEffect();
  static void setupWeapon(ui::UIObjectAcc &acc, GfMenuItemList *list, GfMenuWeaponAdapter::ReferenceChip &chip);
  static void setupItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *selectList, u32 isShop, u32 shop);
  bool seqDstResume();
  bool seqEnd();

  u8 _24[0x28 - 0x24];
  GfMenuItemList *unknown28;                              // Inferred role: blade chips; original member name unknown.
  ui::UISelectObjList *unknown30;                         // Inferred role: chip objects; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown38; // Inferred role: reference number; original member name unknown.
  GfMenuCallContext *unknown40;                           // Inferred role: call context; original member name unknown.
  u32 unknown48;                                          // Inferred role: state of the call context dialog; original member name unknown.
  u8 _4c[0x50 - 0x4c];
  GfMenuCallContext *unknown50;                    // Inferred role: call context; original member name unknown.
  GfMenuSequence<GfMenuObjBlWeapon2, 8> unknown58; // Inferred role: weapon change steps; original member name unknown.
  bool unknown2e8;                                 // Inferred role: control started flag; original member name unknown.
  u8 _2e9[0x2ec - 0x2e9];
  u32 unknown2ec;              // Role and original member name unknown, cleared by the constructor.
  u32 unknown2f0;              // Role and original member name unknown, cleared by the constructor.
  u32 unknown2f4;              // Inferred role: shop; original member name unknown.
  GfMenuBladeList *unknown2f8; // Inferred role: blades; original member name unknown.
  bool unknown300;             // Role and original member name unknown, cleared by the constructor.
  u8 _301[0x308 - 0x301];
};

static_assert(offsetof(GfMenuObjBlWeapon2::OpenParam, unknown04) == 0x04, "");
static_assert(sizeof(GfMenuObjBlWeapon2::OpenParam) == 0x08, "");
static_assert(offsetof(GfMenuObjBlWeapon2::unknown002, unknown02) == 0x02, "");
static_assert(sizeof(GfMenuObjBlWeapon2::unknown002) == 0x04, "");
static_assert(offsetof(GfMenuObjBlWeapon2::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjBlWeapon2::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjBlWeapon2::ItemSelectListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjBlWeapon2::ItemSelectListener) == 0x28, "");
static_assert(offsetof(GfMenuObjBlWeapon2::WeaponListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjBlWeapon2::WeaponListener) == 0x28, "");
static_assert(offsetof(GfMenuObjBlWeapon2::ChrChangeListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjBlWeapon2::ChrChangeListener) == 0x28, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown2e8) == 0x2e8, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown2ec) == 0x2ec, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown2f0) == 0x2f0, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown2f4) == 0x2f4, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown2f8) == 0x2f8, "");
static_assert(offsetof(GfMenuObjBlWeapon2, unknown300) == 0x300, "");
static_assert(sizeof(GfMenuObjBlWeapon2) == 0x308, "");

} // namespace gf
