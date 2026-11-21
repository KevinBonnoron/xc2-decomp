#pragma once
#include "ml/work_cpu.h"

namespace ml {

struct CERR_STRUCT;

enum ERR_DECIDE {};

// Interface that WorkCpu::registErrorCB takes (_ZN2ml7WorkCpu13registErrorCBEPNS_8IErrorCBE). The only game functions that register or unregister
// one are the constructor (0x7100001d84) and destructor (0x7100001e5c) of apps::LauncherApp, which holds it as its second base at 0x1f0. That base's
// vtable (1.0.0: 0x7101171300 + 0xd0) is the destructor pair and errcbCallback (_ZThn496_N4apps11LauncherApp13errcbCallbackEN2ml5CPUIDEm), so the
// interface declares one function besides the destructor. The game has no vtable symbol for it.
class IErrorCB {
public:
  virtual ~IErrorCB() {}
  virtual void errcbCallback(CPUID cpu, unsigned long value) = 0;
};

// Inferred role: file error interface, the second base of DevFileTh at 0x1b8 (vtable 1.0.0: 0x71011ad0b8, whose second base vtable is the destructor pair,
// icbError and icbDecide, symbols _ZN2ml9DevFileTh8icbErrorEPNS_11CERR_STRUCTE and _ZN2ml9DevFileTh9icbDecideEPNS_11CERR_STRUCTENS_10ERR_DECIDEE);
// original type name unknown. It is not IErrorCB: that interface has errcbCallback in that slot, and nothing passes DevFileTh to registErrorCB.
class unknown201 {
public:
  virtual ~unknown201() {}
  virtual bool icbError(CERR_STRUCT *error) = 0;
  virtual void icbDecide(CERR_STRUCT *error, ERR_DECIDE decide) = 0;
};

} // namespace ml
