#pragma once
#include <stddef.h>

#include "gf/data/gf_data_item.h"
#include "gf/data/gf_item_handle.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace mm {
namespace mtl {
class ReferenceObject;
} // namespace mtl
} // namespace mm

namespace ui {
class UIObjectAcc;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuIDList;
class GfMenuItemList;
struct MenuItemInfo;
class GfMenuReferenceItem;
class GfMenuReferenceNumber;

class GfMenuObjHanaCustom : public GfMenuObject {
public:
  class MainListener : public ui::UIObjectListener {
  public:
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x20 - 0x0c];
    GfMenuObjHanaCustom *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjHanaCustom(u32 handle);
  ~GfMenuObjHanaCustom() override;
  static void sendEvent(u32 handle, u32 type, u32 param);
  static int setFadeIn(u32 handle, u32 unknown);
  static int setFadeOut(u32 handle, u32 unknown);
  void initialize() override;
  void finalize() override;
  void update() override;
  static u32 convPartsId(u32 partsId);
  static bool isExpandParts(u32 partsId);
  static void refreshPlanLine(ui::UIObjectAcc &);
  static void setupMain(ui::UIObjectAcc &acc);
  static void updateItemList(GfMenuItemList *list, ItemType::Type type);
  u32 getPartsId();
  bool seqLineAnime();
  static void removeParts(u32 blade, u32 parts);
  static void expandCircuit(u32 blade, u32 parts);
  static void setupItemList(ui::UIObjectAcc &acc, GfMenuItemList *list, ui::UISelectObjList *selectList);
  static void equipParts(u32 blade, u32 parts, u32 partsId, GfItemHandle handle);
  static void setupPlan(ui::UIObjectAcc &acc, GfMenuIDList *list);
  static void setupItemInfo2(ui::UIObjectAcc &acc, mm::mtl::IntrusivePtr<GfMenuReferenceNumber> number, u32 blade);
  static u32 chkSameSlot(mm::mtl::FixedArray<GfMenuIDList *, 7> &lists, u32 parts);
  static bool refreshEquipListSub(ui::UIObjectAcc &acc, u32 type, u32 item, u32 index);
  static void refreshEquipList(ui::UIObjectAcc &acc, u32 blade);
  static void refreshPartsList(ui::UIObjectAcc &acc, mm::mtl::FixedArray<GfMenuIDList *, 7> &lists);
  static void refreshItemList(GfMenuItemList *list, ui::UISelectObjList *selectList, u32 type);
  static void setupItemInfo(ui::UIObjectAcc &acc, GfMenuItemList *list);
  static void getEquipItem(u32 blade, u32 parts, MenuItemInfo &info);
  static void refreshItemInfo(ui::UIObjectAcc &acc, GfMenuItemList *list, u32 type, u32 index);
  static void updatePartsList(ui::UIObjectAcc &acc, GfMenuIDList *list, ui::UISelectObjList *selectList, mm::mtl::FixedArray<GfMenuIDList *, 7> &lists);
  static void setupPartsList(ui::UIObjectAcc &acc, GfMenuIDList *list, ui::UISelectObjList *selectList, GfMenuReferenceItem *item, mm::mtl::FixedArray<GfMenuIDList *, 7> &lists);
  static u32 getEquipSlot(mm::mtl::FixedArray<GfMenuIDList *, 7> &lists, u32 parts);
  static void clearPLanSelect(ui::UIObjectAcc &acc);
  static u32 searchIdList(GfMenuIDList *list, u32 id);

  u8 _24[0x28 - 0x24];
  GfMenuIDList *unknown28;                           // Inferred role: identifiers; original member name unknown.
  GfMenuIDList *unknown30;                           // Inferred role: identifiers; original member name unknown.
  ui::UISelectObjList *unknown38;                    // Inferred role: list objects; original member name unknown.
  mm::mtl::ReferenceObject *unknown40;               // Inferred role: reference-counted object; type and original member name unknown.
  mm::mtl::FixedArray<GfMenuIDList *, 7> unknown48;  // Inferred role: identifiers; original member name unknown.
  u32 unknown80;                                     // Role and original member name unknown, cleared by the constructor.
  u32 unknown84;                                     // Role and original member name unknown, cleared by the constructor.
  GfMenuItemList *unknown88;                         // Inferred role: items; original member name unknown.
  ui::UISelectObjList *unknown90;                    // Inferred role: list objects; original member name unknown.
  mm::mtl::ReferenceObject *unknown98;               // Inferred role: reference-counted object; type and original member name unknown.
  GfMenuCallContext *unknown0a0;                     // Inferred role: call context; original member name unknown.
  GfMenuSequence<GfMenuObjHanaCustom, 8> unknown0a8; // Inferred role: queued steps; original member name unknown.
  u32 unknown338;                                    // Role and original member name unknown.
  u8 _33c[0x340 - 0x33c];
  GfMenuReferenceItem *unknown340; // Inferred role: reference item; original member name unknown.
  void *unknown348;                // Role, type and original member name unknown, cleared by the constructor.
  u32 unknown350;                  // Role and original member name unknown, cleared by the constructor.
  u8 _354[0x358 - 0x354];
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown358; // Inferred role: reference number; original member name unknown.
};

static_assert(offsetof(GfMenuObjHanaCustom::MainListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown88) == 0x88, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown90) == 0x90, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown98) == 0x98, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown0a0) == 0xa0, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown0a8) == 0xa8, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown338) == 0x338, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown340) == 0x340, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown348) == 0x348, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown350) == 0x350, "");
static_assert(offsetof(GfMenuObjHanaCustom, unknown358) == 0x358, "");
static_assert(sizeof(GfMenuObjHanaCustom) == 0x360, "");

} // namespace gf
