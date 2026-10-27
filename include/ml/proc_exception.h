#pragma once
#include <stddef.h>

#include "ml/win_proc.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

enum EXCEPTION_PRIO {};

class ProcException : public WinProc, public mm::mtl::PtrSingleton<ProcException> {
public:
  void setInfo(EXCEPTION_PRIO prio);
  void setInfo(u32 wid, const wchar_t *message);
  bool isCheckOK() const;
  void forceShutdown();
  static void renderWide(const wchar_t *message);
  static void fatal(const wchar_t *message);
  static void setMessage(const wchar_t *message);

  u32 unknown1f8;            // Inferred role: work id; original member name unknown.
  const wchar_t *unknown200; // Inferred role: message; original member name unknown.
  f32 unknown208;            // Inferred role: fade speed; original member name unknown.
  f32 unknown20c;            // Inferred role: fade alpha; original member name unknown.
  u8 _210[0x224 - 0x210];
  bool unknown224;           // Inferred role: force shutdown; original member name unknown.
  EXCEPTION_PRIO unknown228; // Inferred role: priority; original member name unknown.
};

static_assert(offsetof(ProcException, unknown1f8) == 0x1f8, "");
static_assert(offsetof(ProcException, unknown200) == 0x200, "");
static_assert(offsetof(ProcException, unknown208) == 0x208, "");
static_assert(offsetof(ProcException, unknown20c) == 0x20c, "");
static_assert(offsetof(ProcException, unknown224) == 0x224, "");
static_assert(offsetof(ProcException, unknown228) == 0x228, "");

} // namespace ml
