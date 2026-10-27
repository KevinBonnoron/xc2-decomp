#pragma once

#include "grlib/cglib_vtx_instans.h"
#include "types.h"

namespace ml {

class DrResMdoAlpTbl : public grlib::CGLibVtxInstans {
public:
  DrResMdoAlpTbl();
  static int calcCntWorkSize(u32 count);
};

} // namespace ml
