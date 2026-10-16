#pragma once
#include "grlib/cglib_vtx_fetch.h"
#include "types.h"

namespace ml {

struct MdsMatVertexInfo {
  u16 type;
  u16 offset;
  u8 _04[0x8 - 0x4];
};

class DrResFetch : public grlib::CGLibVtxFetch {
public:
  DrResFetch();
  ~DrResFetch();
  void clearWork();
  void setMdlVertexParam(int num, const MdsMatVertexInfo *infos);
  void setDefVertexParam(int type);
  void setLgtVertexParam();
  void setupTexture2D();
  void setupPositionOnly();
  void setupSkinWeightCalc();
  void setupWeightVtx();
  void setupZBuffObj();
  void setupZBuffObjTex();
  void setupZBuffObjAL();
  void setupZBuffObjTexAL();
  void setupZBuffMot();
  void setupZBuffMotTex();
  void setupZBuffMotAL();
  void setupZBuffMotTexAL();
  void setupZBuffInst();
  void setupZBuffInstTex();
  void setupZBuffFw();
  void setupZBuffFwAL();
  void setupShadowObj();
  void setupShadowObjTex();
  void setupShadowMot();
  void setupShadowMotTex();
  void setupShadowMotInst();
  void setupShadowMotInstTex();
  void setupShadowFw();
  void setupMpf_Stm_Bill();
  void setupMpf_Stm_Bill_Wind();
  void setupMpf_Stm_Mdl_Wind();
  void setupMpf_Stm_Mdl_Wind_NoNom();
  void setupMpf_Stm_Mdl_NormalMap_Wind();
  void setupMpf_Stm_Mdl_NormalMap_Wind_VNom();
  void setupMpf_Pre_Bill();
  void setupMpf_Pre_Bill_Nuki();
  void setupMpf_Pre_Bill_Nuki_Layer();
  void setupMpf_Pre_Mdl();
  void setupMpf_Pre_Mdl_Nuki();
  void setupMpf_Pre_Mdl_Nuki_Layer();
  void setupMpf_Pre_Mdl_Layer();
  void setupMpf_Pre_Mdl_Def();
  void setupMpf_Pre_Mdl_Def_Nuki();
  void setupMpf_Pre_Mdl_Def_Nuki_Layer();
  void setupMpf_Pre_Dithe_Bill();
  void setupMpf_Pre_Dithe_Bill_Nuki();
  void setupMpf_Pre_Dithe_Bill_Nuki_Layer();
  void setupMpf_Pre_Dithe_Mdl();
  void setupMpf_Pre_Dithe_Mdl_Nuki();
  void setupMpf_Pre_Dithe_Mdl_Nuki_Layer();
  void setupMpf_Pre_Dithe_Mdl_Layer();
  void setupMpf_Pre_Dithe_Mdl_Def();
  void setupMpf_Pre_Dithe_Mdl_Def_Nuki();
  void setupMpf_Pre_Dithe_Mdl_Def_Nuki_Layer();
  void setupMpf_Drw_Bill();
  void setupMpf_Drw_Bill_Layer();
  void setupMpf_Drw_Mdl();
  void setupMpf_Drw_Mdl_Layer();
  void setupMpf_Drw_Mdl_NoNom();
  void setupMpf_Drw_Mdl_NoNom_Layer();
  void setupMpf_Drw_Mdl_Def();
  void setupMpf_Drw_Mdl_Def_Layer();
  void setupMpf_Drw_Mdl_Def_NoNom();
  void setupMpf_Drw_Mdl_Def_NoNom_Layer();
  void setupMpf_Drw_Mdl_NormalMap();
  void setupMpf_Drw_Mdl_NormalMap_Wind();
  void setupMpf_Drw_Mdl_NormalMap_Wind_Layer();
  void setupMpf_Drw_Mdl_NormalMap_Wind_VNom();
  void setupMpf_Drw_Mdl_NormalMap_Layer();
  void setupMpf_Cull_Fade_Mdl();
  void setupZBuffInstDith();
  void setupZBuffInstDithTex();
  void setupZBuffInstBillDith();
  void setupZBuffInstBillDithTex();
  void setupDebugPosColor();
  void setupXYZW();
  void setupOutLineObj();
  void setupGlassBrObj();
  void setupMofSetObj();
  void setupMeshVtxObj();
  void setupMeshVtxAdd();
  void setupOutMeshVtx();
  void setupMofZBuffObj();
  void setupMofZBuffObjTex();
  void setupMofZBuffObjAL();
  void setupMofZBuffObjTexAL();
  void setupMofZBuffMot();
  void setupMofZBuffMotTex();
  void setupMofZBuffMotAL();
  void setupMofZBuffMotTexAL();
  void setupMofShadowObj();
  void setupMofShadowObjTex();
  void setupMofShadowMot();
  void setupMofShadowMotTex();
  void setupDepthCheck();
  void setupDebTexStm();
  static void vert_set_VEC3(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_BYTE(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_USHORT2(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_VEC2(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_U32(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_SHORT4(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_GmPos4(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_GmScl2(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_GmCol4(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_GmCal1(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_GmCal2(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_GmCal3(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_GmInt(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_S32(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_GmFloat(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_OutLineNom(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_OutLineCol(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_MofPos(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_MofNom(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_MofTan(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_MofNewTan(int offset, u32 location, grlib::CGLibVtxAttr &attribute);
  static void vert_set_SHORT2(int offset, u32 location, grlib::CGLibVtxAttr &attribute);

  static void (*s_callSetVert[52])(int, u32, grlib::CGLibVtxAttr &);
  static void (DrResFetch::*s_callDefVertex[91])();
};

static_assert(sizeof(DrResFetch) == 0x10, "");

} // namespace ml
