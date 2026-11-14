#pragma once
#include <stddef.h>

#include "ml/win_proc.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class IException;
class WorkObj;

enum EXCEPTION_PRIO {
  EXCEPTION_PRIO_UNKNOWN_5 = 5, // Inferred role: priority of a new ProcException before setInfo; original name unknown.
};

class ProcException : public WinProc, public mm::mtl::PtrSingleton<ProcException> {
public:
  ProcException(const char *name, WorkObj *parent);
  ~ProcException() override;
  void setInfo(EXCEPTION_PRIO prio);
  void setInfo(u32 wid, const wchar_t *message);
  bool isCheckOK() const;
  void forceShutdown();
  static ProcException *create(WorkObj *parent, const wchar_t *message, EXCEPTION_PRIO prio);
  static void renderWide(const wchar_t *message);
  static void fatal(const wchar_t *message);
  static void setMessage(const wchar_t *message);
  static void entry(IException *exception);
  static void remove(IException *exception);
  void wkRender() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;

  u32 unknown1f8;            // Inferred role: work id; original member name unknown.
  const wchar_t *unknown200; // Inferred role: message; original member name unknown.
  f32 unknown208;            // Inferred role: fade speed; original member name unknown.
  f32 unknown20c;            // Inferred role: fade alpha; original member name unknown.
  s32 unknown210;            // Inferred role: fade state (0 in, 1 shown, 2 out); original member name unknown.
  u8 unknown214[0x10];       // Inferred role: bytes cleared by the constructor, read by no function of the class; original members unknown.
  bool unknown224;           // Inferred role: force shutdown; original member name unknown.
  EXCEPTION_PRIO m_info;
};

static_assert(offsetof(ProcException, unknown1f8) == 0x1f8, "");
static_assert(offsetof(ProcException, unknown200) == 0x200, "");
static_assert(offsetof(ProcException, unknown208) == 0x208, "");
static_assert(offsetof(ProcException, unknown20c) == 0x20c, "");
static_assert(offsetof(ProcException, unknown210) == 0x210, "");
static_assert(offsetof(ProcException, unknown214) == 0x214, "");
static_assert(offsetof(ProcException, unknown224) == 0x224, "");
static_assert(offsetof(ProcException, m_info) == 0x228, "");
static_assert(sizeof(ProcException) == 0x230, "");

} // namespace ml
