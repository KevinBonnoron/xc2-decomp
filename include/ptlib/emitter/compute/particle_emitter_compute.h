#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "types.h"

namespace ptlib {
namespace emitter {

class ComputeUniform {
public:
  ComputeUniform();
  ~ComputeUniform();
  void releaseUniform();
  void createUniform(u32 type, u32 count);
  void createParticlesUniform();
  void updateData(u32 offset, u32 size);
  void updateData();

  static int s_nUniformBlockSize[5];

  u32 unknown00; // Inferred role: uniform type; original member name unknown.
  grlib::CGLibDblUniformBlock unknown08;
};

static_assert(offsetof(ComputeUniform, unknown08) == 0x08, "");
static_assert(sizeof(ComputeUniform) == 0x40, "");

class ComputeManager {
public:
  ComputeManager();
  virtual ~ComputeManager();
  static ComputeManager *get();
  static ComputeManager *&getPtr();
  static void init();
  static void term();
  void initSub();
  void termSub();
  void resetUpdate();
  void update(u32 viewIndex);
  void calculateParticle();
  void calculateLight(u32 viewIndex);
  void calculateClip(u32 viewIndex);

  ComputeUniform unknown08;     // Inferred role: particle uniform buffer; original member name unknown.
  ComputeUniform unknown48;     // Inferred role: emitter uniform buffer; original member name unknown.
  ComputeUniform unknown88[2];  // Inferred role: light uniform buffers; original member name unknown.
  ComputeUniform unknown108[2]; // Inferred role: clip uniform buffers; original member name unknown.
  ComputeUniform unknown188[2]; // Inferred role: uniform buffers per view; original member name unknown.
  u32 unknown208;               // Inferred role: view index; original member name unknown.
  bool unknown20c;              // Inferred role: updated; original member name unknown.
};

static_assert(offsetof(ComputeManager, unknown48) == 0x48, "");
static_assert(offsetof(ComputeManager, unknown88) == 0x88, "");
static_assert(offsetof(ComputeManager, unknown108) == 0x108, "");
static_assert(offsetof(ComputeManager, unknown188) == 0x188, "");
static_assert(offsetof(ComputeManager, unknown208) == 0x208, "");
static_assert(offsetof(ComputeManager, unknown20c) == 0x20c, "");
static_assert(sizeof(ComputeManager) == 0x210, "");

} // namespace emitter
} // namespace ptlib
