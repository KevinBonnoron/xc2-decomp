#pragma once
#include "event/alpha_obj.h"
#include "event/i_manager.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class AlphaManager : public IManager, public mm::mtl::Singleton<AlphaManager> {
public:
  static constexpr u32 OBJ_COUNT = 256;

  enum {
    FLAG_ACTIVE = 1 << 0,
  };

  enum {
    DISP_FLAG_DISP = 1 << 0,
  };

  AlphaManager();
  virtual ~AlphaManager() {}
  void clear();
  void update();
  void render();
  void setAlpha(gf::GF_OBJ_HANDLE *handle, ALPHA_ATTR attr, f32 alpha, f32 belongingAlpha);
  AlphaObj *search(gf::GF_OBJ_HANDLE *handle) const;
  void setDisp(bool isDisp);
  bool isDisp() const;
  virtual void OnEventProc(MSG_TYPE type);

private:
  u32 unknown10;                                         // Inferred role: flags; original member name unknown.
  u32 unknown14;                                         // Inferred role: disp flags; original member name unknown.
  mm::mtl::FixedVector<AlphaObj *, OBJ_COUNT> unknown18; // Inferred role: objs; original member name unknown.
};

static_assert(sizeof(AlphaManager) == 0x820, "");

} // namespace event
