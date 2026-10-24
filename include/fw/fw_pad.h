#pragma once
#include "framework/manager_object.h"
#include "ml/dev_graph_cb.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace mm {
namespace mtl {
class IAllocator;
}
} // namespace mm

namespace ml {
struct PadVibrationInfo;
} // namespace ml

namespace fw {

struct PadData {
  PadData() : unknown00(0), unknown04(0), unknown08(0), unknown0c(0), _10(), _28(), unknown2c(0.2f), unknown30(0.2f), unknown34(0.2f), unknown38(0.2f), unknown3c(-1), unknown40(), unknown44() {}

  u32 unknown00; // Inferred role: hold; original member name unknown.
  u32 unknown04; // Inferred role: trigger; original member name unknown.
  u32 unknown08; // Inferred role: release; original member name unknown.
  u32 unknown0c; // Inferred role: repeat; original member name unknown.
  u8 _10[0x28 - 0x10];
  u8 _28[0x2c - 0x28];
  f32 unknown2c;  // Inferred role: arx threshold; original member name unknown.
  f32 unknown30;  // Inferred role: ary threshold; original member name unknown.
  f32 unknown34;  // Inferred role: alx threshold; original member name unknown.
  f32 unknown38;  // Inferred role: aly threshold; original member name unknown.
  int unknown3c;  // Inferred role: pad no; original member name unknown.
  bool unknown40; // Inferred role: connected; original member name unknown.
  u32 unknown44;  // Inferred role: style; original member name unknown.
};

static_assert(offsetof(PadData, unknown2c) == 0x2c, "");
static_assert(offsetof(PadData, unknown40) == 0x40, "");
static_assert(offsetof(PadData, unknown3c) == 0x3c, "");
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

class IPadListener;

struct PadConfigData {
  u8 _00[0x54 - 0x00];
};

static_assert(sizeof(PadConfigData) == 0x54, "");

class PadManager : public ManagerObject, public mm::mtl::PtrSingleton<PadManager>, public ml::DevGraphCB {
public:
  static const u32 PAD_MAX = 12;

  static const u32 BUTTON_MAX = 32;
  static const u32 LISTENER_MAX = 16;

  struct PadWork {
    f32 unknown00; // Inferred role: repeat time; original member name unknown.
    f32 unknown04; // Inferred role: hold time; original member name unknown.
    u32 unknown08; // Inferred role: repeat; original member name unknown.
  };

  typedef mm::mtl::FixedArray<mm::mtl::FixedArray<PadWork, BUTTON_MAX>, PAD_MAX> PadWorkArray;

  static PadData m_nullPad;

  ~PadManager();
  bool finalize() override;
  static void stopVibration();
  static void setFilter(int padNo, IPadFilter *filter);
  bool isInitialized() const override;
  const char *getName() const override;
  static int getPadMax();
  u32 updateRepeat(int padNo, const PadData &pad, PadWorkArray &works, f32 deltaTime);
  u32 updateCnt(int padNo, const PadData &pad, PadWorkArray &works, f32 deltaTime);
  u32 updateHold(int padNo, const PadData &pad, PadWorkArray &works, f32 deltaTime);
  static void setRepeatTime(f32 time);
  static void setRepeatTimeFirst(f32 time);
  static void setCntTime(f32 time);
  static void setHoldTime(f32 time);
  static const PadData *getPadData(int padNo);
  static void setControlPadNo(int index, int padNo);
  static void setDebugPadNo(int index, int padNo);
  static const PadData *getControlPadData(int index);
  static const PadData *getDebugPadData(int index);
  static void playVibration(const ml::PadVibrationInfo &info);
  static const char *getPadFilterName(int padNo);
  static void setARXThreshold(int padNo, f32 threshold);
  static void setARYThreshold(int padNo, f32 threshold);
  static void setALXThreshold(int padNo, f32 threshold);
  static void setALYThreshold(int padNo, f32 threshold);
  static void setEnable(int padNo, bool isEnable);
  static void enableDebugDraw(bool isEnable);
  static bool isDebugDraw();
  static void setConfigData(int padNo, const PadConfigData &data);

  IPadFilter *unknown20[PAD_MAX]; // Inferred role: filters; original member name unknown.
  PadData unknown80[PAD_MAX];     // Inferred role: pads; original member name unknown.
  u8 _3e0[0x2b40 - 0x3e0];
  PadData unknown2b40[PAD_MAX];       // Inferred role: control pad data; original member name unknown.
  PadData unknown2ea0[PAD_MAX];       // Inferred role: debug pad data; original member name unknown.
  PadConfigData unknown3200[PAD_MAX]; // Inferred role: configs; original member name unknown.
  int unknown35f0[PAD_MAX];           // Inferred role: control pad nos; original member name unknown.
  int unknown3620[PAD_MAX];           // Inferred role: debug pad nos; original member name unknown.
  mm::mtl::BitFlag<32> unknown3650;   // Inferred role: enable flags; original member name unknown.
  bool unknown3654;                   // Inferred role: debug draw enable; original member name unknown.
  u8 _3655[0x3660 - 0x3655];
  f32 unknown3660; // Inferred role: repeat time; original member name unknown.
  f32 unknown3664; // Inferred role: repeat time first; original member name unknown.
  f32 unknown3668; // Inferred role: cnt time; original member name unknown.
  f32 unknown366c; // Inferred role: hold time; original member name unknown.
  int unknown3670; // Inferred role: user select pad no; original member name unknown.
  u8 _3674[0x3678 - 0x3674];
  mm::mtl::FixedQueue<IPadListener *, LISTENER_MAX> unknown3678; // Inferred role: listeners; original member name unknown.
};

static_assert(offsetof(PadManager, unknown20) == 0x20, "");
static_assert(offsetof(PadManager, unknown80) == 0x80, "");
static_assert(offsetof(PadManager, unknown2b40) == 0x2b40, "");
static_assert(offsetof(PadManager, unknown2ea0) == 0x2ea0, "");
static_assert(offsetof(PadManager, unknown35f0) == 0x35f0, "");
static_assert(offsetof(PadManager, unknown3650) == 0x3650, "");
static_assert(offsetof(PadManager, unknown3200) == 0x3200, "");
static_assert(offsetof(PadManager, unknown3660) == 0x3660, "");
static_assert(offsetof(PadManager, unknown3678) == 0x3678, "");

class alignas(8) PadRelay {
public:
  PadRelay();
  ~PadRelay();
  void bind(int padNo, int, mm::mtl::IAllocator *allocator);
  void unbind();
  void update();
  template <typename T, typename F> void bindAction(const char *name, T *object, F function);
  template <typename T, typename F> void bindAxis(const char *name, T *object, F function);

  u8 _00[0x38 - 0x00];
};

static_assert(sizeof(PadRelay) == 0x38, "");

} // namespace fw
