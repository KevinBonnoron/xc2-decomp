#pragma once

namespace gf {

struct GF_ASSET_HANDLE;
class GfInitParamBelonging;
class GfInitParamBlade;
class GfInitParamDriver;
class GfInitParamEnWeapon;
class GfInitParamEnemy;
class GfInitParamEventObj;
class GfInitParamExtra;
class GfInitParamFobj;
class GfInitParamGimmick;
class GfInitParamMapObj;
class GfInitParamMapSeamless;
class GfInitParamMob;
class GfInitParamNpc;
class GfInitParamUiObj;
class GfInitParamWeapon;

class GfAssetFactory {
public:
  static GF_ASSET_HANDLE *createAssetPackDriverForEvent(const GfInitParamDriver &param);
  static GF_ASSET_HANDLE *createAssetPackDriverForSalvage(const GfInitParamDriver &param);
  static GF_ASSET_HANDLE *createAssetPackDriverForUi(const GfInitParamDriver &param);
  static GF_ASSET_HANDLE *createAssetPackBlade(const GfInitParamBlade &param);
  static GF_ASSET_HANDLE *createAssetPackBladeForEvent(const GfInitParamBlade &param);
  static GF_ASSET_HANDLE *createAssetPackBladeForUi(const GfInitParamBlade &param);
  static GF_ASSET_HANDLE *createAssetPackMap(const GfInitParamMapSeamless &param);
  static GF_ASSET_HANDLE *createAssetPackEnemy(const GfInitParamEnemy &param);
  static GF_ASSET_HANDLE *createAssetPackEnemyForEvent(const GfInitParamEnemy &param);
  static GF_ASSET_HANDLE *createAssetPackNpc(const GfInitParamNpc &param);
  static GF_ASSET_HANDLE *createAssetPackNpcForEvent(const GfInitParamNpc &param);
  static GF_ASSET_HANDLE *createAssetPackMob(const GfInitParamMob &param);
  static GF_ASSET_HANDLE *createAssetPackMobForEvent(const GfInitParamMob &param);
  static GF_ASSET_HANDLE *createAssetPackGimmick(const GfInitParamGimmick &param);
  static GF_ASSET_HANDLE *createAssetPackMapObj(const GfInitParamMapObj &param);
  static GF_ASSET_HANDLE *createAssetPackFobj(const GfInitParamFobj &param);
  static GF_ASSET_HANDLE *createAssetPackWeapon(const GfInitParamWeapon &param);
  static GF_ASSET_HANDLE *createAssetPackWeaponForEventCS(const GfInitParamWeapon &param);
  static GF_ASSET_HANDLE *createAssetPackEnWeapon(const GfInitParamEnWeapon &param);
  static GF_ASSET_HANDLE *createAssetPackBelonging(const GfInitParamBelonging &param);
  static GF_ASSET_HANDLE *createAssetPackExtra(const GfInitParamExtra &param);
  static GF_ASSET_HANDLE *createAssetPackEventObj(const GfInitParamEventObj &param);
  static GF_ASSET_HANDLE *createAssetPackUiObj(const GfInitParamUiObj &param);
};

} // namespace gf
