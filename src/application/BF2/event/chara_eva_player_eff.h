#pragma once
#include "types.h"

class RchaChrEff;
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
  gf::GfEvtModel *model;
  CharaEffectPlayer *effectPlayer;
  RchaChrEff *rcha;
  f32 frame;
};

static_assert(sizeof(CharaEvaPlayerEff) == 0x28, "");

} // namespace event
