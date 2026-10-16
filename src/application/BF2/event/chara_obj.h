#pragma once
#include <stddef.h>

#include "event/chara_dys_updater.h"
#include "event/chara_effect_player.h"
#include "event/chara_ik_updater.h"
#include "event/chara_lens_player.h"
#include "event/chara_part_updater.h"
#include "event/chara_set_pos.h"
#include "event/chara_set_rot.h"
#include "event/chara_tar_player.h"
#include "event/chara_weight_player.h"
#include "event/chara_wink_player.h"
#include "event/cmd_queue.h"
#include "event/curve.h"
#include "event/frame_manager.h"
#include "event/object_chara.h"
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
  void exitModelStream();
  void renderBone();
  void renderAction();
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
  void setRot(const mm::Vec3 &rot);
  void turnRot(const mm::Vec3 &rot, EVT_rotcvtype cv, f32 frame);
  void linerRot(const mm::Vec3 &rot, f32 frame, CV_TYPE cv);
  void setTar(const TarAxis &axis, f32 frame, EVT_tarcvtype cv, EVT_aimtype aim, f32 weight, f32 speed);
  void resetTar();
  void setLensTarget(const mm::Vec2 &target);
  void setIdle(int type);
  void playAutoAction(f32 frame);
  void playAction(int type, f32 frame, bool isLoop, bool isBlend);
  void stopAction();
  void playMotion(const char *name, f32 frame, f32 blend, f32 speed);
  void initModelStream();
  void playMotionABC(const char *nameA, const char *nameB, const char *nameC, f32 frameA, f32 frameB, f32 frameC, f32 blendA, f32 blendB, f32 blendC);
  void playHead(int type, f32 frame, bool isBlend, bool isBlendOut);
  void stopHead();
  void playFacial(int typeA, f32 weightA, int typeB, f32 weightB, int typeC, f32 weightC, int typeD, f32 weightD, f32 frame, f32 blend);
  void playAutoTalk(f32 frame);
  void playTalk(bool isTalk, f32 frame, bool isBlend, bool isAuto, f32 openMin, f32 openMax, f32 closeMin, f32 closeMax);
  void mount(CharaObj *target, const char *bone, const mm::Vec3 &pos, const mm::Vec3 &rot);
  void resetDynamics(int frame);
  void playFade(bool isIn, f32 frame);
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

  const FrameInfo &getFrameInfo() const { return frameInfo; }

private:
  CharaSetPos cmdSetPos;
  CharaSetRot cmdSetRot;
  u8 _28[0xca0 - 0x28];
  u32 flags;
  u32 state;
  mm::mtl::FixStr<64> name;
  CHARA_TYPE type;
  u32 id;
  mm::mtl::FixStr<64> modelName;
  u8 _D38[0xd40 - 0xd38];
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
  f32 _1730;
  CmdQueue<QUEUE_COUNT, 0> queue;
  CmdQueue<QUEUE_COUNT, 0> subQueue;
  CmdQueue<SUB_QUEUE_COUNT, 0> fadeQueue;
  mm::Vec3 pos;
  u8 _2FC0[0x2fd0 - 0x2fc0];
  mm::Vec3 rot;
  u8 _2FE0[0x3030 - 0x2fe0];
  FrameInfo frameInfo;
  f32 weaponScale;
  u32 hideWeaponFlags[2];
  int offscrId;
  u8 _3058[0x3060 - 0x3058];
};

static_assert(sizeof(CharaObj) == 0x3060, "");

} // namespace event
