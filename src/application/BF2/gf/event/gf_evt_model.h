#pragma once
#include <stddef.h>

#include "ai/ai_state.h"
#include "ai/ai_state_fsm.h"
#include "gf/game/gf_game_mount.h"
#include "gf/object/gf_obj_manager.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw
namespace mm {
struct Vec3;
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfInitParamBlade;
class GfInitParamDriver;
class GfInitParamEnemy;
class GfInitParamEventObj;
class GfInitParamNpc;
class GfInitParamWeapon;
struct GF_OBJ_HANDLE;

enum GF_EVT_MODEL {
  GF_EVT_MODEL_DRIVER = 0,
  GF_EVT_MODEL_BLADE = 1,
  GF_EVT_MODEL_WEAPON = 2,
  GF_EVT_MODEL_EVENT = 3,
  GF_EVT_MODEL_NPC = 4,
  GF_EVT_MODEL_ENEMY = 5,
};

class GfEvtModel : public mm::mtl::ReferenceObject, public IGfObjListener {
public:
  static mm::mtl::RTTI m_rtti;

  GfEvtModel(GF_EVT_MODEL type, u32 param);
  virtual ~GfEvtModel();
  virtual const mm::mtl::RTTI *getRTTI() const;
  virtual void update(const fw::UpdateInfo &info);
  virtual void setDispWeapon(bool isDisp);
  virtual void setDispWeapon(bool isDispRight, bool isDispLeft);
  virtual GF_OBJ_HANDLE *getWeaponHandleRight() const;
  virtual GF_OBJ_HANDLE *getWeaponHandleLeft() const;
  virtual void setWeaponBattleCommand();
  virtual void setWeaponFieldCommand();
  virtual void setWeaponBattleState();
  virtual void setWeaponFieldState();
  virtual void setWeaponBattleMount();
  virtual void setWeaponFieldMount();
  void listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) override;
  bool isValid() const;
  bool isBusy(mm::mtl::FixStr<128> *name) const;
  void destroy();
  void resetMount(GfEvtModel *parent);
  void setMount(GfEvtModel *parent, const char *bone);
  void setMount(GfEvtModel *parent, const char *bone, const mm::Vec3 &pos, const mm::Vec3 &rot);

  static u32 changeLayerUI(u32 layer);

  // Inferred role: the GfEvtModel members from 0x18, after the ReferenceObject and IGfObjListener bases.
  GF_EVT_MODEL unknown18;                         // Inferred role: type; original member name unknown.
  u32 unknown1c;                                  // Inferred role: second constructor parameter; original member name unknown.
  GF_OBJ_HANDLE *unknown20;                       // Inferred role: handle; original member name unknown.
  GfEvtModel *unknown28;                          // Inferred role: model this one is mounted on; original member name unknown.
  mm::mtl::FixStr<32> unknown30;                  // Inferred role: mount bone name; original member name unknown.
  mm::mtl::FixedList<GfEvtModel *, 32> unknown58; // Inferred role: models mounted on this one; original member name unknown.
};

static_assert(offsetof(GfEvtModel, unknown18) == 0x18, "");
static_assert(offsetof(GfEvtModel, unknown1c) == 0x1c, "");
static_assert(offsetof(GfEvtModel, unknown20) == 0x20, "");
static_assert(offsetof(GfEvtModel, unknown28) == 0x28, "");
static_assert(offsetof(GfEvtModel, unknown30) == 0x30, "");
static_assert(offsetof(GfEvtModel, unknown58) == 0x58, "");
static_assert(sizeof(GfEvtModel) == 0x298, "");

class GfEvtModelDriver : public GfEvtModel {
public:
  class StateIdleBattle : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
  };

  class StateIdleField : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
  };

  class StateStartBattle : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
    void enter(GfEvtModelDriver *model, ai::State *previous);
    void update(GfEvtModelDriver *model, const fw::UpdateInfo &info);
  };

  class StateEndBattle : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
    void enter(GfEvtModelDriver *model, ai::State *previous);
    void leave(GfEvtModelDriver *model, ai::State *next);
    void update(GfEvtModelDriver *model, const fw::UpdateInfo &info);
  };

  explicit GfEvtModelDriver(GfInitParamDriver &param);
  static GfEvtModelDriver *create(GfInitParamDriver &param);
  ~GfEvtModelDriver() override;
  const mm::mtl::RTTI *getRTTI() const override;
  void update(const fw::UpdateInfo &info) override;
  void setDispWeapon(bool isDisp) override;
  void setDispWeapon(bool isDispRight, bool isDispLeft) override;
  GF_OBJ_HANDLE *getWeaponHandleRight() const override;
  GF_OBJ_HANDLE *getWeaponHandleLeft() const override;
  void setWeaponBattleCommand() override;
  void setWeaponFieldCommand() override;
  void setWeaponBattleState() override;
  void setWeaponFieldState() override;
  void setWeaponBattleMount() override;
  void setWeaponFieldMount() override;
  void setStateWeapon(bool isBattle);
  bool isAnimEnd() const;
  void setDispRexCoreCrystal(bool isDisp);
  void setDispJiji(bool isDisp);
  void playAnimWeaponRightCS(const char *name);
  bool isPlayEndAnimWeaponRightCS();
  void setAnimSpeedWeaponRightCS(f32 speed);
  void playAnimWeaponLeftCS(const char *name);
  bool isPlayEndAnimWeaponLeftCS();
  void setAnimSpeedWeaponLeftCS(f32 speed);

  static mm::mtl::RTTI m_rtti;

  ai::Fsm unknown298; // Inferred role: state machine; original member name unknown.
  u32 unknown310;     // Inferred role: blade; original member name unknown.
  u8 _314[0x318 - 0x314];
};

static_assert(offsetof(GfEvtModelDriver, unknown298) == 0x298, "");
static_assert(offsetof(GfEvtModelDriver, unknown310) == 0x310, "");
static_assert(sizeof(GfEvtModelDriver) == 0x318, "");

class GfEvtModelSalvage : public GfEvtModelDriver {
public:
  static mm::mtl::RTTI m_rtti;

  explicit GfEvtModelSalvage(GfInitParamDriver &param);
  static GfEvtModelSalvage *create(GfInitParamDriver &param);

  const mm::mtl::RTTI *getRTTI() const override;
  bool isValid() const;
  void setTransform(const mm::Vec3 &position, f32 rotation);
};

class GfEvtModelBlade : public GfEvtModel {
public:
  class StateIdleBattle : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
  };

  class StateIdleField : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
  };

  class StateStartBattle : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
    void enter(GfEvtModelBlade *model, ai::State *previous);
    void update(GfEvtModelBlade *model, const fw::UpdateInfo &info);
  };

  class StateEndBattle : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
    void enter(GfEvtModelBlade *model, ai::State *previous);
    void leave(GfEvtModelBlade *model, ai::State *next);
    void update(GfEvtModelBlade *model, const fw::UpdateInfo &info);
  };

  static GfEvtModelBlade *create(GfInitParamBlade &param);
  ~GfEvtModelBlade() override;
  const mm::mtl::RTTI *getRTTI() const override;
  void update(const fw::UpdateInfo &info) override;
  void setDispWeapon(bool isDisp) override;
  void setDispWeapon(bool isDispRight, bool isDispLeft) override;
  GF_OBJ_HANDLE *getWeaponHandleRight() const override;
  GF_OBJ_HANDLE *getWeaponHandleLeft() const override;
  void setWeaponBattleCommand() override;
  void setWeaponFieldCommand() override;
  void setWeaponBattleState() override;
  void setWeaponFieldState() override;
  void setWeaponBattleMount() override;
  void setWeaponFieldMount() override;
  void setStateWeapon(bool isBattle);
  bool isAnimEnd() const;
  void playAnimWeaponRightCS(const char *name);
  bool isPlayEndAnimWeaponRightCS();
  void setAnimSpeedWeaponRightCS(f32 speed);
  void playAnimWeaponLeftCS(const char *name);
  bool isPlayEndAnimWeaponLeftCS();
  void setAnimSpeedWeaponLeftCS(f32 speed);

  static mm::mtl::RTTI m_rtti;

  ai::Fsm unknown298; // Inferred role: state machine; original member name unknown.
};

static_assert(offsetof(GfEvtModelBlade, unknown298) == 0x298, "");
static_assert(sizeof(GfEvtModelBlade) == 0x310, "");

class GfEvtModelEnemy : public GfEvtModel {
public:
  class StateIdleBattle : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
  };

  class StateIdleField : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
  };

  class StateStartBattle : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
    void enter(GfEvtModelEnemy *model, ai::State *previous);
    void update(GfEvtModelEnemy *model, const fw::UpdateInfo &info);
  };

  class StateEndBattle : public ai::State {
  public:
    static ai::State *create(void *buffer);
    const char *getName() const override;
    void onEnter(void *owner, ai::State *previous) override;
    void onLeave(void *owner, ai::State *next) override;
    void onStep(void *owner, const void *param) override;
    void enter(GfEvtModelEnemy *model, ai::State *previous);
    void leave(GfEvtModelEnemy *model, ai::State *next);
    void update(GfEvtModelEnemy *model, const fw::UpdateInfo &info);
  };

  GfEvtModelEnemy(GfInitParamEnemy &param);
  static GfEvtModelEnemy *create(GfInitParamEnemy &param);
  ~GfEvtModelEnemy() override;
  const mm::mtl::RTTI *getRTTI() const override;
  void update(const fw::UpdateInfo &info) override;
  void setDispWeapon(bool isDisp) override;
  void setDispWeapon(bool isDispRight, bool isDispLeft) override;
  GF_OBJ_HANDLE *getWeaponHandleRight() const override;
  GF_OBJ_HANDLE *getWeaponHandleLeft() const override;
  void setWeaponBattleCommand() override;
  void setWeaponFieldCommand() override;
  void setWeaponBattleState() override;
  void setWeaponFieldState() override;
  void setWeaponBattleMount() override;
  void setWeaponFieldMount() override;
  void setStateWeapon(bool isBattle);
  bool isAnimEnd() const;

  static mm::mtl::RTTI m_rtti;

  ai::Fsm unknown298; // Inferred role: state machine; original member name unknown.
};

static_assert(offsetof(GfEvtModelEnemy, unknown298) == 0x298, "");
static_assert(sizeof(GfEvtModelEnemy) == 0x310, "");

class GfEvtModelWeapon : public GfEvtModel {
public:
  static mm::mtl::RTTI m_rtti;

  GfEvtModelWeapon(GfInitParamWeapon &param);
  ~GfEvtModelWeapon() override;
  static void playAnimCS(GF_OBJ_HANDLE *handle, const char *name);
  static bool isPlayEndAnimCS(GF_OBJ_HANDLE *handle);
  static void setAnimSpeedCS(GF_OBJ_HANDLE *handle, f32 speed);
  static GfEvtModelWeapon *create(GfInitParamWeapon &param);
  const mm::mtl::RTTI *getRTTI() const override;
  void setWeaponBattleCommand() override;
  void setWeaponFieldCommand() override;
  void setWeaponBattleState() override;
  void setWeaponFieldState() override;
  void setWeaponCommand(const char *command);
  void setWeaponState(const char *state);
  void playAnimData(void *data);
  void setScale(f32 scale);
  void playAnimCS(const char *name);
  bool isPlayEndAnimCS();
  void setAnimSpeedCS(f32 speed);

  GfWeapon unknown298; // Inferred role: weapon handles; original member name unknown.
  u32 unknown348;      // Inferred role: driver; original member name unknown.
  u8 _34c[0x350 - 0x34c];
};

static_assert(offsetof(GfEvtModelWeapon, unknown298) == 0x298, "");
static_assert(offsetof(GfEvtModelWeapon, unknown348) == 0x348, "");
static_assert(sizeof(GfEvtModelWeapon) == 0x350, "");

class GfEvtModelEvent : public GfEvtModel {
public:
  static mm::mtl::RTTI m_rtti;

  GfEvtModelEvent(GfInitParamEventObj &param);
  static GfEvtModelEvent *create(GfInitParamEventObj &param);
  const mm::mtl::RTTI *getRTTI() const override;
};

static_assert(sizeof(GfEvtModelEvent) == 0x298, "");

class GfEvtModelNpc : public GfEvtModel {
public:
  static mm::mtl::RTTI m_rtti;

  static GfEvtModelNpc *create(GfInitParamNpc &param);
  const mm::mtl::RTTI *getRTTI() const override;
};

} // namespace gf
