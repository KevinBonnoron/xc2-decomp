#pragma once
#include "gf/object/gf_obj_manager.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
class GfAppendInfo;
class GfInitParamDriver;

class GfAppendUtil {
public:
  static void setupPartyBlade(GFATTACH attach, GF_OBJ_HANDLE *handle, u32 weapon, u32 driver, u32 blade);
  static void setupWeapon(GFATTACH attach, GfAppendInfo &info, u32 weapon, u32 driver, u32 blade, bool isViewer);
  static void setupActViewer(GFATTACH attach, GF_OBJ_HANDLE *handle, u32 weapon, u32 driver, u32 blade);
  static void setupEnemyBlade(GFATTACH attach, GF_OBJ_HANDLE *handle, u32 enArrange, GF_OBJ_HANDLE *owner, GF_OBJ_HANDLE *bladeHandle);
  static void setupEnemyBladeWithNoDriver(GFATTACH attach, GF_OBJ_HANDLE *handle, u32 blade, GF_OBJ_HANDLE *owner);
  static void setupBelonging(GF_OBJ_HANDLE *handle, u32 param2, u32 param3, u32 param4, u32 param5);
  static void setupBelongingForDriver(GF_OBJ_HANDLE *handle, const GfInitParamDriver &param);
  static void setupExtraModel(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *owner);
  static void setupEnemy(GFATTACH attach, GF_OBJ_HANDLE *handle, u32 enArrange, GF_OBJ_HANDLE *owner);
  static void setupEventActEnemy(GFATTACH attach, GF_OBJ_HANDLE *handle, u32 enArrange);
};

} // namespace gf
