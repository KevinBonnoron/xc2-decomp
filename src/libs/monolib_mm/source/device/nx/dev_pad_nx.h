#pragma once
#include <stddef.h>

#include "ml/dev_pad.h"
#include "mm_mtl/unique_ptr.h"
#include "nn/hid.h"
#include "types.h"

namespace ml {
class WorkObj;

class DevPadNx : public DevPad {
public:
  class Impl {
  public:
    // Inferred role: pad button flag; original type name unknown.
    enum unknown001 {
      unknown001_0 = 1 << 0,
      unknown001_1 = 1 << 1,
      unknown001_2 = 1 << 2,
      unknown001_3 = 1 << 3,
      unknown001_4 = 1 << 4,
      unknown001_5 = 1 << 5,
      unknown001_6 = 1 << 6,
      unknown001_7 = 1 << 7,
      unknown001_8 = 1 << 8,
      unknown001_9 = 1 << 9,
      unknown001_12 = 1 << 12,
      unknown001_13 = 1 << 13,
      unknown001_14 = 1 << 14,
      unknown001_15 = 1 << 15,
    };

    // Evidence for the size: Impl::Impl constructs two FixedArray<PadData, 4> at 0x3638 and 0x3c38.
    struct PadData {
      u32 unknown00;  // Inferred role: button flags; original member name unknown.
      f32 unknown04;  // Inferred role: left stick x; original member name unknown.
      f32 unknown08;  // Inferred role: left stick y; original member name unknown.
      f32 unknown0c;  // Inferred role: right stick x; original member name unknown.
      f32 unknown10;  // Inferred role: right stick y; original member name unknown.
      bool unknown14; // Inferred role: connected; original member name unknown.
      u8 _15[0x18 - 0x15];
      u32 unknown18; // Inferred role: pad style; original member name unknown.
      u8 _1c[0x60 - 0x1c];
      PadVibrationInfo unknown60; // Inferred role: vibration requested by playVibration; original member name unknown.
      f32 unknown78;              // Inferred role: vibration time; original member name unknown.
      bool unknown7c;             // Inferred role: vibration playing; original member name unknown.
      bool unknown7d;             // Inferred role: vibration initialized; original member name unknown.
      u8 _7e[0x110 - 0x7e];
      nn::hid::VibrationNodeConnection unknown110; // Inferred role: left vibration connection; original member name unknown.
      nn::hid::VibrationNodeConnection unknown148; // Inferred role: right vibration connection; original member name unknown.
    };

    // Inferred role: vibration data and player; original type name unknown.
    struct unknown002 {
      void *unknown00; // Inferred role: vibration data; original member name unknown.
      u64 unknown08;   // Inferred role: size of the vibration data; original member name unknown.
      s32 unknown10;   // Inferred role: vibration id; original member name unknown.
      u8 _14[0x18 - 0x14];
      nn::hid::VibrationPlayer unknown18; // Inferred role: player; original member name unknown.
    };

    void stateUpdate(f32 time);
    void updatePad(f32 time);
    void updateNpad();
    void updateDebugPad(PadData &data);
    void release();
    void stopVibration(PadData &data);
    nn::hid::VibrationPlayer *getVibPlayer(u32 id);

    u8 _0000[0x0020];
    s32 unknown20;    // Inferred role: state of the pad update, 2 updates the npads; original member name unknown.
    u32 unknown24[4]; // Inferred role: npad ids of the pads; original member name unknown.
    u8 _0034[0x38 - 0x34];
    unknown002 unknown38[64]; // Inferred role: vibration entries; original member name unknown.
    u8 _3638[0x4540 - 0x3638];
    s32 unknown4540; // Inferred role: pad index; original member name unknown.
    s32 unknown4544; // Inferred role: user select pad id; original member name unknown.
  };

  DevPadNx(const char *name, WorkObj *parent);
  static void setUserSelectControllerID(u32 id);
  bool isLocalConnect(int padNo) const override;
  u32 getLocalStyle(int padNo) const override;
  int getLocalUserSelectPadID() const override;
  u32 getLocalBtn(int padNo) const override;
  f32 getLocalALX(int padNo) const override;
  f32 getLocalALY(int padNo) const override;
  f32 getLocalARX(int padNo) const override;
  f32 getLocalARY(int padNo) const override;
  void updateDevice(f32 time) override;
  bool createDevice() override;
  void releaseDevice() override;

  mm::mtl::UniquePtr<Impl> unknown548; // Inferred role: implementation; original member name unknown.
};

static_assert(offsetof(DevPadNx::Impl::PadData, unknown04) == 0x04, "");
static_assert(offsetof(DevPadNx::Impl::PadData, unknown10) == 0x10, "");
static_assert(offsetof(DevPadNx::Impl::PadData, unknown14) == 0x14, "");
static_assert(offsetof(DevPadNx::Impl::PadData, unknown18) == 0x18, "");
static_assert(offsetof(DevPadNx::Impl::PadData, unknown60) == 0x60, "");
static_assert(offsetof(DevPadNx::Impl::PadData, unknown78) == 0x78, "");
static_assert(offsetof(DevPadNx::Impl::PadData, unknown7c) == 0x7c, "");
static_assert(offsetof(DevPadNx::Impl::PadData, unknown110) == 0x110, "");
static_assert(offsetof(DevPadNx::Impl::PadData, unknown148) == 0x148, "");
static_assert(sizeof(DevPadNx::Impl::PadData) == 0x180, "");
static_assert(offsetof(DevPadNx::Impl::unknown002, unknown18) == 0x18, "");
static_assert(sizeof(DevPadNx::Impl::unknown002) == 0xd8, "");
static_assert(offsetof(DevPadNx::Impl, unknown20) == 0x0020, "");
static_assert(offsetof(DevPadNx::Impl, unknown24) == 0x0024, "");
static_assert(offsetof(DevPadNx::Impl, unknown38) == 0x0038, "");
static_assert(offsetof(DevPadNx::Impl, unknown4540) == 0x4540, "");
static_assert(offsetof(DevPadNx::Impl, unknown4544) == 0x4544, "");
static_assert(offsetof(DevPadNx, unknown548) == 0x548, "");

} // namespace ml
