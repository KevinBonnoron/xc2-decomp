#include "event/cam_eva_player.h"

#include "event/cam_base.h"

namespace event {

CamEvaPlayer::CamEvaPlayer() : mCam(nullptr), mRcha(nullptr) {}

void CamEvaPlayer::setNearfar(EVT_nearfar nearfar) {
  mCam->setNearFar(CamUtil::id2near(nearfar), CamUtil::id2far(nearfar));
  mNearfar = nearfar;
}

} // namespace event
