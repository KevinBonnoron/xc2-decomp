#pragma once
#include <stddef.h>

#include "grlib/cglib_sampler.h"
#include "grlib/cglib_vtx_fetch.h"
#include "grlib/cglib_vtx_index.h"
#include "grlib/cglib_vtx_vertex.h"

namespace ptlib {

class StaticAllocObj;

namespace screen {

// Layout evidence: init 0x7100937858, InitSub 0x7100937930, term 0x7100937a70.
class ScreenRenderManager {
public:
  ScreenRenderManager() : unknown0e0(nullptr) {}

  static ScreenRenderManager *get();
  static ScreenRenderManager *&getPtr();
  static bool isValid();
  static void init();
  static void term();
  void InitSub(StaticAllocObj *allocator);
  void InitVertex();
  void InitTexture();
  void InitFetchVertex();
  void ReleaseSub();

  grlib::CGLibSampler unknown00[4]; // Inferred role: samplers; original member name unknown.
  grlib::CGLibVtxVertex unknown80;  // Inferred role: screen vertex buffer; original member name unknown.
  grlib::CGLibVtxIndex unknowna8;   // Inferred role: screen index buffer; original member name unknown.
  grlib::CGLibVtxFetch unknownd0;   // Inferred role: screen vertex fetch; original member name unknown.
  StaticAllocObj *unknown0e0;       // Inferred role: allocator; original member name unknown.
};

static_assert(offsetof(ScreenRenderManager, unknown80) == 0x80, "");
static_assert(offsetof(ScreenRenderManager, unknowna8) == 0xa8, "");
static_assert(offsetof(ScreenRenderManager, unknownd0) == 0xd0, "");
static_assert(offsetof(ScreenRenderManager, unknown0e0) == 0xe0, "");
static_assert(sizeof(ScreenRenderManager) == 0xe8, "");

} // namespace screen
} // namespace ptlib
