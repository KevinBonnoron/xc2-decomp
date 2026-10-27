#pragma once
#include <stddef.h>

#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
struct GF_SCOM_HANDLE;

enum SCOM_TYPE {
  SCOM_TYPE_UNKNOWN_0 = 0,
  SCOM_TYPE_UNKNOWN_1 = 1,
  SCOM_TYPE_UNKNOWN_2 = 2,
  SCOM_TYPE_UNKNOWN_5 = 5,
  SCOM_TYPE_UNKNOWN_8 = 8,
  SCOM_TYPE_UNKNOWN_10 = 10,
  SCOM_TYPE_UNKNOWN_11 = 11,
  SCOM_TYPE_UNKNOWN_12 = 0xc,
  SCOM_TYPE_UNKNOWN_15 = 15,
  SCOM_TYPE_UNKNOWN_19 = 19,
  SCOM_TYPE_UNKNOWN_20 = 20,
  SCOM_TYPE_CREATE_PARTY_OBJ = 0x16,
  SCOM_TYPE_UNKNOWN_24 = 24,
  SCOM_TYPE_UNKNOWN_25 = 25,
  SCOM_TYPE_CREATE_MAP_OBJ = 0x1a,
  SCOM_TYPE_FADE = 0x1b,
  SCOM_TYPE_UNKNOWN_28 = 28,
  SCOM_TYPE_UNKNOWN_32 = 32,
  SCOM_TYPE_UNKNOWN_33 = 33,
  SCOM_TYPE_UNKNOWN_35 = 35,
  SCOM_TYPE_UNKNOWN_37 = 37,
  SCOM_TYPE_UNKNOWN_38 = 38,
  SCOM_TYPE_UNKNOWN_39 = 39,
  SCOM_TYPE_UNKNOWN_40 = 0x28,
  SCOM_TYPE_UNKNOWN_41 = 41,
  SCOM_TYPE_UNKNOWN_45 = 45,
  SCOM_TYPE_UNKNOWN_46 = 46,
  SCOM_TYPE_UNKNOWN_47 = 0x2f,
  SCOM_TYPE_UNKNOWN_49 = 49,
  SCOM_TYPE_PARTY_ADD = 0x35,
  SCOM_TYPE_UNKNOWN_58 = 58,
  SCOM_TYPE_UNKNOWN_59 = 59,
  SCOM_TYPE_UNKNOWN_60 = 60,
  SCOM_TYPE_UNKNOWN_62 = 62,
  SCOM_TYPE_UNKNOWN_64 = 0x40,
  SCOM_TYPE_UNKNOWN_66 = 0x42,
  SCOM_TYPE_UNKNOWN_67 = 0x43,
  SCOM_TYPE_UNKNOWN_68 = 68,
  SCOM_TYPE_UNKNOWN_69 = 0x45,
  SCOM_TYPE_UNKNOWN_71 = 0x47,
  SCOM_TYPE_UNKNOWN_72 = 0x48,
  SCOM_TYPE_UNKNOWN_73 = 0x49,
};

enum SCOM_EXEC {
  SCOM_EXEC_UNKNOWN_0 = 0,
};

class SCOM {
public:
  SCOM(GF_SCOM_HANDLE *handle, SCOM_TYPE type, SCOM_EXEC exec, u16 unknown10);
  virtual ~SCOM() { unknown08 = reinterpret_cast<GF_SCOM_HANDLE *>(-1); }
  virtual bool exec(const fw::UpdateInfo &info) = 0;
  virtual GF_OBJ_HANDLE *getObjHandle() const;

  GF_SCOM_HANDLE *unknown08; // Inferred role: command handle; original member name unknown.
  u16 unknown10;             // Inferred role: unknown flag; original member name unknown.
  SCOM_EXEC unknown14;       // Inferred role: exec mode; original member name unknown.
  SCOM_TYPE unknown18;       // Inferred role: command type; original member name unknown.
};

static_assert(offsetof(SCOM, unknown08) == 0x08, "");
static_assert(offsetof(SCOM, unknown10) == 0x10, "");
static_assert(offsetof(SCOM, unknown14) == 0x14, "");
static_assert(offsetof(SCOM, unknown18) == 0x18, "");
static_assert(sizeof(SCOM) == 0x20, "");

} // namespace gf
