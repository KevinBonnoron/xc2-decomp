#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_sequence.h"
#include "types.h"

namespace gf {

struct SDataOption;
class GfMenuCallContext;

class GfMenuObjOption : public GfMenuObject {
public:
  static bool attach(GfMenuCallContext *context);
  void initialize() override;
  void finalize() override;
  void update() override;

  static void initOptionData(SDataOption &option);
  static int getVolumeValue(u8 level, u8 levelMax);
  static u32 getGammaValue(u8 level, u8 levelMax);
  static u8 getVolumeLevel(u8 value, u8 levelMax);
  static u8 getGammaLevel(u16 value, u8 levelMax);

  u8 _24[0x128 - 0x24];
  GfMenuSequence<GfMenuObjOption, 8> unknown128; // Inferred role: queued steps; original member name unknown.
};

static_assert(offsetof(GfMenuObjOption, unknown128) == 0x128, "");

} // namespace gf
