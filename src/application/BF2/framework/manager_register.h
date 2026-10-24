#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"

namespace fw {

class ManagerObject;

class ManagerRegister : public mm::mtl::PtrSingleton<ManagerRegister> {
public:
  static const size_t MANAGER_MAX = 256;

  ManagerRegister();
  ~ManagerRegister();
  void regist(ManagerObject *manager);
  void remove(ManagerObject *manager);
  bool initialize();
  bool finalize();
  void enterFinalizeApplet();

  mm::mtl::FixedVector<ManagerObject *, MANAGER_MAX> unknown08; // Inferred role: managers; original member name unknown.
};

static_assert(offsetof(ManagerRegister, unknown08) == 0x08, "");
static_assert(sizeof(ManagerRegister) == 0x810, "");

} // namespace fw
