#include "dr/dr_environment_man.h"

#include "dr/dr_environment_obj.h"
#include "dr/dr_man.h"
#include "mm_math/mm_mat44.h"

namespace ml {
class DrFogMan;
class DrLightMan;

void DrEnvironmentObj::release() { unknown8c |= FLAG_RELEASE << DrMan::s_nDblStockIdx; }

DrEnvironmentObj::DrEnvironmentObj(DrMan *drMan, DrLightMan *lightMan, DrFogMan *fogMan)
    : unknown08(nullptr), unknown10(nullptr), unknown18(drMan), unknown20(lightMan), unknown28(fogMan), unknown70(0.0f, 0.0f, 0.0f), m_frame(0.0f), m_frameSpd(1.0f), m_maxFrame(0.0f), unknown8c(0),
      unknown90(0) {
  unknown30 = mm::Mat44::identity;
}

void DrEnvironmentMan::releaseObj(DrEnvironmentObj *obj) { obj->release(); }

namespace {

// Inferred role: deletes every object of a list; original name unknown.
void unknown001(DrEnvironmentObj *&head, DrEnvironmentObj *&tail) {
  DrEnvironmentObj *obj = head;
  while (obj != nullptr) {
    DrEnvironmentObj *next = obj->unknown10;
    delete obj;
    obj = next;
  }
  head = nullptr;
  tail = nullptr;
}

} // namespace

void DrEnvironmentMan::releaseAll() {
  unknown001(unknown28[0], unknown28[1]);
  unknown001(unknown28[2], unknown28[3]);
  unknown001(unknown58, unknown60);
  unknown001(unknown48, unknown50);
}

void DrEnvironmentMan::renderLgt() {
  for (DrEnvironmentObj *obj = unknown48; obj != nullptr; obj = obj->unknown10) {
    obj->renderLgt();
  }
}

void DrEnvironmentMan::setZoneObj(DrEnvironmentObj *obj, bool isOn) {
  if (isOn) {
    for (DrEnvironmentObj *current = unknown48; current != nullptr; current = current->unknown10) {
      if (current->unknown8c & DrEnvironmentObj::FLAG_UNKNOWN_1) {
        current->unknown8c &= ~DrEnvironmentObj::FLAG_DISP_OFF;
      }
    }
  } else {
    for (DrEnvironmentObj *current = unknown48; current != nullptr; current = current->unknown10) {
      if (current->unknown8c & DrEnvironmentObj::FLAG_UNKNOWN_1) {
        current->unknown8c |= DrEnvironmentObj::FLAG_DISP_OFF;
      }
    }
  }
}

f32 DrEnvironmentObj::getFrame() const { return m_frame; }

f32 DrEnvironmentObj::getMaxFrame() const { return m_maxFrame; }

void DrEnvironmentObj::setFrameSpd(f32 speed) { m_frameSpd = speed; }

f32 DrEnvironmentObj::getFrameSpd() { return m_frameSpd; }

} // namespace ml
