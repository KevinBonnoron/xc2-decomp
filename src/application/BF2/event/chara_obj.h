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
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"
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
  CHARA_TYPE_UNKNOWN_1 = 1, // Inferred role: driver; original name unknown.
  CHARA_TYPE_UNKNOWN_2 = 2, // Inferred role: blade; original name unknown.
  CHARA_TYPE_UNKNOWN_3 = 3, // Inferred role: npc; original name unknown.
  CHARA_TYPE_UNKNOWN_5 = 5, // Inferred role: enemy; original name unknown.
};

enum WPNHIDEID {
  WPNHIDEID_UNKNOWN_0 = 0, // Inferred role: seq; original name unknown.
  WPNHIDEID_UNKNOWN_1 = 1, // Inferred role: eva; original name unknown.
  WPNHIDEID_UNKNOWN_2 = 2, // Inferred role: hide wpn; original name unknown.
};

class CharaObj {
public:
  static constexpr size_t QUEUE_UNKNOWN_8 = 8;     // Inferred role: queue count; original name unknown.
  static constexpr size_t SUB_QUEUE_UNKNOWN_5 = 5; // Inferred role: sub queue count; original name unknown.

  // Bit indices of the flags, for mm::mtl::unknown027<32>::test/set.
  enum {
    FLAG_UNKNOWN_0 = 0, // Inferred role: attach flag 0 (bone render); original name unknown.
    FLAG_UNKNOWN_1 = 1, // Inferred role: attach flag 1 (bone render); original name unknown.
    FLAG_UNKNOWN_3 = 3, // Inferred role: ready flag; original name unknown.
    FLAG_UNKNOWN_4 = 4, // Inferred role: mount flag; original name unknown.
    FLAG_UNKNOWN_5 = 5, // Inferred role: fade out flag; original name unknown.
    FLAG_UNKNOWN_6 = 6, // Inferred role: model stream flag; original name unknown.
    FLAG_UNKNOWN_7 = 7, // Inferred role: disp jiji flag; original name unknown.
  };

  enum {
    STATE_UNKNOWN_1 = 1, // Role and original name unknown.
    STATE_UNKNOWN_2 = 2, // Role and original name unknown.
    STATE_UNKNOWN_3 = 3, // Role and original name unknown.
    STATE_UNKNOWN_4 = 4, // Role and original name unknown.
    STATE_UNKNOWN_5 = 5, // Role and original name unknown.
    STATE_UNKNOWN_6 = 6, // Role and original name unknown.
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
  bool isReady() const { return unknownca0.test(FLAG_UNKNOWN_3); }
  gf::GF_OBJ_HANDLE *getHandle() const { return unknownd40; }
  IAttachActor *getAttachActor() const { return m_iAttachActor; }
  const FrameInfo &getFrameInfo() const { return m_frameInfo; }

private:
  CharaSetPos m_charaSetPos; // Inferred role: cmd set pos; original member name unknown.
  CharaSetRot m_charaSetRot; // Inferred role: cmd set rot; original member name unknown.
  u8 _28[0x30 - 0x28];
  CharaWalkPos m_charaWalkPos;               // Inferred role: cmd walk pos; original member name unknown.
  CharaLinerPos m_charaLinerPos;             // Inferred role: cmd liner pos; original member name unknown.
  CharaTurnRot m_charaTurnRot;               // Inferred role: cmd turn rot; original member name unknown.
  CharaLinerRot m_charaLinerRot;             // Inferred role: cmd liner rot; original member name unknown.
  CharaSetTar m_charaSetTar;                 // Inferred role: cmd set tar; original member name unknown.
  CharaSetIdle m_charaSetIdle;               // Inferred role: cmd set idle; original member name unknown.
  CharaPlayActionAuto m_charaPlayActionAuto; // Inferred role: cmd play action auto; original member name unknown.
  CharaPlayAction m_charaPlayAction;         // Inferred role: cmd play action; original member name unknown.
  CharaStopAction m_charaStopAction;         // Inferred role: cmd stop action; original member name unknown.
  CharaPlayMotion m_charaPlayMotion;         // Inferred role: cmd play motion; original member name unknown.
  CharaPlayMotionABC m_charaPlayMotionABC;   // Inferred role: cmd play motion abc; original member name unknown.
  CharaPlayEva m_charaPlayEva;               // Inferred role: cmd play eva; original member name unknown.
  CharaPlayEvaEff m_charaPlayEvaEff;         // Inferred role: cmd play eva eff; original member name unknown.
  CharaHideWpn m_charaHideWpn;               // Inferred role: cmd hide wpn; original member name unknown.
  CharaPlayHead m_charaPlayHead;             // Inferred role: cmd play head; original member name unknown.
  CharaStopHead m_charaStopHead;             // Inferred role: cmd stop head; original member name unknown.
  CharaPlayFacial m_charaPlayFacial;         // Inferred role: cmd play facial; original member name unknown.
  CharaPlayTalkAuto m_charaPlayTalkAuto;     // Inferred role: cmd play talk auto; original member name unknown.
  CharaPlayTalk m_charaPlayTalk;             // Inferred role: cmd play talk; original member name unknown.
  CharaPlayWink m_charaPlayWink;             // Inferred role: cmd play wink; original member name unknown.
  CharaMount m_charaMount;                   // Inferred role: cmd mount; original member name unknown.
  CharaFade m_charaFade;                     // Inferred role: cmd fade; original member name unknown.
  // Inferred role: flags; original member name unknown. A bit set (decision 48): the game reads single bits of this word with byte loads, next to the
  // 32-bit state at 0xca4 (update 0x71000c00e0: `ldrb w8, [x19, #0xca0]; tbnz w8, #3`; isFadeOut 0x71000c8310: `ldrb; ubfx #5`), and the other event
  // classes keep their flag words in the same bit set (CharaDysUpdater, CharaWinkPlayer, CharaLensPlayer...).
  mm::mtl::unknown027<32> unknownca0;
  u32 unknownca4; // Inferred role: state; original member name unknown.
  mm::mtl::FixStr<64> m_name;
  CHARA_TYPE unknowncec;                 // Inferred role: type; original member name unknown.
  u32 unknowncf0;                        // Inferred role: id; original member name unknown.
  mm::mtl::FixStr<64> unknowncf4;        // Inferred role: model name; original member name unknown.
  u32 unknownd38;                        // Inferred role: createModel param2; original member name unknown.
  u32 unknownd3c;                        // Inferred role: offscr id; original member name unknown.
  gf::GF_OBJ_HANDLE *unknownd40;         // Inferred role: handle; original member name unknown.
  gf::GfEvtModel *unknownd48;            // Inferred role: model; original member name unknown.
  ModelObj *m_modelObj;                  // Inferred role: model object; original member name unknown.
  IAttachActor *m_iAttachActor;          // Inferred role: attach actor; original member name unknown.
  CharaIKUpdater m_charaIKUpdater;       // Inferred role: ik updater; original member name unknown.
  CharaDysUpdater m_charaDysUpdater;     // Inferred role: dys updater; original member name unknown.
  CharaTarPlayer m_charaTarPlayer;       // Inferred role: tar player; original member name unknown.
  CharaTarPlayerMot m_charaTarPlayerMot; // Inferred role: tar player mot; original member name unknown.
  CharaLensPlayer m_charaLensPlayer;     // Inferred role: lens player; original member name unknown.
  CharaWeightPlayer m_charaWeightPlayer; // Inferred role: weight player; original member name unknown.
  CharaWinkPlayer m_charaWinkPlayer;     // Inferred role: wink player; original member name unknown.
  CharaEffectPlayer m_charaEffectPlayer; // Inferred role: effect player; original member name unknown.
  CharaPartUpdater m_charaPartUpdater;   // Inferred role: part updater; original member name unknown.
  f32 m_eyeOffset;
  CmdQueue<QUEUE_UNKNOWN_8, 0> unknown1738;     // Inferred role: queue; original member name unknown.
  CmdQueue<QUEUE_UNKNOWN_8, 0> unknown2088;     // Inferred role: sub queue; original member name unknown.
  CmdQueue<SUB_QUEUE_UNKNOWN_5, 0> unknown29d8; // Inferred role: fade queue; original member name unknown.
  mm::Vec3 m_pos;                               // Inferred role: pos; named after the game accessor event::CharaObj::getPos.
  mm::Vec3 unknown2fc0;                         // Inferred role: pos to; original member name unknown.
  mm::Vec3 m_rot;                               // Inferred role: rot; named after the game accessor event::CharaObj::getRot.
  mm::Vec3 unknown2fe0;                         // Inferred role: rot to; original member name unknown.
  mm::Mat44 unknown2ff0;                        // Inferred role: matrix; original member name unknown.
  FrameInfo m_frameInfo;                        // Inferred role: frame info; original member name unknown.
  f32 unknown3044;                              // Inferred role: stream frame; original member name unknown.
  f32 unknown3048;                              // Inferred role: weapon scale; original member name unknown.
  u32 unknown304c[2];                           // Inferred role: hide weapon flags; original member name unknown.
  int unknown3054;                              // Inferred role: reuse flag; original member name unknown.
};

static_assert(sizeof(CharaObj) == 0x3060, "");

} // namespace event
