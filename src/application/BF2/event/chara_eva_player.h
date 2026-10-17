#pragma once
#include "event/chara_wpn_asm.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

class CRchaEx;
namespace gf {
class GfEvtModel;
} // namespace gf

namespace event {

class CharaDysUpdater;
class CharaObj;

class CharaEvaPlayer {
public:
  enum {
    FLAG_CHARA = 1 << 0,
    FLAG_WEAPON = 1 << 1,
    FLAG_SP_MOTION = 1 << 2,
    FLAG_WEAPON_OBJ = 1 << 3,
  };

  CharaEvaPlayer();
  virtual ~CharaEvaPlayer();
  void stop();
  void update(f32 delta);
  void setSpMotWeapon(bool isSpMotion, void *data);
  void setScaleWeapon(f32 scale);
  void playTar(bool isPlay, const mm::Vec3 &tar);
  void playAction(int type);
  void setDispWeapon(int type);
  void setMountWeapon(int type);
  void setBattleWeapon(int type);
  void playFoot(bool isRight);
  void play(CharaObj *chara, gf::GfEvtModel *model, CharaDysUpdater *dysUpdater, void *data, void *weaponData, bool isChara, bool isWeapon,
            const char *name, const mm::Vec3 &offset);
  void stopTar();
  void stopAction();

  void setPos(const mm::Vec3 &pos) { this->pos = pos; }

private:
  u32 flags;
  CharaObj *chara;
  gf::GfEvtModel *model;
  CharaDysUpdater *dysUpdater;
  void *weaponData;
  CRchaEx *rcha;
  f32 frame;
  mm::Vec3 offset;
  bool isTar;
  mm::Vec3 tar;
  int action;
  int faceType;
  int eyeType;
  int dispWeapon;
  int mountWeapon;
  int battleWeapon;
  CharaWpnAsm wpnAsmRight;
  CharaWpnAsm wpnAsmLeft;
  mm::Vec3 pos;
};

static_assert(sizeof(CharaEvaPlayer) == 0x150, "");

} // namespace event
