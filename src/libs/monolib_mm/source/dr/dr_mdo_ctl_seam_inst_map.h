#pragma once

#include "dr/dr_mdo_ctl_seam_low_map.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace grlib {
class CGLibVtxInstans;
} // namespace grlib

namespace ml {

class DrPixlShadowCacheObj;
class DrPixlShadowObj;
class DrResMdoSeamWrkInst;
struct MdsMdlInfoHeader;
struct _MdoInstanceWork;
struct MdoWrkMatRes;
struct MdoArgSeamUpdate;

class DrMdoCtlSeamInstMap : public DrMdoCtlSeamLowMap {
public:
  DrMdoCtlSeamInstMap(int viewNum);
  void releaseInstMap();
  void initInstMapParts(DrResMdoSeamWrkInst *inst, DrResMdoSeamWrkInst *linked);
  void changeMemInstMapParts(DrResMdoSeamWrkInst *inst);
  void releaseFreeSeamInst(DrResMdoSeamWrkInst *inst);
  DrResMdoSeamWrkInst *createFreeSeamInst();
  void updateInstMap(MdoArgSeamUpdate &arg);
  bool readInstModelCheck(const mm::Vec3 &position, bool unknown001, bool isFirst);
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
  void callShadowCacheInstUpdate(u64 flags);
  void occInstRender();
  void createInstZPrePassDisplayList();
  void createInstThicknessPassDisplayList(bool isFirst);
  void callInstShadowCacheAddRender(int index);
  void callShadowMapRenderSeamInstMap(DrPixlShadowObj *shadow);
  void callInstShadowCacheRender(DrPixlShadowCacheObj &cache);
};

} // namespace ml
