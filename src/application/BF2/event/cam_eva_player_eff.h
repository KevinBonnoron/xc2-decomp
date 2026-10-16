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
  RchaCamEff *mRcha;
  f32 frame;
};

static_assert(sizeof(CamEvaPlayerEff) == 0x18, "");

} // namespace event
