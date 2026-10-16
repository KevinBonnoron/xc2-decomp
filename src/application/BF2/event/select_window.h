#pragma once
#include "mm_mtl/bitflag.h"
#include "types.h"
#include <stddef.h>

namespace gf {
class GfMenuCallContext;
struct GF_OBJ_HANDLE;
} // namespace gf

namespace event {

enum SELECT_TYPE {};

class SelectWindow {
public:
  enum {
    FLAG_OPEN = 0,
  };

  SelectWindow();
  virtual ~SelectWindow() {}
  void clear();
  void update();
  void close();
  void open(SELECT_TYPE type, int defaultIndex, const int *items, size_t count, u8 *message, gf::GF_OBJ_HANDLE *handle);
  int getResult();
  bool isOpen() const { return flags.test(FLAG_OPEN); }
  int getSelected() const { return mResult; }

private:
  mm::mtl::BitFlag<32> flags;
  int mResult;
  gf::GfMenuCallContext *mContext;
};

static_assert(sizeof(SelectWindow) == 0x18, "");

} // namespace event
