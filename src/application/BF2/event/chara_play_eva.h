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

  void setPos(const mm::Vec3 &pos) { unknown40.setPos(pos); }

private:
  u32 unknown08;              // Inferred role: flags; original member name unknown.
  gf::GfEvtModel *unknown10;  // Inferred role: model; original member name unknown.
  CharaDysUpdater *unknown18; // Inferred role: dys updater; original member name unknown.
  void *unknown20;            // Inferred role: data; original member name unknown.
  void *unknown28;            // Inferred role: weapon data; original member name unknown.
  f32 unknown30;              // Inferred role: life; original member name unknown.
  CharaEvaPlayer unknown40;   // Inferred role: eva player; original member name unknown.
};

static_assert(sizeof(CharaPlayEva) == 0x190, "");

} // namespace event
