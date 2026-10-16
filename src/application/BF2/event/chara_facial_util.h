#pragma once
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
class GfObj;
} // namespace gf
namespace mm {
struct Vec2;
} // namespace mm

namespace event {

class CharaFacialUtil {
public:
  static const char *getFacialBdat(gf::GfObj *obj);
  static u32 transferGroup(int id, u32 type);
  static void getLensLimit(mm::Vec2 &translateMin, mm::Vec2 &translateMax, mm::Vec2 &rotateMin, mm::Vec2 &rotateMax, gf::GfObj *obj);
  static const char *headType2stat(int type);
  static const char *headType2name(int type);
  static f32 headType2bld(int type);
  static f32 headType2weight(int type);
  static const char *browType2stat(int type);
  static const char *browType2name(int type);
  static const char *eyeType2stat(int type);
  static const char *eyeType2name(int type);
  static bool lipType2disableWink(int type);
  static const char *lipType2stat(int type);
  static const char *lipType2name(int type);
  static bool lipType2disableTalkLip(int type);
  static const char *talkHeadStat();
  static const char *talkLipStat();
  static const char *winkType2name(int type);
  static bool checkBdatID(gf::GF_OBJ_HANDLE *handle, int id);
  static u32 transferGroupSub(int id, u32 type);
};

} // namespace event
