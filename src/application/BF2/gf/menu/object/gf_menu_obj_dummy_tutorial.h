#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace gf {

class GfMenuCallContext;
class GfMenuReferenceNumber;

class GfMenuObjDummyTutorial : public GfMenuObject {
public:
  GfMenuObjDummyTutorial(u32 handle);
  ~GfMenuObjDummyTutorial() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  struct OpenParam {
    u32 unknown00; // Inferred role: tutorial; original member name unknown.
  };

  static void open(GfMenuCallContext *context, const OpenParam &param);

  u8 _24[0x28 - 0x24];
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown28; // Inferred role: reference number; original member name unknown.
};

static_assert(offsetof(GfMenuObjDummyTutorial, unknown28) == 0x28, "");

} // namespace gf
