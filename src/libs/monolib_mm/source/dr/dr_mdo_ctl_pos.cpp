#include "dr/dr_mdo_ctl_pos.h"

#include "dr/dr_mdo_mat.h"
#include "dr/dr_res_mdo_vertex.h"

namespace ml {

void DrMdoCtlPos::createRenderDisplayList(const MdsMdlInfoHeader *, int, _MdoInstanceWork *, grlib::CGLibVtxInstans *, int) {}

void DrMdoCtlPos::createThicknessRenderFirstDisplayList() { createThicknessRenderDisplayListSub(true); }

void DrMdoCtlPos::createThicknessRenderSecondDisplayList() { createThicknessRenderDisplayListSub(false); }

void DrMdoCtlPos::callZpreePassRenderPosAll() {
  if ((unknownf8 & unknown028_20) == 0) {
    return;
  }
  createZBuffRenderDisplayList();
}

void DrMdoCtlPos::callThicknessRenderFirstPosAll() {
  if ((unknownf8 & unknown028_6) == 0) {
    return;
  }
  createThicknessRenderDisplayListSub(true);
}

void DrMdoCtlPos::callThicknessRenderSecondPosAll() {
  if ((unknownf8 & unknown028_6) == 0) {
    return;
  }
  createThicknessRenderDisplayListSub(false);
}

void DrMdoCtlPos::callGBuffRenderPosAll() {
  if ((unknownf8 & unknown028_1) == 0) {
    return;
  }
  unknownf4 = 1;
  unknownf2 = 7;
  unknown001();
  unknown30->unknownc8->beginVertexSetup();
  callPosRender(8);
}

void DrMdoCtlPos::callRefractionRenderPosAll() {
  if ((unknownf8 & unknown028_2) == 0) {
    return;
  }
  unknownf4 = 2;
  unknownf2 = 8;
  unknown001();
  unknown30->unknownc8->beginVertexSetup();
  callPosRender(4);
}

void DrMdoCtlPos::callLightPrePassRenderPosAll() {
  if ((unknownf8 & unknown028_3) == 0) {
    return;
  }
  unknownf4 = 3;
  unknownf2 = 4;
  unknown001();
  unknown30->unknownc8->beginVertexSetup();
  callPosRender(0x20);
}

void DrMdoCtlPos::callAlphaRenderPosAll() {
  if ((unknownf8 & unknown028_4) == 0) {
    return;
  }
  unknownf4 = 4;
  unknownf2 = 1;
  unknown001();
  unknown30->unknownc8->beginVertexSetup();
  callPosRender(2);
}

void DrMdoCtlPos::callSpAlphaRenderPosAll() {
  if ((unknownf8 & unknown028_5) == 0) {
    return;
  }
  unknownf4 = 5;
  unknownf2 = 1;
  unknown001();
  unknown30->unknownc8->beginVertexSetup();
  callPosRender(0x40);
}

void DrMdoCtlPos::callDisplistRender(int param) {}

void DrMdoCtlPos::callDisplistPrePsssRender(int param) {}

} // namespace ml
