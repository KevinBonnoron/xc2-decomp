#include "ml/scn.h"

#include "ml/cache_draw.h"
#include "ml/critical_section.h"
#include "ml/dev_graph.h"
#include "ml/file_res_th.h"
#include "ml/path_util.h"
#include "ml/proc_desktop.h"
#include "ml/reslist.h"
#include "ml/scn_obj_model.h"
#include "ml/scn_pool_obj.h"
#include "ml/win_view.h"
#include "ml/win_view_root.h"
#include "ml/work_cpu.h"
#include "ml/work_root.h"
#include "ml/work_util.h"
#include "mm_mtl/algorithm.h"
#include "mtl/mem_manager.h"
#include "scn/scn_debug.h"
#include "scn/scn_render_dr_sys.h"

#include <string.h>

// Scn::move inlines ScnPoolObj::update in the game: keep its definition visible in this unit.
#include "scn_pool_obj.cpp"

namespace ml {

Scn *Scn::create(const ScnSetup *setup) {
  ScnSetup defaultSetup;
  if (setup == nullptr) {
    setup = &defaultSetup;
  }
  Scn *scn = new (WorkUtil::getWorkMem()) Scn(setup);
  if (scn != nullptr) {
    scn->addRef();
  }
  return scn;
}

void Scn::setPause(bool isPause) {
  if (unknowndf8 != isPause) {
    unknowndf8 = isPause;
  }
}

void Scn::term() {
  if (unknownb4 != -1) {
    WorkCpu::removeAutoExecGrp(unknownb4);
    WorkCpu::releaseGroupHandle(unknownb4);
    unknownb4 = -1;
  }
  if (unknown20 != nullptr) {
    delete unknown20;
    unknown20 = nullptr;
  }
  WorkCpu::runThread(WorkCpu::getRenderCPUID(), thRenderKillTerminate, this, nullptr, nullptr, true, WKCPU_SYNC_UNKNOWN_0);
  if (unknown28 != nullptr) {
    delete unknown28;
    unknown28 = nullptr;
  }
  if (unknown30 != nullptr) {
    delete unknown30;
    unknown30 = nullptr;
  }
  for (FileResTh **it = unknowncf0.begin(); it != unknowncf0.end(); it++) {
    if (*it != nullptr) {
      (*it)->Release();
      *it = nullptr;
    }
  }
  unknowncf0.clear();
  if (unknownce0 != nullptr) {
    delete unknownce0;
    unknownce0 = nullptr;
  }
  if (unknownce8 != nullptr) {
    delete unknownce8;
    unknownce8 = nullptr;
  }
  if (unknown64.isValid()) {
    mtl::MemManager::erase(unknown64);
    unknown64 = mtl::ALLOC_HANDLE();
  }
}

void Scn::callbackToListener(SCNCB type) {
  for (int i = 0; i < unknown4b8; i++) {
    if (unknownb8[i].unknown0e) {
      continue;
    }
    switch (type) {
    case SCNCB_UNKNOWN_0:
      unknownb8[i].unknown00->cbPreUpdate(this, unknownb8[i].unknown08);
      break;
    case SCNCB_UNKNOWN_1:
      DevGraph::cmdOpenDisplayList(0);
      if (!unknownb8[i].unknown0d) {
        unknownb8[i].unknown00->cbRenderAfter(this, unknownb8[i].unknown08);
      }
      if (unknowne00[0].unknown00 == unknownb8[i].unknown08) {
        DebDraw::flushPrio(-2, getCam(-1)->unknown70.m_front->unknown1a0, getCam(-1)->unknown70.m_front->unknown00.unknown70);
      }
      DevGraph::cmdCloseDisplayList();
      break;
    case SCNCB_UNKNOWN_2:
      unknownb8[i].unknown00->cbManipuPickOn(this, unknownb8[i].unknown08);
      break;
    case SCNCB_UNKNOWN_3:
      unknownb8[i].unknown00->cbManipuPickOff(this, unknownb8[i].unknown08);
      break;
    case SCNCB_UNKNOWN_4:
      unknownb8[i].unknown00->cbManipuPickMove(this, unknownb8[i].unknown08);
      break;
    }
  }
}

void Scn::move() {
  callbackToListener(SCNCB_UNKNOWN_0);
  unknown28->update();
  unknown20->update();
  if (!unknownb0) {
    unknownb0 = true;
    if (unknown38 != nullptr) {
      unknown38->update();
    }
  }
}

void Scn::draw() {
  if (unknowndf9) {
    return;
  }
  bool isCurrent;
  DevGraph::cmdOpenDisplayList(0);
  {
    CS lock(*unknownce0);
    isCurrent = unknown28->setCurrentCam() && unknown28->getView(-1) == WinView::getView(true);
  }
  DevGraph::cmdCloseDisplayList();
  if (!isCurrent) {
    return;
  }
  DevGraph::cmdOpenDisplayList(0);
  {
    CS lock(*unknownce0);
    unknown20->apply();
  }
  DevGraph::cmdCloseDisplayList();
  {
    CS lock(*unknownce0);
    if (unknown38 != nullptr) {
      DebDraw::getOnly(0xffffffff)->setForceRenderQueue(true);
      unknown38->applyBegin();
      int count = unknown38->applyLoopCnt();
      for (int i = 0; i < count; i++) {
        DevGraph::cmdOpenDisplayList(0);
        unknown38->applyUpdate(i);
        DevGraph::cmdCloseDisplayList();
        DevGraph::cmdOpenDisplayList(0);
        unknown38->applyRender(i);
        DevGraph::cmdCloseDisplayList();
      }
      unknown38->applyEnd();
      DebDraw::getOnly(0xffffffff)->setForceRenderQueue(false);
    }
  }
  callbackToListener(SCNCB_UNKNOWN_1);
  DevGraph::cmdOpenDisplayList(0);
  {
    CS lock(*unknownce0);
    DebDraw *debDraw = DebDraw::get(0xffffffff);
    unknown20->renderDebug(debDraw);
    if (unknown30 != nullptr) {
      unknown30->render(debDraw);
    }
  }
  DevGraph::cmdCloseDisplayList();
}

void Scn::init() {
  mtl::ALLOC_HANDLE mem = unknown64;
  unknown30 = new (mem) ScnDebug(this, mem);
  unknown20 = new (mem) ScnPoolObj(this);
  unknown28 = new (mem) ScnCamMan(this);
}

u32 Scn::thUpAfter(void *argument, void *userData) {
  Scn *scn = static_cast<Scn *>(argument);
  for (int i = 0; i < scn->unknown4b8; i++) {
    if (scn->unknownb8[i].unknown0d) {
      DebDraw::setCurrentPrio(scn->unknownb8[i].unknown08);
      scn->unknownb8[i].unknown00->cbRenderAfter(scn, scn->unknownb8[i].unknown08);
      DebDraw::setCurrentPrio(-1);
    }
  }
  return 0;
}

void Scn::setDebDraw(SCNCAM cam, SCNPRIO_CB priority) { unknowne00[cam].unknown00 = priority; }

ScnObjModel *Scn::createMdl(const void *data, const char *name, int screenID) {
  ScnObjModel *model = unknown38->createMdl(this, data, name, screenID);
  if (model != nullptr) {
    model->setAlwaysTexStm(!unknownac);
  }
  return model;
}

ScnObj *Scn::createLgt(const void *data, int screenID) { return unknown38->createLgt(this, data, screenID); }

ScnObj *Scn::createClip(const void *data, int screenID) { return unknown38->createClip(this, data, screenID); }

ScnObj *Scn::createIBL(const void *data, int screenID) { return unknown38->createIBL(this, data, screenID); }

ScnObj *Scn::createEnvColi(const void *data, int screenID) { return unknown38->createEnvColi(this, data, screenID); }

void Scn::releaseItem(ScnObj *obj) {
  if (obj != nullptr) {
    unknown20->release(obj);
  }
}

void Scn::setDeleteRender() {
  if (unknown38 != nullptr) {
    WorkCpu::runThread(WorkCpu::getRenderCPUID(), thRenderKillTerminate, this, nullptr, nullptr, true, WKCPU_SYNC_UNKNOWN_1);
  }
}

u32 Scn::thRenderKillTerminate(void *argument, void *userData) {
  Scn *scn = static_cast<Scn *>(argument);
  if (scn->unknown38 != nullptr) {
    delete scn->unknown38;
    scn->unknown38 = nullptr;
  }
  return 0;
}

void Scn::renderStop() { unknowndf9 = true; }

void Scn::setFrameSpd(f32 speed) { ProcDesktop::setUpdateRatio(speed); }

f32 Scn::getFrameSpd() const { return ProcDesktop::getUpdateRatio(); }

void Scn::enableScnDebug(bool isEnable) {
  if (unknown30 != nullptr) {
    unknown30->_30 = isEnable;
  }
}

void Scn::addRenderCB(IScnRender *render, SCNPRIO_CB priority, bool flag1, bool flag2) { unknown4c0.push(unknown001(render, priority, flag1, flag2)); }

void Scn::addEntryRes(FileResTh *res) {
  CS lock(*unknownce8);
  if (res != nullptr) {
    res->AddRef();
    unknowncf0.push_back(res);
  }
}

FileResTh *Scn::allocEntryRes(const char *path) {
  CS lock(*unknownce8);
  for (FileResTh **it = unknowncf0.begin(); it != unknowncf0.end(); it++) {
    mm::mtl::FixStr<128> name;
    FileResTh *res = *it;
    {
      CS nameLock(res->unknown90);
      name = res->unknown0c;
    }
    if (strcmp(name.c_str(), PathUtil::getFilePtrFromPath(path)) == 0) {
      (*it)->AddRef();
      return *it;
    }
  }
  return nullptr;
}

void Scn::removeEntryRes(FileResTh *res) {
  CS lock(*unknownce8);
  if (res != nullptr) {
    unknowncf0.erase(mm::mtl::find(unknowncf0.begin(), unknowncf0.end(), res));
    res->Release();
  }
}

ScnCamMan::ScnCamMan(Scn *scn) : unknown08(scn), unknown40(0) {
  for (int i = 0; i < 10; i++) {
    unknown10.push_back(0xffffffff);
  }
  for (int i = 0; i < 10; i++) {
    ScnObjCam::create(unknown08, i);
  }
}

ScnCamMan::~ScnCamMan() {
  for (u32 i = 0; i < unknown10.size(); i++) {
    WinView *view = WinViewRoot::getView(*unknown10.at(i));
    if (view != nullptr) {
      view->detachWorkEvent(unknown08);
    }
  }
}

void ScnCamMan::setView(WinView *view, int screen) {
  if (unknown10[screen] != 0xffffffff) {
    if (unknown10[screen] != view->unknown50) {
      WinView *current = WinViewRoot::getView(unknown10[screen]);
      if (current != nullptr) {
        current->detachWorkEvent(unknown08);
      }
    }
  }
  view->attachWorkEvent(unknown08, false);
  unknown10[screen] = view->unknown50;
}

void ScnCamMan::clrView(WinView *view, int screen) {
  if (view != nullptr) {
    if (unknown10[screen] != 0xffffffff) {
      WinView *current = WinViewRoot::getView(unknown10[screen]);
      if (current != nullptr) {
        current->detachWorkEvent(unknown08);
      }
    }
    unknown10[screen] = 0xffffffff;
  }
}

void Scn::setView(WinView *view, int screen) { unknown28->setView(view, screen); }

void Scn::clrView(WinView *view, int screen) { unknown28->clrView(view, screen); }

WinView *ScnCamMan::getView(s16 screen) {
  if (screen < 0) {
    screen = unknown40;
  }
  if (unknown10[screen] == 0xffffffff) {
    return nullptr;
  }
  return static_cast<WinView *>(WorkRootState::getWork(unknown10[screen]));
}

const WinView *ScnCamMan::getView(s16 screen) const {
  if (screen < 0) {
    screen = unknown40;
  }
  if (unknown10[screen] == 0xffffffff) {
    return nullptr;
  }
  return static_cast<WinView *>(WorkRootState::getWork(unknown10[screen]));
}

WinView *Scn::getView(int index) { return unknown28->getView(index); }

const WinView *Scn::getView(int index) const { return unknown28->getView(index); }

void ScnCamMan::setCrossIdTarget(const WinView *view) {}

const ScnObjCam *ScnCamMan::getCam(const WinView *view) const { return unknown08->unknown20->getCam(view); }

ScnObjCam *ScnCamMan::getCam(const WinView *view) { return unknown08->unknown20->getCam(view); }

ScnObjCam *Scn::getCam(const WinView *view) { return unknown28->getCam(view); }

const ScnObjCam *Scn::getCam(const WinView *view) const { return unknown28->getCam(view); }

bool ScnCamMan::setCurrentCam() {
  ScnObjCam *cam = getCam(WinView::getView(true));
  if (cam != nullptr) {
    unknown40 = cam->m_info;
    return true;
  }
  return false;
}

template class reslist<ScnObj *>;

} // namespace ml

// The game builds these files in one unit with this one (0x710073fc4c to 0x7100755bfc), in this order. Scn::draw inlines ScnDebug::render and Scn::init the ScnDebug constructor; ScnCamUtil
// (0x7100742c24 to 0x7100743708) comes before the ScnDebug block (0x71007437a0 to 0x7100751eb0), which follows every function of this file and ends with ScnDebugUtil (0x7100751cc4); ScnObjCam
// (0x7100751eb0), ScnObj (0x7100753ad4) and ScnUtil (0x7100754c4c) come after it.
// clang-format off
#include "scn_cam_util.cpp"
#include "scn_debug.cpp"
#include "scn_debug_util.cpp"
#include "scn_obj_cam.cpp"
#include "scn_obj.cpp"
#include "scn_util.cpp"
// clang-format on

template mm::mtl::PtrSingleton<ml::Scn>::~PtrSingleton();
