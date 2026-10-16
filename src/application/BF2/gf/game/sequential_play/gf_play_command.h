#pragma once
#include "gf/event/gf_event.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/sequential_play/gf_play_factory.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
struct GfMapjumpInfo;
struct GfSetupPfTalk;
struct ParamReturnTitle;
class GfSequentialPlaySignal;
struct QuestID;

enum GfPlayerDead {};

class GfPlayCom {
public:
  virtual ~GfPlayCom();

private:
  u8 _08[0x10 - 0x08];
};

static_assert(sizeof(GfPlayCom) == 0x10, "");

class GfPlayComEventFade : public GfPlayCom {
public:
  static GfPlayComEventFade *create();
};

class GfPlayComPause : public GfPlayCom {
public:
  static GfPlayComPause *create(u32 pauseBits);
};

class GfPlayComState : public GfPlayCom {
public:
  static GfPlayComState *create(GF_STATE state, bool isPush);
};

class GfPlayComWait : public GfPlayCom {
public:
  static GfPlayComWait *create(f32 time);
};

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
};

class GfPlayComEventPlayerStop : public GfPlayCom {
public:
  static GfPlayComEventPlayerStop *create(bool isStop);
};

class GfPlayComResetBladePlayerStop : public GfPlayCom {
public:
  static GfPlayComResetBladePlayerStop *create(bool isStop);
};

class GfPlayComAfterEventScript : public GfPlayCom {
public:
  static GfPlayComAfterEventScript *create(u32 event);
};

class GfPlayComEvent : public GfPlayCom {
public:
  static GfPlayComEvent *create(u32 event, u32 param0, u32 param1, bool isEndFadeOut);
  static GfPlayComEvent *create(const char *name, u32 param0, u32 param1, bool isEndFadeOut);
};

class GfPlayComCallbackEventSequence : public GfPlayCom {
public:
  static GfPlayComCallbackEventSequence *create(int sequence, bool isStart);
};

class GfPlayComOpenMenu : public GfPlayCom {
public:
  static GfPlayComOpenMenu *create(u32 type);

  static int s_active;
};

class GfPlayComOpenMenu2 : public GfPlayCom {
public:
  static GfPlayComOpenMenu2 *create(u32 type, MAINMENU menu);
};

class GfPlayComStartTutorial : public GfPlayCom {
public:
  static GfPlayComStartTutorial *create(u32 tutorial);
};

class GfPlayComMiniGame : public GfPlayCom {
public:
  static GfPlayComMiniGame *create();
};

class GfPlayComMenuChapterSave : public GfPlayCom {
public:
  static GfPlayComMenuChapterSave *create(u32 chapter);
};

class GfPlayComMenuChapter : public GfPlayCom {
public:
  static GfPlayComMenuChapter *create(u32 chapter);

  static int s_activate;
};

class GfPlayComMenuChapterEnd : public GfPlayCom {
public:
  static GfPlayComMenuChapterEnd *create(u32 chapter);
};

class GfPlayComMenuZone : public GfPlayCom {
public:
  static GfPlayComMenuZone *create(u32 zone);

  static int s_activate;
};

class GfPlayComMenuDummyTutorial : public GfPlayCom {
public:
  static GfPlayComMenuDummyTutorial *create(u32 tutorial);
};

class GfPlayComMenuQuestList : public GfPlayCom {
public:
  static GfPlayComMenuQuestList *create();
};

class GfPlayComMenuKizunaring : public GfPlayCom {
public:
  static GfPlayComMenuKizunaring *create(u32 blade);
};

class GfPlayComMenuPrecious : public GfPlayCom {
public:
  static GfPlayComMenuPrecious *create(u32 item);

  static int s_activate;
};

class GfPlayComSalvage : public GfPlayCom {
public:
  static GfPlayComSalvage *create(GF_OBJ_HANDLE *handle);
};

class GfPlayComCollect : public GfPlayCom {
public:
  static GfPlayComCollect *create(GF_OBJ_HANDLE *handle);
};

class GfPlayComFieldTbox : public GfPlayCom {
public:
  static GfPlayComFieldTbox *create(GF_OBJ_HANDLE *handle);
};

class GfPlayComWaitPlayerToStartGmkTuto : public GfPlayCom {
public:
  static GfPlayComWaitPlayerToStartGmkTuto *create();
};

class GfPlayComGmkTutorialSeq : public GfPlayCom {
public:
  static GfPlayComGmkTutorialSeq *create(const char *name, u32 tutorial);
};

class GfPlayComPlayerDead : public GfPlayCom {
public:
  static bool isDead();
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

class GfPlayComReturnTitle : public GfPlayCom {
public:
  static GfPlayComReturnTitle *create(const ParamReturnTitle &param);
};

class GfPlayComBattleStart : public GfPlayCom {
public:
  static GfPlayComBattleStart *create(bool isStart);
};

class GfPlayComExecuteSignal : public GfPlayCom {
public:
  static GfPlayComExecuteSignal *create(bool isStart, GfSequentialPlaySignal *signal);
};

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
};

class GfPlayComMoverSwitch : public GfPlayCom {
public:
  static GfPlayComMoverSwitch *create();
};

class GfPlayComHoodHomuraBattou : public GfPlayCom, public mm::mtl::PtrSingleton<GfPlayComHoodHomuraBattou> {
public:
  static GfPlayComHoodHomuraBattou *create();
};

} // namespace gf
