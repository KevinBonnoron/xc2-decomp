#pragma once
#include <stddef.h>

#include "gf/request/gf_scom.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

struct GF_SCOM_HANDLE;

class SCOM_SCRIPT : public SCOM {
public:
  SCOM_SCRIPT(GF_SCOM_HANDLE *handle, u32 slot, const mm::mtl::FixStr<32> &name, bool isWait)
      : SCOM(handle, SCOM_TYPE_UNKNOWN_29, SCOM_EXEC_UNKNOWN_0, 1), unknown1c(slot), unknown20(name), unknown44(0), unknown48(isWait) {}
  bool exec(const fw::UpdateInfo &info) override;
  static GF_SCOM_HANDLE *create(u32 slot, const char *script, bool isWait);

  u32 unknown1c;                 // Inferred role: script slot; original member name unknown.
  mm::mtl::FixStr<32> unknown20; // Inferred role: script name without path and extension; original member name unknown.
  int unknown44;                 // Inferred role: state (0 load, 1 wait load, 2 wait end); original member name unknown.
  bool unknown48;                // Inferred role: wait until the script ends; original member name unknown.
};

static_assert(offsetof(SCOM_SCRIPT, unknown1c) == 0x1c, "");
static_assert(offsetof(SCOM_SCRIPT, unknown20) == 0x20, "");
static_assert(offsetof(SCOM_SCRIPT, unknown44) == 0x44, "");
static_assert(offsetof(SCOM_SCRIPT, unknown48) == 0x48, "");
static_assert(sizeof(SCOM_SCRIPT) == 0x50, "");

} // namespace gf
