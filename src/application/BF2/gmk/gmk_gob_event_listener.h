#pragma once
#include "gf/object/gf_obj_manager.h"
#include "types.h"

namespace gmk {

class GmkGobEventListener : public gf::IGfObjListener {
public:
  GmkGobEventListener();
  virtual ~GmkGobEventListener();
  void listenerGfObj(OBJEVT event, gf::GF_OBJ_HANDLE *handle, u32 objectType) override;

  static void createInstance();
  static void disposeInstance();

private:
  int refCount;
};

} // namespace gmk
