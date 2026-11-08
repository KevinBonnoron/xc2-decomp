#pragma once
#include <stddef.h>

#include "gf/game/quest/gf_quest_id.h"
#include "gf/menu/adapter/gf_menu_adapter.h"
#include "gf/menu/gf_menu_reference_quest.h"
#include "gf/menu/list/gf_menu_quest_list.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace ui {
class UIObjectPlugin;
} // namespace ui

namespace gf {
class GfMenuReferenceNumber;

class GfMenuQuestAdapter : public GfMenuAdapter {
public:
  // Inferred role: update kind of a parameter; original type name unknown.
  enum unknown001 {
    unknown001_0, // Inferred role: text; original name unknown.
    unknown001_1, // Inferred role: number; original name unknown.
    unknown001_2, // Inferred role: icon; original name unknown.
    unknown001_3, // Inferred role: task log text; original name unknown.
    unknown001_4, // Inferred role: reward text; original name unknown.
    unknown001_5, // Inferred role: display; original name unknown.
  };

  // Inferred role: parameter shown by the adapter; original type name unknown.
  enum unknown002 {
    unknown002_0 = 0,   // Inferred role: quest title text; original name unknown.
    unknown002_1 = 1,   // Inferred role: quest summary text; original name unknown.
    unknown002_2 = 2,   // Inferred role: quest result text; original name unknown.
    unknown002_3 = 3,   // Inferred role: first needed character icon; original name unknown.
    unknown002_15 = 15, // Inferred role: first needed field skill text; original name unknown.
    unknown002_16 = 16, // Inferred role: second needed field skill text; original name unknown.
    unknown002_17 = 17, // Inferred role: task condition text; original name unknown.
    unknown002_18 = 18, // Inferred role: first task log text; original name unknown.
    unknown002_22 = 22, // Inferred role: first task displayed count; original name unknown.
    unknown002_26 = 26, // Inferred role: first task count; original name unknown.
    unknown002_30 = 30, // Inferred role: first reward text; original name unknown.
    unknown002_38 = 38, // Inferred role: first reward number; original name unknown.
    unknown002_46 = 46, // Inferred role: current task log text; original name unknown.
    unknown002_47 = 47, // Inferred role: current task displayed count; original name unknown.
    unknown002_48 = 48, // Inferred role: current task count; original name unknown.
    unknown002_49 = 49, // Inferred role: current task weather; original name unknown.
    unknown002_50 = 50, // Inferred role: current task time zone; original name unknown.
    unknown002_51 = 51, // Inferred role: first current task time zone icon; original name unknown.
    unknown002_52 = 52, // Inferred role: second current task time zone icon; original name unknown.
    unknown002_57 = 57, // Inferred role: quest icon; original name unknown.
    unknown002_58 = 58, // Inferred role: cleared child quest number; original name unknown.
  };

  class IConverter {
  public:
    virtual ~IConverter() {}
    virtual void getQuestID(QuestID &quest) = 0;
  };

  class ListConverter : public IConverter {
  public:
    ListConverter(GfMenuQuestList *list, int listIndex) : list(list), listIndex(listIndex) { list->addRef(); }
    ~ListConverter() override { mm::mtl::safeRelease(list); }
    void getQuestID(QuestID &quest) override;

    GfMenuQuestList *list;
    int listIndex;
  };

  class ReferenceConverter : public IConverter {
  public:
    ReferenceConverter(mm::mtl::IntrusivePtr<GfMenuReferenceQuest> reference) : reference(reference) {}
    ~ReferenceConverter() override { reference = nullptr; }
    void getQuestID(QuestID &quest) override;

    mm::mtl::IntrusivePtr<GfMenuReferenceQuest> reference;
  };

  GfMenuQuestAdapter(ui::UIObjectPlugin *plugin, bool isUpdateAlways);
  ~GfMenuQuestAdapter() override;
  static GfMenuQuestAdapter *create(u32 handle, QuestID quest, u32 type, bool isUpdateAlways);
  static void init(GfMenuQuestAdapter *adapter, QuestID quest, u32 type, u32 kind);
  static GfMenuQuestAdapter *createFromReference(u32 handle, mm::mtl::IntrusivePtr<GfMenuReferenceQuest> reference, u32 type, bool isUpdateAlways);
  static GfMenuQuestAdapter *createFromList(u32 handle, GfMenuQuestList *list, int listIndex, u32 type, bool isUpdateAlways);
  void update(const fw::UpdateInfo &info) override;
  bool getParamText(QuestID quest, u32 type, const char **text);
  bool getParamNumber(QuestID quest, u32 type, u32 &number, u32 &max);
  bool getParamIcon(QuestID quest, u32 type, u32 &icon);
  bool getParamTextColor(QuestID quest, u32 type, const char **text, const char **color);
  bool getParamRewardText(QuestID quest, u32 type, mm::mtl::FixStr<64> &text);
  bool getParamDisp(QuestID quest, u32 type);
  bool getQuestText(QuestID quest, u32 line, const char **text);
  bool getFaceIcon(u32 icon, u32 &image);
  u32 getTimeZoneIconNumber(int time, u32 zone);

  QuestID unknown30;                                      // Inferred role: quest; original member name unknown.
  u32 unknown34;                                          // Inferred role: parameter; original member name unknown.
  u32 unknown38;                                          // Inferred role: update kind; original member name unknown.
  bool unknown3c;                                         // Inferred role: update needed; original member name unknown.
  mm::mtl::FixStr<64> unknown40;                          // Inferred role: reward text; original member name unknown.
  IConverter *unknown88;                                  // Inferred role: converter; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown90; // Inferred role: task index reference; original member name unknown.
  int unknown98;                                          // Inferred role: task index; original member name unknown.
};

static_assert(offsetof(GfMenuQuestAdapter, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuQuestAdapter, unknown34) == 0x34, "");
static_assert(offsetof(GfMenuQuestAdapter, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuQuestAdapter, unknown3c) == 0x3c, "");
static_assert(offsetof(GfMenuQuestAdapter, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuQuestAdapter, unknown88) == 0x88, "");
static_assert(offsetof(GfMenuQuestAdapter, unknown90) == 0x90, "");
static_assert(offsetof(GfMenuQuestAdapter, unknown98) == 0x98, "");
static_assert(sizeof(GfMenuQuestAdapter) == 0xa0, "");

} // namespace gf
