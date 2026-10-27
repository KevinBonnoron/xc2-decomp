#include "dr/dr_mdo_ctl_seam_inst_map.h"
#include "dr/dr_res_mdo_seam_wrk_inst.h"

namespace ml {

void DrMdoCtlSeamInstMap::releaseInstMap() {
  DrResMdoSeamWrkInst *inst = unknown310;
  while (inst != nullptr) {
    DrResMdoSeamWrkInst *next = inst->unknown08;
    releaseFreeSeamInst(inst);
    inst = next;
  }
}

struct MdoWrkMatRes;

void DrMdoCtlSeamInstMap::callRenderSeamInstMap() { renderSeamInstMap(0); }

void DrMdoCtlSeamInstMap::callGBuffRenderSeamInstMap() { renderSeamInstMap(1); }

void DrMdoCtlSeamInstMap::callLightPrePassRenderSeamInstMap() { renderSeamInstMap(3); }

void DrMdoCtlSeamInstMap::callRefractionRenderSeamInstMap() { renderSeamInstMap(2); }

void DrMdoCtlSeamInstMap::callAlphaRenderSeamInstMap() { renderSeamInstMap(4); }

void DrMdoCtlSeamInstMap::callSpAlphaRenderSeamInstMap() { renderSeamInstMap(5); }

void DrMdoCtlSeamInstMap::createInstRenderDisplayList(const MdsMdlInfoHeader *, int, DrResMdoSeamWrkInst *, _MdoInstanceWork *, grlib::CGLibVtxInstans *, int) {}

void DrMdoCtlSeamInstMap::beginResAll(MdoWrkMatRes *matRes) {
  MdoWrkMatRes *prev = unknown30;
  unknown30 = matRes;
  unknownb38 = prev;
}

void DrMdoCtlSeamInstMap::endResAll() { unknown30 = unknownb38; }

void DrMdoCtlSeamInstMap::updateInstMap(MdoArgSeamUpdate &arg) {
  readInstMapCheck();
  if (((unknownc7c >> 12) & 1) == 0) {
    updateInstMapRenderList(arg);
    createInstMapDisplayList();
  }
}

} // namespace ml
