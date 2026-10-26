#include "event/object_util.h"

#include <math.h>
#include <stdlib.h>

#include "event/manager.h"
#include "fw/fw_debug.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/animation/gf_com_evt_anim.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "ml/scn.h"
#include "ml/scn_cam_util.h"
#include "mm_math/mm_col4.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_rect.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"

namespace event {

f32 ObjectUtil::toFov(f32 focal) { return 2.0f * atanf(25.39f / (2.0f * focal)) * 180.0f / 3.1415f; }

f32 ObjectUtil::toFocal(f32 fov) { return 25.39f / (2.0f * tanf(fov * 0.017452778f * 0.5f)); }

bool ObjectUtil::isBackSide(const mm::Vec3 &position) {
  mm::Vec3 screen;
  return !ml::ScnCamUtil::getScreenPos(screen, Manager::sys()->getScn()->getCam(-1), position);
}

const char *ObjectUtil::num2str(u32 number) {
  static const char *const NUMBERS[] = {"", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
  return NUMBERS[number];
}

const char *ObjectUtil::num2strMulti(u32 number) {
  static const char *const NUMBERS[] = {"", "２", "３", "４", "５", "６", "７", "８", "９", "１０"};
  return NUMBERS[number];
}

int ObjectUtil::getElementCount(const char *string) {
  int count = 0;
  while (string != nullptr && *string != '\0') {
    string = __builtin_strchr(string, '|');
    if (string != nullptr) {
      string++;
      count++;
    }
  }
  return count;
}

s32 ObjectUtil::getElementS32(const char *string, int index, int group) {
  mm::mtl::FixStr<128> element;
  getElement(element, string, index, group);
  return atoi(element.c_str());
}

f32 ObjectUtil::getElementF32(const char *string, int index, int group) {
  mm::mtl::FixStr<128> element;
  getElement(element, string, index, group);
  return atof(element.c_str());
}

bool ObjectUtil::isNumber(int character) {
  if (static_cast<s8>(character) >= 0 && static_cast<u32>(character - '0') < 10) {
    return true;
  }
  return character == '+' || character == '-' || character == '.';
}

void ObjectUtil::drawCameraInfo(int x, int y, const mm::Vec3 &position, const mm::Vec3 &target, const mm::Vec3 &rotation, f32 lens, bool isFocal) {
  fw::debug::drawSquare2D(mm::Rect<s32>(x, y, 225, 85), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(x, y, 225, 85), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(x + 5, y + 5, "CAM0");
  s32 lineY = y + 20;
  fw::debug::drawFontColor(mm::Col4(0.75f, 0.75f, 1.0f, 1.0f));
  s32 labelX = x + 15;
  fw::debug::drawFont(labelX, lineY, "pos:");
  s32 valueX = x + 55;
  fw::debug::drawFont(valueX, lineY, "%.2f %.2f %.2f", position.x, position.y, position.z);
  lineY = y + 35;
  fw::debug::drawFont(labelX, lineY, "tar:");
  fw::debug::drawFont(valueX, lineY, "%.2f %.2f %.2f", target.x, target.y, target.z);
  lineY = y + 50;
  fw::debug::drawFont(labelX, lineY, "rot:");
  fw::debug::drawFont(valueX, lineY, "%.2f %.2f %.2f", rotation.x * mm::RAD_TO_DEG, rotation.y * mm::RAD_TO_DEG, rotation.z * mm::RAD_TO_DEG);
  lineY = y + 65;
  if (isFocal) {
    fw::debug::drawFont(labelX, lineY, "foc:");
    fw::debug::drawFont(valueX, lineY, "%.2f", lens);
    fw::debug::drawFont(x + 115, lineY, "fov:");
    fw::debug::drawFont(x + 155, lineY, "%.2f", toFov(lens));
  } else {
    fw::debug::drawFont(labelX, lineY, "fov:");
    fw::debug::drawFont(valueX, lineY, "%.2f", lens);
    fw::debug::drawFont(x + 115, lineY, "foc:");
    fw::debug::drawFont(x + 155, lineY, "%.2f", toFocal(lens));
  }
}

void ObjectUtil::drawChara(const char *name, const mm::Vec3 &position, const mm::Vec3 &rotation, const char *target, f32 height, gf::GF_OBJ_HANDLE *handle) {
  ml::ScnObjCam *cam = Manager::sys()->getScn()->getCam(-1);
  mm::Vec3 screen;
  if (ml::ScnCamUtil::getScreenPos(screen, cam, position)) {
    s32 x = screen.x;
    s32 y = screen.y;
    s32 rectX = x - 110;
    s32 rectY = y - 25;
    fw::debug::drawSquare2D(mm::Rect<s32>(rectX, rectY, 220, 57), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
    fw::debug::drawLineSquare2D(mm::Rect<s32>(rectX, rectY, 220, 57), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    x -= 105;
    s32 textY = y - 20;
    fw::debug::drawFontColor(mm::Col4(0.8f, 0.8f, 1.0f, 1.0f));
    fw::debug::drawFont(x, textY, "pos %.2f %.2f %.2f", position.x, position.y, position.z);
    fw::debug::drawFont(x, y - 4, "rot %.2f %.2f %.2f", rotation.x * mm::RAD_TO_DEG, rotation.y * mm::RAD_TO_DEG, rotation.z * mm::RAD_TO_DEG);
    if (target == nullptr) {
      fw::debug::drawFont(x, y + 12, "tar     NONE");
    } else {
      fw::debug::drawFont(x, y + 12, "tar     %s", target);
    }
  }
  mm::Vec3 top;
  top.x = position.x;
  top.y = position.y + height + 0.2f;
  top.z = position.z;
  if (ml::ScnCamUtil::getScreenPos(screen, cam, top)) {
    s32 x = screen.x;
    s32 y = screen.y;
    s32 rectY = y - 15;
    fw::debug::drawSquare2D(mm::Rect<s32>(x - 80, rectY, 160, 25), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
    fw::debug::drawLineSquare2D(mm::Rect<s32>(x - 80, rectY, 160, 25), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    s32 textX = x - 75;
    s32 textY = y - 10;
    fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
    fw::debug::drawFont(textX, textY, name);
    if (handle != gf::INVALID_HANDLE) {
      gf::GfObjAcc acc(handle);
      fw::debug::drawFont(x + 15, textY, "ID:%d", acc.getBdatId());
    }
  }
}

void ObjectUtil::drawEffect(const char *name, const mm::Vec3 &position, const mm::Vec3 &rotation, const mm::Vec3 &scale, const mm::Col4 &color, unsigned long count) {
  mm::Vec3 screen;
  if (!ml::ScnCamUtil::getScreenPos(screen, Manager::sys()->getScn()->getCam(-1), position)) {
    return;
  }
  s32 x = screen.x;
  s32 y = screen.y;
  fw::debug::drawSquare2D(mm::Rect<s32>(x - 110, y - 25, 220, 89), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(x - 110, y - 25, 220, 89), mm::Col4(0.8f, 1.0f, 0.8f, 1.0f));
  s32 textX = x - 105;
  s32 textY = y - 20;
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(textX, textY, name);
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(x + 45, textY, "num[%d]", count);
  textY = y - 4;
  fw::debug::drawFontColor(mm::Col4(0.8f, 0.8f, 1.0f, 1.0f));
  fw::debug::drawFont(textX, textY, "pos %.2f %.2f %.2f", position.x, position.y, position.z);
  fw::debug::drawFont(textX, y + 12, "rot %.2f %.2f %.2f", rotation.x * mm::RAD_TO_DEG, rotation.y * mm::RAD_TO_DEG, rotation.z * mm::RAD_TO_DEG);
  fw::debug::drawFont(textX, y + 28, "sca %.2f", scale.x);
  fw::debug::drawFont(textX, y + 44, "col %.2f %.2f %.2f %.2f", color.r, color.g, color.b, color.a);
}

void ObjectUtil::drawState(const mm::Vec3 &position, f32 height, gf::GF_OBJ_HANDLE *handle) {
  gf::GfObj *obj = gf::GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return;
  }
  const char *state = nullptr;
  gf::GfComEvtAnim *evtAnim = obj->getComponent<gf::GfComEvtAnim>();
  if (evtAnim != nullptr) {
    state = evtAnim->getStateName();
  }
  gf::GfComAsm *comAsm = obj->getComponent<gf::GfComAsm>();
  if (comAsm != nullptr) {
    state = comAsm->getStateName(gf::ANIM_LAYER_BASE);
  }
  if (state == nullptr) {
    return;
  }
  mm::Vec3 top;
  top.x = position.x;
  top.y = position.y + height + 0.2f;
  top.z = position.z;
  mm::Vec3 screen;
  if (!ml::ScnCamUtil::getScreenPos(screen, Manager::sys()->getScn()->getCam(-1), top)) {
    return;
  }
  s32 x = screen.x;
  s32 y = screen.y;
  fw::debug::drawSquare2D(mm::Rect<s32>(x - 80, y + 15, 160, 23), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(x - 80, y + 15, 160, 23), mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  fw::debug::drawFont(x - 75, y + 19, state);
}

void ObjectUtil::drawEffectCaster(const char *name, const mm::Vec3 &position, bool isMount, const char *bone) {
  mm::Vec3 screen;
  if (!ml::ScnCamUtil::getScreenPos(screen, Manager::get()->getScn()->getCam(-1), position)) {
    return;
  }
  s32 x = screen.x;
  s32 y = screen.y;
  fw::debug::drawSquare2D(mm::Rect<s32>(x - 110, y - 55, 220, 89), mm::Col4(0.0f, 0.0f, 0.0f, 0.25f));
  fw::debug::drawLineSquare2D(mm::Rect<s32>(x - 110, y - 55, 220, 24), mm::Col4(0.8f, 1.0f, 0.8f, 1.0f));
  s32 textX = x - 105;
  s32 textY = y - 50;
  fw::debug::drawFontColor(mm::Col4(1.0f, 1.0f, 1.0f, 1.0f));
  if (isMount) {
    fw::debug::drawFont(textX, textY, "mount  %s.%s", name, bone);
  } else {
    fw::debug::drawFont(textX, textY, "caster %s", name);
  }
}

} // namespace event
