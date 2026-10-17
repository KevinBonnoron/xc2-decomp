#pragma once
#include "event/chara_wpn_asm.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {
class GfEvtModel;
} // namespace gf

namespace event {

class CharaDysUpdater;
class CharaObj;

class CharaEvaPlayer {
public:
  CharaEvaPlayer();
  virtual ~CharaEvaPlayer();
  void stop();
  void update(f32 delta);
  void setSpMotWeapon(bool isLeft, void *data);
  void setScaleWeapon(f32 scale);
  void playTar(bool isPlay, const mm::Vec3 &tar);
  void playAction(int type);
  void setDispWeapon(int type);
  void setMountWeapon(int type);
  void setBattleWeapon(int type);
  void playFoot(bool isPlay);
  void play(CharaObj *chara, gf::GfEvtModel *model, CharaDysUpdater *dys, void *data, void *weaponData, bool isLoop, bool isBlend, const char *name,
            const mm::Vec3 &offset);
  void stopTar();
  void stopAction();

  void setPos(const mm::Vec3 &pos) { this->pos = pos; }

private:
  u8 _08[0x88 - 0x08];
  CharaWpnAsm wpnAsmRight;
  CharaWpnAsm wpnAsmLeft;
  mm::Vec3 pos;
};

static_assert(sizeof(CharaEvaPlayer) == 0x150, "");

} // namespace event
