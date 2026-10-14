#pragma once
#include "types.h"

namespace gf {

class GfDataEnBook {
public:
  static u32 getEnBoolId(u32 enemy);
  static bool isBook(u32 enemy);
  static bool isNamed(u32 enemy);
  static bool isAttackFlag(u32 enemy);
  static void setAttackFlag(u32 enemy);
  static u32 getDefeatNum(u32 enemy);
  static void incDefeatNum(u32 enemy);
  static u32 getDeadNum(u32 enemy);
  static void incDeadNum(u32 enemy);
  static u32 getClearNamedTime(u32 enemy);
  static void setClearNamedTime(u32 enemy, u32 clearNamedTime);
  static u32 getBaseEnemy(u32 enemy);
  static u32 getPopTime(u32 enemy);
  static u32 getPopWeather(u32 enemy);
};

} // namespace gf
