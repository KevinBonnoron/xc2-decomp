#pragma once
#include "types.h"

namespace gmk {

class AGmkBase;
class IGmkPhantomEventListener;

class GmkPhantom {
public:
  virtual ~GmkPhantom();

  void create(const AGmkBase &gmk, IGmkPhantomEventListener *listener, bool isCheckEnemy);

  u8 _08[0x88 - 0x08];
};

static_assert(sizeof(GmkPhantom) == 0x88, "");

} // namespace gmk
