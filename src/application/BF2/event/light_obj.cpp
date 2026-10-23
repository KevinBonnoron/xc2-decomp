#include "event/light_obj.h"

#include "event/extend.h"
#include "event/frame_manager.h"
#include "fw/fw_debug.h"
#include "ml/scn_obj_light.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_rect.h"
#include "mm_mtl/singleton.h"

namespace event {

constexpr f32 RADIAN_TO_DEGREE = 57.29578f;

LightObj::LightObj(int screenID) : flags(0), mLight(nullptr), mScreenID(screenID), mData(nullptr), mPos(mm::Vec3::zero), mRot(mm::Vec3::zero) {}

LightObj::~LightObj() { clear(); }

void LightObj::update(const FrameInfo &info) {
  if (mLight == nullptr)
    return;
  mLight->setPos(mPos);
  mLight->setRot(mRot);
  mLife -= info.delta;
  if (mLife < 0.0f)
    clear();
}

void LightObj::render(int x, int y) {
  if (mLight == nullptr) {
    return;
  }
  fw::debug::drawSquare2D(mm::Rect<int>(x, y, 230, 75), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<int>(x, y, 230, 75), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(x + 5, y + 5, "[LIGHT]");
  fw::debug::drawFont(x + 100, y + 5, "life(%.2f)", mLife);
  fw::debug::drawFont(x + 10, y + 22, "file:    %s", mm::mtl::Singleton<Extend>::getPtr()->filename(path.c_str()));
  fw::debug::drawFont(x + 10, y + 37, "pos:     %.1f %.1f %.1f", mPos.x, mPos.y, mPos.z);
  fw::debug::drawFont(x + 10, y + 52, "rot:     %.1f %.1f %.1f", mRot.x * RADIAN_TO_DEGREE, mRot.y * RADIAN_TO_DEGREE, mRot.z * RADIAN_TO_DEGREE);
}

bool LightObj::isPlaying() const { return mLight != nullptr; }

void LightObj::setPos(const mm::Vec3 &pos) { mPos = pos; }

const mm::Vec3 &LightObj::getPos() const { return mPos; }

void LightObj::setRot(const mm::Vec3 &rot) { mRot = rot; }

} // namespace event
