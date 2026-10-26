#pragma once

#include "dr/dr_mdo_ctl_seam.h"

namespace grlib {
class CGLibVtxInstans;
} // namespace grlib

namespace ml {

class DrResMdoSeamWrkInst;
struct MdsMdlInfoHeader;
struct MdoArgSeamUpdate;
struct _MdoInstanceWork;
struct MdoWrkMatRes;

class DrMdoCtlSeamInstMap : public DrMdoCtlSeam {
public:
  void updateInstMap(MdoArgSeamUpdate &arg);
  void readInstMapCheck();
  void updateInstMapRenderList(MdoArgSeamUpdate &arg);
  void createInstMapDisplayList();
  void callRenderSeamInstMap();
  void callGBuffRenderSeamInstMap();
  void callLightPrePassRenderSeamInstMap();
  void callRefractionRenderSeamInstMap();
  void callAlphaRenderSeamInstMap();
  void callSpAlphaRenderSeamInstMap();
  void renderSeamInstMap(int renderType);
  void createInstRenderDisplayList(const MdsMdlInfoHeader *header, int index, DrResMdoSeamWrkInst *wrk, _MdoInstanceWork *work, grlib::CGLibVtxInstans *instans, int count);
  void beginResAll(MdoWrkMatRes *matRes);
  void endResAll();
};

} // namespace ml
