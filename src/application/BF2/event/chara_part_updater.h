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
  static constexpr size_t REQUEST_UNKNOWN_8 = 8; // Inferred role: request count; original name unknown.

  enum TYPE {
    TYPE_EXT_UNKNOWN_0 = 0, // Inferred role: disp; original name unknown.
    TYPE_EXT_UNKNOWN_1 = 1, // Inferred role: disp weapon; original name unknown.
    TYPE_EXT_UNKNOWN_2 = 2, // Inferred role: param; original name unknown.
  };

  // Inferred role: request; original type name unknown.
  struct unknown001 {
    TYPE unknown00;        // Inferred role: type; original member name unknown.
    const char *unknown08; // Inferred role: name; original member name unknown.
    f32 unknown10;         // Inferred role: value; original member name unknown.
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
  gf::GF_OBJ_HANDLE *unknown08;                                  // Inferred role: handle; original member name unknown.
  gf::GfEvtModel *unknown10;                                     // Inferred role: model; original member name unknown.
  mm::mtl::FixedVector<unknown001, REQUEST_UNKNOWN_8> unknown18; // Inferred role: requests; original member name unknown.
};

static_assert(sizeof(CharaPartUpdater) == 0xe0, "");

} // namespace event
