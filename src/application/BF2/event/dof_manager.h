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
  void play(int axis, f32 dist, f32 range, f32 pixel, f32 lens, f32 strength, f32 blend, int pixelLv, bool isHlv, const char *name);
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
      unknown14 |= flag;
    } else {
      unknown14 &= ~flag;
    }
  }

  void setChanged() {
    setFlag(FLAG_ENABLE, isEnable());
    setFlag(FLAG_CHANGED, isEnable());
  }

  u32 unknown10; // Inferred role: disp flags; original member name unknown.
  u32 unknown14; // Inferred role: flags; original member name unknown.
  int m_axis;
  f32 m_dist;
  f32 unknown20;         // Inferred role: current dist; original member name unknown.
  f32 unknown24;         // Inferred role: range; original member name unknown.
  bool unknown28;        // Inferred role: is auto focus; original member name unknown.
  int unknown2c;         // Inferred role: focus num; original member name unknown.
  f32 unknown30;         // Inferred role: focus min; original member name unknown.
  f32 unknown34;         // Inferred role: pixel; original member name unknown.
  f32 unknown38;         // Inferred role: lens; original member name unknown.
  f32 unknown3c;         // Inferred role: strength; original member name unknown.
  f32 unknown40;         // Inferred role: blend; original member name unknown.
  int unknown44;         // Inferred role: pixel lv; original member name unknown.
  bool unknown48;        // Inferred role: is hlv; original member name unknown.
  const char *unknown50; // Inferred role: name; original member name unknown.
};

static_assert(sizeof(DofManager) == 0x58, "");

} // namespace event
