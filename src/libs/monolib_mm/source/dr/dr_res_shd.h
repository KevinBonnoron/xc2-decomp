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

  DrShdDataObj *unknown00; // Inferred role: data object; original member name unknown.
  s32 unknown08[8];        // Inferred role: locations; original member name unknown.
  u16 unknown28;           // Inferred role: flags; original member name unknown.
  u16 unknown2a;           // Inferred role: type; original member name unknown.
  u32 unknown2c[2];        // Inferred role: decl ofs; original member name unknown.
};

static_assert(offsetof(DrResShdMpf, unknown28) == 0x28, "");
static_assert(offsetof(DrResShdMpf, unknown2c) == 0x2c, "");
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

  DrShdDataObj *unknown00; // Inferred role: data object; original member name unknown.
  s32 unknown08[11];       // Inferred role: locations; original member name unknown.
  u32 unknown34;           // Inferred role: pass type ofs; original member name unknown.
  u16 unknown38;           // Inferred role: flags; original member name unknown.
  u16 unknown3a;           // Inferred role: type; original member name unknown.
};

static_assert(offsetof(DrResShdPrePass, unknown34) == 0x34, "");
static_assert(offsetof(DrResShdPrePass, unknown38) == 0x38, "");
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

  DrShdDataObj *unknown00; // Inferred role: data object; original member name unknown.
  s32 unknown08[7];        // Inferred role: locations; original member name unknown.
  u16 unknown24;           // Inferred role: tex type ofs; original member name unknown.
  u16 unknown26;           // Inferred role: spt type ofs; original member name unknown.
  u16 unknown28;           // Inferred role: flags; original member name unknown.
  u16 unknown2a;           // Inferred role: type; original member name unknown.
};

static_assert(offsetof(DrResShdShw, unknown24) == 0x24, "");
static_assert(offsetof(DrResShdShw, unknown28) == 0x28, "");
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

  DrShdDataObj *unknown00; // Inferred role: data object; original member name unknown.
  s32 unknown08[3];        // Inferred role: locations; original member name unknown.
  u16 unknown14;           // Inferred role: type; original member name unknown.
  u16 unknown16;           // Inferred role: wet num ofs; original member name unknown.
};

static_assert(offsetof(DrResShdStreamOut, unknown14) == 0x14, "");
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

  DrShdDataObj *unknown00; // Inferred role: data object; original member name unknown.
  s32 unknown08[5];        // Inferred role: locations; original member name unknown.
  u16 unknown1c;           // Inferred role: flags; original member name unknown.
  u16 unknown1e;           // Inferred role: type; original member name unknown.
};

static_assert(offsetof(DrResShdObjMot, unknown1c) == 0x1c, "");
static_assert(sizeof(DrResShdObjMot) == 0x20, "");

} // namespace ml
