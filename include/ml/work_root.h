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

  bool isProductMem;
  void *productMem;
  size_t productMemSize;
  void *debugMem;
  size_t debugMemSize;
  void *graphicMem;
  size_t graphicMemSize;
  s32 fgMemSize;
};

static_assert(offsetof(WorkRootParam, productMem) == 0x8, "");
static_assert(offsetof(WorkRootParam, fgMemSize) == 0x38, "");

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
};

class WorkRootState {
public:
  static void initialize();
  static void finalize();
  static void setThreadRender(bool isThreadRender);
  static void addFrameEnd(WorkObj *work);
  static void removeFrameEnd(WorkObj *work);
  static bool runSingle();
};

} // namespace ml
