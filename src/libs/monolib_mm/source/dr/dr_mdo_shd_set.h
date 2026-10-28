#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibSampler;
} // namespace grlib

namespace ml {
class DrMdoSetup;
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
  u8 _16[0x18 - 0x16];
  u16 unknown18; // Inferred role: second texture index; original member name unknown.
  u8 _1a[0x1c - 0x1a];
  u16 unknown1c; // Inferred role: third texture index; original member name unknown.
};

static_assert(offsetof(MdsMpfMatInfoHeader, unknown12) == 0x12, "");
static_assert(offsetof(MdsMpfMatInfoHeader, unknown18) == 0x18, "");
static_assert(offsetof(MdsMpfMatInfoHeader, unknown1c) == 0x1c, "");

struct DrResMpfSampler {
  u8 _00[0x08];
  grlib::CGLibSampler *unknown08; // Inferred role: sampler; original member name unknown.
  grlib::CGLibSampler *unknown10; // Inferred role: second sampler; original member name unknown.
  grlib::CGLibSampler *unknown18; // Inferred role: third sampler; original member name unknown.
};

static_assert(offsetof(DrResMpfSampler, unknown08) == 0x08, "");
static_assert(offsetof(DrResMpfSampler, unknown18) == 0x18, "");

class DrMdoShdSet {
public:
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

  MdoWrkMatRes *unknown08; // Inferred role: material resource; original member name unknown.
};

static_assert(offsetof(DrMdoShdSetMpf, unknown08) == 0x08, "");

class DrMdoShdSetPrePass : public DrMdoShdSet {
public:
  enum PrePassType {};

  void preshd_Inst(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_InstT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
  void preshd_Inst_Al(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list, PrePassType type);
};

class DrMdoShdSetShadow : public DrMdoShdSet {
public:
  void shwShd_Fw(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);
  void shwShd_Spt_Inst(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);
  void shwShd_Spt_InstT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);
  void shwShd_InstMot(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);
  void shwShd_InstMotT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);
  void shwShd_InstT(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);
  void shwShd_Inst(int index, const MdsMatInfoHeader *header, int uniformIndex, int unused, DrShdDataList *list);

  void unknown001(int index, DrResShdShw *shw, DrShdDataList *list);

  static const u8 s_pShwUseShdader[];
  static const u8 s_pShwFethcDef[];
  static const u8 s_pShwFethcMof[];
  static const u8 s_pShwTypeDec[];
  static const u8 *const s_pShwFethcTbl[2];
};

} // namespace ml
