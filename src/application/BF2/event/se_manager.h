#pragma once
#include "event/curve.h"
#include "event/i_manager.h"
#include "event/se_obj.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace event {

class SeManager : public IManager, public mm::mtl::Singleton<SeManager> {
public:
  static constexpr u32 SE_COUNT = 32;

  enum {
    DISP_FLAG_DISP = 1 << 0,
  };

  SeManager();
  virtual ~SeManager() {}
  void clear();
  void update();
  void render();
  void load(const char *name);
  bool isLoading() const;
  void pause(bool isPause);
  void play(int index, const char *name, f32 life, f32 fadeIn, f32 fadeOut, f32 volume);
  void changeVolume(int index, f32 volume, f32 frame);
  void pan(int index, f32 pan, f32 frame, CV_TYPE cv);
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 unknown10;                                       // Inferred role: disp flags; original member name unknown.
  u32 unknown14;                                       // Inferred role: load count; original member name unknown.
  mm::mtl::FixedArray<SeObj, SE_COUNT> unknown18;      // Inferred role: objs; original member name unknown.
  mm::mtl::FixedVector<SeObj *, SE_COUNT> unknown5318; // Inferred role: play list; original member name unknown.
};

static_assert(sizeof(SeManager) == 0x5420, "");

} // namespace event
