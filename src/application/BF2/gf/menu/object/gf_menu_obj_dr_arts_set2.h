#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class ReferenceObject;
} // namespace mtl
} // namespace mm

namespace ui {
class UIObjectAcc;
} // namespace ui

namespace gf {

class GfMenuArtsList;
class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuItemList;
class GfMenuReferenceNumber;

class GfMenuObjDrArtsSet2 : public GfMenuObject {
public:
  GfMenuObjDrArtsSet2(u32 handle);
  ~GfMenuObjDrArtsSet2() override;
  // Inferred role: result of checkArtsLvUp, 0 when the arts can be leveled up, 4 at the maximum level and 5 without enough WP; original type name unknown.
  enum unknown001 {
    UNKNOWN001_UNKNOWN_0 = 0,
    UNKNOWN001_UNKNOWN_4 = 4,
    UNKNOWN001_UNKNOWN_5 = 5,
  };

  static unknown001 checkArtsLvUp(u32 driver, u32 weaponType, u32 arts, u32 level);
  static unknown001 checkArtsLvUp(u32 driver, u32 weaponType, GfMenuArtsList *list, u32 index);
  static void refreshParam(ui::UIObjectAcc &acc, u32 driver, u32 weaponType, GfMenuArtsList *list, u32 index);
  static void refreshArtsNeedWP(ui::UIObjectAcc &acc, GfMenuArtsList *list, u32 driver, u32 weaponType);
  static void refreshLvUpWpn(ui::UIObjectAcc &acc, u32 driver, const mm::mtl::FixedVector<u32, 27> &weaponTypes);
  static void setupArtsDetail(ui::UIObjectAcc &acc, GfMenuArtsList *list, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number);
  bool seqReturnWeaponSelect();
  bool seqSelectItem();
  bool seqConfirmItem();
  static void moveRight(ui::UIObjectAcc &acc);
  static void moveLeft(ui::UIObjectAcc &acc);
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle, u32 dir, const char *child);
  static int setFadeOut(u32 handle, u32 dir, const char *child);
  static void setFadeInBG(u32 handle);
  static void setFadeOutBG(u32 handle);
  void initialize() override;
  void finalize() override;
  void update() override;

  u8 _24[0x28 - 0x24];
  mm::mtl::FixedVector<u32, 27> unknown28;                 // Inferred role: weapon types; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown0a0; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown0a8; // Inferred role: reference number; original member name unknown.
  u8 _b0[0xb8 - 0xb0];
  mm::mtl::ReferenceObject *unknown0b8; // Inferred role: reference-counted object; type and original member name unknown.
  GfMenuCallContext *unknown0c0;        // Inferred role: call context; original member name unknown.
  GfMenuCallContext *unknown0c8;        // Inferred role: call context; original member name unknown.
  int unknown0d0;                       // Role and original member name unknown, set to -1 by the constructor.
  int unknown0d4;                       // Role and original member name unknown, set to -1 by the constructor.
  GfMenuArtsList *unknown0d8;           // Inferred role: arts; original member name unknown.
  bool unknown0e0;                      // Role and original member name unknown, cleared by the constructor.
  u8 _e1[0xe8 - 0xe1];
  GfMenuBladeList *unknown0e8;                       // Inferred role: blades; original member name unknown.
  GfMenuItemList *unknown0f0;                        // Inferred role: items; original member name unknown.
  GfMenuSequence<GfMenuObjDrArtsSet2, 4> unknown0f8; // Inferred role: queued steps; original member name unknown.
  bool unknown258;                                   // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjDrArtsSet2, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjDrArtsSet2, unknown0a0) == 0xa0, "");
static_assert(offsetof(GfMenuObjDrArtsSet2, unknown0a8) == 0xa8, "");
static_assert(offsetof(GfMenuObjDrArtsSet2, unknown0b8) == 0xb8, "");
static_assert(offsetof(GfMenuObjDrArtsSet2, unknown0c0) == 0xc0, "");
static_assert(offsetof(GfMenuObjDrArtsSet2, unknown0c8) == 0xc8, "");
static_assert(offsetof(GfMenuObjDrArtsSet2, unknown0d0) == 0xd0, "");
static_assert(offsetof(GfMenuObjDrArtsSet2, unknown0d4) == 0xd4, "");
static_assert(offsetof(GfMenuObjDrArtsSet2, unknown0d8) == 0xd8, "");
static_assert(offsetof(GfMenuObjDrArtsSet2, unknown0e0) == 0xe0, "");
static_assert(offsetof(GfMenuObjDrArtsSet2, unknown0e8) == 0xe8, "");
static_assert(offsetof(GfMenuObjDrArtsSet2, unknown0f0) == 0xf0, "");
static_assert(offsetof(GfMenuObjDrArtsSet2, unknown0f8) == 0xf8, "");
static_assert(offsetof(GfMenuObjDrArtsSet2, unknown258) == 0x258, "");
static_assert(sizeof(GfMenuObjDrArtsSet2) == 0x260, "");

} // namespace gf
