#pragma once
#include <stddef.h>

#include "ml/work_background.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class CriticalSection;
struct CERR_STRUCT;

enum ERR_CALL {};

class ErrViewer : public mm::mtl::PtrSingleton<ErrViewer>, public IWorkBackground {
public:
  // Inferred type: error entry; the original type name is unknown.
  struct unknown001 {
    u8 _00[0x08];
    void *unknown08;        // Inferred role: callback; original member name unknown.
    CERR_STRUCT *unknown10; // Inferred role: error; original member name unknown.
    void *unknown18;        // Inferred role: memory; original member name unknown.
  };

  static bool standby();
  static bool isValid(CERR_STRUCT *error);
  static void reqCancel(CERR_STRUCT *error);
  bool isExistError() const;
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

  CriticalSection *unknown10;                     // Inferred role: critical section; original member name unknown.
  mm::mtl::FixedList<unknown001 *, 32> unknown18; // Inferred role: errors; original member name unknown.
  s32 unknown258;                                 // Inferred role: state; original member name unknown.
  u8 _25c[0x26b - 0x25c];
  bool unknown26b; // Inferred role: error displayed; original member name unknown.
  u8 _26c[0x278 - 0x26c];
  void *unknown278; // Inferred role: memory; original member name unknown.
};

static_assert(offsetof(ErrViewer, unknown10) == 0x10, "");
static_assert(offsetof(ErrViewer, unknown18) == 0x18, "");
static_assert(offsetof(ErrViewer, unknown258) == 0x258, "");
static_assert(offsetof(ErrViewer, unknown26b) == 0x26b, "");
static_assert(offsetof(ErrViewer, unknown278) == 0x278, "");

} // namespace ml
