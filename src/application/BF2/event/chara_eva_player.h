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
  void play(CharaObj *chara, gf::GfEvtModel *model, CharaDysUpdater *dysUpdater, void *data, void *weaponData, bool isChara, bool isWeapon, const char *name, const mm::Vec3 &offset);
  void stopTar();
  void stopAction();

  void setPos(const mm::Vec3 &pos) { this->unknown140 = pos; }

private:
  u32 unknown08;              // Inferred role: flags; original member name unknown.
  CharaObj *unknown10;        // Inferred role: chara; original member name unknown.
  gf::GfEvtModel *unknown18;  // Inferred role: model; original member name unknown.
  CharaDysUpdater *unknown20; // Inferred role: dys updater; original member name unknown.
  void *unknown28;            // Inferred role: weapon data; original member name unknown.
  CRchaEx *unknown30;         // Inferred role: rcha; original member name unknown.
  f32 unknown38;              // Inferred role: frame; original member name unknown.
  mm::Vec3 unknown40;         // Inferred role: offset; original member name unknown.
  bool unknown50;             // Inferred role: tar; original member name unknown.
  mm::Vec3 unknown60;         // Inferred role: tar; original member name unknown.
  int unknown70;              // Inferred role: action; original member name unknown.
  int unknown74;              // Inferred role: face type; original member name unknown.
  int unknown78;              // Inferred role: eye type; original member name unknown.
  int unknown7c;              // Inferred role: disp weapon; original member name unknown.
  int unknown80;              // Inferred role: mount weapon; original member name unknown.
  int unknown84;              // Inferred role: battle weapon; original member name unknown.
  CharaWpnAsm unknown88;      // Inferred role: wpn asm right; original member name unknown.
  CharaWpnAsm unknowne0;      // Inferred role: wpn asm left; original member name unknown.
  mm::Vec3 unknown140;        // Inferred role: pos; original member name unknown.
};

static_assert(sizeof(CharaEvaPlayer) == 0x150, "");

} // namespace event
