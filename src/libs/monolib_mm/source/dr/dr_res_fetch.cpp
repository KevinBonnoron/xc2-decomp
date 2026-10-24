#include "dr/dr_res_fetch.h"

namespace ml {

DrResFetch::DrResFetch() {}

DrResFetch::~DrResFetch() { release(); }

void DrResFetch::clearWork() { release(); }

void DrResFetch::setMdlVertexParam(int num, const MdsMatVertexInfo *infos) {
  grlib::CGLibVtxAttr attributes[52];
  for (int i = 0; i < num; i++, infos++) {
    s_callSetVert[infos->type](infos->offset, i, attributes[i]);
  }

  createFetchObj(attributes, num);
}
void DrResFetch::setDefVertexParam(int type) { (this->*s_callDefVertex[type])(); }

void DrResFetch::setLgtVertexParam() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupTexture2D() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupPositionOnly() {
  grlib::CGLibVtxAttr attributes[1];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  createFetchObj(attributes, 1);
}

void DrResFetch::setupSkinWeightCalc() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA8UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupWeightVtx() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGBA16;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA8UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 8;
  attributes[1].unknown0c = 0;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupZBuffObj() {
  grlib::CGLibVtxAttr attributes[1];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  createFetchObj(attributes, 1);
}

void DrResFetch::setupZBuffObjTex() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupZBuffObjAL() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_R32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupZBuffObjTexAL() {
  grlib::CGLibVtxAttr attributes[3];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_R32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  createFetchObj(attributes, 3);
}

void DrResFetch::setupZBuffMot() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG16UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupZBuffMotTex() {
  grlib::CGLibVtxAttr attributes[3];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG16UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 16;
  attributes[2].unknown0c = 0;
  createFetchObj(attributes, 3);
}

void DrResFetch::setupZBuffMotAL() {
  grlib::CGLibVtxAttr attributes[3];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG16UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_R32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  createFetchObj(attributes, 3);
}

void DrResFetch::setupZBuffMotTexAL() {
  grlib::CGLibVtxAttr attributes[4];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG16UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 16;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_R32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 0;
  attributes[3].unknown0c = 1;
  createFetchObj(attributes, 4);
}

void DrResFetch::setupZBuffInst() {
  grlib::CGLibVtxAttr attributes[4];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 16;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 32;
  attributes[3].unknown0c = 1;
  createFetchObj(attributes, 4);
}

void DrResFetch::setupZBuffInstTex() {
  grlib::CGLibVtxAttr attributes[5];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 16;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 32;
  attributes[4].unknown0c = 1;
  createFetchObj(attributes, 5);
}

void DrResFetch::setupZBuffFw() {
  grlib::CGLibVtxAttr attributes[4];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 20;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA8SN;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 24;
  attributes[3].unknown0c = 0;
  createFetchObj(attributes, 4);
}

void DrResFetch::setupZBuffFwAL() {
  grlib::CGLibVtxAttr attributes[5];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 20;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA8SN;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 24;
  attributes[3].unknown0c = 0;
  attributes[4].unknown00 = GRL_VTX_FORMAT_R32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 0;
  attributes[4].unknown0c = 1;
  createFetchObj(attributes, 5);
}

void DrResFetch::setupShadowObj() {
  grlib::CGLibVtxAttr attributes[1];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  createFetchObj(attributes, 1);
}

void DrResFetch::setupShadowObjTex() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupShadowMot() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG16UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupShadowMotTex() {
  grlib::CGLibVtxAttr attributes[3];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG16UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 16;
  attributes[2].unknown0c = 0;
  createFetchObj(attributes, 3);
}

void DrResFetch::setupShadowMotInst() {
  grlib::CGLibVtxAttr attributes[5];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG16UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 16;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 32;
  attributes[4].unknown0c = 1;
  createFetchObj(attributes, 5);
}

void DrResFetch::setupShadowMotInstTex() {
  grlib::CGLibVtxAttr attributes[6];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG16UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 16;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 0;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 16;
  attributes[4].unknown0c = 1;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 32;
  attributes[5].unknown0c = 1;
  createFetchObj(attributes, 6);
}

void DrResFetch::setupShadowFw() {
  grlib::CGLibVtxAttr attributes[4];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 20;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA8SN;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 24;
  attributes[3].unknown0c = 0;
  createFetchObj(attributes, 4);
}

void DrResFetch::setupMpf_Stm_Bill() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupMpf_Stm_Bill_Wind() {
  grlib::CGLibVtxAttr attributes[4];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 20;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_R32UI;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 8;
  attributes[3].unknown0c = 1;
  createFetchObj(attributes, 4);
}

void DrResFetch::setupMpf_Stm_Mdl_Wind() {
  grlib::CGLibVtxAttr attributes[3];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 36;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_R32UI;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  createFetchObj(attributes, 3);
}

void DrResFetch::setupMpf_Stm_Mdl_Wind_NoNom() {
  grlib::CGLibVtxAttr attributes[3];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 24;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_R32UI;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  createFetchObj(attributes, 3);
}

void DrResFetch::setupMpf_Stm_Mdl_NormalMap_Wind() {
  grlib::CGLibVtxAttr attributes[3];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 44;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_R32UI;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  createFetchObj(attributes, 3);
}

void DrResFetch::setupMpf_Stm_Mdl_NormalMap_Wind_VNom() {
  grlib::CGLibVtxAttr attributes[5];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 20;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA16SN;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 32;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 44;
  attributes[3].unknown0c = 0;
  attributes[4].unknown00 = GRL_VTX_FORMAT_R32UI;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 0;
  attributes[4].unknown0c = 1;
  createFetchObj(attributes, 5);
}

void DrResFetch::setupMpf_Pre_Bill() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 1;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 2;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupMpf_Pre_Bill_Nuki() {
  grlib::CGLibVtxAttr attributes[3];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 2;
  createFetchObj(attributes, 3);
}

void DrResFetch::setupMpf_Pre_Bill_Nuki_Layer() {
  grlib::CGLibVtxAttr attributes[4];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 2;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RG16F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 16;
  attributes[3].unknown0c = 2;
  createFetchObj(attributes, 4);
}

void DrResFetch::setupMpf_Pre_Mdl() {
  grlib::CGLibVtxAttr attributes[4];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 1;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 2;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 16;
  attributes[2].unknown0c = 2;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 32;
  attributes[3].unknown0c = 2;
  createFetchObj(attributes, 4);
}

void DrResFetch::setupMpf_Pre_Mdl_Nuki() {
  grlib::CGLibVtxAttr attributes[5];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 2;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 16;
  attributes[3].unknown0c = 2;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 32;
  attributes[4].unknown0c = 2;
  createFetchObj(attributes, 5);
}

void DrResFetch::setupMpf_Pre_Mdl_Nuki_Layer() {
  grlib::CGLibVtxAttr attributes[6];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 2;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 16;
  attributes[3].unknown0c = 2;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 32;
  attributes[4].unknown0c = 2;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RG16F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 52;
  attributes[5].unknown0c = 2;
  createFetchObj(attributes, 6);
}

void DrResFetch::setupMpf_Pre_Mdl_Layer() {
  grlib::CGLibVtxAttr attributes[5];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 1;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 2;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 16;
  attributes[2].unknown0c = 2;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 32;
  attributes[3].unknown0c = 2;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RG16F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 52;
  attributes[4].unknown0c = 2;
  createFetchObj(attributes, 5);
}

void DrResFetch::setupMpf_Pre_Mdl_Def() {
  grlib::CGLibVtxAttr attributes[4];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 16;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 32;
  attributes[3].unknown0c = 1;
  createFetchObj(attributes, 4);
}

void DrResFetch::setupMpf_Pre_Mdl_Def_Nuki() {
  grlib::CGLibVtxAttr attributes[5];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 16;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 32;
  attributes[4].unknown0c = 1;
  createFetchObj(attributes, 5);
}

void DrResFetch::setupMpf_Pre_Mdl_Def_Nuki_Layer() {
  grlib::CGLibVtxAttr attributes[6];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 16;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 32;
  attributes[4].unknown0c = 1;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RG16F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 52;
  attributes[5].unknown0c = 1;
  createFetchObj(attributes, 6);
}

void DrResFetch::setupMpf_Pre_Dithe_Bill() {
  grlib::CGLibVtxAttr attributes[3];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 1;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 2;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 12;
  attributes[2].unknown0c = 2;
  createFetchObj(attributes, 3);
}

void DrResFetch::setupMpf_Pre_Dithe_Bill_Nuki() {
  grlib::CGLibVtxAttr attributes[4];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 2;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 12;
  attributes[3].unknown0c = 2;
  createFetchObj(attributes, 4);
}

void DrResFetch::setupMpf_Pre_Dithe_Bill_Nuki_Layer() {
  grlib::CGLibVtxAttr attributes[5];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 2;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RG16F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 16;
  attributes[3].unknown0c = 2;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 12;
  attributes[4].unknown0c = 2;
  createFetchObj(attributes, 5);
}

void DrResFetch::setupMpf_Pre_Dithe_Mdl() {
  grlib::CGLibVtxAttr attributes[5];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 1;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 2;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 16;
  attributes[2].unknown0c = 2;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 32;
  attributes[3].unknown0c = 2;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 48;
  attributes[4].unknown0c = 2;
  createFetchObj(attributes, 5);
}

void DrResFetch::setupMpf_Pre_Dithe_Mdl_Nuki() {
  grlib::CGLibVtxAttr attributes[6];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 2;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 16;
  attributes[3].unknown0c = 2;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 32;
  attributes[4].unknown0c = 2;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 48;
  attributes[5].unknown0c = 2;
  createFetchObj(attributes, 6);
}

void DrResFetch::setupMpf_Pre_Dithe_Mdl_Nuki_Layer() {
  grlib::CGLibVtxAttr attributes[7];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 2;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 16;
  attributes[3].unknown0c = 2;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 32;
  attributes[4].unknown0c = 2;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RG16F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 52;
  attributes[5].unknown0c = 2;
  attributes[6].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[6].unknown04 = 6;
  attributes[6].unknown08 = 48;
  attributes[6].unknown0c = 2;
  createFetchObj(attributes, 7);
}

void DrResFetch::setupMpf_Pre_Dithe_Mdl_Layer() {
  grlib::CGLibVtxAttr attributes[6];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 1;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 2;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 16;
  attributes[2].unknown0c = 2;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 32;
  attributes[3].unknown0c = 2;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RG16F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 52;
  attributes[4].unknown0c = 2;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 48;
  attributes[5].unknown0c = 2;
  createFetchObj(attributes, 6);
}

void DrResFetch::setupMpf_Pre_Dithe_Mdl_Def() {
  grlib::CGLibVtxAttr attributes[5];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 16;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 32;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 48;
  attributes[4].unknown0c = 1;
  createFetchObj(attributes, 5);
}

void DrResFetch::setupMpf_Pre_Dithe_Mdl_Def_Nuki() {
  grlib::CGLibVtxAttr attributes[6];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 16;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 32;
  attributes[4].unknown0c = 1;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 48;
  attributes[5].unknown0c = 1;
  createFetchObj(attributes, 6);
}

void DrResFetch::setupMpf_Pre_Dithe_Mdl_Def_Nuki_Layer() {
  grlib::CGLibVtxAttr attributes[7];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 16;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 32;
  attributes[4].unknown0c = 1;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RG16F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 52;
  attributes[5].unknown0c = 1;
  attributes[6].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[6].unknown04 = 6;
  attributes[6].unknown08 = 48;
  attributes[6].unknown0c = 1;
  createFetchObj(attributes, 7);
}

void DrResFetch::setupMpf_Drw_Bill() {
  grlib::CGLibVtxAttr attributes[5];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 12;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 0;
  attributes[3].unknown0c = 2;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 12;
  attributes[4].unknown0c = 2;
  createFetchObj(attributes, 5);
}

void DrResFetch::setupMpf_Drw_Bill_Layer() {
  grlib::CGLibVtxAttr attributes[7];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 12;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 0;
  attributes[3].unknown0c = 2;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 12;
  attributes[4].unknown0c = 2;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RG16F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 16;
  attributes[5].unknown0c = 2;
  attributes[6].unknown00 = GRL_VTX_FORMAT_RGBA8SN;
  attributes[6].unknown04 = 6;
  attributes[6].unknown08 = 20;
  attributes[6].unknown0c = 2;
  createFetchObj(attributes, 7);
}

void DrResFetch::setupMpf_Drw_Mdl() {
  grlib::CGLibVtxAttr attributes[9];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 20;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 32;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 0;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 12;
  attributes[4].unknown0c = 1;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 0;
  attributes[5].unknown0c = 2;
  attributes[6].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[6].unknown04 = 6;
  attributes[6].unknown08 = 16;
  attributes[6].unknown0c = 2;
  attributes[7].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[7].unknown04 = 7;
  attributes[7].unknown08 = 32;
  attributes[7].unknown0c = 2;
  attributes[8].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[8].unknown04 = 8;
  attributes[8].unknown08 = 48;
  attributes[8].unknown0c = 2;
  createFetchObj(attributes, 9);
}

void DrResFetch::setupMpf_Drw_Mdl_Layer() {
  grlib::CGLibVtxAttr attributes[10];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 20;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 32;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 0;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 12;
  attributes[4].unknown0c = 1;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 0;
  attributes[5].unknown0c = 2;
  attributes[6].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[6].unknown04 = 6;
  attributes[6].unknown08 = 16;
  attributes[6].unknown0c = 2;
  attributes[7].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[7].unknown04 = 7;
  attributes[7].unknown08 = 32;
  attributes[7].unknown0c = 2;
  attributes[8].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[8].unknown04 = 8;
  attributes[8].unknown08 = 48;
  attributes[8].unknown0c = 2;
  attributes[9].unknown00 = GRL_VTX_FORMAT_RG16F;
  attributes[9].unknown04 = 9;
  attributes[9].unknown08 = 52;
  attributes[9].unknown0c = 2;
  createFetchObj(attributes, 10);
}

void DrResFetch::setupMpf_Drw_Mdl_NoNom() {
  grlib::CGLibVtxAttr attributes[8];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 20;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 12;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 0;
  attributes[4].unknown0c = 2;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 16;
  attributes[5].unknown0c = 2;
  attributes[6].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[6].unknown04 = 6;
  attributes[6].unknown08 = 32;
  attributes[6].unknown0c = 2;
  attributes[7].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[7].unknown04 = 7;
  attributes[7].unknown08 = 48;
  attributes[7].unknown0c = 2;
  createFetchObj(attributes, 8);
}

void DrResFetch::setupMpf_Drw_Mdl_NoNom_Layer() {
  grlib::CGLibVtxAttr attributes[9];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 20;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 12;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 0;
  attributes[4].unknown0c = 2;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 16;
  attributes[5].unknown0c = 2;
  attributes[6].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[6].unknown04 = 6;
  attributes[6].unknown08 = 32;
  attributes[6].unknown0c = 2;
  attributes[7].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[7].unknown04 = 7;
  attributes[7].unknown08 = 48;
  attributes[7].unknown0c = 2;
  attributes[8].unknown00 = GRL_VTX_FORMAT_RG16F;
  attributes[8].unknown04 = 8;
  attributes[8].unknown08 = 52;
  attributes[8].unknown0c = 2;
  createFetchObj(attributes, 9);
}

void DrResFetch::setupMpf_Drw_Mdl_Def() {
  grlib::CGLibVtxAttr attributes[8];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 20;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 32;
  attributes[3].unknown0c = 0;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 0;
  attributes[4].unknown0c = 1;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 16;
  attributes[5].unknown0c = 1;
  attributes[6].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[6].unknown04 = 6;
  attributes[6].unknown08 = 32;
  attributes[6].unknown0c = 1;
  attributes[7].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[7].unknown04 = 7;
  attributes[7].unknown08 = 48;
  attributes[7].unknown0c = 1;
  createFetchObj(attributes, 8);
}

void DrResFetch::setupMpf_Drw_Mdl_Def_Layer() {
  grlib::CGLibVtxAttr attributes[9];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 20;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 32;
  attributes[3].unknown0c = 0;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 0;
  attributes[4].unknown0c = 1;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 16;
  attributes[5].unknown0c = 1;
  attributes[6].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[6].unknown04 = 6;
  attributes[6].unknown08 = 32;
  attributes[6].unknown0c = 1;
  attributes[7].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[7].unknown04 = 7;
  attributes[7].unknown08 = 48;
  attributes[7].unknown0c = 1;
  attributes[8].unknown00 = GRL_VTX_FORMAT_RG16F;
  attributes[8].unknown04 = 8;
  attributes[8].unknown08 = 52;
  attributes[8].unknown0c = 1;
  createFetchObj(attributes, 9);
}

void DrResFetch::setupMpf_Drw_Mdl_Def_NoNom() {
  grlib::CGLibVtxAttr attributes[7];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 20;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 0;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 16;
  attributes[4].unknown0c = 1;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 32;
  attributes[5].unknown0c = 1;
  attributes[6].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[6].unknown04 = 6;
  attributes[6].unknown08 = 48;
  attributes[6].unknown0c = 1;
  createFetchObj(attributes, 7);
}

void DrResFetch::setupMpf_Drw_Mdl_Def_NoNom_Layer() {
  grlib::CGLibVtxAttr attributes[8];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 20;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 0;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 16;
  attributes[4].unknown0c = 1;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 32;
  attributes[5].unknown0c = 1;
  attributes[6].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[6].unknown04 = 6;
  attributes[6].unknown08 = 48;
  attributes[6].unknown0c = 1;
  attributes[7].unknown00 = GRL_VTX_FORMAT_RG16F;
  attributes[7].unknown04 = 7;
  attributes[7].unknown08 = 52;
  attributes[7].unknown0c = 1;
  createFetchObj(attributes, 8);
}

void DrResFetch::setupMpf_Drw_Mdl_NormalMap() {
  grlib::CGLibVtxAttr attributes[9];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 20;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA16SN;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 32;
  attributes[3].unknown0c = 0;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 40;
  attributes[4].unknown0c = 0;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 0;
  attributes[5].unknown0c = 1;
  attributes[6].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[6].unknown04 = 6;
  attributes[6].unknown08 = 16;
  attributes[6].unknown0c = 1;
  attributes[7].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[7].unknown04 = 7;
  attributes[7].unknown08 = 32;
  attributes[7].unknown0c = 1;
  attributes[8].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[8].unknown04 = 8;
  attributes[8].unknown08 = 48;
  attributes[8].unknown0c = 1;
  createFetchObj(attributes, 9);
}

void DrResFetch::setupMpf_Drw_Mdl_NormalMap_Wind() {
  grlib::CGLibVtxAttr attributes[10];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 20;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA16SN;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 32;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 40;
  attributes[3].unknown0c = 0;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 0;
  attributes[4].unknown0c = 1;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 12;
  attributes[5].unknown0c = 1;
  attributes[6].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[6].unknown04 = 6;
  attributes[6].unknown08 = 0;
  attributes[6].unknown0c = 2;
  attributes[7].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[7].unknown04 = 7;
  attributes[7].unknown08 = 16;
  attributes[7].unknown0c = 2;
  attributes[8].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[8].unknown04 = 8;
  attributes[8].unknown08 = 32;
  attributes[8].unknown0c = 2;
  attributes[9].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[9].unknown04 = 9;
  attributes[9].unknown08 = 48;
  attributes[9].unknown0c = 2;
  createFetchObj(attributes, 10);
}

void DrResFetch::setupMpf_Drw_Mdl_NormalMap_Wind_Layer() {
  grlib::CGLibVtxAttr attributes[11];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 20;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA16SN;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 32;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 40;
  attributes[3].unknown0c = 0;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 0;
  attributes[4].unknown0c = 1;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 12;
  attributes[5].unknown0c = 1;
  attributes[6].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[6].unknown04 = 6;
  attributes[6].unknown08 = 0;
  attributes[6].unknown0c = 2;
  attributes[7].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[7].unknown04 = 7;
  attributes[7].unknown08 = 16;
  attributes[7].unknown0c = 2;
  attributes[8].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[8].unknown04 = 8;
  attributes[8].unknown08 = 32;
  attributes[8].unknown0c = 2;
  attributes[9].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[9].unknown04 = 9;
  attributes[9].unknown08 = 48;
  attributes[9].unknown0c = 2;
  attributes[10].unknown00 = GRL_VTX_FORMAT_RG16F;
  attributes[10].unknown04 = 10;
  attributes[10].unknown08 = 52;
  attributes[10].unknown0c = 2;
  createFetchObj(attributes, 11);
}

void DrResFetch::setupMpf_Drw_Mdl_NormalMap_Wind_VNom() {
  grlib::CGLibVtxAttr attributes[10];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 24;
  attributes[1].unknown0c = 1;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 36;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 40;
  attributes[3].unknown0c = 0;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 0;
  attributes[4].unknown0c = 1;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 12;
  attributes[5].unknown0c = 1;
  attributes[6].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[6].unknown04 = 6;
  attributes[6].unknown08 = 0;
  attributes[6].unknown0c = 2;
  attributes[7].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[7].unknown04 = 7;
  attributes[7].unknown08 = 16;
  attributes[7].unknown0c = 2;
  attributes[8].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[8].unknown04 = 8;
  attributes[8].unknown08 = 32;
  attributes[8].unknown0c = 2;
  attributes[9].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[9].unknown04 = 9;
  attributes[9].unknown08 = 48;
  attributes[9].unknown0c = 2;
  createFetchObj(attributes, 10);
}

void DrResFetch::setupMpf_Drw_Mdl_NormalMap_Layer() {
  grlib::CGLibVtxAttr attributes[10];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 12;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 20;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA16SN;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 32;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 40;
  attributes[3].unknown0c = 0;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 0;
  attributes[4].unknown0c = 0;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 0;
  attributes[5].unknown0c = 1;
  attributes[6].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[6].unknown04 = 6;
  attributes[6].unknown08 = 16;
  attributes[6].unknown0c = 1;
  attributes[7].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[7].unknown04 = 7;
  attributes[7].unknown08 = 32;
  attributes[7].unknown0c = 1;
  attributes[8].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[8].unknown04 = 8;
  attributes[8].unknown08 = 48;
  attributes[8].unknown0c = 1;
  attributes[9].unknown00 = GRL_VTX_FORMAT_RG16F;
  attributes[9].unknown04 = 9;
  attributes[9].unknown08 = 52;
  attributes[9].unknown0c = 1;
  createFetchObj(attributes, 10);
}

void DrResFetch::setupMpf_Cull_Fade_Mdl() {
  grlib::CGLibVtxAttr attributes[4];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 16;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 32;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32UI;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 48;
  attributes[3].unknown0c = 0;
  createFetchObj(attributes, 4);
}

void DrResFetch::setupZBuffInstDith() {
  grlib::CGLibVtxAttr attributes[5];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 16;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 32;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_R32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 48;
  attributes[4].unknown0c = 1;
  createFetchObj(attributes, 5);
}

void DrResFetch::setupZBuffInstDithTex() {
  grlib::CGLibVtxAttr attributes[6];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 16;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 32;
  attributes[4].unknown0c = 1;
  attributes[5].unknown00 = GRL_VTX_FORMAT_R32F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 48;
  attributes[5].unknown0c = 1;
  createFetchObj(attributes, 6);
}

void DrResFetch::setupZBuffInstBillDith() {
  grlib::CGLibVtxAttr attributes[6];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG16UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 16;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 32;
  attributes[4].unknown0c = 1;
  attributes[5].unknown00 = GRL_VTX_FORMAT_R32F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 48;
  attributes[5].unknown0c = 1;
  createFetchObj(attributes, 6);
}

void DrResFetch::setupZBuffInstBillDithTex() {
  grlib::CGLibVtxAttr attributes[7];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG16UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 16;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 0;
  attributes[3].unknown0c = 1;
  attributes[4].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[4].unknown04 = 4;
  attributes[4].unknown08 = 16;
  attributes[4].unknown0c = 1;
  attributes[5].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[5].unknown04 = 5;
  attributes[5].unknown08 = 32;
  attributes[5].unknown0c = 1;
  attributes[6].unknown00 = GRL_VTX_FORMAT_R32F;
  attributes[6].unknown04 = 6;
  attributes[6].unknown08 = 52;
  attributes[6].unknown0c = 1;
  createFetchObj(attributes, 7);
}

void DrResFetch::setupDebugPosColor() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupXYZW() {
  grlib::CGLibVtxAttr attributes[1];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  createFetchObj(attributes, 1);
}

void DrResFetch::setupOutLineObj() {
  grlib::CGLibVtxAttr attributes[3];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA8SN;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 4;
  attributes[2].unknown0c = 1;
  createFetchObj(attributes, 3);
}

void DrResFetch::setupGlassBrObj() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGBA16I;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA8SN;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 8;
  attributes[1].unknown0c = 0;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupMofSetObj() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA32UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 16;
  attributes[1].unknown0c = 0;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupMeshVtxObj() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGBA16I;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA8SN;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 8;
  attributes[1].unknown0c = 0;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupMeshVtxAdd() {
  grlib::CGLibVtxAttr attributes[3];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 12;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 16;
  attributes[2].unknown0c = 0;
  createFetchObj(attributes, 3);
}

void DrResFetch::setupOutMeshVtx() {
  grlib::CGLibVtxAttr attributes[4];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 8;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  attributes[3].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 12;
  attributes[3].unknown0c = 1;
  createFetchObj(attributes, 4);
}

void DrResFetch::setupMofZBuffObj() {
  grlib::CGLibVtxAttr attributes[1];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 2;
  createFetchObj(attributes, 1);
}

void DrResFetch::setupMofZBuffObjTex() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 2;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 0;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupMofZBuffObjAL() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 2;
  attributes[1].unknown00 = GRL_VTX_FORMAT_R32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupMofZBuffObjTexAL() {
  grlib::CGLibVtxAttr attributes[3];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 2;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_R32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  createFetchObj(attributes, 3);
}

void DrResFetch::setupMofZBuffMot() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 2;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG16UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 0;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupMofZBuffMotTex() {
  grlib::CGLibVtxAttr attributes[3];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 2;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG16UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 4;
  attributes[2].unknown0c = 0;
  createFetchObj(attributes, 3);
}

void DrResFetch::setupMofZBuffMotAL() {
  grlib::CGLibVtxAttr attributes[3];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 2;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG16UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_R32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 0;
  attributes[2].unknown0c = 1;
  createFetchObj(attributes, 3);
}

void DrResFetch::setupMofZBuffMotTexAL() {
  grlib::CGLibVtxAttr attributes[4];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 2;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG16UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 4;
  attributes[2].unknown0c = 0;
  attributes[3].unknown00 = GRL_VTX_FORMAT_R32F;
  attributes[3].unknown04 = 3;
  attributes[3].unknown08 = 0;
  attributes[3].unknown0c = 1;
  createFetchObj(attributes, 4);
}

void DrResFetch::setupMofShadowObj() {
  grlib::CGLibVtxAttr attributes[1];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 2;
  createFetchObj(attributes, 1);
}

void DrResFetch::setupMofShadowObjTex() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 2;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 0;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupMofShadowMot() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 2;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG16UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 0;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupMofShadowMotTex() {
  grlib::CGLibVtxAttr attributes[3];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 2;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RG16UI;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 0;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 4;
  attributes[2].unknown0c = 0;
  createFetchObj(attributes, 3);
}

void DrResFetch::setupDepthCheck() {
  grlib::CGLibVtxAttr attributes[2];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RGB32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  createFetchObj(attributes, 2);
}

void DrResFetch::setupDebTexStm() {
  grlib::CGLibVtxAttr attributes[3];
  attributes[0].unknown00 = GRL_VTX_FORMAT_RG32F;
  attributes[0].unknown04 = 0;
  attributes[0].unknown08 = 0;
  attributes[0].unknown0c = 0;
  attributes[1].unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attributes[1].unknown04 = 1;
  attributes[1].unknown08 = 0;
  attributes[1].unknown0c = 1;
  attributes[2].unknown00 = GRL_VTX_FORMAT_RGBA8;
  attributes[2].unknown04 = 2;
  attributes[2].unknown08 = 16;
  attributes[2].unknown0c = 1;
  createFetchObj(attributes, 3);
}

void DrResFetch::vert_set_VEC3(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RGB32F;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 0;
}

void DrResFetch::vert_set_BYTE(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RGBA8UI;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 0;
}

void DrResFetch::vert_set_USHORT2(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RG16UI;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 0;
}

void DrResFetch::vert_set_VEC2(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RG32F;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 0;
}

void DrResFetch::vert_set_U32(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RGBA8;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 0;
}

void DrResFetch::vert_set_SHORT4(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RGBA16SN;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 0;
}

void DrResFetch::vert_set_GmPos4(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RGB32F;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 1;
}

void DrResFetch::vert_set_GmScl2(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RG32F;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 1;
}

void DrResFetch::vert_set_GmCol4(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RGBA8;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 1;
}

void DrResFetch::vert_set_GmCal1(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 1;
}

void DrResFetch::vert_set_GmCal2(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 1;
}

void DrResFetch::vert_set_GmCal3(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 1;
}

void DrResFetch::vert_set_GmInt(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_R32UI;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 1;
}

void DrResFetch::vert_set_S32(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RGBA8SN;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 0;
}

void DrResFetch::vert_set_GmFloat(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_R32F;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 1;
}

void DrResFetch::vert_set_OutLineNom(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RGBA8SN;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 1;
}

void DrResFetch::vert_set_OutLineCol(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RGBA8;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 1;
}

void DrResFetch::vert_set_MofPos(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RGB32F;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 2;
}

void DrResFetch::vert_set_MofNom(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RGBA8;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 2;
}

void DrResFetch::vert_set_MofTan(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RGBA32F;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 2;
}

void DrResFetch::vert_set_MofNewTan(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RGBA8;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 2;
}

void DrResFetch::vert_set_SHORT2(int offset, u32 location, grlib::CGLibVtxAttr &attribute) {
  attribute.unknown00 = GRL_VTX_FORMAT_RG16SN;
  attribute.unknown04 = location;
  attribute.unknown08 = offset;
  attribute.unknown0c = 0;
}

void (*DrResFetch::s_callSetVert[52])(int, u32, grlib::CGLibVtxAttr &) = {
    vert_set_VEC3,      vert_set_VEC3,   vert_set_BYTE,   vert_set_USHORT2, vert_set_USHORT2,    vert_set_VEC2,       vert_set_VEC2,   vert_set_VEC2,   vert_set_VEC2,   vert_set_VEC2,
    vert_set_VEC2,      vert_set_VEC2,   vert_set_VEC2,   vert_set_VEC2,    vert_set_U32,        vert_set_VEC3,       vert_set_SHORT4, vert_set_U32,    vert_set_VEC3,   vert_set_SHORT4,
    vert_set_SHORT4,    vert_set_GmPos4, vert_set_GmScl2, vert_set_GmCol4,  vert_set_GmCal1,     vert_set_GmCal2,     vert_set_GmCal3, vert_set_GmInt,  vert_set_S32,    vert_set_S32,
    vert_set_GmFloat,   vert_set_BYTE,   vert_set_S32,    vert_set_S32,     vert_set_OutLineNom, vert_set_OutLineCol, vert_set_MofPos, vert_set_MofNom, vert_set_MofTan, vert_set_MofPos,
    vert_set_MofNewTan, vert_set_SHORT2, vert_set_SHORT2, vert_set_SHORT2,  vert_set_SHORT2,     vert_set_SHORT2,     vert_set_SHORT2, vert_set_SHORT2, vert_set_SHORT2, vert_set_SHORT2,
};

void (DrResFetch::*DrResFetch::s_callDefVertex[91])() = {
    &DrResFetch::setupTexture2D,
    &DrResFetch::setupPositionOnly,
    &DrResFetch::setupSkinWeightCalc,
    &DrResFetch::setupZBuffObj,
    &DrResFetch::setupZBuffObjTex,
    &DrResFetch::setupZBuffMot,
    &DrResFetch::setupZBuffMotTex,
    &DrResFetch::setupZBuffInst,
    &DrResFetch::setupZBuffInstTex,
    &DrResFetch::setupZBuffObjAL,
    &DrResFetch::setupZBuffObjTexAL,
    &DrResFetch::setupZBuffMotAL,
    &DrResFetch::setupZBuffMotTexAL,
    &DrResFetch::setupShadowObj,
    &DrResFetch::setupShadowObjTex,
    &DrResFetch::setupShadowMot,
    &DrResFetch::setupShadowMotTex,
    &DrResFetch::setupShadowMotInst,
    &DrResFetch::setupShadowMotInstTex,
    &DrResFetch::setupMpf_Stm_Bill,
    &DrResFetch::setupMpf_Stm_Bill_Wind,
    &DrResFetch::setupMpf_Stm_Mdl_Wind,
    &DrResFetch::setupMpf_Stm_Mdl_Wind_NoNom,
    &DrResFetch::setupMpf_Stm_Mdl_NormalMap_Wind,
    &DrResFetch::setupMpf_Stm_Mdl_NormalMap_Wind_VNom,
    &DrResFetch::setupMpf_Pre_Bill,
    &DrResFetch::setupMpf_Pre_Bill_Nuki,
    &DrResFetch::setupMpf_Pre_Bill_Nuki_Layer,
    &DrResFetch::setupMpf_Pre_Mdl,
    &DrResFetch::setupMpf_Pre_Mdl_Nuki,
    &DrResFetch::setupMpf_Pre_Mdl_Nuki_Layer,
    &DrResFetch::setupMpf_Pre_Mdl_Def,
    &DrResFetch::setupMpf_Pre_Mdl_Def_Nuki,
    &DrResFetch::setupMpf_Pre_Mdl_Def_Nuki_Layer,
    &DrResFetch::setupMpf_Pre_Dithe_Bill,
    &DrResFetch::setupMpf_Pre_Dithe_Bill_Nuki,
    &DrResFetch::setupMpf_Pre_Dithe_Bill_Nuki_Layer,
    &DrResFetch::setupMpf_Pre_Dithe_Mdl,
    &DrResFetch::setupMpf_Pre_Dithe_Mdl_Nuki,
    &DrResFetch::setupMpf_Pre_Dithe_Mdl_Nuki_Layer,
    &DrResFetch::setupMpf_Pre_Dithe_Mdl_Def,
    &DrResFetch::setupMpf_Pre_Dithe_Mdl_Def_Nuki,
    &DrResFetch::setupMpf_Pre_Dithe_Mdl_Def_Nuki_Layer,
    &DrResFetch::setupMpf_Drw_Bill,
    &DrResFetch::setupMpf_Drw_Bill_Layer,
    &DrResFetch::setupMpf_Drw_Mdl,
    &DrResFetch::setupMpf_Drw_Mdl_Layer,
    &DrResFetch::setupMpf_Drw_Mdl_NoNom,
    &DrResFetch::setupMpf_Drw_Mdl_NoNom_Layer,
    &DrResFetch::setupMpf_Drw_Mdl_Def,
    &DrResFetch::setupMpf_Drw_Mdl_Def_Layer,
    &DrResFetch::setupMpf_Drw_Mdl_Def_NoNom,
    &DrResFetch::setupMpf_Drw_Mdl_Def_NoNom_Layer,
    &DrResFetch::setupMpf_Drw_Mdl_NormalMap,
    &DrResFetch::setupMpf_Drw_Mdl_NormalMap_Wind,
    &DrResFetch::setupMpf_Drw_Mdl_NormalMap_Wind_Layer,
    &DrResFetch::setupMpf_Drw_Mdl_NormalMap_Wind_VNom,
    &DrResFetch::setupMpf_Drw_Mdl_NormalMap_Layer,
    &DrResFetch::setupZBuffInstDith,
    &DrResFetch::setupZBuffInstDithTex,
    &DrResFetch::setupZBuffInstBillDith,
    &DrResFetch::setupZBuffInstBillDithTex,
    &DrResFetch::setupDebugPosColor,
    &DrResFetch::setupXYZW,
    &DrResFetch::setupOutLineObj,
    &DrResFetch::setupGlassBrObj,
    &DrResFetch::setupMofSetObj,
    &DrResFetch::setupMeshVtxObj,
    &DrResFetch::setupOutMeshVtx,
    &DrResFetch::setupMpf_Cull_Fade_Mdl,
    &DrResFetch::setupMpf_Pre_Mdl_Layer,
    &DrResFetch::setupMpf_Pre_Dithe_Mdl_Layer,
    &DrResFetch::setupWeightVtx,
    &DrResFetch::setupShadowFw,
    &DrResFetch::setupDepthCheck,
    &DrResFetch::setupDebTexStm,
    &DrResFetch::setupZBuffFw,
    &DrResFetch::setupZBuffFwAL,
    &DrResFetch::setupMofZBuffObj,
    &DrResFetch::setupMofZBuffObjTex,
    &DrResFetch::setupMofZBuffMot,
    &DrResFetch::setupMofZBuffMotTex,
    &DrResFetch::setupMofZBuffObjAL,
    &DrResFetch::setupMofZBuffObjTexAL,
    &DrResFetch::setupMofZBuffMotAL,
    &DrResFetch::setupMofZBuffMotTexAL,
    &DrResFetch::setupMofShadowObj,
    &DrResFetch::setupMofShadowObjTex,
    &DrResFetch::setupMofShadowMot,
    &DrResFetch::setupMofShadowMotTex,
    &DrResFetch::setupMeshVtxAdd,
};
} // namespace ml
