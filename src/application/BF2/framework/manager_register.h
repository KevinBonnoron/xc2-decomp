#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"

namespace fw {

class ManagerObject;

class ManagerRegister : public mm::mtl::PtrSingleton<ManagerRegister> {
public:
  static const size_t MANAGER_UNKNOWN_256 = 256; // Inferred role: maximum number of managers; original name unknown.

  ManagerRegister();
  ~ManagerRegister();
  void regist(ManagerObject *manager);
  void remove(ManagerObject *manager);
  bool initialize();
  bool finalize();
  void enterFinalizeApplet();

  mm::mtl::FixedVector<ManagerObject *, MANAGER_UNKNOWN_256> unknown08; // Inferred role: managers; original member name unknown.
};

static_assert(offsetof(ManagerRegister, unknown08) == 0x08, "");
static_assert(sizeof(ManagerRegister) == 0x810, "");

} // namespace fw
