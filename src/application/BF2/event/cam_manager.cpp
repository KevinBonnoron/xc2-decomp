#include "event/cam_manager.h"

#include <stddef.h>

#include "event/cam_base.h"
#include "event/cam_interface.h"
#include "event/cam_obj.h"
#include "event/cam_util.h"
#include "event/extend.h"
#include "event/frame_manager.h"
#include "event/memory_manager.h"
#include "event/res_manager.h"
#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace fw {
enum CAMERA_TYPE : int;
} // namespace fw

namespace event {

bool CamManager::isOffscrMode() const { return (unknown10 & FLAG_OFFSCR_MODE) != 0; }

u32 CamManager::getOffscrID() const { return m_offscrID; }

bool CamManager::isFreeCam() const { return (unknown14 & DISP_FLAG_FREE_CAM) != 0; }

CamManager::CamManager() : unknown10(0), unknown14(0), unknown88(nullptr), m_freeCam(false), m_offscrID(0) {}

void CamManager::destroyCam(CamObj *cam) {
  for (CamObj **it = unknown18.begin(); it != unknown18.end(); ++it) {
    if (*it == cam) {
      if (cam->getScreenID() == 0) {
        unknown88 = nullptr;
      }
      delete cam;
      unknown18.erase(it);
      return;
    }
  }
}

void CamManager::clear() {
  while (!unknown18.empty()) {
    destroyCam(unknown18[0]);
  }
  for (size_t i = 0; i < INTERFACE_COUNT; i++) {
    if (unknown60[i]) {
      delete unknown60[i];
      unknown60[i] = nullptr;
    }
  }
  unknown60.clear();
  m_freeCam.setActive(false);
  unknown10 = 0;
  unknown14 &= ~DISP_FLAG_FREE_CAM;
  unknown88 = nullptr;
  m_offscrID = 0;
}

void CamManager::init() {
  unknown10 = 0;
  for (size_t i = 0; i < INTERFACE_COUNT; i++) {
    CamInterface *cam = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CamInterface(static_cast<fw::CAMERA_TYPE>(i));
    cam->addRef();
    unknown60.push_back(cam);
  }
}

void CamManager::update() {
  if ((unknown14 & DISP_FLAG_FREE_CAM) != 0) {
    mm::mtl::Singleton<FrameManager>::getPtr()->frameInfo();
    mm::Vec3 pos = m_freeCam.getPos();
    mm::Vec3 target = m_freeCam.getTarget();
    f32 fov = m_freeCam.getFov();
    f32 roll = m_freeCam.getRoll();
    if (m_freeCam.isFocal()) {
      fov = CamUtil::toFov(fov);
    }
    CamInterface *cam = mm::mtl::Singleton<CamManager>::getPtr()->unknown001(0);
    cam->setTargetPos(pos, target, roll);
    cam->setFov(__builtin_fmaxf(fov, 5.0f));
  }
}

void CamManager::render() {
  if (!unknown18.empty() && (unknown14 & (DISP_FLAG_DISP | DISP_FLAG_FREE_CAM)) != 0) {
    CamBase *cam = (unknown14 & DISP_FLAG_FREE_CAM) != 0 ? static_cast<CamBase *>(&m_freeCam) : unknown88;
    if (cam != nullptr) {
      mm::Vec3 pos = cam->getPos();
      mm::Vec3 target = cam->getTarget();
      mm::Vec3 rot = cam->getRot();
      f32 fov = cam->getFov();
      bool isFocal = cam->isFocal();
      int width = ml::DevGraph::getRootWidth();
      int x = width - 415;
      int y = 30;
      fw::debug::drawSquare2D(mm::Rect<int>(x, y, 225, 85), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
      fw::debug::drawLineSquare2D(mm::Rect<int>(x, y, 225, 85), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
      fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
      fw::debug::drawFont(x + 5, y + 5, "CAM");
      int labelX = x + 10;
      fw::debug::drawFont(labelX, y + 20, "pos:");
      int valueX = x + 50;
      fw::debug::drawFont(valueX, y + 20, "%.2f %.2f %.2f", pos.x, pos.y, pos.z);
      fw::debug::drawFont(labelX, y + 35, "tar:");
      fw::debug::drawFont(valueX, y + 35, "%.2f %.2f %.2f", target.x, target.y, target.z);
      fw::debug::drawFont(labelX, y + 50, "rot:");
      fw::debug::drawFont(valueX, y + 50, "%.2f %.2f %.2f", rot.x * mm::RAD_TO_DEG, rot.y * mm::RAD_TO_DEG, rot.z * mm::RAD_TO_DEG);
      if (isFocal) {
        fw::debug::drawFont(labelX, y + 65, "foc:");
        fw::debug::drawFont(valueX, y + 65, "%.2f", fov);
        fw::debug::drawFont(x + 110, y + 65, "fov:");
        fw::debug::drawFont(x + 150, y + 65, "%.2f", CamUtil::toFov(fov));
      } else {
        fw::debug::drawFont(labelX, y + 65, "fov:");
        fw::debug::drawFont(valueX, y + 65, "%.2f", fov);
        fw::debug::drawFont(x + 110, y + 65, "foc:");
        fw::debug::drawFont(x + 150, y + 65, "%.2f", CamUtil::toFocal(fov));
      }
    }
  }
  if ((unknown14 & DISP_FLAG_FREE_CAM) != 0) {
    int width = ml::DevGraph::getRootWidth();
    int x = width - 520;
    int y = 30;
    fw::debug::drawSquare2D(mm::Rect<int>(x, y, 100, 25), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
    fw::debug::drawLineSquare2D(mm::Rect<int>(x, y, 100, 25), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFont(x + 5, y + 5, "FREE CAMERA");
  }
}

void CamManager::setStreamMode(bool isStreamMode) { setFlag(FLAG_STREAM_MODE, isStreamMode); }

void CamManager::loadResource(const char *name) {
  if ((unknown10 & FLAG_STREAM_MODE) != 0) {
    return;
  }
  mm::mtl::Singleton<ResManager>::getPtr()->load(mm::mtl::Singleton<Extend>::getPtr()->eva(name), nullptr, false);
}

void CamManager::setOffscrMode(bool isOffscrMode, u32 offscrID) {
  if (isOffscrMode) {
    unknown10 |= FLAG_OFFSCR_MODE;
    m_offscrID = offscrID;
  } else {
    unknown10 &= ~FLAG_OFFSCR_MODE;
    m_offscrID = 0;
  }
}

CamObj *CamManager::createCam(u32 screenID) {
  CamObj *cam = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false) CamObj(screenID, (unknown10 & FLAG_FOCAL) != 0, (unknown10 & FLAG_STREAM_MODE) != 0);
  unknown18.push_back(cam);
  if (screenID == 0) {
    unknown88 = cam;
  }
  return cam;
}

void CamManager::OnEventProc(MSG_TYPE type) {
  switch (type) {
  case MSG_TYPE_INIT:
    init();
    break;
  case MSG_TYPE_CLEAR:
    clear();
    break;
  case MSG_TYPE_UPDATE:
    update();
    break;
  case MSG_TYPE_RENDER:
    render();
    break;
  default:
    break;
  }
}

CamFree *CamManager::getFreeCam() { return &m_freeCam; }

void CamManager::setFreeCam(bool isFreeCam) {
  if (isFreeCam) {
    if ((unknown14 & DISP_FLAG_FREE_CAM) != 0 || unknown88 == nullptr) {
      return;
    }
    m_freeCam.setActive(true);
    m_freeCam.unknown002(*unknown88);
    unknown14 |= DISP_FLAG_FREE_CAM;
  } else {
    m_freeCam.setActive(false);
    unknown14 &= ~DISP_FLAG_FREE_CAM;
  }
}

void CamManager::setDisp(bool isDisp) { setDispFlag(DISP_FLAG_DISP, isDisp); }

bool CamManager::isDisp() const { return (unknown14 & DISP_FLAG_DISP) != 0; }

void CamManager::setFocal(bool isFocal) { setFlag(FLAG_FOCAL, isFocal); }

bool CamManager::isFocal() const { return (unknown10 & FLAG_FOCAL) != 0; }

} // namespace event
