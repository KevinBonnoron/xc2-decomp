#pragma once
#include <stddef.h>

#include "gf/menu/gf_menu_fade.h"
#include "gf/request/gf_scom.h"
#include "mm_math/mm_col4.h"
#include "types.h"

namespace gf {

struct GF_SCOM_HANDLE;

class SCOM_FADE : public SCOM {
public:
  // Inferred role: pending fade request of one fade channel; original type name unknown.
  struct unknown001 {
    u32 unknown00;      // Inferred role: fade channel, -1 when no fade is pending; original member name unknown.
    u32 unknown04;      // Inferred role: frame count; original member name unknown.
    mm::Col4 unknown08; // Inferred role: color; original member name unknown.
  };

  SCOM_FADE(GF_SCOM_HANDLE *handle);
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 channel, u32 frame, const mm::Col4 &color);

  static unknown001 s_fades[GfMenuFade::FADE_UNKNOWN_3];
  static GF_SCOM_HANDLE *s_hCreatedReq;
};

static_assert(offsetof(SCOM_FADE::unknown001, unknown08) == 0x08, "");
static_assert(sizeof(SCOM_FADE::unknown001) == 0x18, "");
static_assert(sizeof(SCOM_FADE) == 0x20, "");

} // namespace gf
