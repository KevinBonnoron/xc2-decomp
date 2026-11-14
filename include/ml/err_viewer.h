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

const char *SYS_TAG_ERR();

// Name from the game symbol of ml::ErrViewer::reqError.
class ICBError {
public:
  virtual ~ICBError() {}
  // Inferred role: error callback, returns true while the error is handled; original name unknown.
  virtual bool unknown001(CERR_STRUCT *error) = 0;
};

class ErrViewer : public mm::mtl::PtrSingleton<ErrViewer>, public IWorkBackground {
public:
  // Name from the game symbol of mm::mtl::FixedList<ml::ErrViewer::ERRINFO*, 32>::erase.
  struct ERRINFO {
    u8 _00[0x04];
    ERR_CALL unknown04;     // Inferred role: callback call type; original member name unknown.
    ICBError *unknown08;    // Inferred role: callback; original member name unknown.
    CERR_STRUCT *unknown10; // Inferred role: error; original member name unknown.
    void *unknown18;        // Inferred role: memory; original member name unknown.
    u8 _20[0xac - 0x20];
    s32 unknownac; // Inferred role: remaining wait; original member name unknown.
    s32 unknownb0; // Inferred role: wait reset value; original member name unknown.
  };

  static void standby();
  static bool isValid(CERR_STRUCT *error);
  static void reqCancel(CERR_STRUCT *error);
  bool isExistError() const;
  static void update();
  ERRINFO *getError() const;
  void deleteError();
  static bool isInitialized();
  static bool isErrorDisp();
  virtual void setup();
  virtual void term();
  virtual void upErrViewer();
  void bkgHomeMenu(bool isEnter) override;
  void bkgHomeMenuDenied() override;
  static void renderDRC();
  static void fnRender();
  ErrViewer();
  ~ErrViewer() override;
  static ErrViewer *create();
  static void tail();
  static bool destroy();
  s32 createHandle() const;
  void callbackError(ERR_CALL call);

  static s32 s_nHandle;

  CriticalSection *unknown10;                  // Inferred role: critical section; original member name unknown.
  mm::mtl::FixedList<ERRINFO *, 32> unknown18; // Inferred role: errors; original member name unknown.
  s32 unknown258;                              // Inferred role: state; original member name unknown.
  u8 _25c[0x260 - 0x25c];
  long unknown260; // Inferred role: clock; original member name unknown.
  bool unknown268; // Inferred role: render registered; original member name unknown.
  bool unknown269; // Inferred role: destroy requested; original member name unknown.
  bool unknown26a; // Inferred role: terminated; original member name unknown.
  bool unknown26b; // Inferred role: error displayed; original member name unknown.
  bool unknown26c; // Inferred role: error cooldown; original member name unknown.
  u8 _26d[0x270 - 0x26d];
  s32 unknown270; // Inferred role: unknown, cleared by the constructor; original member name unknown.
  u8 _274[0x278 - 0x274];
  void *unknown278; // Inferred role: memory; original member name unknown.
};

static_assert(offsetof(ErrViewer, unknown10) == 0x10, "");
static_assert(offsetof(ErrViewer, unknown18) == 0x18, "");
static_assert(offsetof(ErrViewer, unknown258) == 0x258, "");
static_assert(offsetof(ErrViewer, unknown260) == 0x260, "");
static_assert(offsetof(ErrViewer, unknown269) == 0x269, "");
static_assert(offsetof(ErrViewer, unknown26a) == 0x26a, "");
static_assert(offsetof(ErrViewer, unknown26b) == 0x26b, "");
static_assert(offsetof(ErrViewer, unknown26c) == 0x26c, "");
static_assert(offsetof(ErrViewer, unknown278) == 0x278, "");

} // namespace ml
