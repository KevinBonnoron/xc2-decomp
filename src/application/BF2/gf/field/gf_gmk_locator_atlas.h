#pragma once
#include <stddef.h>

#include "gf/field/gf_gmk_locator.h"
#include "gmk/gmk_set.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace gf {

struct GfGmkLocators {
  mm::mtl::Vector<GfGmkLocator> unknown00; // Inferred role: locators of one gimmick type; original member name unknown.
  int unknown28;                           // Inferred role: gimmick type; original member name unknown.
};

static_assert(offsetof(GfGmkLocators, unknown28) == 0x28, "");
static_assert(sizeof(GfGmkLocators) == 0x30, "");

class GfGmkLocatorAtlas {
public:
  struct CreateInfo {
    // Inline in the game: the GfMenuObjWorldMap constructor (0x71004e5950) builds its member at 0x2fa0 with these values.
    CreateInfo() : unknown00(0), unknown04(0), unknown10(1.0e12f, 1.0e12f, 1.0e12f), unknown20(-1.0e12f, -1.0e12f, -1.0e12f) {}

    int unknown00;      // Inferred role: map; original member name unknown.
    int unknown04;      // Inferred role: map of the area; original member name unknown.
    mm::Vec3 unknown10; // Inferred role: area minimum; original member name unknown.
    mm::Vec3 unknown20; // Inferred role: area maximum; original member name unknown.
  };

  struct BdatInfo {
    BdatInfo() : unknown00(nullptr), unknown08(0) {}

    const char *unknown00; // Inferred role: level name; original member name unknown.
    u16 unknown08;         // Inferred role: level priority; original member name unknown.
  };

  explicit GfGmkLocatorAtlas(const CreateInfo *info);
  ~GfGmkLocatorAtlas() { dispose(); }
  void create(const CreateInfo &info);
  const BdatInfo *getBdatInfo(int id) const;
  void dispose();
  void createBdatInfos();
  void disposeBdatInfos();
  void update(f32 deltaTime);
  bool isBelongToCurMap(const mm::Vec3 &position) const;
  void seqWaitToCreateCurMapGmkSet(f32 deltaTime);
  void seqWaitToCreateGmkSet(f32 deltaTime);

  // The first four members are those of CreateInfo: the constructor gives them its default values, and GfMenuObjWorldMap::initialize copies them
  // with the implicit CreateInfo assignment (one 64-bit load and store for the two ints, 0x71004e6a68, then the two vectors component by component).
  CreateInfo unknown00;                       // Inferred role: map, map of the area and area bounds that the atlas was created with; original member name unknown.
  mm::mtl::Vector<BdatInfo> unknown30;        // Inferred role: level bdat infos; original member name unknown.
  int unknown58;                              // Inferred role: first level bdat id; original member name unknown.
  gmk::GmkSet *unknown60;                     // Inferred role: gimmick set of the locators; original member name unknown.
  gmk::GmkSet unknown70;                      // Inferred role: gimmick set of another map; original member name unknown.
  mm::mtl::Vector<GfGmkLocators> unknown410;  // Inferred role: locators; original member name unknown.
  void (GfGmkLocatorAtlas::*unknown438)(f32); // Inferred role: seq; original member name unknown.
};

static_assert(offsetof(GfGmkLocatorAtlas::CreateInfo, unknown10) == 0x10, "");
static_assert(offsetof(GfGmkLocatorAtlas::CreateInfo, unknown20) == 0x20, "");
static_assert(sizeof(GfGmkLocatorAtlas::CreateInfo) == 0x30, "");
static_assert(offsetof(GfGmkLocatorAtlas, unknown30) == 0x30, "");
static_assert(offsetof(GfGmkLocatorAtlas, unknown58) == 0x58, "");
static_assert(offsetof(GfGmkLocatorAtlas, unknown60) == 0x60, "");
static_assert(offsetof(GfGmkLocatorAtlas, unknown70) == 0x70, "");
static_assert(offsetof(GfGmkLocatorAtlas, unknown410) == 0x410, "");
static_assert(offsetof(GfGmkLocatorAtlas, unknown438) == 0x438, "");
static_assert(sizeof(GfGmkLocatorAtlas) == 0x450, "");

} // namespace gf
