#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace gf {

class GfMenuCallContext : public mm::mtl::ReferenceObject {
public:
  enum STATE {
    STATE_IDLE,
    STATE_ACTIVE,
    STATE_TERM,
  };

  struct GfMenuResult {
    int unknown00; // Inferred role: value; original member name unknown.
    u32 unknown04; // Inferred role: type; original member name unknown.
  };

  GfMenuCallContext();
  ~GfMenuCallContext() override;
  static GfMenuCallContext *create();
  STATE getState();
  bool isTerm() const;
  bool isActive() const;
  void reset();
  void terminate();
  void abort();
  bool popResult(GfMenuResult &result);
  void addResult(const GfMenuResult &result);
  void setup(u32 object, u32 menu);
  void callNext(u32 menu);

  u32 unknown0c;                                   // Inferred role: id; original member name unknown.
  u32 unknown10;                                   // Inferred role: menu; original member name unknown.
  u32 unknown14;                                   // Inferred role: object; original member name unknown.
  mm::mtl::FixedVector<GfMenuResult, 4> unknown18; // Inferred role: results; original member name unknown.
  bool unknown40;                                  // Inferred role: terminated; original member name unknown.
};

static_assert(offsetof(GfMenuCallContext, unknown0c) == 0x0c, "");
static_assert(offsetof(GfMenuCallContext, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuCallContext, unknown14) == 0x14, "");
static_assert(offsetof(GfMenuCallContext, unknown18) == 0x18, "");
static_assert(offsetof(GfMenuCallContext, unknown40) == 0x40, "");
static_assert(sizeof(GfMenuCallContext) == 0x48, "");

} // namespace gf
