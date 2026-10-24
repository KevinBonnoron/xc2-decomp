#include "event/cam_eva_player.h"

#include "event/cam_base.h"

namespace event {

CamEvaPlayer::CamEvaPlayer() : unknown08(nullptr), unknown10(nullptr) {}

void CamEvaPlayer::setNearfar(EVT_nearfar nearfar) {
  unknown08->setNearFar(CamUtil::id2near(nearfar), CamUtil::id2far(nearfar));
  unknown30 = nearfar;
}

} // namespace event
