#pragma once
#include <stddef.h>

#include "framework/sound/sound_res_trigger.h"
#include "gf/asset/gf_asset_def.h"
#include "gf/asset/gf_extend_resource.h"
#include "mm_mtl/fixed_queue.h"
#include "types.h"

struct CBdatWrapper;

namespace mm {
struct Vec3;

namespace mtl {
class ReferenceObject;
class RTTI;
} // namespace mtl
} // namespace mm

namespace anm {
class ResASM;
} // namespace anm

namespace gf {

struct GF_OBJ_HANDLE;
class GfComSound;
class GfAppendHandles;
class GfInitParamBelonging;
class GfInitParamBlade;
class GfInitParamDriver;
class GfInitParamEnWeapon;
class GfInitParamEnemy;
class GfInitParamEventObj;
class GfInitParamExtra;
class GfInitParamFobj;
class GfInitParamGimmick;
class GfInitParamMap;
class GfInitParamMapSeamless;
class GfInitParamMob;
class GfInitParamNpc;
class GfInitParamUiObj;
class GfInitParamWeapon;
struct GF_ASSET_HANDLE;

// Layout from its constructor, destructor and registerSoundTrigger.
class GfExtendPacking : public GfExtendResource {
public:
  static mm::mtl::RTTI m_rtti;

  GfExtendPacking();
  ~GfExtendPacking() override;
  const mm::mtl::RTTI *getRTTI() const override;

  anm::ResASM *unknown10;              // Inferred role: asm resource, released through its anmlib reference count by the destructor; original member name unknown.
  mm::mtl::ReferenceObject *unknown18; // Inferred role: object released by the destructor; original member name unknown.
  mm::mtl::FixedQueue<fw::SoundResTriggerImporter::unknown001 *, 8> unknown20; // Inferred role: sound triggers registered by registerSoundTrigger; original member name unknown.
};

static_assert(offsetof(GfExtendPacking, unknown10) == 0x10, "");
static_assert(offsetof(GfExtendPacking, unknown20) == 0x20, "");
static_assert(sizeof(GfExtendPacking) == 0x70, "");

bool checkSoundTriggerPlayer(GfComSound *sound, const fw::ResSoundTriggerInfo &info);
void addExtendPackingSoundTrigger(GF_ASSET_HANDLE *handle, GfFileIdx index, GfExtendPacking *packing);

class GfObjFactory {
public:
  static GF_OBJ_HANDLE *createGmkMapObj(const CBdatWrapper &bdat, int id);
  static GF_OBJ_HANDLE *createGmkTbox(const CBdatWrapper &bdat, int id);
  static GF_OBJ_HANDLE *createGmkEnemy(int id, s8 levelOffset, u16 priority, const mm::Vec3 &position, const mm::Vec3 &rotation, bool flag);
  static GF_OBJ_HANDLE *createGmkNpc(const CBdatWrapper &bdat, int id);
  static GF_OBJ_HANDLE *createGmkCommonBlade(u32 blade);
  static GF_OBJ_HANDLE *createGmkBlade(const CBdatWrapper &bdat, int id, int blade);
  static GF_OBJ_HANDLE *createGmkCollection(const CBdatWrapper &bdat, int id);
  static GF_OBJ_HANDLE *createGmkEvent(const CBdatWrapper &bdat, int id);
  static GF_OBJ_HANDLE *createGmkMapGimmick(const CBdatWrapper &bdat, int id);
  static GF_OBJ_HANDLE *createMap(const GfInitParamMapSeamless &param);
  static GF_OBJ_HANDLE *createDebugMap(const GfInitParamMap &param);
  static GF_OBJ_HANDLE *createMapObj(const GfInitParamGimmick &param);
  // Inferred return type: the function returns the object handle (0x7100585a1c) that GfEvtModelDriver stores (0x7100308e64).
  static GF_OBJ_HANDLE *createDriver(GfInitParamDriver &param);
  static GF_OBJ_HANDLE *createBlade(GfInitParamBlade &param);
  static GF_OBJ_HANDLE *createEnemy(GfInitParamEnemy &param);
  static GF_OBJ_HANDLE *createEventObj(const GfInitParamEventObj &param);
  static GF_OBJ_HANDLE *createUiObj(const GfInitParamUiObj &param);
  static GF_OBJ_HANDLE *createMapLodAnim();
  static GF_OBJ_HANDLE *createGmkMob(int id, u16 param2, u16 param3, u16 param4, u16 param5);
  static GF_OBJ_HANDLE *createNpc(const GfInitParamNpc &param);
  static GF_OBJ_HANDLE *createMob(const GfInitParamMob &param);
  static GF_OBJ_HANDLE *createMobNull();
  static GF_OBJ_HANDLE *createFieldObj(const GfInitParamFobj &param);
  // Inferred return type: the function returns the result of GfMountManager::getAppendHandles (0x7100589a10) or &param.unknown130 (0x7100589aa8), and the GfEvtModelWeapon constructor copies
  // a GfAppendHandles from it (0x710030c468).
  static GfAppendHandles *createDriverWeapon(GfInitParamWeapon &param);
  static GF_OBJ_HANDLE *createBelonging(GfInitParamBelonging &param);
  static GF_OBJ_HANDLE *createEnWeapon(GfInitParamEnWeapon &param);
  static GF_OBJ_HANDLE *createExtraModel(GfInitParamExtra &param);
  static void destroyObj(GF_OBJ_HANDLE *handle);
  static GF_OBJ_HANDLE *createSmnEnemy(int id, const mm::Vec3 &position, const mm::Vec3 &rotation, bool flag);
  static bool destroyObjHandle(GF_OBJ_HANDLE *handle);
  static void createUiWeapon(GF_OBJ_HANDLE *handle, u32 blade);
};

} // namespace gf
