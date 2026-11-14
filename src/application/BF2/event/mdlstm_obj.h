#pragma once
#include <stddef.h>

#include "event/i_res_event.h"
#include "event/model_obj.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
} // namespace gf

namespace ml {
class DrStmReadObj;
} // namespace ml

namespace event {

class MdlstmObj : public IResEvent {
public:
  enum STATE {
    STATE_UNKNOWN_0, // Inferred role: none; original name unknown.
    STATE_UNKNOWN_1, // Inferred role: init; original name unknown.
    STATE_UNKNOWN_2, // Inferred role: load; original name unknown.
    STATE_UNKNOWN_3, // Inferred role: loading; original name unknown.
    STATE_UNKNOWN_4, // Inferred role: loaded; original name unknown.
    STATE_UNKNOWN_5, // Inferred role: model; original name unknown.
    STATE_UNKNOWN_6, // Inferred role: delay; original name unknown.
    STATE_UNKNOWN_7, // Inferred role: busy; original name unknown.
    STATE_UNKNOWN_8, // Inferred role: active; original name unknown.
    STATE_UNKNOWN_9, // Inferred role: dispose; original name unknown.
  };

  MdlstmObj();
  virtual ~MdlstmObj();
  void destroy();
  void finishFree();
  void init(f32 frame, const char *path, u32 value, bool isActive, int param);
  void init(f32 frame, MODEL_TYPE type, u32 id, u32 value, bool isActive, int param);
  void finishLoad();
  void finishLoaded();
  void finishModel();
  void finishDelay();
  void finishBusy();
  void load();
  void exec(f32 minFrame, f32 maxFrame);
  ModelObj *build();
  void dispose();
  bool isLoaded() const;
  bool isDisposeable(ModelObj *model) const;
  bool isActive() const;
  bool isLoading(f32 frame) const;
  bool isBuildable(const char *path, u32 value) const;
  bool isBuildable(MODEL_TYPE type, u32 id, u32 value) const;
  bool checkByHandle(gf::GF_OBJ_HANDLE *handle) const;
  virtual void OnResEvent(const PARAM &param);

private:
  friend class MdlstmManager;

  u32 unknown08;                  // Inferred role: flags; original member name unknown.
  STATE unknown0c;                // Inferred role: state; original member name unknown.
  f32 unknown10;                  // Inferred role: frame; original member name unknown.
  mm::mtl::FixStr<128> unknown14; // Inferred role: path; original member name unknown.
  u32 _98;
  u32 _9c;
  ModelObj::OPTION _a0;
  u32 _a8;
  void *_b0;
  size_t _b8;
  void *_c0;
  size_t _c8;
  ml::DrStmReadObj *_d0;
  ModelObj *unknownd8; // Inferred role: reuse model; original member name unknown.
  ModelObj *unknowne0; // Inferred role: model; original member name unknown.
  u32 unknowne8;       // Inferred role: dispose delay; original member name unknown.
  u32 unknownec;       // Role and original member name unknown.
};

static_assert(sizeof(MdlstmObj) == 0xf0, "");

} // namespace event
