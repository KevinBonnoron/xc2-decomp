// No game string names this file: named after the class, between the fw wind code and gf_asset_log.cpp (game string C:/Monolithsoft/BF2/prog/application/BF2/gf/asset/gf_asset_log.cpp) in the game's
// code order.
#include "gf/asset/gf_asset_factory.h"

#include "gf/asset/gf_asset_manager.h"
#include "gf/asset/gf_asset_setup.h"
#include "gf/object/gf_init_param.h"
#include "mm_mtl/rtti.h"

namespace gf {

namespace {

// Inferred role: sets up an asset pack with the setup of the init param, or a default one; original name unknown.
template <typename SETUP, typename PARAM> GF_ASSET_HANDLE *unknown001(GF_ASSET_HANDLE *handle, const PARAM &param) {
  SETUP defaultSetup;
  SETUP *setup = &defaultSetup;
  if (param.unknown88 != nullptr) {
    setup = static_cast<SETUP *>(param.unknown88);
  }
  setup->setup(handle, param);
  return setup->unknown10;
}

// Inferred role: creates the asset handle and sets it up as unknown001, checking the type of the setup of the init param; original name unknown.
template <typename SETUP, typename PARAM> GF_ASSET_HANDLE *unknown002(const PARAM &param) {
  GF_ASSET_HANDLE *handle = GfAssetManager::createAssetHandle(param);
  SETUP defaultSetup;
  SETUP *setup = &defaultSetup;
  if (param.unknown88 != nullptr) {
    setup = mm::mtl::dynamicCast<SETUP>(param.unknown88);
  }
  setup->setup(handle, param);
  return setup->unknown10;
}

} // namespace

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackDriverForEvent(const GfInitParamDriver &param) { return unknown002<GfAssetSetupEventDriver>(param); }

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackDriverForSalvage(const GfInitParamDriver &param) { return unknown002<GfAssetSetupSalvage>(param); }

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackDriverForUi(const GfInitParamDriver &param) { return unknown002<GfAssetSetupDriverForUi>(param); }

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackBlade(const GfInitParamBlade &param) {
  if (param.isEvent()) {
    return createAssetPackBladeForEvent(param);
  }
  if (param.unknown002()) {
    return createAssetPackBladeForUi(param);
  }
  return unknown001<GfAssetSetupBlade>(GfAssetManager::createAssetHandle(param), param);
}

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackBladeForEvent(const GfInitParamBlade &param) { return unknown002<GfAssetSetupEventBlade>(param); }

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackBladeForUi(const GfInitParamBlade &param) { return unknown002<GfAssetSetupBladeForUi>(param); }

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackMap(const GfInitParamMapSeamless &param) { return unknown001<GfAssetSetupMapSeamless>(GfAssetManager::createAssetHandle(param), param); }

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackEnemy(const GfInitParamEnemy &param) {
  if (param.isEvent()) {
    return createAssetPackEnemyForEvent(param);
  }
  GF_ASSET_HANDLE *handle = GfAssetManager::createAssetHandle(param);
  if (param.unknown08 == unknown030_5) {
    return unknown001<GfAssetSetupEnemyBlade>(handle, param);
  }
  return unknown001<GfAssetSetupEnemy>(handle, param);
}

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackEnemyForEvent(const GfInitParamEnemy &param) { return unknown002<GfAssetSetupEventEnemy>(param); }

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackNpc(const GfInitParamNpc &param) {
  if (param.isEvent()) {
    return createAssetPackNpcForEvent(param);
  }
  return unknown001<GfAssetSetupNpc>(GfAssetManager::createAssetHandle(param), param);
}

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackNpcForEvent(const GfInitParamNpc &param) { return unknown002<GfAssetSetupEventNpc>(param); }

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackMob(const GfInitParamMob &param) {
  if (param.isEvent()) {
    return createAssetPackMobForEvent(param);
  }
  return unknown001<GfAssetSetupMob>(GfAssetManager::createAssetHandle(param), param);
}

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackMobForEvent(const GfInitParamMob &param) { return unknown002<GfAssetSetupEventMob>(param); }

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackGimmick(const GfInitParamGimmick &param) { return unknown001<GfAssetSetupGimmick>(GfAssetManager::createAssetHandle(param), param); }

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackMapObj(const GfInitParamMapObj &param) { return unknown001<GfAssetSetupMapObj>(GfAssetManager::createAssetHandle(param), param); }

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackFobj(const GfInitParamFobj &param) { return unknown001<GfAssetSetupFobj>(GfAssetManager::createAssetHandle(param), param); }

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackWeapon(const GfInitParamWeapon &param) {
  if (param.unknown08 == unknown030_3) {
    return createAssetPackWeaponForEventCS(param);
  }
  return unknown001<GfAssetSetupWeapon>(GfAssetManager::createAssetHandle(param), param);
}

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackWeaponForEventCS(const GfInitParamWeapon &param) { return unknown002<GfAssetSetupWeaponEventCS>(param); }

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackEnWeapon(const GfInitParamEnWeapon &param) { return unknown001<GfAssetSetupEnWeapon>(GfAssetManager::createAssetHandle(param), param); }

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackBelonging(const GfInitParamBelonging &param) { return unknown001<GfAssetSetupBelonging>(GfAssetManager::createAssetHandle(param), param); }

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackExtra(const GfInitParamExtra &param) { return unknown001<GfAssetSetupExtra>(GfAssetManager::createAssetHandle(param), param); }

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackEventObj(const GfInitParamEventObj &param) { return unknown001<GfAssetSetupEventObj>(GfAssetManager::createAssetHandle(param), param); }

GF_ASSET_HANDLE *GfAssetFactory::createAssetPackUiObj(const GfInitParamUiObj &param) { return unknown001<GfAssetSetupUiObj>(GfAssetManager::createAssetHandle(param), param); }

} // namespace gf
