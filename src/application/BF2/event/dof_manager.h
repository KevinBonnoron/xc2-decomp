#pragma once
#include "event/i_manager.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class CharaObj;

class DofManager : public IManager, public mm::mtl::Singleton<DofManager> {
public:
  enum {
    FLAG_ENABLE = 1 << 0,
    FLAG_CHANGED = 1 << 1,
  };

  enum {
    DISP_FLAG_DISP = 1 << 0,
  };

  DofManager();
  virtual ~DofManager() {}
  void play(int axis, f32 dist, f32 range, f32 pixel, f32 lens, f32 strength, f32 blend, int pixelLv, bool isHlv, const char *name) {
    flags |= FLAG_ENABLE | FLAG_CHANGED;
    mAxis = axis;
    mDist = dist;
    mCurrentDist = dist;
    mRange = range;
    mIsAutoFocus = false;
    mPixel = pixel;
    mLens = lens;
    mStrength = strength;
    mBlend = blend;
    mPixelLv = pixelLv;
    mIsHlv = isHlv;
    mName = name;
  }
  void stop();
  void clear();
  void update();
  static f32 calcDist(int axis, f32 dist);
  void render();
  static const char *getAxisName(int axis);
  static f32 calcDistSub(CharaObj *chara, f32 dist);
  void play(int axis, int id);
  void playSimple(int focusNum, f32 focusMin, f32 pixel, f32 lens, f32 strength, f32 blend, int pixelLv, bool isHlv, const char *name);
  void playSimple(int focusNum, int id);
  void setEnable(bool isEnable);
  bool isEnable() const;
  void setAxis(int axis);
  int getAxis() const;
  void setDist(f32 dist);
  f32 getDist() const;
  void setRange(f32 range);
  void setFocusNum(int focusNum);
  void setFocusMin(f32 focusMin);
  void setPixel(f32 pixel);
  void setLens(f32 lens);
  void setStrength(f32 strength);
  void setBlend(f32 blend);
  void setPixelLv(int pixelLv);
  void setHlv(bool isHlv);
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  void setFlag(u32 flag, bool isSet) {
    if (isSet) {
      flags |= flag;
    } else {
      flags &= ~flag;
    }
  }

  void setChanged() {
    setFlag(FLAG_ENABLE, isEnable());
    setFlag(FLAG_CHANGED, isEnable());
  }

  u32 dispFlags;
  u32 flags;
  int mAxis;
  f32 mDist;
  f32 mCurrentDist;
  f32 mRange;
  bool mIsAutoFocus;
  int mFocusNum;
  f32 mFocusMin;
  f32 mPixel;
  f32 mLens;
  f32 mStrength;
  f32 mBlend;
  int mPixelLv;
  bool mIsHlv;
  const char *mName;
};

static_assert(sizeof(DofManager) == 0x58, "");

} // namespace event
