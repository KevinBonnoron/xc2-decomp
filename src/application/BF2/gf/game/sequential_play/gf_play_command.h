#pragma once
#include "gf/event/gf_event.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
struct GF_SCOM_HANDLE;
struct GfMapjumpInfo;
struct GfSetupPfTalk;
struct MenuCommonWindowParam;
struct QuestID;
class GfMenuCallContext;
class IFieldSeq;

struct ParamReturnTitle {
  bool unknown00; // Inferred role: wait voice; original member name unknown.
  bool unknown01; // Inferred role: game clear; original member name unknown.
};

struct GfSequentialPlaySignal {
  bool isActive;
};

enum PCOMTYPE {
  PCOMTYPE_EVENT_FADE,
  PCOMTYPE_PAUSE,
  PCOMTYPE_STATE,
  PCOMTYPE_WAIT,
  PCOMTYPE_WAIT_EVENT,
  PCOMTYPE_MAPJUMP,
  PCOMTYPE_PLAYER_STOP,
  PCOMTYPE_AFTER_EVENT_SCRIPT = 8,
  PCOMTYPE_EVENT,
  PCOMTYPE_CALLBACK_EVENT_SEQUENCE,
  PCOMTYPE_OPEN_MENU,
  PCOMTYPE_OPEN_MENU2,
  PCOMTYPE_MENU_CHAPTER_SAVE,
  PCOMTYPE_MENU_CHAPTER,
  PCOMTYPE_MENU_CHAPTER_END,
  PCOMTYPE_MENU_ZONE,
  PCOMTYPE_MENU_DUMMY_TUTORIAL,
  PCOMTYPE_MENU_QUEST_LIST,
  PCOMTYPE_MENU_KIZUNARING = 0x15,
  PCOMTYPE_MENU_PRECIOUS,
  PCOMTYPE_MENU_COMMON,
  PCOMTYPE_MENU_COMMON_FROM_PARAM,
  PCOMTYPE_SALVAGE,
  PCOMTYPE_COLLECT,
  PCOMTYPE_FIELD_TBOX,
  PCOMTYPE_FIELD_SEQ,
  PCOMTYPE_WAIT_PLAYER_TO_START_GMK_TUTO,
  PCOMTYPE_GMK_TUTORIAL_SEQ,
  PCOMTYPE_GMK_CAMERA_SEQ,
  PCOMTYPE_PLAYER_DEAD,
  PCOMTYPE_TALK,
  PCOMTYPE_QUEST_ORDER_UI,
  PCOMTYPE_QUEST_COMPLETE_UI,
  PCOMTYPE_RETURN_TITLE,
  PCOMTYPE_BATTLE_START,
  PCOMTYPE_EXECUTE_SIGNAL,
  PCOMTYPE_MINI_GAME,
  PCOMTYPE_CHAIN_ATTACK,
  PCOMTYPE_ARTS_MOVIE,
  PCOMTYPE_RESET_BLADE,
  PCOMTYPE_MOVER_SWITCH,
};

class GfPlayCom {
public:
  GfPlayCom(PCOMTYPE type, bool isContinue) : unknown08(true), unknown09(isContinue), unknown0c(type) {}
  virtual const mm::mtl::RTTI *getRTTI() const { return &m_rtti; }
  virtual ~GfPlayCom() {}
  virtual const char *getFuncName() const = 0;
  virtual void start() {}
  virtual void end() {}
  virtual bool update(const fw::UpdateInfo &, bool) { return true; }

  static mm::mtl::RTTI m_rtti;

  bool unknown08;     // Inferred role: start request; original member name unknown.
  bool unknown09;     // Inferred role: continue; original member name unknown.
  PCOMTYPE unknown0c; // Inferred role: type; original member name unknown.
};

static_assert(sizeof(GfPlayCom) == 0x10, "");

#define GF_PLAY_COM(funcName)                                                                                                                                                                          \
public:                                                                                                                                                                                                \
  static mm::mtl::RTTI m_rtti;                                                                                                                                                                         \
  const mm::mtl::RTTI *getRTTI() const override { return &m_rtti; }                                                                                                                                    \
  const char *getFuncName() const override {                                                                                                                                                           \
    static const char *func = funcName;                                                                                                                                                                \
    return func;                                                                                                                                                                                       \
  }

class GfPlayComEventFade : public GfPlayCom {
public:
  static GfPlayComEventFade *create();
};

class GfPlayComPause : public GfPlayCom {
  GF_PLAY_COM("PlayComPause")

public:
  GfPlayComPause(u32 pauseBits) : GfPlayCom(PCOMTYPE_PAUSE, true), unknown10(pauseBits) {}
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComPause *create(u32 pauseBits);

  u32 unknown10; // Inferred role: pause bits; original member name unknown.
};

static_assert(sizeof(GfPlayComPause) == 0x18, "");

class GfPlayComState : public GfPlayCom {
  GF_PLAY_COM("PlayComState")

public:
  GfPlayComState(GF_STATE state, bool isSequence) : GfPlayCom(PCOMTYPE_STATE, true), unknown10(state), unknown14(isSequence) {}
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComState *create(GF_STATE state, bool isSequence);

  GF_STATE unknown10; // Inferred role: state; original member name unknown.
  bool unknown14;     // Inferred role: sequence; original member name unknown.
};

static_assert(sizeof(GfPlayComState) == 0x18, "");

class GfPlayComWait : public GfPlayCom {
  GF_PLAY_COM("PlayComWait")

public:
  GfPlayComWait(f32 time) : GfPlayCom(PCOMTYPE_WAIT, false), unknown10(time) {}
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComWait *create(f32 time);

  f32 unknown10; // Inferred role: time; original member name unknown.
};

static_assert(sizeof(GfPlayComWait) == 0x18, "");

class GfPlayComWaitEvent : public GfPlayCom {
public:
  static GfPlayComWaitEvent *create(f32 time, GF_OBJ_HANDLE *handle);
};

class GfPlayComMapjump : public GfPlayCom {
public:
  static GfPlayComMapjump *create(const GfMapjumpInfo &info);
};

class GfPlayComWaitBattleEnd : public GfPlayCom {
public:
  static GfPlayComWaitBattleEnd *create(u32 battle);

  static int s_activate;
};

class GfPlayComEventPlayerStop : public GfPlayCom {
  GF_PLAY_COM("PlayComEventPlayerStop")

public:
  GfPlayComEventPlayerStop(bool isStop);
  void start() override;
  void end() override {}
  bool update(const fw::UpdateInfo &, bool) override { return true; }
  static GfPlayComEventPlayerStop *create(bool isStop);

  bool unknown10; // Inferred role: stop; original member name unknown.
};

static_assert(sizeof(GfPlayComEventPlayerStop) == 0x18, "");

class GfPlayComResetBladePlayerStop : public GfPlayCom {
  GF_PLAY_COM("GfPlayComResetBladePlayerStop")

public:
  GfPlayComResetBladePlayerStop(bool isStop);
  void start() override;
  void end() override {}
  bool update(const fw::UpdateInfo &, bool) override { return true; }
  static GfPlayComResetBladePlayerStop *create(bool isStop);

  bool unknown10; // Inferred role: stop; original member name unknown.
};

static_assert(sizeof(GfPlayComResetBladePlayerStop) == 0x18, "");

class GfPlayComAfterEventScript : public GfPlayCom {
  GF_PLAY_COM("PlayComAfterEventScript")

public:
  GfPlayComAfterEventScript(u32 event);
  ~GfPlayComAfterEventScript() override;
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComAfterEventScript *create(u32 event);

  int unknown10;             // Inferred role: state; original member name unknown.
  u32 unknown14;             // Inferred role: event; original member name unknown.
  GF_SCOM_HANDLE *unknown18; // Inferred role: handle; original member name unknown.

  static int s_activate;
};

static_assert(sizeof(GfPlayComAfterEventScript) == 0x20, "");

class GfPlayComEvent : public GfPlayCom {
public:
  static GfPlayComEvent *create(u32 event, u32 param0, u32 param1, bool isEndFadeOut);
  static GfPlayComEvent *create(const char *name, u32 param0, u32 param1, bool isEndFadeOut);
};

class GfPlayComCallbackEventSequence : public GfPlayCom {
  GF_PLAY_COM("PlayComCallbackEventSequence")

public:
  GfPlayComCallbackEventSequence(int sequence, bool isStart) : GfPlayCom(PCOMTYPE_CALLBACK_EVENT_SEQUENCE, false), unknown10(sequence), unknown14(isStart) {}
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComCallbackEventSequence *create(int sequence, bool isStart);

  int unknown10;  // Inferred role: sequence; original member name unknown.
  bool unknown14; // Inferred role: start; original member name unknown.
};

static_assert(sizeof(GfPlayComCallbackEventSequence) == 0x18, "");

class GfPlayComOpenMenu : public GfPlayCom {
  GF_PLAY_COM("GfPlayComOpenMenu")

public:
  GfPlayComOpenMenu();
  ~GfPlayComOpenMenu() override;
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComOpenMenu *create(u32 menu);

  u32 unknown10; // Inferred role: menu; original member name unknown.

  static int s_active;
};

static_assert(sizeof(GfPlayComOpenMenu) == 0x18, "");

class GfPlayComOpenMenu2 : public GfPlayCom {
  GF_PLAY_COM("GfPlayComOpenMenu")

public:
  GfPlayComOpenMenu2(u32 type, MAINMENU menu) : GfPlayCom(PCOMTYPE_OPEN_MENU2, false), unknown18(0), unknown1c(0) {
    this->unknown10 = type;
    this->unknown14 = menu;
  }
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComOpenMenu2 *create(u32 type, MAINMENU menu);

  u32 unknown10;      // Inferred role: type; original member name unknown.
  MAINMENU unknown14; // Inferred role: menu; original member name unknown.
  int unknown18;      // Inferred role: state; original member name unknown.
  int unknown1c;      // Inferred role: wait count; original member name unknown.
};

static_assert(sizeof(GfPlayComOpenMenu2) == 0x20, "");

class GfPlayComStartTutorial : public GfPlayCom {
  GF_PLAY_COM("GfPlayComStartTutorial")

public:
  GfPlayComStartTutorial(u32 tutorial) : GfPlayCom(PCOMTYPE_OPEN_MENU2, false), unknown10(tutorial) {}
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComStartTutorial *create(u32 tutorial);

  u32 unknown10; // Inferred role: tutorial; original member name unknown.

  static int s_activateCount;
};

static_assert(sizeof(GfPlayComStartTutorial) == 0x18, "");

class GfPlayComMiniGame : public GfPlayCom {
  GF_PLAY_COM("GfPlayComMiniGame")

public:
  GfPlayComMiniGame() : GfPlayCom(PCOMTYPE_MINI_GAME, false) {}
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComMiniGame *create();
};

static_assert(sizeof(GfPlayComMiniGame) == 0x10, "");

class GfPlayComMenuChapterSave : public GfPlayCom {
  GF_PLAY_COM("PlayComMenuChapterSave")

public:
  GfPlayComMenuChapterSave(u32 chapter) : GfPlayCom(PCOMTYPE_MENU_CHAPTER_SAVE, false), unknown10(chapter) {}
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static bool isDisp();
  static GfPlayComMenuChapterSave *create(u32 chapter);

  u32 unknown10;  // Inferred role: chapter; original member name unknown.
  bool unknown14; // Inferred role: open; original member name unknown.

  static bool s_bExist;
};

static_assert(sizeof(GfPlayComMenuChapterSave) == 0x18, "");

class GfPlayComMenuCommon : public GfPlayCom {
public:
  static bool isDisp(u32 window);
  static u32 getResult(u32 window);
  static GfPlayComMenuCommon *create(u32 window);

  u32 unknown10; // Inferred role: window; original member name unknown.
  int unknown14; // Inferred role: id; original member name unknown.
};

static_assert(sizeof(GfPlayComMenuCommon) == 0x18, "");

class GfPlayComMenuCommonFromParam : public GfPlayCom {
public:
  static GfPlayComMenuCommonFromParam *create(const MenuCommonWindowParam &param);

  u8 _10[0x60 - 0x10];
  int unknown60; // Inferred role: id; original member name unknown.
};

static_assert(sizeof(GfPlayComMenuCommonFromParam) == 0x68, "");

class GfPlayComMenuChapter : public GfPlayCom {
  GF_PLAY_COM("PlayComMenuChapter")

public:
  GfPlayComMenuChapter(u32 chapter);
  ~GfPlayComMenuChapter() override;
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComMenuChapter *create(u32 chapter);

  u32 unknown10; // Inferred role: chapter; original member name unknown.

  static int s_activate;
};

static_assert(sizeof(GfPlayComMenuChapter) == 0x18, "");

class GfPlayComMenuChapterEnd : public GfPlayCom {
  GF_PLAY_COM("PlayComMenuChapterEnd")

public:
  GfPlayComMenuChapterEnd(u32 chapter);
  ~GfPlayComMenuChapterEnd() override;
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComMenuChapterEnd *create(u32 chapter);

  u32 unknown10; // Inferred role: chapter; original member name unknown.

  static int s_activate;
};

static_assert(sizeof(GfPlayComMenuChapterEnd) == 0x18, "");

class GfPlayComMenuZone : public GfPlayCom {
  GF_PLAY_COM("PlayComMenuZone")

public:
  GfPlayComMenuZone(u32 zone);
  ~GfPlayComMenuZone() override;
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComMenuZone *create(u32 zone);

  u32 unknown10; // Inferred role: zone; original member name unknown.
  f32 unknown14; // Inferred role: time; original member name unknown.

  static int s_activate;
};

static_assert(sizeof(GfPlayComMenuZone) == 0x18, "");

class GfPlayComMenuDummyTutorial : public GfPlayCom {
  GF_PLAY_COM("PlayComMenuDummyTutorial")

public:
  GfPlayComMenuDummyTutorial(u32 tutorial);
  ~GfPlayComMenuDummyTutorial() override;
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComMenuDummyTutorial *create(u32 tutorial);

  u32 unknown10; // Inferred role: tutorial; original member name unknown.

  static int s_activate;
};

static_assert(sizeof(GfPlayComMenuDummyTutorial) == 0x18, "");

class GfPlayComMenuQuestList : public GfPlayCom {
  GF_PLAY_COM("PlayComMenuQuestList")

public:
  GfPlayComMenuQuestList() : GfPlayCom(PCOMTYPE_MENU_QUEST_LIST, false) {}
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComMenuQuestList *create();
};

static_assert(sizeof(GfPlayComMenuQuestList) == 0x10, "");

class GfPlayComMenuKizunaring : public GfPlayCom {
  GF_PLAY_COM("PlayComMenuKizunaring")

public:
  GfPlayComMenuKizunaring(u32 blade) : GfPlayCom(PCOMTYPE_MENU_KIZUNARING, false), unknown10(blade) {}
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComMenuKizunaring *create(u32 blade);

  u32 unknown10; // Inferred role: blade; original member name unknown.
};

static_assert(sizeof(GfPlayComMenuKizunaring) == 0x18, "");

class GfPlayComMenuPrecious : public GfPlayCom {
  GF_PLAY_COM("PlayComMenuPrecious")

public:
  GfPlayComMenuPrecious(u32 item);
  ~GfPlayComMenuPrecious() override;
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComMenuPrecious *create(u32 item);

  u32 unknown10; // Inferred role: item; original member name unknown.

  static int s_activate;
};

static_assert(sizeof(GfPlayComMenuPrecious) == 0x18, "");

class GfPlayComSalvage : public GfPlayCom {
  GF_PLAY_COM("PlayComSalvage")

public:
  enum STATE {
    STATE_WAIT,
    STATE_SALVAGE,
  };

  GfPlayComSalvage(GF_OBJ_HANDLE *handle);
  void start() override;
  void end() override;
  bool updateForWait(const fw::UpdateInfo &info);
  bool updateForSalvage(const fw::UpdateInfo &info, bool isCancel);
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComSalvage *create(GF_OBJ_HANDLE *handle);

  u32 unknown10;            // Inferred role: pause; original member name unknown.
  GF_OBJ_HANDLE *unknown18; // Inferred role: handle; original member name unknown.
  int unknown20;            // Inferred role: wait frame; original member name unknown.
  STATE unknown24;          // Inferred role: state; original member name unknown.
};

static_assert(sizeof(GfPlayComSalvage) == 0x28, "");

class GfPlayComCollect : public GfPlayCom {
public:
  static GfPlayComCollect *create(GF_OBJ_HANDLE *handle);
};

class GfPlayComFieldTbox : public GfPlayCom {
public:
  static GfPlayComFieldTbox *create(GF_OBJ_HANDLE *handle);
};

class GfPlayComFieldSeq : public GfPlayCom {
public:
  static GfPlayComFieldSeq *create(IFieldSeq *sequence, GF_OBJ_HANDLE *handle);
};

class GfPlayComWaitPlayerToStartGmkTuto : public GfPlayCom {
  GF_PLAY_COM("PlayComWaitPlayerToStartGmkTuto")

public:
  GfPlayComWaitPlayerToStartGmkTuto() : GfPlayCom(PCOMTYPE_WAIT_PLAYER_TO_START_GMK_TUTO, true) {}
  void start() override { unknown10 = 0.0f; }
  void end() override {}
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComWaitPlayerToStartGmkTuto *create();

  f32 unknown10; // Inferred role: time; original member name unknown.
};

static_assert(sizeof(GfPlayComWaitPlayerToStartGmkTuto) == 0x18, "");

class GfPlayComGmkTutorialSeq : public GfPlayCom {
public:
  static GfPlayComGmkTutorialSeq *create(const char *name, u32 tutorial);

  static int s_activate;
};

class GfPlayComPlayerDead : public GfPlayCom {
public:
  static bool isDead();
  static bool replaceDeadType(GfPlayerDead dead);
  static GfPlayComPlayerDead *create(GfPlayerDead dead);
};

class GfPlayComTalk : public GfPlayCom {
public:
  static GfPlayComTalk *create(const GfSetupPfTalk &talk);
};

class GfPlayComQuestOrderUI : public GfPlayCom {
public:
  static GfPlayComQuestOrderUI *create(QuestID quest, bool isForce);
};

class GfPlayComQuestCompleteUI : public GfPlayCom {
public:
  static GfPlayComQuestCompleteUI *create(QuestID quest, QuestID child, QSTATE state);

  static int s_active;
};

class GfPlayComGimmickTaskComplete : public GfPlayCom {
  GF_PLAY_COM("GimmickTaskComplete")

public:
  GfPlayComGimmickTaskComplete(gmk::GmkType gmkType, u32 gimmick, f32 time);
  void start() override {}
  void end() override {}
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  static GfPlayComGimmickTaskComplete *create(gmk::GmkType gmkType, u32 gimmick, f32 time);

  gmk::GmkType unknown10; // Inferred role: gmk type; original member name unknown.
  u32 unknown14;          // Inferred role: gimmick; original member name unknown.
  f32 unknown18;          // Inferred role: time; original member name unknown.
};

static_assert(sizeof(GfPlayComGimmickTaskComplete) == 0x20, "");

class GfPlayComReturnTitle : public GfPlayCom, public mm::mtl::PtrSingleton<GfPlayComReturnTitle> {
public:
  static GfPlayComReturnTitle *create(const ParamReturnTitle &param);
};

class GfPlayComBattleStart : public GfPlayCom, public mm::mtl::PtrSingleton<GfPlayComBattleStart> {
public:
  static GfPlayComBattleStart *create(bool isStart);
};

class GfPlayComExecuteSignal : public GfPlayCom {
  GF_PLAY_COM("PlayComExecuteSignal")

public:
  GfPlayComExecuteSignal(bool isStart, GfSequentialPlaySignal *signal);
  void start() override;
  static GfPlayComExecuteSignal *create(bool isStart, GfSequentialPlaySignal *signal);

  bool unknown10;                    // Inferred role: start; original member name unknown.
  GfSequentialPlaySignal *unknown18; // Inferred role: signal; original member name unknown.
};

static_assert(sizeof(GfPlayComExecuteSignal) == 0x20, "");

class GfPlayComChainAttack : public GfPlayCom {
public:
  static GfPlayComChainAttack *create();
};

class GfPlayComArtsMovie : public GfPlayCom {
public:
  static GfPlayComArtsMovie *create(const char *name);
};

class GfPlayComResetBlade : public GfPlayCom {
public:
  static GfPlayComResetBlade *create(u32 partyId, int blade);
  static bool isPlaying(u32 partyId);

  static mm::mtl::FixedVector<u8, 8> s_execFlag;
};

class GfPlayComMoverSwitch : public GfPlayCom {
public:
  static GfPlayComMoverSwitch *create();
};

class GfPlayComHoodHomuraBattou : public GfPlayCom, public mm::mtl::PtrSingleton<GfPlayComHoodHomuraBattou> {
public:
  static GfPlayComHoodHomuraBattou *create();
};

class GfPlayComMenuObjCommonText : public GfPlayCom {
  GF_PLAY_COM("PlayComMenuObjCommonText")

public:
  void start() override;
  void end() override;
  bool update(const fw::UpdateInfo &info, bool isCancel) override;
  GfPlayComMenuObjCommonText(GfMenuObjCommonText::OpenKizunaParam &param);
  ~GfPlayComMenuObjCommonText() override;
  static GfPlayComMenuObjCommonText *create(GfMenuObjCommonText::OpenKizunaParam &param);

  GfMenuObjCommonText::OpenKizunaParam unknown10; // Inferred role: param; original member name unknown.
  GfMenuCallContext *unknown20;                   // Inferred role: context; original member name unknown.

  static int s_activate;
};

static_assert(sizeof(GfPlayComMenuObjCommonText) == 0x28, "");

} // namespace gf
