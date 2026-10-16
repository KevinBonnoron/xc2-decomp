#pragma once
#include "gf/object/component/animation/gf_com_asm.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
class GfEvtModel;
class GfObj;
} // namespace gf
namespace mm {
struct Vec3;
} // namespace mm

namespace event {

class CharaUtil {
public:
  static void execCmd(gf::GfObj *obj, const char *command);
  static void execCmd(gf::GfObj *obj, const char *command, const char *state, const char *currentState);
  static void setStat(gf::GfObj *obj, const char *state);
  static const char *getStat(gf::GfObj *obj);
  static bool checkStat(gf::GfObj *obj, const char *state);
  static bool checkStat(gf::GfObj *obj, const char *state, const char *otherState);
  static bool checkStatSeries(gf::GfObj *obj, const char *series);
  static bool isActionBusy(gf::GfObj *obj);
  static bool easeIn(gf::GfObj *obj, const char *name, gf::AnimLayer layer);
  static bool easeOut(gf::GfObj *obj, const char *name, gf::AnimLayer layer);
  static bool setEaseWeight(gf::GfObj *obj, const char *name, gf::AnimLayer layer, f32 weight);
  static bool setEaseSpeed(gf::GfObj *obj, const char *name, gf::AnimLayer layer, f32 speed);
  static bool hasResAsm(gf::GfObj *obj);
  static bool isNeedMove(const mm::Vec3 &position, const mm::Vec3 &target);
  static bool isNeedTurn(f32 rotation, f32 target);
  static bool isCanTarget(gf::GF_OBJ_HANDLE *handle, gf::GF_OBJ_HANDLE *target);
  static bool isCanTarget(const mm::Vec3 &position, const mm::Vec3 &rotation, const mm::Vec3 &target);
  static void setVariable(gf::GfObj *obj, const char *name, f32 value);
  static void setVariable(gf::GfObj *obj, const char *name, int value);
  static void adjestPosY(mm::Vec3 &position, mm::Vec3 *reference);
  static void combat(gf::GfEvtModel *model, bool isBattle, bool isState);
  static void setGravity(gf::GF_OBJ_HANDLE *handle, bool isEnable);
};

} // namespace event
