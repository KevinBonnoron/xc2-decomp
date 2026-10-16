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
    u32 type;
    u32 value;
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

  u32 id;
  u32 menu;
  u32 object;
  mm::mtl::FixedVector<GfMenuResult, 4> results;
  bool isTerminated;
};

static_assert(offsetof(GfMenuCallContext, id) == 0x0c, "");
static_assert(offsetof(GfMenuCallContext, menu) == 0x10, "");
static_assert(offsetof(GfMenuCallContext, object) == 0x14, "");
static_assert(offsetof(GfMenuCallContext, results) == 0x18, "");
static_assert(offsetof(GfMenuCallContext, isTerminated) == 0x40, "");
static_assert(sizeof(GfMenuCallContext) == 0x48, "");

} // namespace gf
