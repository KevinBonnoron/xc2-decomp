#pragma once
#include "rcha/rcha_node.h"
#include "types.h"

// Declared from the symbols _ZN10RchaCamEffC1Ev (0x710069d640), _ZN10RchaCamEff5setupEN3mtl12ALLOC_HANDLEEPKv
// (0x710069d8a8) and the vtable _ZTV10RchaCamEff (0x71011a75d0); its size is the allocation size in CamEvaPlayerEff::play.
class RchaCamEff : public RchaNode {
public:
  RchaCamEff();
  virtual ~RchaCamEff();
  virtual void setup(mtl::ALLOC_HANDLE handle, const void *data);

private:
  u8 _19a0[0x19b8 - 0x19a0];
};

static_assert(sizeof(RchaCamEff) == 0x19b8, "");
