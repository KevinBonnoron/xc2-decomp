#pragma once
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
}

namespace gmk {

enum GmkType {
  GMK_TYPE_ENEMY = 0,
  GMK_TYPE_ROUTED_ENEMY = 1,
};

class AGmkBase;

int getCurrentMapBdatId();
AGmkBase *getBindedGmkInst(gf::GF_OBJ_HANDLE *handle);
void setDispByGmkType(GmkType type, bool isDisp);
void setDispByGmkTypeAndBdatId(GmkType type, int bdatId, bool isDisp);
void setDispByGmkTypeAndGmkIdx(int gmkSet, GmkType type, u32 index, bool isDisp);

} // namespace gmk
