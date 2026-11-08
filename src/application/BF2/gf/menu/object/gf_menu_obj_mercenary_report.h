#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace gf {
class GfMenuBladeList;
class GfMenuCallContext;
class GfMenuReferenceNumber;

class GfMenuObjMercenaryReport : public GfMenuObject {
public:
  GfMenuObjMercenaryReport(u32 handle);
  ~GfMenuObjMercenaryReport() override;
  void initialize() override;
  void finalize() override;
  void update() override;
  bool seqCheckAchive();
  bool seqClose();
  bool seqDispInfo();
  bool seqDispReward();
  bool seqEnd();
  bool seqWaitEndKizuna();
  bool seqWaitLoadKizuna();

  u32 unknown24;                                           // Inferred role: team; original member name unknown.
  GfMenuBladeList *unknown28;                              // Inferred role: team blades; original member name unknown.
  GfMenuSequence<GfMenuObjMercenaryReport, 10> unknown30;  // Inferred role: report steps; original member name unknown.
  bool unknown358;                                         // Inferred role: animation or control started flag; original member name unknown.
  bool unknown359;                                         // Inferred role: reward closed flag; original member name unknown.
  mm::mtl::IntrusivePtr<GfMenuReferenceNumber> unknown360; // Inferred role: reward number; original member name unknown.
  GfMenuCallContext *unknown368;                           // Inferred role: reward call context; original member name unknown.
  GfMenuCallContext *unknown370;                           // Inferred role: kizuna ring call context; original member name unknown.
};

static_assert(offsetof(GfMenuObjMercenaryReport, unknown24) == 0x24, "");
static_assert(offsetof(GfMenuObjMercenaryReport, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuObjMercenaryReport, unknown30) == 0x30, "");
static_assert(offsetof(GfMenuObjMercenaryReport, unknown358) == 0x358, "");
static_assert(offsetof(GfMenuObjMercenaryReport, unknown359) == 0x359, "");
static_assert(offsetof(GfMenuObjMercenaryReport, unknown360) == 0x360, "");
static_assert(offsetof(GfMenuObjMercenaryReport, unknown368) == 0x368, "");
static_assert(offsetof(GfMenuObjMercenaryReport, unknown370) == 0x370, "");
static_assert(sizeof(GfMenuObjMercenaryReport) == 0x378, "");

} // namespace gf
