#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrResMdoMeshObj;
struct MdoWrkVanishEffect;

class DrResEtcParams {
public:
  DrResEtcParams();
  void setParams(f32 value);
  void setPreParams(f32 value);
  void setInitParams(f32 value);
  void update();
  f32 getValParams() const;
  f32 getParams() const;

  u16 unknown00; // Inferred role: param flags; original member name unknown.
  u8 _02[0x04 - 0x02];
  f32 unknown04[2]; // Inferred role: params per buffer; original member name unknown.
  f32 unknown0c[2]; // Inferred role: pre params per buffer; original member name unknown.
  f32 m_params;
};

static_assert(offsetof(DrResEtcParams, unknown00) == 0x00, "");
static_assert(offsetof(DrResEtcParams, unknown04) == 0x04, "");
static_assert(offsetof(DrResEtcParams, m_params) == 0x14, "");
static_assert(sizeof(DrResEtcParams) == 0x18, "");

// Inferred role: resource etc pam name; original type name unknown.
struct unknown040 {
  u32 unknown00; // Inferred role: name offset; original member name unknown.
  u8 _04[0x10 - 0x04];
};

static_assert(sizeof(unknown040) == 0x10, "");

struct MdsEtcParamsCallBack {
  u16 unknown00; // Inferred role: index into the callback table; original member name unknown.
  u16 unknown02; // Inferred role: param index; original member name unknown.
  u32 unknown04; // Inferred role: mesh parts index; original member name unknown.
  u8 _08[0x14 - 0x08];
};

static_assert(offsetof(MdsEtcParamsCallBack, unknown02) == 0x02, "");
static_assert(offsetof(MdsEtcParamsCallBack, unknown04) == 0x04, "");
static_assert(sizeof(MdsEtcParamsCallBack) == 0x14, "");

class DrResEtcPamObj {
public:
  // Inferred role: model resource header; original type name unknown.
  struct unknown001 {
    u8 _00[0x84];
    u32 unknown84; // Inferred role: offset of the params table; original member name unknown.
  };

  // Inferred role: params table header; original type name unknown.
  struct unknown002 {
    u32 unknown00; // Inferred role: offset of the name table; original member name unknown.
    s32 unknown04; // Inferred role: param count; original member name unknown.
    u8 _08[0x10 - 0x08];
    u32 unknown10; // Inferred role: offset of the initial values; original member name unknown.
  };

  struct wrkCallbackArg {
    DrResMdoMeshObj *unknown00;    // Inferred role: mesh parts; original member name unknown.
    MdoWrkVanishEffect *unknown08; // Inferred role: vanish effects; original member name unknown.
  };

  ~DrResEtcPamObj();
  int setup(const u8 *data, u8 *work);
  void update();
  void callback(DrResMdoMeshObj *meshObj, MdoWrkVanishEffect *vanish);
  void mdonode_etcpam_etcmesh_disp(const MdsEtcParamsCallBack *callback, DrResEtcParams *param, wrkCallbackArg &arg);
  void mdonode_etcpam_volfadeanm(const MdsEtcParamsCallBack *callback, DrResEtcParams *param, wrkCallbackArg &arg);
  static int calcWorkSize(const u8 *data);
  static void release(DrResEtcPamObj *&obj);

  const unknown002 *unknown00; // Inferred role: params table header, base of the names; original member name unknown.
  const unknown040 *unknown08; // Inferred role: name table; original member name unknown.
  DrResEtcParams *unknown10;   // Inferred role: params; original member name unknown.
  u32 unknown18;               // Inferred role: params max; original member name unknown.
  u32 unknown1c;               // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(DrResEtcPamObj::unknown001, unknown84) == 0x84, "");
static_assert(offsetof(DrResEtcPamObj::unknown002, unknown10) == 0x10, "");
static_assert(offsetof(DrResEtcPamObj::unknown002, unknown04) == 0x04, "");
static_assert(offsetof(DrResEtcPamObj, unknown10) == 0x10, "");
static_assert(offsetof(DrResEtcPamObj, unknown18) == 0x18, "");
static_assert(offsetof(DrResEtcPamObj, unknown1c) == 0x1c, "");

} // namespace ml
