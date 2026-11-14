#pragma once
#include "event/i_manager.h"
#include "ml/work_background.h"
#include "ml/work_event.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
class GfGameTalk;
} // namespace gf

namespace ml {
class Scn;
class EventView;
} // namespace ml

namespace event {

class Manager : public mm::mtl::PtrSingleton<Manager>, public ml::IWorkEvent, public ml::IWorkBackground {
  friend class ::gf::GfGameTalk;
  friend class MemoryManager;

public:
  static constexpr u32 MANAGER_UNKNOWN_64 = 64; // Inferred role: manager count; original name unknown.

  enum LANGUAGE_MODE {
    LANGUAGE_MODE_UNKNOWN_0, // Inferred role: none; original name unknown.
    LANGUAGE_MODE_UNKNOWN_1, // Inferred role: voice type 0; original name unknown.
    LANGUAGE_MODE_UNKNOWN_2, // Inferred role: voice type 1; original name unknown.
  };

  enum {
    FLAG_UNKNOWN_0 = 1 << 0,   // Inferred role: play flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1,   // Inferred role: play end flag; original name unknown.
    FLAG_UNKNOWN_2 = 1 << 2,   // Inferred role: end fade out flag; original name unknown.
    FLAG_UNKNOWN_10 = 1 << 10, // Inferred role: hide info flag; original name unknown.
  };

  enum {
    STATE_UNKNOWN_0 = 1 << 0, // Inferred role: init; original name unknown.
    STATE_UNKNOWN_1 = 1 << 1, // Inferred role: setup scene end; original name unknown.
    STATE_UNKNOWN_2 = 1 << 2, // Inferred role: start scene; original name unknown.
    STATE_UNKNOWN_3 = 1 << 3, // Inferred role: start page; original name unknown.
    STATE_UNKNOWN_4 = 1 << 4, // Inferred role: end scene; original name unknown.
    STATE_UNKNOWN_5 = 1 << 5, // Inferred role: stop; original name unknown.
  };

  Manager(ml::Scn *scn);
  virtual ~Manager();
  int getStartPageID() const { return unknown278; }
  gf::GF_OBJ_HANDLE *getObjHandle() const { return unknown280; }
  ml::Scn *getScn() const { return unknown228; }
  const char *getSceneName() const { return unknown254.c_str(); }
  bool isEndFadeOut() const { return (unknown18 & FLAG_UNKNOWN_2) != 0; }
  bool isPlay() const { return (unknown18 & FLAG_UNKNOWN_0) != 0; }
  u32 getPlayParam(u32 index) const { return unknown288[index]; }
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
  u32 unknown18;                                                  // Inferred role: flags; original member name unknown.
  u32 unknown1c;                                                  // Inferred role: state; original member name unknown.
  mm::mtl::FixedVector<IManager *, MANAGER_UNKNOWN_64> unknown20; // Inferred role: managers; original member name unknown.
  ml::Scn *unknown228;                                            // Inferred role: scn; original member name unknown.
  mm::mtl::FixStr<32> unknown230;                                 // Inferred role: event name; original member name unknown.
  mm::mtl::FixStr<32> unknown254;                                 // Inferred role: scene name; original member name unknown.
  int unknown278;                                                 // Inferred role: start page id; original member name unknown.
  gf::GF_OBJ_HANDLE *unknown280;                                  // Inferred role: object handle; original member name unknown.
  u32 unknown288[4];                                              // Inferred role: play params; original member name unknown.
  LANGUAGE_MODE unknown298;                                       // Inferred role: language mode; original member name unknown.
};

static_assert(sizeof(Manager) == 0x2a0, "");

} // namespace event
