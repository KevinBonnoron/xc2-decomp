#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_handle.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
class GfComAsm;

// Executes an asm command on the object until it ends. The layout follows TFieldExecCmd<GfComAsm>::create (0x710050d904)
// and the inlined constructor of the enemy field states.
template <typename T> class TFieldExecCmd {
public:
  struct CreateInfo {
    CreateInfo() : unknown00(INVALID_HANDLE), unknown08(), unknown2c(5.0f) {}

    GF_OBJ_HANDLE *unknown00;      // Inferred role: object; original member name unknown.
    mm::mtl::FixStr<32> unknown08; // Inferred role: command name; original member name unknown.
    f32 unknown2c;                 // Inferred role: time out; original member name unknown.
  };

  TFieldExecCmd() : unknown00(INVALID_HANDLE), unknown08(), unknown2c(5.0f), unknown30(0.0f), unknown34(false), unknown35(false) {}

  ~TFieldExecCmd() { dispose(); }

  void dispose() {
    unknown35 = false;
    unknown34 = false;
    unknown30 = 0.0f;
    CreateInfo info;
    unknown00 = info.unknown00;
    unknown08 = info.unknown08;
    unknown2c = info.unknown2c;
  }

  void create(const CreateInfo &info);
  void update(f32 deltaTime);
  bool execCmd(T &comAsm, const char *command) const;

  GF_OBJ_HANDLE *unknown00;      // Inferred role: object; original member name unknown.
  mm::mtl::FixStr<32> unknown08; // Inferred role: command name; original member name unknown.
  f32 unknown2c;                 // Inferred role: time out; original member name unknown.
  f32 unknown30;                 // Inferred role: elapsed time; original member name unknown.
  bool unknown34;                // Inferred role: executed; original member name unknown.
  bool unknown35;                // Inferred role: executed this update; original member name unknown.
};

static_assert(offsetof(TFieldExecCmd<GfComAsm>::CreateInfo, unknown2c) == 0x2c, "");
static_assert(offsetof(TFieldExecCmd<GfComAsm>, unknown08) == 0x08, "");
static_assert(offsetof(TFieldExecCmd<GfComAsm>, unknown2c) == 0x2c, "");
static_assert(offsetof(TFieldExecCmd<GfComAsm>, unknown34) == 0x34, "");
static_assert(sizeof(TFieldExecCmd<GfComAsm>) == 0x38, "");

} // namespace gf
