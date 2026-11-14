#pragma once
#include <stddef.h>

#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_reference_item.h"   // IWYU pragma: keep
#include "gf/menu/gf_menu_reference_number.h" // IWYU pragma: keep
#include "gf/menu/gf_menu_sequence.h"
#include "gf/util/gf_recipe_orb_util.h"
#include "mm_mtl/array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace mm {
namespace mtl {
class ReferenceObject;
} // namespace mtl
} // namespace mm

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuIDList;
class GfMenuItemList;

class GfMenuObjShop : public GfMenuObject {
public:
  struct OpenParam {
    u32 unknown00; // Inferred role: shop; original member name unknown.
  };

  class MainListener : public ui::UIObjectListener {
  public:
    MainListener(GfMenuObjShop *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjShop *unknown20; // Inferred role: owner; original member name unknown.
  };

  class CommonListener : public ui::UIObjectListener {
  public:
    CommonListener(GfMenuObjShop *owner) : unknown0c(0), _10(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    int unknown0c; // Inferred role: control of the open and close fade; original member name unknown.
    u8 _10[0x1c - 0x10];
    GfMenuObjShop *unknown20; // Inferred role: owner; original member name unknown.
  };

  class OrbListListener : public ui::UIObjectListener {
  public:
    OrbListListener(GfMenuObjShop *owner) : _0c(), unknown20(owner) {}
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    u8 _0c[0x1c - 0x0c];
    GfMenuObjShop *unknown20; // Inferred role: owner; original member name unknown.
  };

  GfMenuObjShop(u32 handle);
  ~GfMenuObjShop() override;
  static void open(GfMenuCallContext *context, const OpenParam &param);
  static void close(GfMenuCallContext *context);
  static u32 getSellItemTypeMax();
  static void dispBlade(bool isDisp);
  void initialize() override;
  void finalize() override;
  void update() override;
  void refreshItemList();
  void sendEnableEvent(u32 handle);
  void sendExitEvent(u32 handle);
  void sendCloseEvent(u32 handle);
  void sendOpenEvent(u32 handle, int value);
  void sendReturnEvent(u32 handle, int value);
  void addCallContextResult(u32 type, u32 value);
  void reqRefreshItemList();
  void openOrbError(u32 error);
  bool seqWaitFSClose();
  bool seqEndDialog();
  bool seqIntervalSleep();
  bool seqWaitLoadBlWeapon();
  bool seqWaitEndBlWeapon();
  bool seqStartSleepFade();
  bool seqWaitSleepFade();
  bool seqStartLevelUp();
  bool seqEnd();
  u32 getShopSubLayer(u32 handle);
  u32 getShopSubActLayer(u32 handle);
  void openNumSelect(u32 owner, u32 value, bool isFlag);
  bool getExcTaskQuestAdditionalValue(u32 id, u32 &value);
  bool seqEndRecipeIndexOpen();
  void setFilterIndex();
  void refreshFilterIcon();
  static int getSpecialShop(u32 shop);
  static bool isShopWeapon(u32 shop);
  void setupExcItem();
  void setGuideText(u32 id);
  bool seqWaitExchange();
  void refreshExcReward();
  bool seqItemGet();
  bool seqStartRecipeIndexOpen();
  bool canGetExcTaskReward(u32 id);
  bool getExcTaskReward(u32 id, u32 &value, GfMenuItemList *list, bool &isHide);
  void setupIndex(u32 handle, const char *name, u32 count);
  void updateOrbRecipe();
  bool seqWaitOrbCreate();

  u32 unknown24; // Inferred role: shop id; original member name unknown.
  int unknown28; // Inferred role: shop kind; original member name unknown.
  u32 unknown2c; // Inferred role: shop icon; original member name unknown.
  u32 unknown30; // Inferred role: shop table id; original member name unknown.
  int unknown34; // Inferred role: special shop id; original member name unknown.
  u32 unknown38; // Inferred role: cleared when the shop opens; original member name unknown.
  u8 _3c[0x40 - 0x3c];
  ui::UISelectObjList *unknown40; // Inferred role: store item objects; original member name unknown.
  GfMenuItemList *unknown48;      // Inferred role: store or sell items; original member name unknown.
  ui::UISelectObjList *unknown50; // Inferred role: item objects; original member name unknown.
  bool unknown58;                 // Inferred role: sell mode flag; original member name unknown.
  bool unknown59;                 // Inferred role: item list refresh request; original member name unknown.
  u8 _5a[0x60 - 0x5a];
  mm::mtl::FixedVector<u32, 22> unknown60; // Inferred role: sell filters; original member name unknown.
  u32 unknownc0;                           // Inferred role: current sell filter index; original member name unknown.
  u8 _c4[0xc8 - 0xc4];
  ui::UICtrlCursorSelect *unknownc8; // Inferred role: item cursor; original member name unknown.
  u32 unknownd0;                     // Inferred role: number select owner; original member name unknown.
  u8 _d4[0xd8 - 0xd4];
  ui::UISelectObjList *unknownd8;                              // Inferred role: store item objects; original member name unknown.
  mm::mtl::ReferenceObject *unknowne0;                         // Inferred role: reference-counted object; type and original member name unknown.
  GfMenuItemList *unknowne8;                                   // Inferred role: orb items; original member name unknown.
  GfMenuItemList *unknownf0;                                   // Inferred role: orb recipe items; original member name unknown.
  RecipeInfo unknownf8;                                        // Inferred role: recipe of the orb item selected in the orb list; original member name unknown.
  mm::mtl::Array<u32> unknown130;                              // Inferred role: owned count of each page of the orb recipe items; original member name unknown.
  u32 unknown148;                                              // Inferred role: orb item to hand over; original member name unknown.
  u32 unknown14c;                                              // Inferred role: orb item sort index; original member name unknown.
  GfMenuIDList *unknown150;                                    // Inferred role: exchange task list; original member name unknown.
  GfMenuItemList *unknown158;                                  // Inferred role: exchange items; original member name unknown.
  GfMenuItemList *unknown160;                                  // Inferred role: items received; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown168[26]; // Inferred role: reference numbers shown by the texts; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceItem> unknown238;       // Inferred role: reference item shown by the orb texts; original member name unknown.
  bool unknown240;                                             // Inferred role: cloud sea inn flag pending; original member name unknown.
  u8 _241[0x248 - 0x241];
  GfMenuSequence<GfMenuObjShop, 8> unknown248; // Inferred role: shop steps; original member name unknown.
  int unknown4d8;                              // Inferred role: sleep interval frames; original member name unknown.
  bool unknown4dc;                             // Inferred role: sleep fade started flag; original member name unknown.
  u8 _4dd[0x4e0 - 0x4dd];
  u32 unknown4e0; // Inferred role: call result type; original member name unknown.
  int unknown4e4; // Inferred role: call result value; original member name unknown.
  u8 _4e8[0x4f0 - 0x4e8];
  mm::mtl::ReferenceObject *unknown4f0; // Inferred role: reference-counted object; type and original member name unknown.
  u32 unknown4f8;                       // Inferred role: dialog object; original member name unknown.
  u8 _4fc[0x500 - 0x4fc];
  int unknown500;                          // Inferred role: result of the last exchange, 1 done and 2 refused; original member name unknown.
  int unknown504;                          // Inferred role: unused, -1 after the constructor; original member name unknown.
  mm::mtl::ReferenceObject *unknown508[8]; // Inferred role: reference-counted objects; type and original member name unknown.
  QuestTaskParam unknown548;               // Inferred role: linked exchange quest task; original member name unknown.
  int unknown568;                          // Inferred role: exchange task index type; original member name unknown.
  u8 _56c[0x570 - 0x56c];
  GfMenuCallContext *unknown570; // Inferred role: blade weapon call context; original member name unknown.
  GfMenuCallContext *unknown578; // Inferred role: item get call context; original member name unknown.
};

static_assert(offsetof(GfMenuObjShop::MainListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjShop::MainListener) == 0x28, "");
static_assert(offsetof(GfMenuObjShop::CommonListener, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjShop::CommonListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjShop::CommonListener) == 0x28, "");
static_assert(offsetof(GfMenuObjShop::OrbListListener, unknown20) == 0x20, "");
static_assert(sizeof(GfMenuObjShop::OrbListListener) == 0x28, "");
static_assert(offsetof(GfMenuObjShop, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjShop, unknown2c) == 0x2c, "");
static_assert(offsetof(GfMenuObjShop, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjShop, unknown34) == 0x34, "");
static_assert(offsetof(GfMenuObjShop, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjShop, unknown14c) == 0x14c, "");
static_assert(offsetof(GfMenuObjShop, unknown150) == 0x150, "");
static_assert(offsetof(GfMenuObjShop, unknown168) == 0x168, "");
static_assert(offsetof(GfMenuObjShop, unknown548) == 0x548, "");
static_assert(offsetof(GfMenuObjShop, unknown568) == 0x568, "");
static_assert(offsetof(GfMenuObjShop, unknown59) == 0x59, "");
static_assert(offsetof(GfMenuObjShop, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjShop, unknownc0) == 0xc0, "");
static_assert(offsetof(GfMenuObjShop, unknown248) == 0x248, "");
static_assert(offsetof(GfMenuObjShop, unknown4d8) == 0x4d8, "");
static_assert(offsetof(GfMenuObjShop, unknown4f8) == 0x4f8, "");
static_assert(offsetof(GfMenuObjShop, unknown148) == 0x148, "");
static_assert(offsetof(GfMenuObjShop, unknown160) == 0x160, "");
static_assert(offsetof(GfMenuObjShop, unknown578) == 0x578, "");
static_assert(offsetof(GfMenuObjShop, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjShop, unknownd0) == 0xd0, "");
static_assert(offsetof(GfMenuObjShop, unknownd8) == 0xd8, "");
static_assert(offsetof(GfMenuObjShop, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjShop, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjShop, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjShop, unknownf8) == 0xf8, "");
static_assert(offsetof(GfMenuObjShop, unknown240) == 0x240, "");
static_assert(offsetof(GfMenuObjShop, unknown4dc) == 0x4dc, "");
static_assert(offsetof(GfMenuObjShop, unknown4e0) == 0x4e0, "");
static_assert(offsetof(GfMenuObjShop, unknown500) == 0x500, "");
static_assert(offsetof(GfMenuObjShop, unknown504) == 0x504, "");
static_assert(offsetof(GfMenuObjShop, unknown508) == 0x508, "");
static_assert(offsetof(GfMenuObjShop, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjShop, unknownc8) == 0xc8, "");
static_assert(offsetof(GfMenuObjShop, unknowne0) == 0xe0, "");
static_assert(offsetof(GfMenuObjShop, unknowne8) == 0xe8, "");
static_assert(offsetof(GfMenuObjShop, unknownf0) == 0xf0, "");
static_assert(offsetof(GfMenuObjShop, unknown130) == 0x130, "");
static_assert(offsetof(GfMenuObjShop, unknown158) == 0x158, "");
static_assert(offsetof(GfMenuObjShop, unknown238) == 0x238, "");
static_assert(offsetof(GfMenuObjShop, unknown4f0) == 0x4f0, "");
static_assert(offsetof(GfMenuObjShop, unknown570) == 0x570, "");
static_assert(sizeof(GfMenuObjShop) == 0x580, "");

} // namespace gf
