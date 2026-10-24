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

LightObj::LightObj(int screenID) : unknown08(0), unknown10(nullptr), unknown18(screenID), unknowna0(nullptr), m_pos(mm::Vec3::zero), unknownc0(mm::Vec3::zero) {}

LightObj::~LightObj() { clear(); }

void LightObj::update(const FrameInfo &info) {
  if (unknown10 == nullptr)
    return;
  unknown10->setPos(m_pos);
  unknown10->setRot(unknownc0);
  unknowna8 -= info.unknown04;
  if (unknowna8 < 0.0f)
    clear();
}

void LightObj::render(int x, int y) {
  if (unknown10 == nullptr) {
    return;
  }
  fw::debug::drawSquare2D(mm::Rect<int>(x, y, 230, 75), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<int>(x, y, 230, 75), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(x + 5, y + 5, "[LIGHT]");
  fw::debug::drawFont(x + 100, y + 5, "life(%.2f)", unknowna8);
  fw::debug::drawFont(x + 10, y + 22, "file:    %s", mm::mtl::Singleton<Extend>::getPtr()->filename(unknown1c.c_str()));
  fw::debug::drawFont(x + 10, y + 37, "pos:     %.1f %.1f %.1f", m_pos.x, m_pos.y, m_pos.z);
  fw::debug::drawFont(x + 10, y + 52, "rot:     %.1f %.1f %.1f", unknownc0.x * RADIAN_TO_DEGREE, unknownc0.y * RADIAN_TO_DEGREE, unknownc0.z * RADIAN_TO_DEGREE);
}

bool LightObj::isPlaying() const { return unknown10 != nullptr; }

void LightObj::setPos(const mm::Vec3 &pos) { m_pos = pos; }

const mm::Vec3 &LightObj::getPos() const { return m_pos; }

void LightObj::setRot(const mm::Vec3 &rot) { unknownc0 = rot; }

} // namespace event
