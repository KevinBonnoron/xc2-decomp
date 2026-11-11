#pragma once
#include <stddef.h>

#include "dr/dr_irr_vol_allocator.h"
#include "ml/work_event.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/list.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace ml {
class DebDraw;
class EventFileTh;
class FileHandleTh;

namespace irrvol {

class DrIrrVolResMan;
struct SSectorInfo;

// Inferred role: header of the sector file table, after the "STAC" magic and the version; original type name unknown.
struct unknown001 {
  u8 _00[0x10];
  u32 *unknown10; // Inferred role: sector file sizes, stored as an offset in the file; original member name unknown.
  u32 *unknown18; // Inferred role: sector file offsets, stored as an offset in the file; original member name unknown.
};

static_assert(offsetof(unknown001, unknown10) == 0x10, "");
static_assert(offsetof(unknown001, unknown18) == 0x18, "");
static_assert(sizeof(unknown001) == 0x20, "");

class DrIrrVolResObj {
public:
  DrIrrVolResObj(int index, DrIrrVolResMan *manager, FileHandleTh *handle);
  ~DrIrrVolResObj();
  void release();
  void onLoaded(EventFileTh *event);

  DrIrrVolResMan *unknown00;    // Inferred role: owner; original member name unknown.
  FileHandleTh *unknown08;      // Inferred role: file handle; original member name unknown.
  void *unknown10;              // Inferred role: file data; original member name unknown.
  const SSectorInfo *unknown18; // Inferred role: resolved sector info; original member name unknown.
  int unknown20;                // Inferred role: loaded state; original member name unknown.
  u32 unknown24;                // Inferred role: sector index; original member name unknown.
};

static_assert(offsetof(DrIrrVolResObj, unknown08) == 0x08, "");
static_assert(offsetof(DrIrrVolResObj, unknown10) == 0x10, "");
static_assert(offsetof(DrIrrVolResObj, unknown18) == 0x18, "");
static_assert(offsetof(DrIrrVolResObj, unknown20) == 0x20, "");
static_assert(offsetof(DrIrrVolResObj, unknown24) == 0x24, "");
static_assert(sizeof(DrIrrVolResObj) == 0x28, "");

class DrIrrVolResMan : public IWorkEvent {
public:
  ~DrIrrVolResMan() override;
  bool OnFileEvent(EventFileTh *event) override;
  DrIrrVolResObj *loadSector(u32 index);
  void update();
  void drawDebugInfo(DebDraw *debDraw);
  void releaseSector(DrIrrVolResObj *resObj);
  void destroy();
  void setupHeader(EventFileTh *event);

  FileHandleTh *unknown08;                   // Inferred role: header file handle; original member name unknown.
  void *unknown10;                           // Inferred role: header file buffer; original member name unknown.
  unknown001 *unknown18;                     // Inferred role: header; original member name unknown.
  mtl::ALLOC_HANDLE unknown20;               // Inferred role: memory handle; original member name unknown.
  MemHandlebaseAllocator unknown28;          // Inferred role: list node allocator; original member name unknown.
  mm::mtl::List<DrIrrVolResObj *> unknown38; // Inferred role: used sectors; original member name unknown.
  mm::mtl::List<DrIrrVolResObj *> unknown78; // Inferred role: released sectors kept as a cache; original member name unknown.
  u32 unknownb8;                             // Inferred role: cascade index; original member name unknown.
  u32 unknownbc;                             // Inferred role: sector count; original member name unknown.
  mm::mtl::FixStr<128> unknownc0;            // Inferred role: file name base; original member name unknown.
};

static_assert(offsetof(DrIrrVolResMan, unknown08) == 0x08, "");
static_assert(offsetof(DrIrrVolResMan, unknown18) == 0x18, "");
static_assert(offsetof(DrIrrVolResMan, unknown20) == 0x20, "");
static_assert(offsetof(DrIrrVolResMan, unknown28) == 0x28, "");
static_assert(offsetof(DrIrrVolResMan, unknown38) == 0x38, "");
static_assert(offsetof(DrIrrVolResMan, unknown78) == 0x78, "");
static_assert(offsetof(DrIrrVolResMan, unknownb8) == 0xb8, "");
static_assert(offsetof(DrIrrVolResMan, unknownbc) == 0xbc, "");
static_assert(offsetof(DrIrrVolResMan, unknownc0) == 0xc0, "");

} // namespace irrvol
} // namespace ml
