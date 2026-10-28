#pragma once
#include <stddef.h>

#include "types.h"

namespace anm {

struct Job {
  Job(const char *typeName, u32 size, u32 queueIndex) : unknown00(typeName), unknown08(size), m_funcIndex(queueIndex) {}

  const char *unknown00; // Inferred role: type name; original member name unknown.
  u32 unknown08;         // Inferred role: job size; original member name unknown.
  u32 m_funcIndex;
};

static_assert(offsetof(Job, unknown08) == 0x08, "");
static_assert(offsetof(Job, m_funcIndex) == 0x0c, "");
static_assert(sizeof(Job) == 0x10, "");

} // namespace anm
