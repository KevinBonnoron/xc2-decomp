#pragma once
#include <stddef.h>

#include "gf/asset/gf_asset_def.h"
#include "gf/asset/gf_asset_path.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

struct CBdatWrapper;

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

struct GF_ASSET_HANDLE;
struct GfAssetFilesInfo;
class GfAssetPack;
class GfInitParam;

class GfAssetSetup {
public:
  static mm::mtl::RTTI m_rtti;

  struct RefResource {
    RefResource() : data(nullptr), size(0), index(0) {}

    mm::mtl::FixStr<128> name;
    void *data;
    u32 size;
    u32 index;
  };

  static const u32 REF_RESOURCE_MAX = 24;

  GfAssetSetup();
  virtual const mm::mtl::RTTI *getRTTI() const { return &m_rtti; }

  virtual ~GfAssetSetup();

  virtual const char *getAssetCategoryName() const { return nullptr; }
  virtual const char *getMdlFile(GfAssetType type) { return nullptr; }
  virtual const char *getArcFile(GfAssetType type) { return nullptr; }
  virtual const char *getMotFile(GfAssetType type) { return nullptr; }
  virtual const char *getRetargetMotFile(GfAssetType type) { return nullptr; }
  virtual const char *getEvtMotFile(GfAssetType type) { return nullptr; }
  virtual const char *getSalvageMotFile(GfAssetType type) { return nullptr; }
  virtual const char *getUiMotFile(GfAssetType type) { return nullptr; }
  virtual const char *getEfpFile(GfAssetType type) { return nullptr; }
  virtual const char *getEabFile(GfAssetType type) { return nullptr; }
  virtual const char *getEfbFile(GfAssetType type) { return nullptr; }
  virtual const char *getEfTailFile(GfAssetType type) { return nullptr; }
  virtual const char *getStpFile(GfAssetType type) { return nullptr; }
  virtual const char *getEvtStpFile(GfAssetType type) { return nullptr; }
  virtual const char *getUiStpFile(GfAssetType type) { return nullptr; }
  virtual const char *getSalvageStpFile(GfAssetType type) { return nullptr; }
  virtual GfFileIdx getMdlSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getArcSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getMotSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getRetargetMotSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getEvtMotSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getSalvageMotSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getUiMotSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getEfpSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getEabSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getEfbSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getStpSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getEvtStpSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getUiStpSlot() const { return FILE_IDX_NONE; }
  virtual GfFileIdx getSalvageStpSlot() const { return FILE_IDX_NONE; }
  virtual const char *getPath() const { return ""; }
  virtual const char *getEvtPath() const { return ""; }
  virtual const char *getEffPath() const { return GfAssetPath::getEff(); }
  virtual const char *getStpPath() const { return GfAssetPath::getStp(); }
  virtual const char *getSePackPath() const { return GfAssetPath::getSePack(); }
  virtual void requestCoreResource(GfAssetPack *pack, GF_ASSET_HANDLE *handle);
  virtual GfAssetType getAssetType() const { return ASSET_TYPE_BASE; }

  void setupParam(GF_ASSET_HANDLE *handle, const GfInitParam &param);
  bool setupReference(GfAssetPack *pack, const char *name, GfFileIdx index);
  static void makeAssetNamePrefix(mm::mtl::FixStr<128> &name, GfAssetType type, const char *file, const char *suffix);
  bool checkValidResource();
  RefResource *getRefResource(u32 index);
  void setRefResource(u32 index, const char *name, void *data, u32 size);
  static void makeAssetName(mm::mtl::FixStr<128> &name, GfAssetType type, const char *file);
  static void requestFootStepSePackFile(GfAssetFilesInfo &info, u32 footStep, GfFileIdx firstIndex, GfFileIdx secondIndex);
  static void requestWpnSePackFile(GfAssetFilesInfo &info, u32 weaponType, GfFileIdx index);

  u32 id;
  GF_ASSET_HANDLE *handle;
  CBdatWrapper *bdat;
  mm::mtl::FixedVector<RefResource *, REF_RESOURCE_MAX> refResources;
  const GfInitParam *initParam;
  bool hasRefResource;
  mm::mtl::FixStr<128> debugModelName;
  mm::mtl::FixStr<128> debugMotionName;
};

static_assert(sizeof(GfAssetSetup::RefResource) == 0x98, "");
static_assert(offsetof(GfAssetSetup, id) == 0x08, "");
static_assert(offsetof(GfAssetSetup, handle) == 0x10, "");
static_assert(offsetof(GfAssetSetup, bdat) == 0x18, "");
static_assert(offsetof(GfAssetSetup, refResources) == 0x20, "");
static_assert(offsetof(GfAssetSetup, initParam) == 0xe8, "");
static_assert(offsetof(GfAssetSetup, hasRefResource) == 0xf0, "");
static_assert(offsetof(GfAssetSetup, debugModelName) == 0xf4, "");

} // namespace gf
