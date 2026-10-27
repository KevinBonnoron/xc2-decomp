#pragma once
#include <stddef.h>

#include "ml/work_background.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

enum ERR_CALL {};

class ErrViewer : public mm::mtl::PtrSingleton<ErrViewer>, public IWorkBackground {
public:
  static bool standby();
  static void update();
  static bool isInitialized();
  static bool isErrorDisp();
  static void setup();
  static void upErrViewer();
  static void renderDRC();
  s32 createHandle() const;
  void callbackError(ERR_CALL call);
  void term();

  static s32 s_nHandle;

  u8 _10[0x258 - 0x10];
  s32 unknown258; // Inferred role: state; original member name unknown.
  u8 _25c[0x26b - 0x25c];
  bool unknown26b; // Inferred role: error displayed; original member name unknown.
  u8 _26c[0x278 - 0x26c];
  void *unknown278; // Inferred role: memory; original member name unknown.
};

static_assert(offsetof(ErrViewer, unknown258) == 0x258, "");
static_assert(offsetof(ErrViewer, unknown26b) == 0x26b, "");
static_assert(offsetof(ErrViewer, unknown278) == 0x278, "");

} // namespace ml
