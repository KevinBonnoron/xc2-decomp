#pragma once
#include "event/chara_eva_player.h"
#include "event/i_cmd.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {
class GfEvtModel;
} // namespace gf

namespace event {

class CharaDysUpdater;

class CharaPlayEva : public ICmd {
public:
  enum {
    FLAG_CHARA = 1 << 0,
    FLAG_WEAPON = 1 << 1,
    FLAG_PLAY = 1 << 2,
    FLAG_LOOP = 1 << 3,
  };

  virtual RESULT update(const Param &param);
  virtual void term();

  void setPos(const mm::Vec3 &pos) { evaPlayer.setPos(pos); }

private:
  u32 flags;
  gf::GfEvtModel *model;
  CharaDysUpdater *dysUpdater;
  void *data;
  void *weaponData;
  f32 life;
  CharaEvaPlayer evaPlayer;
};

static_assert(sizeof(CharaPlayEva) == 0x190, "");

} // namespace event
