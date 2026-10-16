#include "event/cam_hands.h"

namespace event {

void CamHands::replay() {
  mPosAnm.replay();
  mTarAnm.replay();
  mFovAnm.replay();
  mRotZAnm.replay();
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

} // namespace event
