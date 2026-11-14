#include "ml/err_viewer.h"

#include "ml/critical_section.h"
#include "ml/dev_clock.h"
#include "ml/dev_graph.h"
#include "ml/ml_mem.h"
#include "ml/work_control.h"
#include "ml/work_cpu.h"
#include "ml/work_root.h"
#include "ml/work_util.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace ml {

s32 ErrViewer::s_nHandle;

const char *SYS_TAG_ERR() { return "SYS:ERR"; }

ErrViewer::ErrViewer() {
  unknown258 = 0;
  unknown270 = 0;
  unknown278 = nullptr;
  unknown260 = 0;
  unknown268 = false;
  unknown269 = false;
  unknown26a = false;
  unknown26b = false;
  unknown26c = false;
  unknown10 = new (WorkUtil::getWorkMem()) CriticalSection();
  s_nHandle = 0;
  WorkCpu::addBackgroundListener(this);
}

ErrViewer::~ErrViewer() {
  if (unknown26b) {
    WorkControl::pause(false, SYS_TAG_ERR());
  }
  WorkCpu::removeBackgroundListener(this);
  if (unknown10 != nullptr) {
    delete unknown10;
    unknown10 = nullptr;
  }
}

bool ErrViewer::isValid(CERR_STRUCT *error) {
  ErrViewer *viewer = get();
  if (viewer == nullptr) {
    return false;
  }
  CS lock(*viewer->unknown10);
  for (mm::mtl::FixedList<ERRINFO *, 32>::iterator it = viewer->unknown18.begin(); it != viewer->unknown18.end(); ++it) {
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
    for (mm::mtl::FixedList<ERRINFO *, 32>::iterator it = viewer->unknown18.begin(); it != viewer->unknown18.end(); ++it) {
      if ((*it)->unknown10 == error) {
        (*it)->unknown08 = nullptr;
        break;
      }
    }
  }
}

void ErrViewer::standby() {
  ErrViewer *viewer = get();
  if (viewer == nullptr) {
    return;
  }
  if (viewer->unknown258 == 0) {
    viewer->setup();
    viewer->unknown268 = true;
    DevGraph::addOuterRender(fnRender);
    viewer->unknown258++;
  } else if (viewer->unknown258 == 2) {
    DevGraph::removeOuterRender(fnRender);
    viewer->unknown268 = false;
    viewer->term();
    viewer->unknown26a = true;
    viewer->unknown258++;
    viewer->callbackError(static_cast<ERR_CALL>(0));
    return;
  } else if (viewer->unknown258 != 1) {
    viewer->callbackError(static_cast<ERR_CALL>(0));
    return;
  }
  viewer->upErrViewer();
  if (viewer->unknown269) {
    CS lock(*viewer->unknown10);
    for (mm::mtl::FixedList<ERRINFO *, 32>::iterator it = viewer->unknown18.begin(); it != viewer->unknown18.end(); ++it) {
      if ((*it)->unknown18 != nullptr) {
        mtl::MemManager::deallocate((*it)->unknown18, 0, false);
        (*it)->unknown18 = nullptr;
      }
      if (*it != nullptr) {
        delete *it;
        *it = nullptr;
      }
    }
    viewer->unknown18.clear();
    viewer->unknown258++;
  }
  viewer->callbackError(static_cast<ERR_CALL>(0));
}

bool ErrViewer::isExistError() const {
  if (WorkRoot::isRestart()) {
    return false;
  }
  CS lock(*unknown10);
  return unknown18.begin() != unknown18.end();
}

ErrViewer::ERRINFO *ErrViewer::getError() const {
  CS lock(*unknown10);
  if (!isExistError()) {
    return nullptr;
  }
  return *unknown18.begin();
}

void ErrViewer::deleteError() {
  if (!isExistError()) {
    return;
  }
  CS lock(*unknown10);
  mm::mtl::FixedList<ERRINFO *, 32>::iterator it = unknown18.begin();
  if (it != unknown18.end()) {
    if ((*it)->unknown18 != nullptr) {
      mtl::MemManager::deallocate((*it)->unknown18, 0, false);
      (*it)->unknown18 = nullptr;
    }
    if (*it != nullptr) {
      delete *it;
      *it = nullptr;
    }
    unknown18.erase(it);
  }
}

void ErrViewer::callbackError(ERR_CALL call) {
  if (!isExistError()) {
    return;
  }
  CS lock(*unknown10);
  ERRINFO *info = *unknown18.begin();
  if (info->unknown04 == call && info->unknown08 != nullptr && !info->unknown08->unknown001(info->unknown10) && info->unknownb0 > 0) {
    info->unknownac = info->unknownb0;
  }
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

ErrViewer *ErrViewer::create() {
  ErrViewer *viewer = get();
  if (viewer == nullptr) {
    viewer = new (MlMem::getProductMem()) ErrViewer();
  }
  return viewer;
}

void ErrViewer::tail() {
  ErrViewer *viewer = get();
  if (viewer != nullptr) {
    viewer->callbackError(static_cast<ERR_CALL>(2));
    if (viewer->unknown26c) {
      f32 elapsed;
      DevClock::getTimeNow(elapsed, viewer->unknown260);
      if (3.0f <= elapsed) {
        viewer->unknown26c = false;
      }
    }
  }
}

bool ErrViewer::destroy() {
  ErrViewer *viewer = get();
  if (viewer == nullptr) {
    return true;
  }
  if (!viewer->unknown269) {
    viewer->unknown269 = true;
  }
  if (viewer->unknown26a) {
    delete viewer;
    return true;
  }
  return false;
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

void ErrViewer::bkgHomeMenu(bool isEnter) {}

void ErrViewer::bkgHomeMenuDenied() {
  if (!WorkCpu::isHomeMenuEnable()) {
    DevClock::getClockNow(unknown260);
    unknown26c = true;
  }
}

void ErrViewer::fnRender() {
  ErrViewer *viewer = get();
  if (viewer != nullptr && ((viewer->unknown268 && !viewer->unknown269) || viewer->unknown26c)) {
    viewer->callbackError(static_cast<ERR_CALL>(3));
  }
}

} // namespace ml

template mm::mtl::PtrSingleton<ml::ErrViewer>::~PtrSingleton();
template mm::mtl::FixedList<ml::ErrViewer::ERRINFO *, 32>::iterator mm::mtl::FixedList<ml::ErrViewer::ERRINFO *, 32>::erase(mm::mtl::FixedList<ml::ErrViewer::ERRINFO *, 32>::iterator it);
