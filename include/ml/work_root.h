#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace mtl {
class ALLOC_HANDLE;
} // namespace mtl

namespace ml {

class WorkObj;

struct WorkRootParam {
  WorkRootParam &operator=(const WorkRootParam &other);

  bool unknown00;   // Inferred role: product mem; original member name unknown.
  void *unknown08;  // Inferred role: product mem; original member name unknown.
  size_t unknown10; // Inferred role: product mem size; original member name unknown.
  void *unknown18;  // Inferred role: debug mem; original member name unknown.
  size_t unknown20; // Inferred role: debug mem size; original member name unknown.
  void *unknown28;  // Inferred role: graphic mem; original member name unknown.
  size_t unknown30; // Inferred role: graphic mem size; original member name unknown.
  s32 unknown38;    // Inferred role: fg mem size; original member name unknown.
};

static_assert(offsetof(WorkRootParam, unknown08) == 0x8, "");
static_assert(offsetof(WorkRootParam, unknown38) == 0x38, "");

class WorkRoot {
public:
  static bool isErrorStop();
  static bool isErrorLog();
  static bool initialize(const WorkRootParam *param);
  static void destroy();
  static bool run(const WorkRootParam *param);
  static f32 getDefaultMemRatio();
  static void setThreadRender(bool isThreadRender);
  static void setKillWin32Log(bool isKill);
  static int getWidth();
  static int getHeight();
  static bool isWinDestroy();
  static void reqShutdown();
  static bool isProductMem();
  static mtl::ALLOC_HANDLE getMemFG();
  static mtl::ALLOC_HANDLE getMemTMP();
  static void setErrorStop();
  static void setErrorLog();
  static void setErrorReset();
  static bool isErrorReset();
  static void setInfiniteLoop(bool isInfiniteLoop);
  static bool isInfiniteLoop();
  static void setErrorRestart(bool isErrorRestart);
  static bool isErrorRestart();
  static void setErrorLogSD(bool isErrorLogSD);
  static bool isErrorLogSD();
  static void setBlueScreen(bool isBlueScreen);
  static bool isBlueScreen();
  static void addArgParam(const char *param);
  static const mm::mtl::FixedVector<mm::mtl::FixStr<128>, 16> *getArgParam();
  static void setRestart();
  static bool isRestart();
  static WorkRootParam *getParam();
};

class WorkRootMem {
public:
  static bool initialize(const WorkRootParam *param);
  static void finalize();
  static mtl::ALLOC_HANDLE getMemFG();
  static mtl::ALLOC_HANDLE getMemTMP();
  static mtl::ALLOC_HANDLE getMemState();
  static mtl::ALLOC_HANDLE getMemStateDebug();
};

class WorkRootState {
public:
  static void initialize();
  static void entryWork();
  static void standbyWork();
  static void finalize();
  static WorkObj *getWork(u32 wid);
  static bool isDebug(WorkObj *work);
  static u32 allocWID(WorkObj *work);
  static void freeWID(u32 wid);
  static bool isUsedWID(u32 wid);
  static mtl::ALLOC_HANDLE getWorkMem();
  static void setThreadRender(bool isThreadRender);
  static bool isThreadRender();
  static void shutdownAll();
  static bool isShutdownAll();
  static void entryWork(WorkObj *work, WorkObj *parent, bool isFront);
  static void addFrameEnd(WorkObj *work);
  static void removeFrameEnd(WorkObj *work);
  static void standbyWork(WorkObj *work);
  static void updateWork(WorkObj *work);
  static void tailWork(WorkObj *work);
  static void updateWork();
  static void tailWork();
  static bool runSingle();
};

} // namespace ml
