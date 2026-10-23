#pragma once
#include "event/i_res_event.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

class ModelObj;

class MdlstmObj : public IResEvent {
public:
  enum STATE {
    STATE_NONE,
    STATE_INIT,
    STATE_LOAD,
    STATE_LOADING,
    STATE_LOADED,
    STATE_MODEL,
    STATE_DELAY,
    STATE_BUSY,
    STATE_ACTIVE,
    STATE_DISPOSE,
  };

  MdlstmObj();
  virtual ~MdlstmObj();
  void destroy();
  void finishLoaded();
  void finishDelay();
  void finishBusy();
  void load();
  void dispose();
  bool isLoaded() const;
  bool isDisposeable(ModelObj *model) const;
  bool isActive() const;
  bool isLoading(f32 frame) const;
  bool isBuildable(const char *path, u32 value) const;
  bool checkByHandle(gf::GF_OBJ_HANDLE *handle) const;
  virtual void OnResEvent(const PARAM &param);

private:
  u32 flags;
  STATE state;
  f32 frame;
  mm::mtl::FixStr<128> path;
  u32 _98;
  u32 _9c;
  u32 _a0;
  bool _a4;
  bool _a5;
  u32 _a8;
  void *_b0;
  void *_b8;
  void *_c0;
  void *_c8;
  void *_d0;
  ModelObj *mReuseModel;
  ModelObj *mModel;
  u32 mDisposeDelay;
};

static_assert(sizeof(MdlstmObj) == 0xf0, "");

} // namespace event
