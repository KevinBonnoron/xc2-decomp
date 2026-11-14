#pragma once
#include <stddef.h>

#include "dr/dr_res_chank_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class CriticalSection;
class DrCalcStmListObj;

// Inferred layout from DrCalcTexStreamMan list walks; the original member names are unknown.
class DrCalcTexStmObj {
public:
  DrCalcTexStmObj();
  virtual ~DrCalcTexStmObj() {}

  DrCalcTexStmObj *unknown08; // Inferred role: previous object; original member name unknown.
  DrCalcTexStmObj *unknown10; // Inferred role: next object; original member name unknown.
  u8 *unknown18;              // Inferred role: address; original member name unknown.
  u32 unknown20;              // Inferred role: size; original member name unknown.
  u32 unknown24;              // Inferred role: flags, bit 0 is in use; original member name unknown.
  u32 unknown28;              // Inferred role: unused; original member name unknown.
};

static_assert(offsetof(DrCalcTexStmObj, unknown08) == 0x08, "");
static_assert(offsetof(DrCalcTexStmObj, unknown10) == 0x10, "");
static_assert(offsetof(DrCalcTexStmObj, unknown18) == 0x18, "");
static_assert(offsetof(DrCalcTexStmObj, unknown20) == 0x20, "");
static_assert(offsetof(DrCalcTexStmObj, unknown24) == 0x24, "");
static_assert(offsetof(DrCalcTexStmObj, unknown28) == 0x28, "");
static_assert(sizeof(DrCalcTexStmObj) == 0x30, "");

class DrCalcTexStreamMan : public mm::mtl::PtrSingleton<DrCalcTexStreamMan> {
public:
  static CriticalSection &getCriticalSection();
  DrCalcTexStreamMan();
  int getUseMax() const;
  int getFreeMax() const;
  int getAllFreeSize() const;
  int getAllUseSize() const;
  DrCalcTexStmObj *getTopAheadFreeObj();

  DrCalcStmListObj *createTexStmListObj(const char *path);
  DrCalcStmListObj *createTexStmListObj(const char *path, const u8 *header);
  DrCalcStmListObj *checkTexStmListObj(const char *path, u32 length);
  DrCalcStmListObj *createBufferListObj(u32 size);
  void release();
  void setupMem(int count, u32 size, u32 limit);
  void entryJob();
  ~DrCalcTexStreamMan() override;
  void update();
  void stateUpdate();
  void calcUpdateList();
  bool calcMemOptimization();
  void afterUpdate();
  static u32 jobUpdate(void *argument, void *userData);
  void clearMemObj(DrCalcTexStmObj *object);
  DrCalcTexStmObj *copyMemObj(DrCalcTexStmObj *object);
  DrCalcTexStmObj *copyTempBuff(DrCalcTexStmObj *object);
  DrCalcTexStmObj *createReadFreeObj(u32 size);
  void changeListAndCopyMemObj(DrCalcTexStmObj *first, DrCalcTexStmObj *second);
  void changeListAndMoveMemObj(DrCalcTexStmObj *object);
  void releaseFreeObj(DrCalcTexStmObj *&object);
  void jobWait();
  void callHlvTexOptimization();
  void callOptimization(u32 value);
  void callReadStopMode();
  void calcPieceMem(int &pieceCount, u32 &freeSize, u32 &objectCount);
  void cntMemUpdate();
  bool memSeachOptimization(u32 size);
  bool memTempCopy(u32 size);
  DrCalcTexStmObj *createAheadFreeObj(u32 size);
  DrCalcTexStmObj *createBackwardFreeObj(u32 size);
  bool createSizeFreeObj(DrCalcTexStmObj *object, u32 size);
  DrCalcTexStmObj *createSizeModeFreeObj(u32 size);
  DrCalcTexStmObj *createChildObj(DrCalcTexStmObj *parent, u32 size);

  // Name from the game symbol of DrCalcTexStreamMan::callReadType.
  enum DrTxtmType {};

  bool callReadType(DrTxtmType type);
  void apiUpdate();

  enum Flag {
    FLAG_UNKNOWN_4 = 1 << 4, // Inferred role: cacher clear mode; original name unknown.
  };

  DrResChankList<DrCalcTexStmObj> unknown08;     // Inferred role: object list; original member name unknown.
  DrResChankList<DrCalcTexStmObj> unknown18;     // Inferred role: free object list; original member name unknown.
  DrResChankList<DrCalcStmListObj> unknown28;    // Inferred role: update list; original member name unknown.
  DrResChankList<DrCalcStmListObj> unknown38[2]; // Inferred role: entry list per buffer; original member name unknown.
  DrCalcStmListObj *unknown58[2][512];           // Inferred role: objects to update on the api side per buffer; original member name unknown.
  u32 unknown2058[2];                            // Inferred role: number of used entries of unknown58 per buffer; original member name unknown.
  u8 _2060[0x2068 - 0x2060];
  u32 unknown2068;                  // Inferred role: flags; original member name unknown.
  u32 unknown206c;                  // Inferred role: object count; original member name unknown.
  DrCalcTexStmObj *unknown2070;     // Inferred role: object array; original member name unknown.
  void *unknown2078;                // Inferred role: memory; original member name unknown.
  DrCalcTexStmObj *unknown2080[64]; // Inferred role: objects to clear; original member name unknown.
  DrCalcTexStmObj *unknown2280[64]; // Inferred role: objects to optimize; original member name unknown.
  s32 unknown2480;                  // Inferred role: clear wait count; original member name unknown.
  s32 unknown2484;                  // Inferred role: listed object count; original member name unknown.
  u32 unknown2488;                  // Inferred role: optimization count; original member name unknown.
  s16 unknown248c;                  // Inferred role: read mode; original member name unknown.
  u16 unknown248e;                  // Inferred role: read mode flags; original member name unknown.
  s32 unknown2490;                  // Inferred role: read mode limit; original member name unknown.
  s32 unknown2494;                  // Inferred role: read mode limit of the previous update; original member name unknown.
  u32 unknown2498;                  // Inferred role: job cpu; original member name unknown.
};

static_assert(offsetof(DrCalcTexStreamMan, unknown08) == 0x08, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown18) == 0x18, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown28) == 0x28, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown38) == 0x38, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown58) == 0x58, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown2058) == 0x2058, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown2068) == 0x2068, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown206c) == 0x206c, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown2070) == 0x2070, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown2078) == 0x2078, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown2080) == 0x2080, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown2280) == 0x2280, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown2480) == 0x2480, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown2484) == 0x2484, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown2488) == 0x2488, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown248c) == 0x248c, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown248e) == 0x248e, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown2490) == 0x2490, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown2494) == 0x2494, "");
static_assert(offsetof(DrCalcTexStreamMan, unknown2498) == 0x2498, "");

} // namespace ml
