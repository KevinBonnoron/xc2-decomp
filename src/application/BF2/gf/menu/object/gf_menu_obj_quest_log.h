#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class ReferenceObject;
} // namespace mtl
} // namespace mm

namespace gf {

class GfMenuCallContext;
class GfMenuReferenceItem;
class GfMenuReferenceNumber;
class GfMenuReferenceQuest;
struct QuestID;
struct QuestTaskParam;

class GfMenuObjQuestLog : public GfMenuObject {
public:
  GfMenuObjQuestLog(u32 handle);
  ~GfMenuObjQuestLog() override;
  // Inferred helper: fades out the title text and an optional subtitle child; original name unknown.
  void unknown004(const char *sub) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown00 = 0.2f;
    param.unknown08 = 2;
    param.unknown14 = 2;
    GfMenuObjUtil::startCtrl(unknown18, param, "TXT_title");
    if (sub != nullptr) {
      GfMenuObjUtil::startCtrl(unknown18, param, sub);
    }
  }

  // Inferred helper: fades in a title child; original name unknown.
  void unknown005(const char *child) {
    GfMenuObjUtil::CtrlParam param;
    param.unknown00 = 0.2f;
    param.unknown08 = 1;
    GfMenuObjUtil::startCtrl(unknown18, param, child);
  }

  static void changeActiveQuest();
  static void updateTask();
  static void completeTask(const QuestTaskParam &param);
  static void closeLog();
  static void openLog();
  void setupLogClear();
  u32 nextTaskIndex(u32 index);
  void setupLogItem();
  bool seqLogNextEnd();
  bool seqLogNextWaitInfo();
  bool seqLogStart();
  bool seqLogIn();
  bool seqLogOpen();
  bool seqLogClose();
  bool seqLogCloseEnd();
  bool seqLogTaskComplete();
  bool seqOrderStart();
  bool seqCompleteStart();
  bool seqOrderWait();
  bool seqOrderWaitCtrl();
  bool seqCompleteWait();
  bool seqCompleteWaitCtrl();
  bool seqTitleEndWait();
  bool seqTitleFadeInScenario();
  bool seqTitleFadeInText();
  bool seqLogOut();
  bool seqTitleFadeOutScenario();
  bool seqTitleFadeInNormal();
  bool seqTitleFadeOutNormal();
  bool seqTitleFadeOutText();
  void initialize() override;
  void finalize() override;
  static void order(GfMenuCallContext *context, QuestID quest);
  static void complete(GfMenuCallContext *context, QuestID quest);
  static void lockLogOpen();
  static void unlockLogOpen();

  u8 _24[0x28 - 0x24];
  mm::mtl::IntrusivePtr<GfMenuReferenceQuest> unknown28;  // Inferred role: quest reference; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceQuest> unknown30;  // Inferred role: quest reference; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceQuest> unknown38;  // Inferred role: quest reference; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown40; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown48; // Inferred role: reference number; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceItem> unknown50;   // Inferred role: reference item; original member name unknown.
  bool unknown58;                                         // Role and original member name unknown, cleared by the constructor.
  bool unknown59;                                         // Inferred role: log open flag; original member name unknown.
  bool unknown5a;                                         // Inferred role: log out after close request flag; original member name unknown.
  bool unknown5b;                                         // Inferred role: detail link shown flag; original member name unknown.
  u8 _5c[0x60 - 0x5c];
  GfMenuSequence<GfMenuObjQuestLog, 8> unknown60;  // Inferred role: title steps; original member name unknown.
  GfMenuSequence<GfMenuObjQuestLog, 8> unknown2f0; // Inferred role: log steps; original member name unknown.
  GfMenuSequence<GfMenuObjQuestLog, 8> unknown580; // Inferred role: order and complete steps; original member name unknown.
  bool unknown810;                                 // Inferred role: control started flag of the multi-step sequences; original member name unknown.
  u8 _811[0x814 - 0x811];
  int unknown814;  // Inferred role: control id of the log info; original member name unknown.
  bool unknown818; // Inferred role: order activation request flag; original member name unknown.
  u8 _819[0x820 - 0x819];
  mm::mtl::ReferenceObject *unknown820; // Inferred role: reference-counted object; type and original member name unknown.
  u32 unknown828;                       // Inferred role: task count of the quest; original member name unknown.
  u32 unknown82c;                       // Role and original member name unknown, cleared by the constructor.
};

static_assert(offsetof(GfMenuObjQuestLog, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown40) == 0x40, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown48) == 0x48, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown50) == 0x50, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown58) == 0x58, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown59) == 0x59, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown5b) == 0x5b, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown2f0) == 0x2f0, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown580) == 0x580, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown580.unknown278) == 0x7f8, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown810) == 0x810, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown814) == 0x814, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown818) == 0x818, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown820) == 0x820, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown828) == 0x828, "");
static_assert(offsetof(GfMenuObjQuestLog, unknown82c) == 0x82c, "");
static_assert(sizeof(GfMenuObjQuestLog) == 0x830, "");
} // namespace gf
