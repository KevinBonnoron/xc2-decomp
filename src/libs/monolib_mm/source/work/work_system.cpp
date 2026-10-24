#include "ml/work_system.h"

#include "ml/dev_file_th.h"
#include "ml/dev_font.h"
#include "ml/dev_graph.h"
#include "ml/ml_mem.h"
#include "ml/reslist.h"
#include "ml/win_proc_root.h"
#include "ml/win_view_root.h"
#include "ml/work_control.h"
#include "ml/work_root.h"
#include "mm_mtl/fixstr.h"
#include "mtl/mem_manager.h"

namespace ml {

namespace {

void (*s_exitFunc)();

} // namespace

WorkSystem::WorkSystem(const char *name, WorkObj *parent) : WorkObj(name, parent, 32), unknown1b4(false), unknown1b5(false), unknown1b6(false) {}

WorkSystem::~WorkSystem() {}

bool WorkSystem::isOff() {
  WorkSystem *system = get();
  if (system != nullptr) {
    return system->unknown1b4 || system->unknown1b5;
  }

  return false;
}

bool WorkSystem::isPowerOff() {
  WorkSystem *system = get();
  if (system != nullptr) {
    return system->unknown1b4;
  }

  return false;
}

bool WorkSystem::isReset() {
  WorkSystem *system = get();
  if (system != nullptr) {
    return system->unknown1b5;
  }

  return false;
}

mtl::ALLOC_HANDLE WorkSystem::getMem() { return get()->unknown1b0; }

void WorkSystem::setSaveLoadInvalidReset(bool isInvalid) {
  WorkSystem *system = get();
  if (system != nullptr) {
    system->unknown1b6 = isInvalid;
  }
}

void WorkSystem::wkUpdate() {}

bool WorkSystem::wkStandbyLogin() {
  if (!DevFileTh::isInitialized()) {
    return false;
  }

  if (!DevGraph::isIgnore()) {
    DevFont *font = DevFont::get();
    if (font == nullptr || font->wkIsWaitException() || !font->wkIsActive()) {
      return false;
    }
  }

  unknown1b0 = mtl::MemManager::create(MlMem::getProductMem(), 0xfe0, unknown08.c_str(), false);
  WinProcRoot::create(this);
  WinViewRoot::create(this);
  return WorkObj::wkStandbyLogin();
}

bool WorkSystem::wkStandbyLogout() {
  if (unknown60.size() != 0) {
    return false;
  }

  if (unknown1b0.isValid()) {
    mtl::MemManager::erase(unknown1b0);
    unknown1b0 = mtl::ALLOC_HANDLE();
  }

  return WorkObj::wkStandbyLogout();
}

WorkSystem *WorkSystem::create() {
  WorkControl *control = WorkControl::get();
  WorkSystem *system = new (WorkRootState::getWorkMem()) WorkSystem("WorkSystem", control);
  WorkRootState::entryWork(system, control, false);
  return system;
}

void WorkSystem::setExitFunc(void (*func)()) { s_exitFunc = func; }

void WorkSystem::callExitFunc() {
  if (s_exitFunc != nullptr) {
    s_exitFunc();
  }
}

} // namespace ml
