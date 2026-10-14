#pragma once
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class SCOM_ACHIEV_INC {
public:
  static void createBladeArts(GF_OBJ_HANDLE *handle, u32 arts);
  static void createBladeArtsSp(GF_OBJ_HANDLE *handle, u32 arts);
  static void createBladeNArts(GF_OBJ_HANDLE *handle);
  static void createElementalCombo(GF_OBJ_HANDLE *handle);
  static void createElementalComboFinish(GF_OBJ_HANDLE *handle);
  static void createFightCombo(GF_OBJ_HANDLE *handle);
  static void createFightComboFinish(GF_OBJ_HANDLE *handle);
  static void createChainAttack(GF_OBJ_HANDLE *handle);
  static void createButtonChallenge();
  static void createHelp(GF_OBJ_HANDLE *handle);
  static void createPotGet();
  static void createAvoid(GF_OBJ_HANDLE *handle);
  static void createGuard(GF_OBJ_HANDLE *handle);
  static void createBladeChange(GF_OBJ_HANDLE *handle);
  static void createRecover(GF_OBJ_HANDLE *handle, u32 value);
  static void createBackAttack(GF_OBJ_HANDLE *handle);
  static void createKizuna(GF_OBJ_HANDLE *handle);
};

} // namespace gf
