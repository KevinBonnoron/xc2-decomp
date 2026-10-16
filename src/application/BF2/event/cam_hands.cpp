#include "event/cam_hands.h"

#include "event/frame_manager.h"
#include "event/object_manager.h"
#include "event/skip_manager.h"
#include "fw/fw_debug.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/singleton.h"

namespace event {

static void makeTranslation(mm::Mat44 &matrix, const mm::Vec3 &position) {
  mm::Vec3 translation = position;
  matrix.rows[0][0] = 1.0f;
  matrix.rows[0][1] = 0.0f;
  matrix.rows[0][2] = 0.0f;
  matrix.rows[0][3] = 0.0f;
  matrix.rows[1][0] = 0.0f;
  matrix.rows[1][1] = 1.0f;
  matrix.rows[1][2] = 0.0f;
  matrix.rows[1][3] = 0.0f;
  matrix.rows[2][0] = 0.0f;
  matrix.rows[2][1] = 0.0f;
  matrix.rows[2][2] = 1.0f;
  matrix.rows[2][3] = 0.0f;
  matrix.rows[3][0] = translation.x;
  matrix.rows[3][1] = translation.y;
  matrix.rows[3][2] = translation.z;
  matrix.rows[3][3] = 1.0f;
}

CamHands::CamHands(bool isFocal) : CamBase(isFocal), flags(0) {}

void CamHands::update(const FrameInfo &info) {
  f32 delta = info.streamDelta;
  if ((flags & FLAG_FOLLOW_POS) != 0) {
    calcFollowPos();
  }
  if (posAnm.isPlay()) {
    posAnm.update(delta);
    mPos = posAnm.getValue();
  }
  if ((flags & (FLAG_FOLLOW_TAR | FLAG_FOLLOW_TAR_ANGLE)) != 0) {
    calcFollowTar();
  }
  if (tarAnm.isPlay()) {
    tarAnm.update(delta);
    mTarget = tarAnm.getValue();
  }
  if (fovAnm.isPlay()) {
    fovAnm.update(delta);
    mFov = fovAnm.getValue();
  }
  if (rotZAnm.isPlay()) {
    rotZAnm.update(delta);
    mRoll = rotZAnm.getValue();
  }
}

void CamHands::calcFollowPos() {
  for (size_t i = 0; i < posAxes.size(); i++) {
    posAnm.insert(i, posAxes[i].calcPos());
  }
}

void CamHands::calcFollowTar() {
  for (size_t i = 0; i < tarAxes.size(); i++) {
    tarAnm.insert(i, tarAxes[i].calcTar(mPos));
  }
}

void CamHands::render(const mm::Col4 &color) {
  static const mm::Vec3 BOX_SIZE(0.05f, 0.05f, 0.05f);
  if (posAnm.isPlay() && posAnm.count() != 0) {
    for (size_t i = 0; i < posAnm.count(); i++) {
      for (f32 alpha = 0.0f; alpha < 1.0f; alpha += 0.1f) {
        mm::Vec3 pos;
        pos = posAnm.calcEvalute(i, alpha);
        if (alpha == 0.0f) {
          mm::Mat44 matrix;
          makeTranslation(matrix, pos);
          fw::debug::drawBoxLine(matrix, BOX_SIZE, color);
        }
        if (i == posAnm.count() - 1) {
          break;
        }
      }
    }
  }
  if (tarAnm.isPlay() && tarAnm.count() != 0) {
    for (size_t i = 0; i < tarAnm.count(); i++) {
      for (f32 alpha = 0.0f; alpha < 1.0f; alpha += 0.1f) {
        mm::Vec3 tar;
        tar = tarAnm.calcEvalute(i, alpha);
        if (alpha == 0.0f) {
          mm::Mat44 matrix;
          makeTranslation(matrix, tar);
          fw::debug::drawBoxLine(matrix, BOX_SIZE, color);
        }
        if (i == tarAnm.count() - 1) {
          break;
        }
      }
    }
  }
  if (posAnm.isPlay() && tarAnm.isPlay()) {
    size_t posCount = posAnm.count();
    size_t tarCount = tarAnm.count();
    size_t count = posCount > tarCount ? posCount : tarCount;
    mm::Vec3 pos = posAnm.getValue(0);
    mm::Vec3 tar = tarAnm.getValue(0);
    for (size_t i = 0; i < count; i++) {
      if (i < posCount) {
        pos = posAnm.getValue(i);
      }
      if (i < tarCount) {
        tar = tarAnm.getValue(i);
      }
      fw::debug::drawLine(pos, tar, color);
    }
  }
}

void CamHands::setPos(const PosAxis &pos, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  mm::Vec3 position = pos.calcPos();
  mPos = position;
  posAnm.clear();
  posAnm.append(0.0f, position, CV_TYPE_STEP);
  posAnm.setCv(cv);
  posAxes.clear();
  posAxes.push_back(pos);
}

void CamHands::addAnmPos(f32 frame, const PosAxis &pos, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  mm::Vec3 position = pos.calcPos();
  posAnm.append(frame, position, cv);
  posAxes.push_back(pos);
}

void CamHands::insertAnmPos(size_t index, const PosAxis &pos) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  posAnm.insert(index, pos.calcPos());
  if (index < posAxes.size()) {
    posAxes[index] = pos;
  }
}

void CamHands::setTar(const TarAxis &tar, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  mm::Vec3 target = tar.calcTar(mPos);
  mTarget = target;
  tarAnm.clear();
  tarAnm.append(0.0f, target, CV_TYPE_STEP);
  tarAnm.setCv(cv);
  tarAxes.clear();
  tarAxes.push_back(tar);
  setFollowTarAngle(tar.getAxis());
}

void CamHands::addAnmTar(f32 frame, const TarAxis &tar, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  mm::Vec3 target = tar.calcTar(mPos);
  tarAnm.append(frame, target, cv);
  tarAxes.push_back(tar);
  setFollowTarAngle(tar.getAxis());
}

void CamHands::insertAnmTar(size_t index, const TarAxis &tar) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  tarAnm.insert(index, tar.calcTar(mPos));
  if (index < tarAxes.size()) {
    tarAxes[index] = tar;
  }
  setFollowTarAngle(tar.getAxis());
}

void CamHands::setFov(f32 fov, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  mFov = fov;
  fovAnm.clear();
  fovAnm.append(0.0f, fov, CV_TYPE_STEP);
  fovAnm.setCv(cv);
  fovs.clear();
  fovs.push_back(fov);
}

void CamHands::addAnmFov(f32 frame, f32 fov, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  fovAnm.append(frame, fov, cv);
  fovs.push_back(fov);
}

void CamHands::insertAnmFov(size_t index, f32 fov) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  fovAnm.setValue(index, fov);
  if (index < fovs.size()) {
    fovs[index] = fov;
  }
}

void CamHands::setRotZ(f32 rotZ, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  mRoll = rotZ;
  rotZAnm.clear();
  rotZAnm.append(0.0f, rotZ, CV_TYPE_STEP);
  rotZAnm.setCv(cv);
  rotZs.clear();
  rotZs.push_back(rotZ);
}

void CamHands::addAnmRotZ(f32 frame, f32 rotZ, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  rotZAnm.append(frame, rotZ, cv);
  rotZs.push_back(rotZ);
}

void CamHands::insertAnmRotZ(size_t index, f32 rotZ) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  rotZAnm.setValue(index, rotZ);
  if (index < rotZs.size()) {
    rotZs[index] = rotZ;
  }
}

void CamHands::replay() {
  posAnm.replay();
  tarAnm.replay();
  fovAnm.replay();
  rotZAnm.replay();
}

void CamHands::followPos(bool isFollow) {
  if (isFollow) {
    flags |= FLAG_FOLLOW_POS;
  } else {
    flags &= ~FLAG_FOLLOW_POS;
  }
}

bool CamHands::isFollowPos() const { return (flags & FLAG_FOLLOW_POS) != 0; }

void CamHands::followTar(bool isFollow) {
  if (isFollow) {
    flags |= FLAG_FOLLOW_TAR;
  } else {
    flags &= ~FLAG_FOLLOW_TAR;
  }
}

bool CamHands::isFollowTar() const { return (flags & FLAG_FOLLOW_TAR) != 0; }

void CamHands::setNearfar(f32 nearClip, f32 farClip) { setNearFar(nearClip, farClip); }

void CamHands::setNearfar(EVT_nearfar nearfar) { setNearFar(CamUtil::id2near(nearfar), CamUtil::id2far(nearfar)); }

void CamHands::getPosString(mm::mtl::FixStr<256> &string) {
  string = "";
  for (size_t i = 0; i < posAnm.count(); i++) {
    mm::Vec3 pos = posAxes[i].getPos();
    f32 frame = posAnm.getKeyFrame(i);
    mm::mtl::FixStr<256> line;
    line.format("%.3f %.3f %.3f %d|", pos.x, pos.y, pos.z, static_cast<int>(frame));
    string += line.c_str();
  }
}

void CamHands::getTarString(mm::mtl::FixStr<256> &string) {
  string = "";
  for (size_t i = 0; i < tarAnm.count(); i++) {
    mm::Vec3 tar = tarAxes[i].getTar();
    f32 frame = tarAnm.getKeyFrame(i);
    mm::mtl::FixStr<256> line;
    if (tarAxes[i].getAxis() < TarAxis::AXIS_ANGLE) {
      line.format("%.3f %.3f %.3f %d|", tar.x, tar.y, tar.z, static_cast<int>(frame));
    } else if (tarAxes[i].getAxis() < TarAxis::AXIS_CHARA) {
      line.format("%.3f %.3f %.3f %d|", tar.x * mm::RAD_TO_DEG, tar.y * mm::RAD_TO_DEG, tar.z * mm::RAD_TO_DEG, static_cast<int>(frame));
    } else if (tarAxes[i].getAxis() < mm::mtl::Singleton<ObjectManager>::getPtr()->getCharaCount() + TarAxis::AXIS_CHARA) {
      line.format("%.3f %.3f %.3f %d|", tar.x, tar.y, tar.z, static_cast<int>(frame));
    }
    string += line.c_str();
  }
}

void CamHands::getFovString(mm::mtl::FixStr<256> &string) {
  string = "";
  for (size_t i = 0; i < fovs.size(); i++) {
    f32 fov = fovs[i];
    f32 frame = fovAnm.getKeyFrame(i);
    mm::mtl::FixStr<256> line;
    line.format("%.3f %d|", fov, static_cast<int>(frame));
    string += line.c_str();
  }
}

void CamHands::getRotZString(mm::mtl::FixStr<256> &string) {
  string = "";
  for (size_t i = 0; i < rotZs.size(); i++) {
    f32 rotZ = rotZs[i];
    f32 frame = rotZAnm.getKeyFrame(i);
    mm::mtl::FixStr<256> line;
    line.format("%.3f %d|", rotZ * mm::RAD_TO_DEG, static_cast<int>(frame));
    string += line.c_str();
  }
}

} // namespace event
