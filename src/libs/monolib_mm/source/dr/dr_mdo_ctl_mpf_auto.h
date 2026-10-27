#pragma once
#include <stddef.h>

#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace ml {
class DrMdoMpfMan;
struct _wkMpfAutoBuff;
struct _MPFWorkAutoInf;

class DrMdoCtlMpfAuto {
public:
  // Inferred role: auto mpf resource header; original type name unknown.
  struct unknown001 {
    s32 unknown00; // Inferred role: object count; original member name unknown.
  };

  DrMdoCtlMpfAuto();
  ~DrMdoCtlMpfAuto();
  void autoMpfRelease();
  void resetPrePos();
  void setBuffTbl(_wkMpfAutoBuff **table, int count);
  void SeqListCount();

  const unknown001 *unknown00; // Inferred role: resource header; original member name unknown.
  u8 _08[0x28 - 0x08];
  u64 unknown28; // Inferred role: unknown value cleared by the constructor; original member name unknown.
  u8 _30[0x60 - 0x30];
  _wkMpfAutoBuff **unknown60; // Inferred role: buffer table; original member name unknown.
  s32 unknown68;              // Inferred role: buffer table count; original member name unknown.
  s32 unknown6c;              // Inferred role: unknown value cleared by the constructor; original member name unknown.
  s32 unknown70;              // Inferred role: unknown value cleared by the constructor; original member name unknown.
  u8 _74[0x80 - 0x74];
  s32 unknown80; // Inferred role: sequence index; original member name unknown.
  s32 unknown84; // Inferred role: unknown value cleared by the constructor; original member name unknown.
  u8 _88[0xc0 - 0x88];
  mm::Vec3 *unknownc0; // Inferred role: previous positions; original member name unknown.
  u8 _c8[0xd0 - 0xc8];
  u64 unknownd0; // Inferred role: unknown value cleared by the constructor; original member name unknown.
  s32 unknownd8; // Inferred role: unknown value cleared by the constructor; original member name unknown.
  u8 _dc[0x158 - 0xdc];
  _MPFWorkAutoInf **unknown158; // Inferred role: work lists; original member name unknown.
  _MPFWorkAutoInf **unknown160; // Inferred role: work list tails; original member name unknown.
  DrMdoMpfMan *unknown168;      // Inferred role: mpf manager; original member name unknown.
};

static_assert(offsetof(DrMdoCtlMpfAuto, unknown28) == 0x28, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknown60) == 0x60, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknown68) == 0x68, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknown70) == 0x70, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknown80) == 0x80, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknownc0) == 0xc0, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknownd0) == 0xd0, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknownd8) == 0xd8, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknown158) == 0x158, "");
static_assert(offsetof(DrMdoCtlMpfAuto, unknown168) == 0x168, "");

} // namespace ml
