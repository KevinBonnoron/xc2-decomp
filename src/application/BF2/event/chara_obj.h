#pragma once
#include <stddef.h>

#include "event/chara_dys_updater.h"
#include "event/chara_effect_player.h"
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

class IAttachActor;
class ModelObj;
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

  enum {
    STATE_UNKNOWN_1 = 1, // Role and original name unknown.
    STATE_UNKNOWN_2 = 2, // Role and original name unknown.
    STATE_UNKNOWN_5 = 5, // Role and original name unknown.
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
  void playFacial(int type, f32 life, int browType, f32 browWeight, int eyeType, f32 eyeWeight, int lipType, f32 lipWeight, f32 blendIn, f32 blendOut);
  int getFacial() const;
  void playAutoTalk(f32 frame);
  void playTalk(bool isManual, f32 frame, bool isBlend, bool isAuto, f32 openMin, f32 openMax, f32 closeMin, f32 closeMax);
  void mount(CharaObj *target, const char *bone, const mm::Vec3 &pos, const mm::Vec3 &rot);
  void resetDynamics(int frame);
  void playFade(bool isOut, f32 frame);
  bool isFadeOut() const;
  void playVolumeFade(CharaEffectPlayer::VF_TYPE type, int id, const mm::Vec3 &position, const mm::Vec3 &scale, f32 frame, f32 rate, int mode, f32 speed);
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

  const char *getName() const;
  bool isReady() const { return (unknownca0 & FLAG_READY) != 0; }
  gf::GF_OBJ_HANDLE *getHandle() const { return unknownd40; }
  IAttachActor *getAttachActor() const { return unknownd58; }
  const FrameInfo &getFrameInfo() const { return unknown3030; }

private:
  CharaSetPos unknown08; // Inferred role: cmd set pos; original member name unknown.
  CharaSetRot unknown18; // Inferred role: cmd set rot; original member name unknown.
  u8 _28[0x30 - 0x28];
  CharaWalkPos unknown30;         // Inferred role: cmd walk pos; original member name unknown.
  CharaLinerPos unknown100;       // Inferred role: cmd liner pos; original member name unknown.
  CharaTurnRot unknown310;        // Inferred role: cmd turn rot; original member name unknown.
  CharaLinerRot unknown330;       // Inferred role: cmd liner rot; original member name unknown.
  CharaSetTar unknown530;         // Inferred role: cmd set tar; original member name unknown.
  CharaSetIdle unknown5e0;        // Inferred role: cmd set idle; original member name unknown.
  CharaPlayActionAuto unknown608; // Inferred role: cmd play action auto; original member name unknown.
  CharaPlayAction unknown630;     // Inferred role: cmd play action; original member name unknown.
  CharaStopAction unknown670;     // Inferred role: cmd stop action; original member name unknown.
  CharaPlayMotion unknown680;     // Inferred role: cmd play motion; original member name unknown.
  CharaPlayMotionABC unknown6d0;  // Inferred role: cmd play motion abc; original member name unknown.
  CharaPlayEva unknown750;        // Inferred role: cmd play eva; original member name unknown.
  CharaPlayEvaEff unknown8e0;     // Inferred role: cmd play eva eff; original member name unknown.
  CharaHideWpn unknown938;        // Inferred role: cmd hide wpn; original member name unknown.
  CharaPlayHead unknown950;       // Inferred role: cmd play head; original member name unknown.
  CharaStopHead unknown988;       // Inferred role: cmd stop head; original member name unknown.
  CharaPlayFacial unknown9a0;     // Inferred role: cmd play facial; original member name unknown.
  CharaPlayTalkAuto unknowna10;   // Inferred role: cmd play talk auto; original member name unknown.
  CharaPlayTalk unknowna38;       // Inferred role: cmd play talk; original member name unknown.
  CharaPlayWink unknownab0;       // Inferred role: cmd play wink; original member name unknown.
  CharaMount unknownb40;          // Inferred role: cmd mount; original member name unknown.
  CharaFade unknownb80;           // Inferred role: cmd fade; original member name unknown.
  u32 unknownca0;                 // Inferred role: flags; original member name unknown.
  u32 unknownca4;                 // Inferred role: state; original member name unknown.
  mm::mtl::FixStr<64> m_name;
  CHARA_TYPE unknowncec;          // Inferred role: type; original member name unknown.
  u32 unknowncf0;                 // Inferred role: id; original member name unknown.
  mm::mtl::FixStr<64> unknowncf4; // Inferred role: model name; original member name unknown.
  u8 unknownd38[0xd3c - 0xd38];   // Inferred role: d38; original member name unknown.
  u32 unknownd3c;                 // Inferred role: offscr id; original member name unknown.
  gf::GF_OBJ_HANDLE *unknownd40;  // Inferred role: handle; original member name unknown.
  gf::GfEvtModel *unknownd48;     // Inferred role: model; original member name unknown.
  ModelObj *unknownd50;           // Inferred role: model object; original member name unknown.
  IAttachActor *unknownd58;       // Inferred role: attach actor; original member name unknown.
  CharaIKUpdater unknownd60;      // Inferred role: ik updater; original member name unknown.
  CharaDysUpdater unknownde0;     // Inferred role: dys updater; original member name unknown.
  CharaTarPlayer unknowne10;      // Inferred role: tar player; original member name unknown.
  CharaTarPlayerMot unknownfe0;   // Inferred role: tar player mot; original member name unknown.
  CharaLensPlayer unknown1280;    // Inferred role: lens player; original member name unknown.
  CharaWeightPlayer unknown12d0;  // Inferred role: weight player; original member name unknown.
  CharaWinkPlayer unknown1350;    // Inferred role: wink player; original member name unknown.
  CharaEffectPlayer unknown1390;  // Inferred role: effect player; original member name unknown.
  CharaPartUpdater unknown1650;   // Inferred role: part updater; original member name unknown.
  f32 m_eyeOffset;
  CmdQueue<QUEUE_COUNT, 0> unknown1738;     // Inferred role: queue; original member name unknown.
  CmdQueue<QUEUE_COUNT, 0> unknown2088;     // Inferred role: sub queue; original member name unknown.
  CmdQueue<SUB_QUEUE_COUNT, 0> unknown29d8; // Inferred role: fade queue; original member name unknown.
  mm::Vec3 unknown2fb0;                     // Inferred role: pos; original member name unknown.
  mm::Vec3 unknown2fc0;                     // Inferred role: pos to; original member name unknown.
  mm::Vec3 unknown2fd0;                     // Inferred role: rot; original member name unknown.
  mm::Vec3 unknown2fe0;                     // Inferred role: rot to; original member name unknown.
  u8 unknown2ff0[0x3030 - 0x2ff0];          // Inferred role: 2 ff0; original member name unknown.
  FrameInfo unknown3030;                    // Inferred role: frame info; original member name unknown.
  f32 unknown3044;                          // Inferred role: stream frame; original member name unknown.
  f32 unknown3048;                          // Inferred role: weapon scale; original member name unknown.
  u32 unknown304c[2];                       // Inferred role: hide weapon flags; original member name unknown.
  int unknown3054;                          // Inferred role: reuse flag; original member name unknown.
};

static_assert(sizeof(CharaObj) == 0x3060, "");

} // namespace event
