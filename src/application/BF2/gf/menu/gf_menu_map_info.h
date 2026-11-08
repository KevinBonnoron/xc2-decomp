#pragma once
#include <stddef.h>

#include "mm_math/mm_pnt.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace fw {
class CommonResource;
} // namespace fw

namespace gf {

// Layout evidence: the constructor (0x71003c5ee4) fills 0x158 bytes, the destructor releases the vectors at 0x10, 0x38
// and 0x80 + 0x28 * n (n < 5), getMapRatio reads 0x148 and 0x14c and getMapSize 0x150 to 0x156.
class GfMenuMapInfo : public mm::mtl::PtrSingleton<GfMenuMapInfo> {
public:
  // Layout evidence: getMapArea(int, u32) at 0x71003c8658 returns the elements of 0x48 bytes of the map asset and
  // getMapAreaFromName(int, const char *, MapAreaInfo &) copies one of them into a MapAreaInfo.
  struct MapAreaInfo {
    MapAreaInfo() : unknown20(0.0f), unknown24(0.0f), unknown28(0.0f), unknown2c(0.0f), unknown30(0.0f), unknown34(0.0f), _38() { unknown00[0] = 0; }

    char unknown00[0x20]; // Inferred role: area name; original member name unknown.
    f32 unknown20;        // Inferred role: minimum x; original member name unknown.
    f32 unknown24;        // Inferred role: minimum y; original member name unknown.
    f32 unknown28;        // Inferred role: minimum z; original member name unknown.
    f32 unknown2c;        // Inferred role: maximum x; original member name unknown.
    f32 unknown30;        // Inferred role: maximum y; original member name unknown.
    f32 unknown34;        // Inferred role: maximum z; original member name unknown.
    u8 _38[0x48 - 0x38];
  };

  // Layout evidence: setCurrentMap (0x71003c7be4) fills the elements of 0x18 bytes and getMapSegImageName reads 0x0a and 0x10.
  struct SegInfo {
    fw::CommonResource *unknown00; // Inferred role: segment resource; original member name unknown.
    u16 unknown08;                 // Inferred role: level priority; original member name unknown.
    bool unknown0a;                // Inferred role: condition result; original member name unknown.
    u16 unknown0c;                 // Inferred role: condition; original member name unknown.
    u32 unknown10;                 // Inferred role: area index of the second level name; original member name unknown.
    int unknown14;                 // Inferred role: bdat row; original member name unknown.
  };

  // Layout evidence: Vector<MiniIcon>::push_back (0x71003c7b14) copies 0x00 as 8 bytes and 0x10, 0x14 and 0x18.
  struct MiniIcon {
    u32 unknown00;      // Inferred role: icon type; original member name unknown.
    u32 unknown04;      // Inferred role: map id; original member name unknown.
    mm::Vec3 unknown10; // Inferred role: position in the area; original member name unknown.
  };

  ~GfMenuMapInfo();
  static void destroy();
  void finalize();
  static bool isInitialized();
  static bool isLoading();
  static void setCurrentMap(u32 map);
  static u32 getMapAreaCount(int index);
  static bool getMapArea(int index, u32 areaIndex, MapAreaInfo &info);
  static int getMapInfoIndex(const char *name);
  static const MapAreaInfo *getMapArea(int index, u32 areaIndex);
  static bool getMapAreaFromName(int index, const char *name, MapAreaInfo &info);
  static const MapAreaInfo *getMapAreaFromName(int index, const char *name);
  static bool isValid();
  static bool getMapSegImageOffs(mm::Pnt<s16> &offset);
  static bool getMapRatio(f32 &x, f32 &y);
  static bool getMiniIconList(u32 type, const mm::mtl::Vector<MiniIcon> **list);
  static bool getMapSize(s16 &left, s16 &top, s16 &right, s16 &bottom);
  static bool getCurMapAreaInfo(MapAreaInfo &info);

  // Layout evidence: getMapAreaCount reads the area count at 0x04 of the asset data and getMapArea returns 0x08 + 0x48 * index.
  struct unknown001 {
    u32 unknown00;            // Inferred role: version; original member name unknown.
    u32 unknown04;            // Inferred role: area count; original member name unknown.
    MapAreaInfo unknown08[1]; // Inferred role: areas; original member name unknown.
  };

  bool unknown08;                                  // Inferred role: initialized; original member name unknown.
  mm::mtl::Vector<fw::CommonResource *> unknown10; // Inferred role: map info resources; original member name unknown.
  mm::mtl::Vector<SegInfo> unknown38;              // Inferred role: segment infos of the current map; original member name unknown.
  int unknown60;                                   // Inferred role: current map info index; original member name unknown.
  int unknown64;                                   // Inferred role: current area index; original member name unknown.
  int unknown68;                                   // Inferred role: previous area index; original member name unknown.
  int unknown6c;                                   // Inferred role: segment x offset; original member name unknown.
  int unknown70;                                   // Inferred role: segment y offset; original member name unknown.
  int unknown74;                                   // Inferred role: segment image x offset; original member name unknown.
  int unknown78;                                   // Inferred role: segment image y offset; original member name unknown.
  u32 unknown7c;                                   // Inferred role: current map id; original member name unknown.
  mm::mtl::Vector<MiniIcon> unknown80[5];          // Inferred role: mini icons per type; original member name unknown.
  f32 unknown148;                                  // Inferred role: map x ratio; original member name unknown.
  f32 unknown14c;                                  // Inferred role: map y ratio; original member name unknown.
  s16 unknown150;                                  // Inferred role: map left; original member name unknown.
  s16 unknown152;                                  // Inferred role: map top; original member name unknown.
  s16 unknown154;                                  // Inferred role: map right; original member name unknown.
  s16 unknown156;                                  // Inferred role: map bottom; original member name unknown.
};

static_assert(offsetof(GfMenuMapInfo::MapAreaInfo, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuMapInfo::MapAreaInfo, unknown34) == 0x34, "");
static_assert(sizeof(GfMenuMapInfo::MapAreaInfo) == 0x48, "");
static_assert(offsetof(GfMenuMapInfo::SegInfo, unknown10) == 0x10, "");
static_assert(sizeof(GfMenuMapInfo::SegInfo) == 0x18, "");
static_assert(offsetof(GfMenuMapInfo::MiniIcon, unknown10) == 0x10, "");
static_assert(sizeof(GfMenuMapInfo::MiniIcon) == 0x20, "");
static_assert(offsetof(GfMenuMapInfo, unknown10) == 0x10, "");
static_assert(offsetof(GfMenuMapInfo, unknown38) == 0x38, "");
static_assert(offsetof(GfMenuMapInfo, unknown60) == 0x60, "");
static_assert(offsetof(GfMenuMapInfo, unknown80) == 0x80, "");
static_assert(offsetof(GfMenuMapInfo, unknown148) == 0x148, "");
static_assert(offsetof(GfMenuMapInfo, unknown150) == 0x150, "");
static_assert(sizeof(GfMenuMapInfo) == 0x158, "");

} // namespace gf
