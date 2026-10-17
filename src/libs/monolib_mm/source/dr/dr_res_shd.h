#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrResFetch;
class DrShdDataObj;

class DrResShdMpf {
public:
  DrResShdMpf(DrShdDataObj *dataObj, int type);
  void setShaderParam();
  void setupShader(u32 mode);

  DrShdDataObj *m_dataObj;
  s32 m_locations[8];
  u16 m_flags;
  u16 m_type;
  u32 m_declOfs[2];
};

static_assert(offsetof(DrResShdMpf, m_flags) == 0x28, "");
static_assert(offsetof(DrResShdMpf, m_declOfs) == 0x2c, "");
static_assert(sizeof(DrResShdMpf) == 0x38, "");

class DrResShdPrePass {
public:
  DrResShdPrePass(DrShdDataObj *dataObj, int type);
  void setShaderParam();
  void setupShader(u32 index, u32 passType);
  void preshdset_Obj();
  void preshdset_ObjT();
  void preshdset_ObjT_Al();
  void preshdset_Mot();
  void preshdset_MotT();
  void preshdset_MotT_Al();
  void preshdset_Inst();
  void preshdset_InstT();
  void preshdset_Obj_Al();
  void preshdset_ObjT_Al_Fs();
  void preshdset_Mot_Al();
  void preshdset_MotT_Al_Fs();
  void preshdset_Inst_Al();
  void preshdset_InstT_Al();
  void preshdset_Inst_Bill_Al();
  void preshdset_InstT_Bill_Al();
  void preshdset_Fw();
  void preshdset_FwT();
  void preshdset_FwT_Al();
  void preshdset_Fw_Al();
  void preshdset_FwT_Al_Fs();

  static void (DrResShdPrePass::*s_callShdSet[])();

  DrShdDataObj *m_dataObj;
  s32 m_locations[11];
  u32 m_passTypeOfs;
  u16 m_flags;
  u16 m_type;
};

static_assert(offsetof(DrResShdPrePass, m_passTypeOfs) == 0x34, "");
static_assert(offsetof(DrResShdPrePass, m_flags) == 0x38, "");
static_assert(sizeof(DrResShdPrePass) == 0x40, "");

class DrResShdShw {
public:
  DrResShdShw(DrShdDataObj *dataObj, int type);
  void setShaderParam();
  void setupShader(DrResFetch *fetch);
  void setDecAType(u32 index);
  void setDecBType(u32 index);
  void shwShdset_DefObj();
  void shwShdset_Inst();
  void shwShdset_Mot();
  void shwShdset_InstMot();
  void shwShdset_Fw();

  static void (DrResShdShw::*s_callShwSet[])();

  DrShdDataObj *m_dataObj;
  s32 m_locations[7];
  u16 m_texTypeOfs;
  u16 m_sptTypeOfs;
  u16 m_flags;
  u16 m_type;
};

static_assert(offsetof(DrResShdShw, m_texTypeOfs) == 0x24, "");
static_assert(offsetof(DrResShdShw, m_flags) == 0x28, "");
static_assert(sizeof(DrResShdShw) == 0x30, "");

class DrResShdStreamOut {
public:
  void setupStreamShader(u32 index);
  DrResShdStreamOut(DrShdDataObj *dataObj, int type);
  void setShaderParam();
  void setDecNum(u32 num);
  void stmShdset_Weight();
  void stmShdset_WetVtx();
  void stmShdset_MofSet();
  void stmShdset_MeshVtxSet();

  static void (DrResShdStreamOut::*s_callStmOuSet[])();

  DrShdDataObj *m_dataObj;
  s32 m_locations[3];
  u16 m_type;
  u16 m_wetNumOfs;
};

static_assert(offsetof(DrResShdStreamOut, m_type) == 0x14, "");
static_assert(sizeof(DrResShdStreamOut) == 0x18, "");

class DrResShdObjMot {
public:
  DrResShdObjMot(DrShdDataObj *dataObj, int type);
  void setShaderParam();
  void setupShader();
  void motblur_motObj();
  void motblur_motObjTex();
  void motblur_notObj();
  void motblur_notObjTex();

  static void (DrResShdObjMot::*s_callMotObjSet[])();

  DrShdDataObj *m_dataObj;
  s32 m_locations[5];
  u16 m_flags;
  u16 m_type;
};

static_assert(offsetof(DrResShdObjMot, m_flags) == 0x1c, "");
static_assert(sizeof(DrResShdObjMot) == 0x20, "");

} // namespace ml
