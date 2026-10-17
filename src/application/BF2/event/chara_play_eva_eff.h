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
    FLAG_PLAY = 1 << 0,
    FLAG_LOOP = 1 << 1,
  };

  virtual RESULT update(const Param &param);
  virtual void term();

private:
  u32 flags;
  gf::GfEvtModel *model;
  CharaEffectPlayer *effectPlayer;
  void *data;
  f32 life;
  CharaEvaPlayerEff evaPlayer;
};

static_assert(sizeof(CharaPlayEvaEff) == 0x58, "");

} // namespace event
