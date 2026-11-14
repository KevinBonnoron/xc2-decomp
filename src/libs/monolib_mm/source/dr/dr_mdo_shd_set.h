#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrMdoSetup;
struct DrResMpfSampler;
class DrResShdMpf;
struct MdoWrkMatRes;
class DrResShdShw;
class DrShdDataList;
struct MdsMatInfoHeader;

struct MdsMpfMatInfoHeader {
  u8 _00[0x04];
  u32 unknown04; // Inferred role: flags; original member name unknown.
  f32 unknown08; // Inferred role: alpha test reference; original member name unknown.
  u8 _0c[0x12 - 0x0c];
  u16 unknown12; // Inferred role: uniform index; original member name unknown.
  u16 unknown14; // Inferred role: texture index; original member name unknown.
  u16 unknown16; // Inferred role: sampler flags of the texture; original member name unknown.
  u16 unknown18; // Inferred role: second texture index; original member name unknown.
  u16 unknown1a; // Inferred role: sampler flags of the second texture; original member name unknown.
  u16 unknown1c; // Inferred role: third texture index; original member name unknown.
  u16 unknown1e; // Inferred role: sampler flags of the third texture; original member name unknown.
};

static_assert(offsetof(MdsMpfMatInfoHeader, unknown12) == 0x12, "");
static_assert(offsetof(MdsMpfMatInfoHeader, unknown18) == 0x18, "");
static_assert(offsetof(MdsMpfMatInfoHeader, unknown1c) == 0x1c, "");

class DrMdoShdSet {
public:
  void setupMofFetchShader(const MdsMatInfoHeader *header);
  void setOneTexShaderSet(int index, u32 location);
  void setDitherTexShaderSet(u32 location, int index);
  void setDitherShaderSet(u32 location, u32 binding, int index);
  void setFlagWaveTexSet(u32 location, int index);
  void setFlagWaveUniform(int index, u32 binding);

  DrMdoSetup *unknown00; // Inferred role: setup; original member name unknown.
};

static_assert(sizeof(DrMdoShdSet) == 0x08, "");

class DrMdoShdSetMpf : public DrMdoShdSet {
public:
  void mpfshd_stm_bill(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);
  void mpfshd_stm_wind(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);
  void mpfshd_stm_bill_wind(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);
  void mpfshd_pre_bill(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);
  void mpfshd_pre_bill_nuki(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);
  void mpfshd_pre_mdl(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);
  void mpfshd_pre_mdl_nuki(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);
  void mpfshd_pre_Dithe_nom(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);
  void mpfshd_pre_Dithe_nuki(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);
  void mpfshd_drw_bill(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);
  void mpfshd_drw_mdl(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);
  void mpfshd_drw_mdl_nonom(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);
  void mpfshd_drw_mdl_def(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);
  void mpfshd_drw_mdl_defnonom(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);
  void mpfshd_drw_mdl_normalmap(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);
  void mpfshd_cull_fade_mdl(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);

  void unknown001(DrResShdMpf *shd, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler);

  static void (DrMdoShdSetMpf::*const s_pMpfMaterial[])(DrResShdMpf *shd, DrShdDataList *list, const MdsMpfMatInfoHeader *header, const DrResMpfSampler *sampler, bool isPre);

  MdoWrkMatRes *unknown08; // Inferred role: material resource; original member name unknown.
};

static_assert(offsetof(DrMdoShdSetMpf, unknown08) == 0x08, "");

class DrMdoShdSetPrePass : public DrMdoShdSet {
public:
  enum PrePassType {
    PRE_PASS_TYPE_UNKNOWN_1 = 1, // Inferred role: pre pass; original name unknown.
    PRE_PASS_TYPE_UNKNOWN_2,     // Inferred role: first thickness pass; original name unknown.
    PRE_PASS_TYPE_UNKNOWN_3,     // Inferred role: second thickness pass; original name unknown.
  };

  void preshd_Obj(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_ObjT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_Obj_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_ObjT_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_Mot(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_MotT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_Mot_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_MotT_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_Inst(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_InstT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_InstT_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_Inst_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_Inst_Bill_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_InstT_Bill_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_Fw(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_FwT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_FwT_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_Fw_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_ObjT_Al_FS(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_MotT_Al_FS(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_FwT_Al_Fs(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);

  static void (DrMdoShdSetPrePass::*const s_pPreMaterial[])(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);

  MdoWrkMatRes *unknown08; // Inferred role: material resource; original member name unknown.
};

static_assert(offsetof(DrMdoShdSetPrePass, unknown08) == 0x08, "");

class DrMdoShdSetShadow : public DrMdoShdSet {
public:
  void shwShd_Obj(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);
  void shwShd_ObjT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);
  void shwShd_Mot(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);
  void shwShd_MotT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);
  void shwShd_Fw(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);
  void shwShd_Spt_Inst(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);
  void shwShd_Spt_InstT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);
  void shwShd_InstMot(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);
  void shwShd_InstMotT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);
  void shwShd_InstT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);
  void shwShd_Inst(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);

  void unknown001(int index, DrResShdShw *shw, DrShdDataList *list);
  void unknown002(int index, DrResShdShw *shw, DrShdDataList *list);

  static void (DrMdoShdSetShadow::*const s_pShwMaterial[])(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);
  static const u8 s_pShwUseShdader[];       // Name from the game symbol _ZN2ml17DrMdoShdSetShadow16s_pShwUseShdaderE; also in torna and xc1de.
  static const u8 s_pShwFethcDef[];         // Name from the game symbol _ZN2ml17DrMdoShdSetShadow14s_pShwFethcDefE; also in torna and xc1de.
  static const u8 s_pShwFethcMof[];         // Name from the game symbol _ZN2ml17DrMdoShdSetShadow14s_pShwFethcMofE; also in torna and xc1de.
  static const u8 s_pShwTypeDec[];          // Name from the game symbol _ZN2ml17DrMdoShdSetShadow13s_pShwTypeDecE; also in torna and xc1de.
  static const u8 *const s_pShwFethcTbl[2]; // Name from the game symbol _ZN2ml17DrMdoShdSetShadow14s_pShwFethcTblE; also in torna and xc1de.
};

} // namespace ml
