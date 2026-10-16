#include "event/cam_manager.h"

#include "event/cam_base.h"
#include "event/cam_obj.h"
#include "event/cam_util.h"
#include "event/extend.h"
#include "event/memory_manager.h"
#include "event/res_manager.h"
#include "fw/fw_debug.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"

namespace event {

bool CamManager::isOffscrMode() const { return (flags & FLAG_OFFSCR_MODE) != 0; }

u32 CamManager::getOffscrID() const { return mOffscrID; }

bool CamManager::isFreeCam() const { return (dispFlags & DISP_FLAG_FREE_CAM) != 0; }

constexpr f32 RAD_TO_DEG = 57.29578f;

CamManager::CamManager() : flags(0), dispFlags(0), mMainCam(nullptr), mFreeCam(false), mOffscrID(0) {}

void CamManager::destroyCam(CamObj *cam) {
  for (CamObj **it = mCams.begin(); it != mCams.end(); ++it) {
    if (*it == cam) {
      if (cam->getScreenID() == 0) {
        mMainCam = nullptr;
      }
      delete cam;
      mCams.erase(it);
      return;
    }
  }
}

void CamManager::render() {
  if (!mCams.empty() && (dispFlags & (DISP_FLAG_DISP | DISP_FLAG_FREE_CAM)) != 0) {
    CamBase *cam = (dispFlags & DISP_FLAG_FREE_CAM) != 0 ? static_cast<CamBase *>(&mFreeCam) : mMainCam;
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
      fw::debug::drawFont(valueX, y + 50, "%.2f %.2f %.2f", rot.x * RAD_TO_DEG, rot.y * RAD_TO_DEG, rot.z * RAD_TO_DEG);
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
  if ((dispFlags & DISP_FLAG_FREE_CAM) != 0) {
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
  if ((flags & FLAG_STREAM_MODE) != 0) {
    return;
  }
  mm::mtl::Singleton<ResManager>::getPtr()->load(mm::mtl::Singleton<Extend>::getPtr()->eva(name), nullptr, false);
}

void CamManager::setOffscrMode(bool isOffscrMode, u32 offscrID) {
  if (isOffscrMode) {
    flags |= FLAG_OFFSCR_MODE;
    mOffscrID = offscrID;
  } else {
    flags &= ~FLAG_OFFSCR_MODE;
    mOffscrID = 0;
  }
}

CamObj *CamManager::createCam(u32 screenID) {
  CamObj *cam = new (mm::mtl::Singleton<MemoryManager>::getPtr()->getSysHandle(), nullptr, 0, 4, false)
      CamObj(screenID, (flags & FLAG_FOCAL) != 0, (flags & FLAG_STREAM_MODE) != 0);
  mCams.push_back(cam);
  if (screenID == 0) {
    mMainCam = cam;
  }
  return cam;
}

CamFree *CamManager::getFreeCam() { return &mFreeCam; }

void CamManager::setDisp(bool isDisp) { setDispFlag(DISP_FLAG_DISP, isDisp); }

bool CamManager::isDisp() const { return (dispFlags & DISP_FLAG_DISP) != 0; }

void CamManager::setFocal(bool isFocal) { setFlag(FLAG_FOCAL, isFocal); }

bool CamManager::isFocal() const { return (flags & FLAG_FOCAL) != 0; }

} // namespace event
