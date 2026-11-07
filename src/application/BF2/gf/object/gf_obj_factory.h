#pragma once
#include <stddef.h>

#include "gf/asset/gf_extend_resource.h"
#include "types.h"

struct CBdatWrapper;
namespace mm {
struct Vec3;
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace anm {
class ResASM;
} // namespace anm

namespace gf {

struct GF_OBJ_HANDLE;
class GfInitParamMap;
class GfInitParamMapSeamless;

// Layout from its constructor, destructor and registerSoundTrigger. The game's destructor is out of line
// (D1/D2 at 0x710058464c); it is not declared here until it is decompiled.
class GfExtendPacking : public GfExtendResource {
public:
  static mm::mtl::RTTI m_rtti;

  const mm::mtl::RTTI *getRTTI() const override;

  anm::ResASM *unknown10; // Inferred role: asm resource, released through its anmlib reference count by the destructor; original member name unknown.
  u8 _18[0x70 - 0x18];
};

static_assert(offsetof(GfExtendPacking, unknown10) == 0x10, "");
static_assert(sizeof(GfExtendPacking) == 0x70, "");

class GfObjFactory {
public:
  static GF_OBJ_HANDLE *createGmkMapObj(const CBdatWrapper &bdat, int id);
  static GF_OBJ_HANDLE *createGmkTbox(const CBdatWrapper &bdat, int id);
  static GF_OBJ_HANDLE *createGmkEnemy(int id, s8 param2, u16 param3, const mm::Vec3 &position, const mm::Vec3 &rotation, bool param6);
  static GF_OBJ_HANDLE *createGmkNpc(const CBdatWrapper &bdat, int id);
  static GF_OBJ_HANDLE *createGmkBlade(const CBdatWrapper &bdat, int id, int param3);
  static GF_OBJ_HANDLE *createGmkCollection(const CBdatWrapper &bdat, int id);
  static GF_OBJ_HANDLE *createGmkEvent(const CBdatWrapper &bdat, int id);
  static GF_OBJ_HANDLE *createGmkMapGimmick(const CBdatWrapper &bdat, int id);
  static GF_OBJ_HANDLE *createMap(const GfInitParamMapSeamless &param);
  static GF_OBJ_HANDLE *createDebugMap(const GfInitParamMap &param);
  static void destroyObj(GF_OBJ_HANDLE *handle);
  static void createUiWeapon(GF_OBJ_HANDLE *handle, u32 blade);
};

} // namespace gf
