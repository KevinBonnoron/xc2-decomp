#pragma once
#include <stddef.h>

#include "dr/dr_mdl_obj.h"
#include "dr/dr_res_mdo_inst_anm_obj.h"
#include "types.h"

namespace ml {
struct MdoWrkMatRes;

struct MdsSeamEtcPosData {
  u32 unknown00;    // Inferred role: object name offset; original member name unknown.
  u32 unknown04;    // Inferred role: eff name offset; original member name unknown.
  f32 unknown08;    // Inferred role: range; original member name unknown.
  u32 unknown0c;    // Inferred role: matrix max; original member name unknown.
  u32 unknown10;    // Inferred role: matrix offset; original member name unknown.
  f32 unknown14[2]; // Inferred role: near clips; original member name unknown.
  f32 unknown1c[2]; // Inferred role: far clips; original member name unknown.
  u32 unknown24;    // Inferred role: groups offset; original member name unknown.
};

static_assert(offsetof(MdsSeamEtcPosData, unknown10) == 0x10, "");
static_assert(offsetof(MdsSeamEtcPosData, unknown14) == 0x14, "");
static_assert(offsetof(MdsSeamEtcPosData, unknown1c) == 0x1c, "");
static_assert(offsetof(MdsSeamEtcPosData, unknown24) == 0x24, "");

struct DrSeamEtcPos {
  const MdsSeamEtcPosData *unknown00; // Inferred role: data; original member name unknown.
  bool unknown08;                     // Inferred role: always disp; original member name unknown.
};

static_assert(sizeof(DrSeamEtcPos) == 0x10, "");

struct DrSeamEtcPosList {
  DrSeamEtcPos *unknown00; // Inferred role: objs; original member name unknown.
  u32 unknown08;           // Inferred role: object max; original member name unknown.
};

// Inferred type: seam resource header; the original type name is unknown.
struct MdsSeamInfo {
  u8 _00[0x18];
  u32 m_seamBaseMdlMax;
  u8 _1c[0x20 - 0x1c];
  u32 m_seamInstMdlMax;
  u8 _24[0x28 - 0x24];
  u32 m_seamColiMax;
  u8 _2c[0x44 - 0x2c];
  u32 m_seamShaderMax;
  u8 _48[0x50 - 0x48];
  u32 m_seamVertexMax;
  u8 _54[0x58 - 0x54];
  u32 m_seamTextureMax;
  u8 _5c[0x64 - 0x5c];
  u32 m_seamMpfMdlMax;
  u8 _68[0x6c - 0x68];
  u32 m_seamEtcPosDataMax;
  u8 _70[0x74 - 0x70];
  u32 m_seamMpfPosDataMax;
};

static_assert(offsetof(MdsSeamInfo, m_seamBaseMdlMax) == 0x18, "");
static_assert(offsetof(MdsSeamInfo, m_seamInstMdlMax) == 0x20, "");
static_assert(offsetof(MdsSeamInfo, m_seamColiMax) == 0x28, "");
static_assert(offsetof(MdsSeamInfo, m_seamShaderMax) == 0x44, "");
static_assert(offsetof(MdsSeamInfo, m_seamVertexMax) == 0x50, "");
static_assert(offsetof(MdsSeamInfo, m_seamTextureMax) == 0x58, "");
static_assert(offsetof(MdsSeamInfo, m_seamMpfMdlMax) == 0x64, "");
static_assert(offsetof(MdsSeamInfo, m_seamEtcPosDataMax) == 0x6c, "");
static_assert(offsetof(MdsSeamInfo, m_seamMpfPosDataMax) == 0x74, "");

class DrMdoCtlSeam : public DrMdlObj {
public:
  void *getColiListTbl();
  u32 getColiListMax();
  u32 isRead(int index) const;
  void setErrCode(int code, int param);
  static int calcSemaAlignment(u32 size, u32 alignment);
  void seamZPrePassEnd();
  void seamThicknessPassEnd(bool value);

  u8 _190[0x1a8 - 0x190];
  MdsSeamInfo *unknown1a8; // Inferred role: seam resource header; original member name unknown.
  u8 _1b0[0x640 - 0x1b0];
  void *unknown640[2]; // Inferred role: collision list tables per buffer; original member name unknown.
  u32 unknown650[2];   // Inferred role: collision list max per buffer; original member name unknown.
  u8 _658[0x698 - 0x658];
  DrResMdoInstAnmObj unknown698; // Inferred role: inst anm object; original member name unknown.
  DrSeamEtcPosList unknown6c8;   // Inferred role: etc pos list; original member name unknown.
  u8 _6d8[0xb38 - 0x6d8];
  MdoWrkMatRes *unknownb38; // Inferred role: saved mat res; original member name unknown.
  u8 _b40[0xc7c - 0xb40];
  u32 unknownc7c; // Inferred role: seam flags; original member name unknown.
  u8 _c80[0xcac - 0xc80];
  s16 unknowncac;    // Inferred role: error code write index; original member name unknown.
  s16 unknowncae[4]; // Inferred role: error codes; original member name unknown.
  u8 _cb6[0xcb8 - 0xcb6];
  u32 unknowncb8[4]; // Inferred role: error parameters; original member name unknown.
  u8 _cc8[0xd1a - 0xcc8];
  u16 unknownd1a; // Inferred role: read bits; original member name unknown.
};

static_assert(offsetof(DrMdoCtlSeam, unknown1a8) == 0x1a8, "");
static_assert(offsetof(DrMdoCtlSeam, unknown640) == 0x640, "");
static_assert(offsetof(DrMdoCtlSeam, unknown650) == 0x650, "");
static_assert(offsetof(DrMdoCtlSeam, unknowncac) == 0xcac, "");
static_assert(offsetof(DrMdoCtlSeam, unknowncae) == 0xcae, "");
static_assert(offsetof(DrMdoCtlSeam, unknowncb8) == 0xcb8, "");
static_assert(offsetof(DrMdoCtlSeam, unknownd1a) == 0xd1a, "");
static_assert(offsetof(DrMdoCtlSeam, unknown698) == 0x698, "");
static_assert(offsetof(DrMdoCtlSeam, unknown6c8) == 0x6c8, "");
static_assert(offsetof(DrMdoCtlSeam, unknownb38) == 0xb38, "");
static_assert(offsetof(DrMdoCtlSeam, unknownc7c) == 0xc7c, "");

class DrMdoCtlSeamAll : public DrMdoCtlSeam {
public:
  u32 getSeamBaseMdlMax() const;
  u32 getSeamInstMdlMax() const;
  u32 getSeamMpfMdlMax() const;
  u32 getSeamTextureMax() const;
  u32 getSeamVertexMax() const;
  u32 getSeamEtcPosDataMax() const;
  u32 getSeamMpfPosDataMax() const;
  u32 getSeamColiMax() const;
  u32 getSeamShaderMax() const;
  void setSelectIdDisp(int id, bool isOff);
  void setMdlReadOff(bool isOff);
  bool isReadSafe() const;
  bool isRenderSafe() const;
  void debugRender();
  void setClearResource(bool isClear);
  void callZPrePassSeamAll();
  void callThicknessFirstSeamAll();
  void callThicknessSecondSeamAll();
  void callRenderSeamAll();
  void callGBuffRenderSeamAll();
  void callLightPrePassRenderSeamAll();
  void callAlphaRenderSeamAll();
  void callSpAlphaRenderSeamAll();
  void callRefractionRenderSeamAll();
  void callRenderSeamEnvMap();
  void callGBuffRenderSeamEnvMap();
  void callLightPrePassRenderSeamEnvMap();
  void callAlphaRenderSeamEnvMap();
  void callSpAlphaRenderSeamEnvMap();
  void callRefractionRenderSeamEnvMap();
};

} // namespace ml
