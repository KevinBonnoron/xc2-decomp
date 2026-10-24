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

CamHands::CamHands(bool isFocal) : CamBase(isFocal), unknown40(0) {}

void CamHands::update(const FrameInfo &info) {
  f32 delta = info.unknown0c;
  if ((unknown40 & FLAG_FOLLOW_POS) != 0) {
    calcFollowPos();
  }
  if (unknown50.isPlay()) {
    unknown50.update(delta);
    unknown10 = unknown50.getValue();
  }
  if ((unknown40 & (FLAG_FOLLOW_TAR | FLAG_FOLLOW_TAR_ANGLE)) != 0) {
    calcFollowTar();
  }
  if (unknown240.isPlay()) {
    unknown240.update(delta);
    unknown20 = unknown240.getValue();
  }
  if (unknown430.isPlay()) {
    unknown430.update(delta);
    unknown30 = unknown430.getValue();
  }
  if (unknown540.isPlay()) {
    unknown540.update(delta);
    unknown34 = unknown540.getValue();
  }
}

void CamHands::calcFollowPos() {
  for (size_t i = 0; i < unknown650.size(); i++) {
    unknown50.insert(i, unknown650[i].calcPos());
  }
}

void CamHands::calcFollowTar() {
  for (size_t i = 0; i < unknown860.size(); i++) {
    unknown240.insert(i, unknown860[i].calcTar(unknown10));
  }
}

void CamHands::render(const mm::Col4 &color) {
  static const mm::Vec3 BOX_SIZE(0.05f, 0.05f, 0.05f);
  if (unknown50.isPlay() && unknown50.count() != 0) {
    for (size_t i = 0; i < unknown50.count(); i++) {
      for (f32 alpha = 0.0f; alpha < 1.0f; alpha += 0.1f) {
        mm::Vec3 pos;
        pos = unknown50.calcEvalute(i, alpha);
        if (alpha == 0.0f) {
          mm::Mat44 matrix;
          makeTranslation(matrix, pos);
          fw::debug::drawBoxLine(matrix, BOX_SIZE, color);
        }
        if (i == unknown50.count() - 1) {
          break;
        }
      }
    }
  }
  if (unknown240.isPlay() && unknown240.count() != 0) {
    for (size_t i = 0; i < unknown240.count(); i++) {
      for (f32 alpha = 0.0f; alpha < 1.0f; alpha += 0.1f) {
        mm::Vec3 tar;
        tar = unknown240.calcEvalute(i, alpha);
        if (alpha == 0.0f) {
          mm::Mat44 matrix;
          makeTranslation(matrix, tar);
          fw::debug::drawBoxLine(matrix, BOX_SIZE, color);
        }
        if (i == unknown240.count() - 1) {
          break;
        }
      }
    }
  }
  if (unknown50.isPlay() && unknown240.isPlay()) {
    size_t posCount = unknown50.count();
    size_t tarCount = unknown240.count();
    size_t count = posCount > tarCount ? posCount : tarCount;
    mm::Vec3 pos = unknown50.getValue(0);
    mm::Vec3 tar = unknown240.getValue(0);
    for (size_t i = 0; i < count; i++) {
      if (i < posCount) {
        pos = unknown50.getValue(i);
      }
      if (i < tarCount) {
        tar = unknown240.getValue(i);
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
  unknown10 = position;
  unknown50.clear();
  unknown50.append(0.0f, position, CV_TYPE_STEP);
  unknown50.setCv(cv);
  unknown650.clear();
  unknown650.push_back(pos);
}

void CamHands::addAnmPos(f32 frame, const PosAxis &pos, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  mm::Vec3 position = pos.calcPos();
  unknown50.append(frame, position, cv);
  unknown650.push_back(pos);
}

void CamHands::insertAnmPos(size_t index, const PosAxis &pos) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  unknown50.insert(index, pos.calcPos());
  if (index < unknown650.size()) {
    unknown650[index] = pos;
  }
}

void CamHands::setTar(const TarAxis &tar, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  mm::Vec3 target = tar.calcTar(unknown10);
  unknown20 = target;
  unknown240.clear();
  unknown240.append(0.0f, target, CV_TYPE_STEP);
  unknown240.setCv(cv);
  unknown860.clear();
  unknown860.push_back(tar);
  setFollowTarAngle(tar.getAxis());
}

void CamHands::addAnmTar(f32 frame, const TarAxis &tar, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  mm::Vec3 target = tar.calcTar(unknown10);
  unknown240.append(frame, target, cv);
  unknown860.push_back(tar);
  setFollowTarAngle(tar.getAxis());
}

void CamHands::insertAnmTar(size_t index, const TarAxis &tar) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  unknown240.insert(index, tar.calcTar(unknown10));
  if (index < unknown860.size()) {
    unknown860[index] = tar;
  }
  setFollowTarAngle(tar.getAxis());
}

void CamHands::setFov(f32 fov, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  unknown30 = fov;
  unknown430.clear();
  unknown430.append(0.0f, fov, CV_TYPE_STEP);
  unknown430.setCv(cv);
  unknowna70.clear();
  unknowna70.push_back(fov);
}

void CamHands::addAnmFov(f32 frame, f32 fov, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  unknown430.append(frame, fov, cv);
  unknowna70.push_back(fov);
}

void CamHands::insertAnmFov(size_t index, f32 fov) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  unknown430.setValue(index, fov);
  if (index < unknowna70.size()) {
    unknowna70[index] = fov;
  }
}

void CamHands::setRotZ(f32 rotZ, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  unknown34 = rotZ;
  unknown540.clear();
  unknown540.append(0.0f, rotZ, CV_TYPE_STEP);
  unknown540.setCv(cv);
  unknownab8.clear();
  unknownab8.push_back(rotZ);
}

void CamHands::addAnmRotZ(f32 frame, f32 rotZ, CV_TYPE cv) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  unknown540.append(frame, rotZ, cv);
  unknownab8.push_back(rotZ);
}

void CamHands::insertAnmRotZ(size_t index, f32 rotZ) {
  if (mm::mtl::Singleton<SkipManager>::getPtr()->isSkipFast()) {
    return;
  }
  unknown540.setValue(index, rotZ);
  if (index < unknownab8.size()) {
    unknownab8[index] = rotZ;
  }
}

void CamHands::replay() {
  unknown50.replay();
  unknown240.replay();
  unknown430.replay();
  unknown540.replay();
}

void CamHands::followPos(bool isFollow) {
  if (isFollow) {
    unknown40 |= FLAG_FOLLOW_POS;
  } else {
    unknown40 &= ~FLAG_FOLLOW_POS;
  }
}

bool CamHands::isFollowPos() const { return (unknown40 & FLAG_FOLLOW_POS) != 0; }

void CamHands::followTar(bool isFollow) {
  if (isFollow) {
    unknown40 |= FLAG_FOLLOW_TAR;
  } else {
    unknown40 &= ~FLAG_FOLLOW_TAR;
  }
}

bool CamHands::isFollowTar() const { return (unknown40 & FLAG_FOLLOW_TAR) != 0; }

void CamHands::setNearfar(f32 nearClip, f32 farClip) { setNearFar(nearClip, farClip); }

void CamHands::setNearfar(EVT_nearfar nearfar) { setNearFar(CamUtil::id2near(nearfar), CamUtil::id2far(nearfar)); }

void CamHands::getPosString(mm::mtl::FixStr<256> &string) {
  string = "";
  for (size_t i = 0; i < unknown50.count(); i++) {
    mm::Vec3 pos = unknown650[i].getPos();
    f32 frame = unknown50.getKeyFrame(i);
    mm::mtl::FixStr<256> line;
    line.format("%.3f %.3f %.3f %d|", pos.x, pos.y, pos.z, static_cast<int>(frame));
    string += line.c_str();
  }
}

void CamHands::getTarString(mm::mtl::FixStr<256> &string) {
  string = "";
  for (size_t i = 0; i < unknown240.count(); i++) {
    mm::Vec3 tar = unknown860[i].getTar();
    f32 frame = unknown240.getKeyFrame(i);
    mm::mtl::FixStr<256> line;
    if (unknown860[i].getAxis() < TarAxis::AXIS_ANGLE) {
      line.format("%.3f %.3f %.3f %d|", tar.x, tar.y, tar.z, static_cast<int>(frame));
    } else if (unknown860[i].getAxis() < TarAxis::AXIS_CHARA) {
      line.format("%.3f %.3f %.3f %d|", tar.x * mm::RAD_TO_DEG, tar.y * mm::RAD_TO_DEG, tar.z * mm::RAD_TO_DEG, static_cast<int>(frame));
    } else if (unknown860[i].getAxis() < mm::mtl::Singleton<ObjectManager>::getPtr()->getCharaCount() + TarAxis::AXIS_CHARA) {
      line.format("%.3f %.3f %.3f %d|", tar.x, tar.y, tar.z, static_cast<int>(frame));
    }
    string += line.c_str();
  }
}

void CamHands::getFovString(mm::mtl::FixStr<256> &string) {
  string = "";
  for (size_t i = 0; i < unknowna70.size(); i++) {
    f32 fov = unknowna70[i];
    f32 frame = unknown430.getKeyFrame(i);
    mm::mtl::FixStr<256> line;
    line.format("%.3f %d|", fov, static_cast<int>(frame));
    string += line.c_str();
  }
}

void CamHands::getRotZString(mm::mtl::FixStr<256> &string) {
  string = "";
  for (size_t i = 0; i < unknownab8.size(); i++) {
    f32 rotZ = unknownab8[i];
    f32 frame = unknown540.getKeyFrame(i);
    mm::mtl::FixStr<256> line;
    line.format("%.3f %d|", rotZ * mm::RAD_TO_DEG, static_cast<int>(frame));
    string += line.c_str();
  }
}

} // namespace event
