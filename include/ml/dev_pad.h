#pragma once
#include <stddef.h>

#include "ml/dev_graph_cb.h"
#include "ml/work_obj.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

// Layout evidence: ml::DevPadNx::Impl::playVibration reads the id at 0x00, tests bits 0 and 1 of 0x04 and copies the four
// floats at 0x08; every caller (GfGameSalvage::playDiveVibration, GfMenuObjUtil::playVibration) stores 3 at 0x04 and 1.0f
// at 0x0c and 0x14.
// Store order evidence: with a constant amplitude the game keeps four separate 32-bit stores (stp w8,w8 twice) in
// StateUtil::playVibration and GfGameSalvage::playDiveVibration, and with a variable amplitude it keeps
// GfMenuObjUtil::playVibration's 0c, 14, 08, 10 order; only a body that stores the motors first and the id last gives
// both (any in-order spelling merges the constant stores into one 64-bit store).
struct PadVibrationInfo {
  explicit PadVibrationInfo(u32 id, f32 amplitude = 1.0f) {
    unknown04 = 3;
    unknown0c = 1.0f;
    unknown14 = 1.0f;
    unknown08 = amplitude;
    unknown10 = amplitude;
    unknown00 = id;
  }

  u32 unknown00; // Inferred role: vibration id; original member name unknown.
  u32 unknown04; // Inferred role: motors (bit 0 left, bit 1 right); original member name unknown.
  f32 unknown08; // Inferred role: left amplitude; original member name unknown.
  f32 unknown0c; // Inferred role: left frequency scale; original member name unknown.
  f32 unknown10; // Inferred role: right amplitude; original member name unknown.
  f32 unknown14; // Inferred role: right frequency scale; original member name unknown.
};

static_assert(sizeof(PadVibrationInfo) == 0x18, "");

// Inferred role: dev pad repeat; original type name unknown.
struct unknown034 {
  f32 unknown00; // Inferred role: time; original member name unknown.
  u8 _04[0xc - 0x4];
};

class DevPad : public WorkObj, public mm::mtl::PtrSingleton<DevPad>, public DevGraphCB {
public:
  ~DevPad() override;
  static void setWirelessPadMax(u32 max);
  static u32 getWirelessPadMax();
  static int getPadMax();
  static void setRepeatTime(float time);
  static bool isInitialized();
  static bool isConnectPad(int padNo);
  static u32 getStylePad(int padNo);
  static int getUserSelectPadID();
  static bool isDebugPad(int padNo);
  static u32 getBtn(int padNo);
  static u32 getDown(int padNo);
  static u32 getUp(int padNo);
  static u32 getRepeat(int padNo);
  static u32 getDbl(int padNo);
  static f32 getALX(int padNo, bool isLowCut);
  static f32 getLowAnalog();
  static f32 getALY(int padNo, bool isLowCut);
  static f32 getARX(int padNo, bool isLowCut);
  static f32 getARY(int padNo, bool isLowCut);
  static void playVibration(int padNo, const PadVibrationInfo &info);
  static void stopVibration(int padNo);
  static void loadVibration(u32 id, void *data, unsigned long size);
  static void setLowAnalog(f32 lowAnalog);
  static void initCaptureName(const char *name);
  static void capturePad(bool isCapture);
  static bool isCaprurePad();
  void updateLocal();
  void wkUpdate() override;
  bool wkStandbyLogin() override;
  bool wkStandbyLogout() override;
  virtual bool isLocalConnect(int padNo) const = 0;
  virtual u32 getLocalStyle(int padNo) const = 0;
  virtual int getLocalUserSelectPadID() const = 0;
  virtual u32 getLocalBtn(int padNo) const = 0;
  virtual f32 getLocalALX(int padNo) const = 0;
  virtual f32 getLocalALY(int padNo) const = 0;
  virtual f32 getLocalARX(int padNo) const = 0;
  virtual f32 getLocalARY(int padNo) const = 0;
  virtual void updateDevice(f32 time) = 0;
  virtual bool createDevice() = 0;
  virtual void releaseDevice() = 0;
  virtual void setCaptureName(const char *name);
  virtual void setCapture(bool isCapture);
  virtual bool isCapture() const;
  virtual void playLocalVibration(int padNo, const PadVibrationInfo &info);
  virtual void stopLocalVibration(int padNo);
  virtual void loadLocalVibration(u32 id, void *data, unsigned long size);
  void viBeginFrame() override;
  static void fnSubCpuUpdate(void *pad);

  static u32 s_nMaxWirelessPad;
  static int s_debugPadNo;

  u8 _1b8[0x1ec - 0x1b8];
  u32 unknown1ec[11]; // Inferred role: down; original member name unknown.
  u32 unknown218[11]; // Inferred role: up; original member name unknown.
  u32 unknown244[11]; // Inferred role: btn; original member name unknown.
  u32 unknown270[11]; // Inferred role: dbl; original member name unknown.
  u32 unknown29c[11]; // Inferred role: repeat; original member name unknown.
  u8 _2c8[0x4b0 - 0x2c8];
  unknown034 unknown4b0[11]; // Inferred role: repeats; original member name unknown.
  u8 _534[0x540 - 0x534];
  f32 unknown540; // Inferred role: low analog; original member name unknown.
};

static_assert(offsetof(DevPad, unknown1ec) == 0x1ec, "");
static_assert(offsetof(DevPad, unknown29c) == 0x29c, "");
static_assert(offsetof(DevPad, unknown4b0) == 0x4b0, "");
static_assert(offsetof(DevPad, unknown540) == 0x540, "");

} // namespace ml
