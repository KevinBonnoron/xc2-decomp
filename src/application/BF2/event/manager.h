#pragma once
#include "event/i_manager.h"
#include "ml/work_event.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace ml {
class Scn;
class EventView;
} // namespace ml

namespace event {

class Manager : public mm::mtl::PtrSingleton<Manager>, public ml::IWorkEvent, public ml::IWorkBackground {
public:
  static constexpr u32 MANAGER_COUNT = 64;

  enum LANGUAGE_MODE {
    LANGUAGE_MODE_NONE,
    LANGUAGE_MODE_VOICE_TYPE_0,
    LANGUAGE_MODE_VOICE_TYPE_1,
  };

  enum {
    FLAG_PLAY = 1 << 0,
    FLAG_PLAY_END = 1 << 1,
    FLAG_END_FADE_OUT = 1 << 2,
    FLAG_HIDE_INFO = 1 << 10,
  };

  enum {
    STATE_INIT = 1 << 0,
    STATE_SETUP_SCENE_END = 1 << 1,
    STATE_START_SCENE = 1 << 2,
    STATE_START_PAGE = 1 << 3,
    STATE_STOP = 1 << 5,
  };

  Manager(ml::Scn *scn);
  virtual ~Manager();
  int getStartPageID() const { return mStartPageID; }
  gf::GF_OBJ_HANDLE *getObjHandle() const { return mObjHandle; }
  const char *getSceneName() const { return mSceneName.c_str(); }
  bool isEndFadeOut() const { return (flags & FLAG_END_FADE_OUT) != 0; }
  u32 getPlayParam(u32 index) const { return mPlayParams[index]; }
  void failureSkip();
  void nextEvent(int next);
  bool isPlayCancel() const;
  void clearAlways();
  void clear();
  void update();
  void execMessage(MSG_TYPE type);
  void render();
  void drawInfo();
  void tail();
  void post();
  void play(const char *name, gf::GF_OBJ_HANDLE *handle, u32 param0, u32 param1, u32 param2, u32 param3, bool isEndFadeOut);
  void stop();
  bool end();
  void finishNewGameWait();
  bool init(const char *name);
  bool setupScene(const char *name);
  bool setupSceneEnd();
  bool startScene(const char *name, int pageID);
  bool startPage(const char *name, int pageID, f32 maxFrame);
  bool endScene();
  void setLanguageMode(bool isEnable, LANGUAGE_MODE mode);
  bool checkLanguageMode() const;
  void setDebugPlayOnetime(bool isPlayOnetime);
  bool isDebugPlayOnetime() const;
  void setDebugFastSkipDisable(bool isDisable);
  void setDebugAgeingSkipEnable(bool isEnable);
  void setDebugDisableBgm(bool isDisable);
  void setDebugReplaceDefaultEquip(bool isReplace, u32 slot, u32 item);
  bool isReplaceDefaultEquip(u32 slot, u32 *item) const;
  void setDebugReplaceMaximumEquip(bool isReplace);
  bool isDebugReplaceMaximumEquip() const;
  void setDebugReplaceMaximumBlade(bool isReplace);
  bool isDebugReplaceMaximumBlade() const;
  void setSyncFreeCam(bool isSync, bool isOneTime);
  static Manager *create(ml::Scn *scn);
  static void destroy();
  virtual bool OnKeyDown(ml::EventView *view);
  virtual void bkgHomeMenu(bool isOpen);

private:
  u32 flags;
  u32 state;
  mm::mtl::FixedVector<IManager *, MANAGER_COUNT> mManagers;
  ml::Scn *mScn;
  mm::mtl::FixStr<32> mEventName;
  mm::mtl::FixStr<32> mSceneName;
  int mStartPageID;
  gf::GF_OBJ_HANDLE *mObjHandle;
  u32 mPlayParams[4];
  LANGUAGE_MODE mLanguageMode;
};

static_assert(sizeof(Manager) == 0x2a0, "");

} // namespace event
