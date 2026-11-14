#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_reference_number.h"
#include "gf/menu/gf_menu_reference_quest.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"
#include "ui/event/ui_object_listener.h"

namespace gf {

class GfMenuCallContext;
class GfMenuItemList;

class GfMenuObjQuestReward : public GfMenuObject {
public:
  struct OpenParam {
    OpenParam() : unknown08(0), unknown0c(0) {}

    mm::mtl::IntrusivePtr<GfMenuReferenceQuest> unknown00;  // Inferred role: quest of the reward; original member name unknown.
    u32 unknown08;                                          // Inferred role: object handle of the reward layout; original member name unknown.
    u32 unknown0c;                                          // Role and original member name unknown.
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown10; // Inferred role: mission of the reward; original member name unknown.
  };

  class RewardListener : public ui::UIObjectListener {
  public:
    RewardListener() {
      unknown0c = unknown142();
      unknown20 = nullptr;
    }
    void reciveEvent(const ui::EventData &event, u32 handle) override;

    unknown142 unknown0c;                                   // Inferred role: work values, unused by this listener; original member name unknown.
    GfMenuObjQuestReward *unknown20;                        // Inferred role: owner, always null; original member name unknown.
    GfMenuItemList *unknown28;                              // Inferred role: reward items; original member name unknown.
    mm::mtl::IntrusivePtr<GfMenuReferenceQuest> unknown30;  // Inferred role: quest of the reward; original member name unknown.
    mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown38; // Inferred role: mission of the reward; original member name unknown.
    int unknown40;                                          // Inferred role: reward kind, 1 for a mission; original member name unknown.
    bool unknown44;                                         // Inferred role: animated open flag; original member name unknown.
  };

  GfMenuObjQuestReward(u32 handle);
  ~GfMenuObjQuestReward() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  static void create(GfMenuCallContext *context, const OpenParam &param, bool isAnim);
  static void open(GfMenuCallContext *context, bool isAnim);
  static void close(GfMenuCallContext *context, bool isAnim);
};

static_assert(offsetof(GfMenuObjQuestReward::OpenParam, unknown08) == 0x08, "");
static_assert(offsetof(GfMenuObjQuestReward::OpenParam, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuObjQuestReward::OpenParam, unknown10) == 0x10, "");
static_assert(sizeof(GfMenuObjQuestReward::OpenParam) == 0x18, "");
static_assert(offsetof(GfMenuObjQuestReward::RewardListener, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuObjQuestReward::RewardListener, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjQuestReward::RewardListener, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjQuestReward::RewardListener, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjQuestReward::RewardListener, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjQuestReward::RewardListener, unknown44) == 0x44, "");
static_assert(sizeof(GfMenuObjQuestReward::RewardListener) == 0x48, "");

} // namespace gf
