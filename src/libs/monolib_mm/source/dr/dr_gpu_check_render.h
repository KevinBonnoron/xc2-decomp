#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "types.h"

namespace grlib {
class CGLibVtxInstans;
} // namespace grlib

namespace ml {

class DrCalcViewWork;
class DrShdDataList;

// Evidence: member offsets from DrGpuCheckRender::DrGpuCheckRender, beginUpdate, endUpdate and stockParmPos.
class DrGpuCheckRender {
public:
  DrGpuCheckRender();
  ~DrGpuCheckRender();
  void beginUpdate();
  void endUpdate();
  void endRender();

  DrCalcViewWork *unknown00;             // Inferred role: view work; original member name unknown.
  DrShdDataList *unknown08;              // Inferred role: shader data list; original member name unknown.
  grlib::CGLibVtxInstans *unknown10;     // Inferred role: instance buffer; original member name unknown.
  grlib::CGLibDblUniformBlock unknown18; // Inferred role: uniform block; original member name unknown.
  void *unknown50;                       // Inferred role: write buffer; original member name unknown.
  s32 unknown58;                         // Inferred role: write offset; original member name unknown.
  s32 unknown5c;                         // Inferred role: begin offset; original member name unknown.
  s32 unknown60;                         // Inferred role: effect mode declaration; original member name unknown.
  s32 unknown64;                         // Inferred role: render mode; original member name unknown.
};

static_assert(offsetof(DrGpuCheckRender, unknown18) == 0x18, "");
static_assert(offsetof(DrGpuCheckRender, unknown50) == 0x50, "");
static_assert(offsetof(DrGpuCheckRender, unknown64) == 0x64, "");

} // namespace ml
