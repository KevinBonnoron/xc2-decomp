#pragma once
#include "framework/manager_object.h"
#include "ml/dev_graph_cb.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace mm {
namespace mtl {
class IAllocator;
}
} // namespace mm

namespace fw {

struct PadData {
  PadData()
      : hold(0), trigger(0), release(0), repeat(0), _10(), _28(), alxThreshold(0.2f), alyThreshold(0.2f), arxThreshold(0.2f), aryThreshold(0.2f),
        padNo(-1), _40(), _44() {}

  u32 hold;
  u32 trigger;
  u32 release;
  u32 repeat;
  u8 _10[0x28 - 0x10];
  u8 _28[0x2c - 0x28];
  f32 alxThreshold;
  f32 alyThreshold;
  f32 arxThreshold;
  f32 aryThreshold;
  int padNo;
  u8 _40[0x41 - 0x40];
  u8 _41[0x44 - 0x41];
  u8 _44[0x48 - 0x44];
};

static_assert(offsetof(PadData, alxThreshold) == 0x2c, "");
static_assert(offsetof(PadData, padNo) == 0x3c, "");
static_assert(sizeof(PadData) == 0x48, "");

class IPadFilter {
public:
  virtual u32 filterBtn(u32 button) = 0;
  virtual f32 filterALX(f32 x, f32 y) = 0;
  virtual f32 filterALY(f32 x, f32 y) = 0;
  virtual f32 filterARX(f32 x, f32 y) = 0;
  virtual f32 filterARY(f32 x, f32 y) = 0;
  virtual const char *getFilterName() const = 0;
  virtual ~IPadFilter();
};

class PadManager : public ManagerObject, public mm::mtl::PtrSingleton<PadManager>, public ml::DevGraphCB {
public:
  static const u32 PAD_MAX = 12;

  static PadData m_nullPad;

  ~PadManager();
  bool isInitialized() const override;
  const char *getName() const override;
  static int getPadMax();
  static void setRepeatTime(f32 time);
  static void setRepeatTimeFirst(f32 time);
  static void setCntTime(f32 time);
  static void setHoldTime(f32 time);
  static const PadData *getPadData(int padNo);
  static void setControlPadNo(int index, int padNo);
  static void setDebugPadNo(int index, int padNo);
  static const PadData *getControlPadData(int index);
  static const PadData *getDebugPadData(int index);
  static const char *getPadFilterName(int padNo);
  static void setEnable(int padNo, bool isEnable);
  static void enableDebugDraw(bool isEnable);
  static bool isDebugDraw();

  IPadFilter *filters[PAD_MAX];
  PadData pads[PAD_MAX];
  u8 _3e0[0x2b40 - 0x3e0];
  PadData controlPadData[PAD_MAX];
  PadData debugPadData[PAD_MAX];
  u8 _3200[0x35f0 - 0x3200];
  int controlPadNos[PAD_MAX];
  int debugPadNos[PAD_MAX];
  mm::mtl::BitFlag<32> enableFlags;
  bool debugDrawEnable;
  u8 _3655[0x3660 - 0x3655];
  f32 repeatTime;
  f32 repeatTimeFirst;
  f32 cntTime;
  f32 holdTime;
};

static_assert(offsetof(PadManager, filters) == 0x20, "");
static_assert(offsetof(PadManager, pads) == 0x80, "");
static_assert(offsetof(PadManager, controlPadData) == 0x2b40, "");
static_assert(offsetof(PadManager, debugPadData) == 0x2ea0, "");
static_assert(offsetof(PadManager, controlPadNos) == 0x35f0, "");
static_assert(offsetof(PadManager, enableFlags) == 0x3650, "");
static_assert(offsetof(PadManager, repeatTime) == 0x3660, "");

class alignas(8) PadRelay {
public:
  PadRelay();
  ~PadRelay();
  void bind(int padNo, int, mm::mtl::IAllocator *allocator);
  void unbind();
  void update();
  template <typename T, typename F> void bindAction(const char *name, T *object, F function);

  u8 _00[0x38 - 0x00];
};

static_assert(sizeof(PadRelay) == 0x38, "");

} // namespace fw
