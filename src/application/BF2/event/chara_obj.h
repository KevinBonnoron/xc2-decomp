#pragma once
#include <stddef.h>

#include "event/chara_dys_updater.h"
#include "event/chara_effect_player.h"
#include "event/chara_eva_player.h"
#include "event/chara_eva_player_eff.h"
#include "event/chara_fade.h"
#include "event/chara_hide_wpn.h"
#include "event/chara_ik_updater.h"
#include "event/chara_lens_player.h"
#include "event/chara_liner_pos.h"
#include "event/chara_liner_rot.h"
#include "event/chara_mount.h"
#include "event/chara_part_updater.h"
#include "event/chara_play_action.h"
#include "event/chara_play_action_auto.h"
#include "event/chara_play_eva.h"
#include "event/chara_play_eva_eff.h"
#include "event/chara_play_facial.h"
#include "event/chara_play_head.h"
#include "event/chara_play_motion.h"
#include "event/chara_play_motion_abc.h"
#include "event/chara_play_talk.h"
#include "event/chara_play_talk_auto.h"
#include "event/chara_play_wink.h"
#include "event/chara_set_idle.h"
#include "event/chara_set_pos.h"
#include "event/chara_set_rot.h"
#include "event/chara_set_tar.h"
#include "event/chara_stop_action.h"
#include "event/chara_stop_head.h"
#include "event/chara_tar_player.h"
#include "event/chara_turn_rot.h"
#include "event/chara_walk_pos.h"
#include "event/chara_weight_player.h"
#include "event/chara_wink_player.h"
#include "event/cmd_queue.h"
#include "event/curve.h"
#include "event/frame_manager.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

enum EVT_poscvtype : int;
enum EVT_rotcvtype : int;
enum EVT_tarcvtype : int;
enum EVT_aimtype : int;

namespace gf {
struct GF_OBJ_HANDLE;
class GfEvtModel;
} // namespace gf
namespace mm {
struct Vec2;
} // namespace mm

namespace event {

class TarAxis;

enum CHARA_TYPE {
  CHARA_TYPE_DRIVER = 1,
  CHARA_TYPE_BLADE = 2,
  CHARA_TYPE_NPC = 3,
  CHARA_TYPE_ENEMY = 5,
};

enum WPNHIDEID {
  WPNHIDEID_SEQ = 0,
  WPNHIDEID_EVA = 1,
  WPNHIDEID_HIDE_WPN = 2,
};

class CharaObj {
public:
  static constexpr size_t QUEUE_COUNT = 8;
  static constexpr size_t SUB_QUEUE_COUNT = 5;

  enum {
    FLAG_READY = 1 << 3,
    FLAG_MOUNT = 1 << 4,
    FLAG_FADE_OUT = 1 << 5,
    FLAG_MODEL_STREAM = 1 << 6,
    FLAG_DISP_JIJI = 1 << 7,
  };

  CharaObj(const char *name);
  virtual ~CharaObj();
  void createGfObj(gf::GF_OBJ_HANDLE *handle);
  void createGfObj(CHARA_TYPE type, u32 id, u32 param3, u32 param4);
  void createModel(const char *model, u32 param2, u32 param3);
  void createGhost();
  void clear();
  void start();
  void playWink(int type, f32 frame, bool isLoop, f32 lensX, f32 lensY, int lensType, bool isDirect, bool isAuto);
  void end();
  void update(const FrameInfo &info);
  void initModel();
  const mm::Vec3 &getPos() const;
  bool isCharaObjPause(const FrameInfo &info) const;
  void exitModelStream();
  void renderBone();
  void renderAction();
  f32 getEyeOffset() const;
  void renderMotion();
  void renderHead();
  void renderFacial();
  void renderTalk();
  void renderWink();
  void renderLens();
  void renderWeight();
  void renderIK();
  void tail(const FrameInfo &info);
  void setPos(const mm::Vec3 &pos);
  void walkPos(const mm::Vec3 &pos, EVT_poscvtype cv, bool isRun);
  void linerPos(const mm::Vec3 &pos, bool isWalk, f32 frame, CV_TYPE cv);
  const mm::Vec3 &getPosTo() const;
  void setRot(const mm::Vec3 &rot);
  void turnRot(const mm::Vec3 &rot, EVT_rotcvtype cv, f32 frame);
  void linerRot(const mm::Vec3 &rot, f32 frame, CV_TYPE cv);
  const mm::Vec3 &getRot() const;
  const mm::Vec3 &getRotTo() const;
  bool isTurnable() const;
  void setTar(const TarAxis &axis, f32 frame, EVT_tarcvtype cv, EVT_aimtype aim, f32 weight, f32 speed);
  void resetTar();
  const mm::Vec3 &getTar() const;
  bool isTar() const;
  void setLensTarget(const mm::Vec2 &target);
  const mm::Vec2 &getLensTarget() const;
  void setIdle(int type);
  int getIdle() const;
  void playAutoAction(f32 frame);
  void playAction(int type, f32 frame, bool isLoop, bool isBlend);
  void stopAction();
  int getAction() const;
  f32 getActionLastFrame() const;
  void playMotion(const char *name, f32 frame, f32 blend, f32 speed);
  void initModelStream();
  void playMotionABC(const char *nameA, const char *nameB, const char *nameC, f32 frameA, f32 frameB, f32 frameC, f32 blendA, f32 blendB, f32 blendC);
  void playHead(int type, f32 life, bool isBlendIn, bool isBlendOut);
  void stopHead();
  int getHead() const;
  void playFacial(int type, f32 life, int browType, f32 browWeight, int eyeType, f32 eyeWeight, int lipType, f32 lipWeight, f32 blendIn,
                  f32 blendOut);
  int getFacial() const;
  void playAutoTalk(f32 frame);
  void playTalk(bool isManual, f32 frame, bool isBlend, bool isAuto, f32 openMin, f32 openMax, f32 closeMin, f32 closeMax);
  void mount(CharaObj *target, const char *bone, const mm::Vec3 &pos, const mm::Vec3 &rot);
  void resetDynamics(int frame);
  void playFade(bool isOut, f32 frame);
  bool isFadeOut() const;
  void playVolumeFade(CharaEffectPlayer::VF_TYPE type, int id, const mm::Vec3 &position, const mm::Vec3 &scale, f32 frame, f32 rate, int mode,
                      f32 speed);
  void playVolumeFadeAnim(CharaEffectPlayer::VF_TYPE type, f32 rate, f32 frame);
  void stopVolumeFade(CharaEffectPlayer::VF_TYPE type);
  void playRimBloom(int id);
  void stopRimBloom();
  void setExtDisp(const char *name, bool isDisp);
  void setExtDispWeapon(const char *name, bool isDisp);
  void setExtParam(const char *name, f32 value);
  void setScaleWeapon(f32 scale);
  void updateScaleWeapon();
  void setHideWeapon(WPNHIDEID id, bool isHide, bool isLeft);
  void updateHideWeapon(bool isLeft);
  void setDispJiji(bool isDisp);
  void updateDispJiji();

  const char *getName() const { return name.c_str(); }
  bool isReady() const { return (flags & FLAG_READY) != 0; }
  gf::GF_OBJ_HANDLE *getHandle() const { return handle; }
  const FrameInfo &getFrameInfo() const { return frameInfo; }

private:
  CharaSetPos cmdSetPos;
  CharaSetRot cmdSetRot;
  u8 _28[0x30 - 0x28];
  CharaWalkPos cmdWalkPos;
  CharaLinerPos cmdLinerPos;
  CharaTurnRot cmdTurnRot;
  CharaLinerRot cmdLinerRot;
  CharaSetTar cmdSetTar;
  CharaSetIdle cmdSetIdle;
  CharaPlayActionAuto cmdPlayActionAuto;
  CharaPlayAction cmdPlayAction;
  CharaStopAction cmdStopAction;
  CharaPlayMotion cmdPlayMotion;
  CharaPlayMotionABC cmdPlayMotionABC;
  CharaPlayEva cmdPlayEva;
  CharaEvaPlayer evaPlayer;
  CharaPlayEvaEff cmdPlayEvaEff;
  CharaEvaPlayerEff evaPlayerEff;
  CharaHideWpn cmdHideWpn;
  CharaPlayHead cmdPlayHead;
  CharaStopHead cmdStopHead;
  CharaPlayFacial cmdPlayFacial;
  CharaPlayTalkAuto cmdPlayTalkAuto;
  CharaPlayTalk cmdPlayTalk;
  CharaPlayWink cmdPlayWink;
  CharaMount cmdMount;
  CharaFade cmdFade;
  u32 flags;
  u32 state;
  mm::mtl::FixStr<64> name;
  CHARA_TYPE type;
  u32 id;
  mm::mtl::FixStr<64> modelName;
  u8 _D38[0xd3c - 0xd38];
  u32 offscrId;
  gf::GF_OBJ_HANDLE *handle;
  gf::GfEvtModel *model;
  u8 _D50[0xd60 - 0xd50];
  CharaIKUpdater ikUpdater;
  CharaDysUpdater dysUpdater;
  CharaTarPlayer tarPlayer;
  CharaTarPlayerMot tarPlayerMot;
  CharaLensPlayer lensPlayer;
  CharaWeightPlayer weightPlayer;
  CharaWinkPlayer winkPlayer;
  CharaEffectPlayer effectPlayer;
  CharaPartUpdater partUpdater;
  f32 eyeOffset;
  CmdQueue<QUEUE_COUNT, 0> queue;
  CmdQueue<QUEUE_COUNT, 0> subQueue;
  CmdQueue<SUB_QUEUE_COUNT, 0> fadeQueue;
  mm::Vec3 pos;
  mm::Vec3 posTo;
  mm::Vec3 rot;
  mm::Vec3 rotTo;
  u8 _2FF0[0x3030 - 0x2ff0];
  FrameInfo frameInfo;
  f32 streamFrame;
  f32 weaponScale;
  u32 hideWeaponFlags[2];
  int reuseFlag;
};

static_assert(sizeof(CharaObj) == 0x3060, "");

} // namespace event
