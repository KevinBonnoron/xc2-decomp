#pragma once
#include "types.h"

class RchaCamEff;

namespace event {

class CamEvaPlayerEff {
public:
  CamEvaPlayerEff();
  virtual ~CamEvaPlayerEff();
  void stop();
  void update(f32 deltaFrame);
  void play(void *data);

private:
  RchaCamEff *unknown08; // Inferred role: rcha; original member name unknown.
  f32 unknown10;         // Inferred role: frame; original member name unknown.
};

static_assert(sizeof(CamEvaPlayerEff) == 0x18, "");

} // namespace event
