#pragma once
#include <stddef.h>

#include "grlib/cglib_mem_pool.h"
#include "nvn/nvn.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace grlib {

class CGLibCmdBuffer_plf {
public:
  void setCallback();

  NVNcommandBuffer unknown00; // Inferred role: nvn command buffer; original member name unknown.
};

static_assert(sizeof(CGLibCmdBuffer_plf) == 0xa0, "");

// Layout evidence: constructor 0x71007b21e4 (0xa8, 0xb0, 0xb8, 0xe0, 0xe8), setup 0x71007b2428 (0xa0 pool, 0xc8 to
// 0xd8), begin 0x71007b28ac and end 0x71007b2960 (0xc0, 0xe0, 0xe4), and the 0xf0 stride of the arrays at
// CGLibSystemContext 0x88 and 0x268.
class CGLibCmdBuffer : public CGLibCmdBuffer_plf {
public:
  CGLibCmdBuffer();
  ~CGLibCmdBuffer();
  void release();
  void setup(mtl::ALLOC_HANDLE handle, u32 size, u32 controlSize);
  void setup(void *buffer, u32 size, u32 controlSize);
  void setup(u32 offset, u32 size, CGLibMemPool &memPool, u32 controlSize);
  void begin();
  void beginResetOff();
  void end();
  void call();

  CGLibMemPool unknowna0;     // Inferred role: owned command memory pool; original member name unknown.
  NVNcommandHandle unknownc0; // Inferred role: recorded command handle; original member name unknown.
  u32 unknownc8;              // Inferred role: command memory offset; original member name unknown.
  u32 unknowncc;              // Inferred role: command memory size; original member name unknown.
  u32 unknownd0;              // Inferred role: control memory size; original member name unknown.
  CGLibMemPool *unknownd8;    // Inferred role: command memory pool in use; original member name unknown.
  u32 unknowne0;              // Inferred role: command memory used; original member name unknown.
  u32 unknowne4;              // Inferred role: control memory used; original member name unknown.
  bool unknowne8;             // Inferred role: initialized; original member name unknown.
};

static_assert(offsetof(CGLibCmdBuffer, unknowna0) == 0xa0, "");
static_assert(offsetof(CGLibCmdBuffer, unknownc0) == 0xc0, "");
static_assert(offsetof(CGLibCmdBuffer, unknownc8) == 0xc8, "");
static_assert(offsetof(CGLibCmdBuffer, unknownd8) == 0xd8, "");
static_assert(offsetof(CGLibCmdBuffer, unknowne0) == 0xe0, "");
static_assert(offsetof(CGLibCmdBuffer, unknowne8) == 0xe8, "");
static_assert(sizeof(CGLibCmdBuffer) == 0xf0, "");

} // namespace grlib
