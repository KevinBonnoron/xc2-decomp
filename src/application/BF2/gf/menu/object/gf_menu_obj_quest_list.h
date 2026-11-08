#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace ui {
class UICtrlCursorSelect;
class UISelectObjList;
} // namespace ui

namespace gf {

class GfMenuCallContext;
class GfMenuItemList;
class GfMenuQuestList;
class GfMenuReferenceNumber;
class GfMenuReferenceQuest;

class GfMenuObjQuestList : public GfMenuObject {
public:
  GfMenuObjQuestList(u32 handle);
  ~GfMenuObjQuestList() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  struct OpenParam {
    u32 unknown00; // Role and original member name unknown.
  };

  static void registOpenParam(const OpenParam &param);
  void sendUpdateEvent(u32 handle, int param);
  void sendResumeEvent(u32 handle, int param);
  void sendSuspendEvent(u32 handle, int param);
  void changeView(u32 view);
  bool seqActivateSelect();
  bool seqEnd();
  bool seqActivateError();

  u8 _24[0x28 - 0x24];
  GfMenuQuestList *unknown28;        // Inferred role: quests; original member name unknown.
  GfMenuQuestList *unknown30;        // Inferred role: quests; original member name unknown.
  ui::UICtrlCursorSelect *unknown38; // Inferred role: cursor; original member name unknown.
  ui::UICtrlCursorSelect *unknown40; // Inferred role: cursor; original member name unknown.
  ui::UICtrlCursorSelect *unknown48; // Inferred role: cursor; original member name unknown.
  u8 _50[0x58 - 0x50];
  u32 unknown58; // Role and original member name unknown, cleared by the constructor.
  u32 unknown5c; // Role and original member name unknown, cleared by the constructor.
  u32 unknown60; // Role and original member name unknown, cleared by the constructor.
  u8 _64[0x68 - 0x64];
  ui::UISelectObjList *unknown68;                          // Inferred role: list objects; original member name unknown.
  ui::UISelectObjList *unknown70;                          // Inferred role: list objects; original member name unknown.
  ui::UISelectObjList *unknown78;                          // Inferred role: list objects; original member name unknown.
  ui::UISelectObjList *unknown80;                          // Inferred role: list objects; original member name unknown.
  ui::UISelectObjList *unknown88;                          // Inferred role: list objects; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown90;  // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown98;  // Inferred role: reference number; original member name unknown.
  GfMenuCallContext *unknown0a0;                           // Inferred role: call context; original member name unknown.
  GfMenuCallContext *unknown0a8;                           // Inferred role: call context; original member name unknown.
  GfMenuSequence<GfMenuObjQuestList, 8> unknown0b0;        // Inferred role: queued steps; original member name unknown.
  u32 unknown340;                                          // Role and original member name unknown, cleared by the constructor.
  u32 unknown344;                                          // Role and original member name unknown, cleared by the constructor.
  mm::mtl::IntrusivePtr<GfMenuReferenceQuest> unknown348;  // Inferred role: quest reference; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown350; // Inferred role: reference number; original member name unknown.
  GfMenuItemList *unknown358;                              // Inferred role: items; original member name unknown.
  bool unknown360;                                         // Role and original member name unknown, set to true by the constructor.
  u8 _361[0x364 - 0x361];
  u32 unknown364;  // Role and original member name unknown.
  bool unknown368; // Role and original member name unknown.
};

static_assert(offsetof(GfMenuObjQuestList, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjQuestList, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjQuestList, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjQuestList, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjQuestList, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjQuestList, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjQuestList, unknown5c) == 0x5c, "");
static_assert(offsetof(GfMenuObjQuestList, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjQuestList, unknown68) == 0x68, "");
static_assert(offsetof(GfMenuObjQuestList, unknown70) == 0x70, "");
static_assert(offsetof(GfMenuObjQuestList, unknown78) == 0x78, "");
static_assert(offsetof(GfMenuObjQuestList, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuObjQuestList, unknown88) == 0x88, "");
static_assert(offsetof(GfMenuObjQuestList, unknown90) == 0x90, "");
static_assert(offsetof(GfMenuObjQuestList, unknown98) == 0x98, "");
static_assert(offsetof(GfMenuObjQuestList, unknown0a0) == 0xa0, "");
static_assert(offsetof(GfMenuObjQuestList, unknown0a8) == 0xa8, "");
static_assert(offsetof(GfMenuObjQuestList, unknown0b0) == 0xb0, "");
static_assert(offsetof(GfMenuObjQuestList, unknown340) == 0x340, "");
static_assert(offsetof(GfMenuObjQuestList, unknown344) == 0x344, "");
static_assert(offsetof(GfMenuObjQuestList, unknown348) == 0x348, "");
static_assert(offsetof(GfMenuObjQuestList, unknown350) == 0x350, "");
static_assert(offsetof(GfMenuObjQuestList, unknown358) == 0x358, "");
static_assert(offsetof(GfMenuObjQuestList, unknown360) == 0x360, "");
static_assert(offsetof(GfMenuObjQuestList, unknown364) == 0x364, "");
static_assert(offsetof(GfMenuObjQuestList, unknown368) == 0x368, "");
static_assert(sizeof(GfMenuObjQuestList) == 0x370, "");

} // namespace gf
