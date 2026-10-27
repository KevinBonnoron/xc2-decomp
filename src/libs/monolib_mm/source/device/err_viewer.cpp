#include "ml/err_viewer.h"

#include "ml/critical_section.h"
#include "ml/work_root.h"
#include "mtl/mem_manager.h"

namespace ml {

s32 ErrViewer::s_nHandle;

bool ErrViewer::isValid(CERR_STRUCT *error) {
  ErrViewer *viewer = get();
  if (viewer == nullptr) {
    return false;
  }
  CS lock(*viewer->unknown10);
  for (mm::mtl::FixedList<unknown001 *, 32>::iterator it = viewer->unknown18.begin(); it != viewer->unknown18.end(); ++it) {
    if ((*it)->unknown10 == error) {
      return true;
    }
  }
  return false;
}

void ErrViewer::reqCancel(CERR_STRUCT *error) {
  ErrViewer *viewer = get();
  if (viewer != nullptr) {
    CS lock(*viewer->unknown10);
    for (mm::mtl::FixedList<unknown001 *, 32>::iterator it = viewer->unknown18.begin(); it != viewer->unknown18.end(); ++it) {
      if ((*it)->unknown10 == error) {
        (*it)->unknown08 = nullptr;
        break;
      }
    }
  }
}

bool ErrViewer::isExistError() const {
  if (WorkRoot::isRestart()) {
    return false;
  }
  CS lock(*unknown10);
  return unknown18.begin() != unknown18.end();
}

bool ErrViewer::isInitialized() {
  ErrViewer *viewer = get();
  if (viewer != nullptr) {
    return viewer->unknown258 == 1;
  }
  return false;
}

bool ErrViewer::isErrorDisp() {
  ErrViewer *viewer = get();
  if (viewer != nullptr) {
    return viewer->unknown26b;
  }
  return false;
}

void ErrViewer::update() {
  ErrViewer *viewer = get();
  if (viewer != nullptr) {
    viewer->callbackError(static_cast<ERR_CALL>(1));
  }
}

s32 ErrViewer::createHandle() const { return s_nHandle++; }

void ErrViewer::setup() {}

void ErrViewer::upErrViewer() {}

void ErrViewer::renderDRC() {}

void ErrViewer::term() {
  if (unknown278 != nullptr) {
    mtl::MemManager::deallocate(unknown278, 0, false);
    unknown278 = nullptr;
  }
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::ErrViewer>::~PtrSingleton();
