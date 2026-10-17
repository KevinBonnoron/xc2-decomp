#pragma once
#include "types.h"

namespace gf {
class GfEvtModel;
} // namespace gf

namespace event {

class CharaEffectPlayer;

class CharaEvaPlayerEff {
public:
  CharaEvaPlayerEff();
  virtual ~CharaEvaPlayerEff();
  void stop();
  void update(f32 delta);
  void play(gf::GfEvtModel *model, CharaEffectPlayer *effectPlayer, void *data);

private:
  u8 _08[0x28 - 0x08];
};

static_assert(sizeof(CharaEvaPlayerEff) == 0x28, "");

} // namespace event
