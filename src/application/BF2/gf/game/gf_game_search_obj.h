#pragma once
#include <stddef.h>

#include "framework/reference_frame.h"
#include "gf/object/gf_obj_handle.h"
#include "ml/fixed_size_alloc.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
struct GF_SEARCH_OBJ;
struct GfSetupParam;

static GF_SEARCH_OBJ *const unknown012 = reinterpret_cast<GF_SEARCH_OBJ *>(-1); // Inferred role: invalid search obj; original name unknown.

// Size from the GfSearchInfo pool of GfGameSearchObj (1024 elements in 0xc000 bytes). Members from the consumers GfGameTarget::selectTarget
// and GfGameSearchObj::updateObj, which fills them.
struct GfSearchInfo {
  GF_OBJ_HANDLE *unknown00; // Inferred role: found object; original member name unknown.
  u8 _08[0x24 - 0x08];
  f32 unknown24;       // Inferred role: forward angle; original member name unknown.
  f32 unknown28;       // Inferred role: sort key copied from the cached position; original member name unknown.
  u32 unknown2c_0 : 1; // Inferred role: visible; original member name unknown.
  u32 : 31;
};

static_assert(offsetof(GfSearchInfo, unknown24) == 0x24, "");
static_assert(offsetof(GfSearchInfo, unknown28) == 0x28, "");
static_assert(sizeof(GfSearchInfo) == 0x30, "");

struct GfSearchParam {
  explicit GfSearchParam(u32 type = 0)
      : unknown00(0), unknown04(type), unknown10(mm::Vec3::zero), unknown20(mm::Quat::identity), unknown30(0.0f), unknown34(0.0f), unknown38(0.0f), unknown3c(0.0f), unknown40(unknown020),
        unknown50(true), unknown58(0), unknown60(unknown020) {}

  u32 unknown00;                                       // Inferred role: search kind; original member name unknown.
  u32 unknown04;                                       // Inferred role: searched object type bits; original member name unknown.
  mm::Vec3 unknown10;                                  // Inferred role: search position; original member name unknown.
  mm::Quat unknown20;                                  // Inferred role: search rotation; original member name unknown.
  f32 unknown30;                                       // Inferred role: minimum distance; original member name unknown.
  f32 unknown34;                                       // Inferred role: maximum distance; original member name unknown.
  f32 unknown38;                                       // Inferred role: unknown, 0 by default; original member name unknown.
  f32 unknown3c;                                       // Inferred role: unknown, copied to the cached positions; original member name unknown.
  GF_OBJ_HANDLE *unknown40;                            // Inferred role: searching object; original member name unknown.
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> unknown48; // Inferred role: searching frame; original member name unknown.
  bool unknown50;                                      // Inferred role: unknown, true by default; original member name unknown.
  u64 unknown58;                                       // Inferred role: unknown, 0 by default; original member name unknown.
  GF_OBJ_HANDLE *unknown60;                            // Inferred role: excluded object; original member name unknown.
};

static_assert(offsetof(GfSearchParam, unknown04) == 0x04, "");
static_assert(offsetof(GfSearchParam, unknown10) == 0x10, "");
static_assert(offsetof(GfSearchParam, unknown20) == 0x20, "");
static_assert(offsetof(GfSearchParam, unknown30) == 0x30, "");
static_assert(offsetof(GfSearchParam, unknown3c) == 0x3c, "");
static_assert(offsetof(GfSearchParam, unknown40) == 0x40, "");
static_assert(offsetof(GfSearchParam, unknown48) == 0x48, "");
static_assert(offsetof(GfSearchParam, unknown50) == 0x50, "");
static_assert(offsetof(GfSearchParam, unknown58) == 0x58, "");
static_assert(offsetof(GfSearchParam, unknown60) == 0x60, "");
static_assert(sizeof(GfSearchParam) == 0x70, "");

class GfGameSearchObj : public mm::mtl::PtrSingleton<GfGameSearchObj> {
public:
  struct GFSEARCH_INFO {
    GFSEARCH_INFO() : unknown70(unknown012), unknown78(nullptr), unknown80(0) {}

    GfSearchParam unknown00;                            // Inferred role: search parameters; original member name unknown.
    GF_SEARCH_OBJ *unknown70;                           // Inferred role: handle; original member name unknown.
    mm::mtl::FixedList<GfSearchInfo *, 256> *unknown78; // Inferred role: found objects; original member name unknown.
    u32 unknown80;                                      // Inferred role: flags, bit 0 disables the search; original member name unknown.
  };

  struct GfSearchCache {
    struct POS {
      const mm::Vec3 *unknown00; // Inferred role: position; original member name unknown.
      const mm::Quat *unknown08; // Inferred role: rotation; original member name unknown.
      f32 unknown10;             // Inferred role: copied from GfSearchParam::unknown3c; original member name unknown.
      GF_OBJ_HANDLE *unknown18;  // Inferred role: object; original member name unknown.
      f32 unknown20;             // Inferred role: forward angle; original member name unknown.
    };

    GfSearchCache() { unknown001(); }

    // Inferred role: marks every cached list as outdated; original name unknown.
    void unknown001() {
      for (int type = 0; type < 13; type++) {
        unknown82000[type] = -1;
      }
    }

    POS unknown00[13][1024]; // Inferred role: positions per object list type; original member name unknown.
    int unknown82000[13];    // Inferred role: position count per object list type, -1 when outdated; original member name unknown.
  };

  GfGameSearchObj(const GfSetupParam &param);
  virtual ~GfGameSearchObj();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  void destroyList(mm::mtl::FixedList<GfSearchInfo *, 256> *list);
  static GF_SEARCH_OBJ *createObj(const GfSearchParam &param);
  static void update(const fw::UpdateInfo &info);
  void updateObj(GF_SEARCH_OBJ *searchObj);
  static void destroyObj(GF_SEARCH_OBJ *searchObj);
  static void setEnable(GF_SEARCH_OBJ *searchObj, bool isEnable);
  static bool isEnable(GF_SEARCH_OBJ *searchObj);
  static bool isInitialized();
  static GFSEARCH_INFO *getInfo(GF_SEARCH_OBJ *searchObj);
  static mm::mtl::FixedList<GfSearchInfo *, 256> *getObj(GF_SEARCH_OBJ *searchObj);
  u64 createHandle(u32 index);
  void initialize(const GfSetupParam &param);

  ml::fixed_size_alloc_inside<GFSEARCH_INFO, 64> unknown08;    // Inferred role: search infos; original member name unknown.
  mm::mtl::FixedList<GF_SEARCH_OBJ *, 64> unknown2438;         // Inferred role: active searches; original member name unknown.
  ml::fixed_size_alloc_inside<GfSearchInfo, 1024> unknown2898; // Inferred role: found object pool; original member name unknown.
  GfSearchCache unknowne940;                                   // Inferred role: object position cache; original member name unknown.
  u32 unknown90978;                                            // Inferred role: handle serial; original member name unknown.
  bool unknown9097c;                                           // Inferred role: initialized; original member name unknown.
};

static_assert(sizeof(GfGameSearchObj::GFSEARCH_INFO) == 0x90, "");
static_assert(offsetof(GfGameSearchObj::GFSEARCH_INFO, unknown70) == 0x70, "");
static_assert(offsetof(GfGameSearchObj::GFSEARCH_INFO, unknown78) == 0x78, "");
static_assert(offsetof(GfGameSearchObj::GFSEARCH_INFO, unknown80) == 0x80, "");
static_assert(sizeof(GfGameSearchObj::GfSearchCache::POS) == 0x28, "");
static_assert(offsetof(GfGameSearchObj::GfSearchCache, unknown82000) == 0x82000, "");
static_assert(offsetof(GfGameSearchObj, unknown08) == 0x08, "");
static_assert(offsetof(GfGameSearchObj, unknown2438) == 0x2438, "");
static_assert(offsetof(GfGameSearchObj, unknown2898) == 0x2898, "");
static_assert(offsetof(GfGameSearchObj, unknowne940) == 0xe940, "");
static_assert(offsetof(GfGameSearchObj, unknown90978) == 0x90978, "");
static_assert(offsetof(GfGameSearchObj, unknown9097c) == 0x9097c, "");
static_assert(sizeof(GfGameSearchObj) == 0x90980, "");

} // namespace gf
