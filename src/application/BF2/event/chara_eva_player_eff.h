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
  gf::GfEvtModel *unknown08;              // Inferred role: model; original member name unknown.
  CharaEffectPlayer *m_charaEffectPlayer; // Inferred role: effect player; original member name unknown.
  RchaChrEff *m_rchaChrEff;               // Inferred role: rcha; original member name unknown.
  f32 unknown20;                          // Inferred role: frame; original member name unknown.
};

static_assert(sizeof(CharaEvaPlayerEff) == 0x28, "");

} // namespace event
