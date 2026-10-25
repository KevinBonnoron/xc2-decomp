#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_dec_shader.h"
#include "types.h"

namespace ml {

// Layout from DrShdLgtObj::DrShdLgtObj() and ~DrShdLgtObj() (CGLibDecShader base, four
// CGLibDblUniformBlock constructed at 0x68, 0xa0, 0xd8 and 0x110, -1 stored at 0x148 and 0x150)
// and the 0x158 stride of DrShdLgtMan::getGlobalIBLShader.
class DrShdLgtObj : public grlib::CGLibDecShader {
public:
  grlib::CGLibDblUniformBlock unknown68[4]; // Inferred role: uniform blocks; original member name unknown.
  u8 _148[0x158 - 0x148];
};

static_assert(offsetof(DrShdLgtObj, unknown68) == 0x68, "");
static_assert(sizeof(DrShdLgtObj) == 0x158, "");

} // namespace ml
