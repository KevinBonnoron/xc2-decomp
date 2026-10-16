#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {
struct GF_OBJ_HANDLE;
class GfEvtModel;
} // namespace gf

namespace event {

class CharaPartUpdater {
public:
  static constexpr size_t REQUEST_COUNT = 8;

  enum TYPE {
    TYPE_EXT_DISP = 0,
    TYPE_EXT_DISP_WEAPON = 1,
    TYPE_EXT_PARAM = 2,
  };

  struct Request {
    TYPE type;
    const char *name;
    f32 value;
  };

  CharaPartUpdater();
  virtual ~CharaPartUpdater() {}
  void create(gf::GF_OBJ_HANDLE *handle, gf::GfEvtModel *model);
  void destroy();
  void update(f32 delta);
  void updateRequest();
  void eraseRequest(TYPE type, const char *name);
  void setExtDisp(const char *name, bool isDisp);
  void setExtDispWeapon(const char *name, bool isDisp);
  void setExtParam(const char *name, f32 value);

private:
  gf::GF_OBJ_HANDLE *handle;
  gf::GfEvtModel *mModel;
  mm::mtl::FixedVector<Request, REQUEST_COUNT> mRequests;
};

static_assert(sizeof(CharaPartUpdater) == 0xe0, "");

} // namespace event
