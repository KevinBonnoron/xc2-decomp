#include "ml/work_root.h"

#include "ml/dev_graph.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mtl/alloc_handle.h"

namespace ml {

namespace _wroot {

bool s_bKillWin32Log;
bool s_bErrorStop;
bool s_bErrorLog;
bool s_bErrorReset;
bool s_bInfiniteLoop;
bool s_bErrorRestart;
bool s_bErrorLogSD;
bool s_bBlueScreen;
bool s_bRestart;
WorkRootParam s_inParam;
mm::mtl::FixedVector<mm::mtl::FixStr<128>, 16> s_aArgParam;

} // namespace _wroot

bool WorkRoot::isErrorStop() { return _wroot::s_bErrorStop; }

bool WorkRoot::isErrorLog() { return _wroot::s_bErrorLog; }

bool WorkRoot::initialize(const WorkRootParam *param) {
  _wroot::s_inParam = *param;
  WorkRootMem::initialize(param);
  WorkRootState::initialize();
  return true;
}

WorkRootParam &WorkRootParam::operator=(const WorkRootParam &other) {
  productMem = other.productMem;
  productMemSize = other.productMemSize;
  debugMem = other.debugMem;
  debugMemSize = other.debugMemSize;
  graphicMem = other.graphicMem;
  graphicMemSize = other.graphicMemSize;
  isProductMem = other.isProductMem;
  fgMemSize = other.fgMemSize;
  return *this;
}

void WorkRoot::destroy() {
  WorkRootState::finalize();
  WorkRootMem::finalize();
}

bool WorkRoot::run(const WorkRootParam *param) {
  DevGraph::setVSync(2);
  _wroot::s_inParam = *param;
  WorkRootMem::initialize(param);
  WorkRootState::initialize();
  while (WorkRootState::runSingle()) {
  }

  WorkRootState::finalize();
  WorkRootMem::finalize();
  return true;
}

f32 WorkRoot::getDefaultMemRatio() { return 0.0f; }

void WorkRoot::setThreadRender(bool isThreadRender) { WorkRootState::setThreadRender(isThreadRender); }

void WorkRoot::setKillWin32Log(bool isKill) { _wroot::s_bKillWin32Log = isKill; }

int WorkRoot::getWidth() { return 1280; }

int WorkRoot::getHeight() { return 720; }

bool WorkRoot::isWinDestroy() { return false; }

void WorkRoot::reqShutdown() {}

bool WorkRoot::isProductMem() { return _wroot::s_inParam.isProductMem; }

mtl::ALLOC_HANDLE WorkRoot::getMemFG() { return WorkRootMem::getMemFG(); }

mtl::ALLOC_HANDLE WorkRoot::getMemTMP() { return WorkRootMem::getMemTMP(); }

void WorkRoot::setErrorStop() { _wroot::s_bErrorStop = true; }

void WorkRoot::setErrorLog() { _wroot::s_bErrorLog = true; }

void WorkRoot::setErrorReset() { _wroot::s_bErrorReset = true; }

bool WorkRoot::isErrorReset() { return _wroot::s_bErrorReset; }

void WorkRoot::setInfiniteLoop(bool isInfiniteLoop) { _wroot::s_bInfiniteLoop = isInfiniteLoop; }

bool WorkRoot::isInfiniteLoop() { return _wroot::s_bInfiniteLoop; }

void WorkRoot::setErrorRestart(bool isErrorRestart) { _wroot::s_bErrorRestart = isErrorRestart; }

bool WorkRoot::isErrorRestart() { return _wroot::s_bErrorRestart; }

void WorkRoot::setErrorLogSD(bool isErrorLogSD) { _wroot::s_bErrorLogSD = isErrorLogSD; }

bool WorkRoot::isErrorLogSD() { return _wroot::s_bErrorLogSD; }

void WorkRoot::setBlueScreen(bool isBlueScreen) { _wroot::s_bBlueScreen = isBlueScreen; }

bool WorkRoot::isBlueScreen() { return _wroot::s_bBlueScreen; }

void WorkRoot::addArgParam(const char *param) { _wroot::s_aArgParam.push_back(mm::mtl::FixStr<128>(param)); }

const mm::mtl::FixedVector<mm::mtl::FixStr<128>, 16> *WorkRoot::getArgParam() { return &_wroot::s_aArgParam; }

void WorkRoot::setRestart() { _wroot::s_bRestart = true; }

bool WorkRoot::isRestart() { return _wroot::s_bRestart; }

WorkRootParam *WorkRoot::getParam() { return &_wroot::s_inParam; }

} // namespace ml
