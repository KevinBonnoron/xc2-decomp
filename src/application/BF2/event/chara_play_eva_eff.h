#pragma once
#include "event/chara_eva_player_eff.h"
#include "event/i_cmd.h"
#include "types.h"

namespace gf {
class GfEvtModel;
} // namespace gf

namespace event {

class CharaEffectPlayer;

class CharaPlayEvaEff : public ICmd {
public:
  enum {
    FLAG_UNKNOWN_0 = 1 << 0, // Inferred role: play flag; original name unknown.
    FLAG_UNKNOWN_1 = 1 << 1, // Inferred role: loop flag; original name unknown.
  };

  virtual RESULT update(const Param &param);
  virtual void term();

private:
  u32 unknown08;                // Inferred role: flags; original member name unknown.
  gf::GfEvtModel *unknown10;    // Inferred role: model; original member name unknown.
  CharaEffectPlayer *unknown18; // Inferred role: effect player; original member name unknown.
  void *unknown20;              // Inferred role: data; original member name unknown.
  f32 unknown28;                // Inferred role: life; original member name unknown.
  CharaEvaPlayerEff unknown30;  // Inferred role: eva player; original member name unknown.
};

static_assert(sizeof(CharaPlayEvaEff) == 0x58, "");

} // namespace event
