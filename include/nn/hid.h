#pragma once
#include <stddef.h>

#include "nn/result.h"
#include "types.h"

// Controller support applet of the SDK. The type and function names come from the import of the game
// nn::hid::ShowControllerSupport(nn::hid::ControllerSupportResultInfo*, nn::hid::ControllerSupportArg const&);
// the layouts come from the stack layout of ml::ControllerApplet::showApplet. The member names are unknown.

namespace nn {
namespace util {

// Public SDK name, as in open-ead nnheaders include/nn/util/MathTypes.h (https://github.com/open-ead/nnheaders).
struct Color4u8Type {
  u8 unknown00[4]; // Inferred role: RGBA components; original member name unknown.
};

} // namespace util

namespace hid {

struct ControllerSupportArg {
  s8 unknown00;                    // Inferred role: minimum player count; original member name unknown.
  s8 unknown01;                    // Inferred role: maximum player count; original member name unknown.
  bool unknown02;                  // Inferred role: take over connection enable; original member name unknown.
  bool unknown03;                  // Inferred role: left justify enable; original member name unknown.
  bool unknown04;                  // Inferred role: permit joy dual enable; original member name unknown.
  bool unknown05;                  // Inferred role: single mode enable; original member name unknown.
  bool unknown06;                  // Inferred role: identification color enable; original member name unknown.
  util::Color4u8Type unknown07[4]; // Inferred role: identification colors; original member name unknown.
  bool unknown17;                  // Inferred role: explain text enable; original member name unknown.
  char unknown18[4][0x81];         // Inferred role: explain texts; original member name unknown.

  // Inferred role: sets the default arguments; original name unknown.
  void unknown001() {
    unknown00 = 0;
    unknown01 = 4;
    unknown02 = true;
    unknown03 = true;
    unknown04 = true;
    unknown05 = false;
    unknown06 = false;
    unknown17 = false;
  }
};

static_assert(offsetof(ControllerSupportArg, unknown07) == 0x07, "");
static_assert(offsetof(ControllerSupportArg, unknown17) == 0x17, "");
static_assert(offsetof(ControllerSupportArg, unknown18) == 0x18, "");

struct ControllerSupportResultInfo {
  s8 unknown00;  // Inferred role: player count; original member name unknown.
  u32 unknown04; // Inferred role: selected npad id; original member name unknown.
};

static_assert(offsetof(ControllerSupportResultInfo, unknown04) == 0x04, "");

Result ShowControllerSupport(ControllerSupportResultInfo *resultInfo, const ControllerSupportArg &arg);

// Debug pad state of the SDK. The type and function names come from the import of the game
// nn::hid::GetDebugPadState(nn::hid::DebugPadState*); the layout comes from the stack layout of
// ml::DevPadNx::Impl::updateDebugPad (attributes at 0x08, buttons at 0x0c, right stick at 0x10, left stick at 0x18).
// The member names are the nnheaders names (open-ead nnheaders include/nn/hid.h); mAttributes and mButtons are u32
// because the BitFlagSet types of nnheaders are not declared here.
struct AnalogStickState {
  s32 mX;
  s32 mY;
};

struct DebugPadState {
  u64 mSamplingNumber;
  u32 mAttributes;
  u32 mButtons;
  AnalogStickState mAnalogStickR;
  AnalogStickState mAnalogStickL;
};

static_assert(offsetof(DebugPadState, mAttributes) == 0x08, "");
static_assert(offsetof(DebugPadState, mButtons) == 0x0c, "");
static_assert(offsetof(DebugPadState, mAnalogStickR) == 0x10, "");
static_assert(offsetof(DebugPadState, mAnalogStickL) == 0x18, "");

void GetDebugPadState(DebugPadState *state);

// Vibration classes of the SDK. open-ead nnheaders include/nn/hid.h (https://github.com/open-ead/nnheaders) does not
// declare them: the class names and member functions come from the imports of the game (the __imp__ stubs of
// main_100.elf). The mangled names give the parameter types but not the return types, so every return type below
// is unverified: bool for the IsLoaded and IsPlaying predicates, void for the rest.
class VibrationDeviceHandle;
class VibrationModulation;
class VibrationNode;

// Size and members unknown. The repository has no size evidence for it, so no data member is declared.
class VibrationTarget {
public:
  VibrationTarget();
  ~VibrationTarget();
  void SetVibrationDeviceHandle(const VibrationDeviceHandle &);
};

// The sizes come from the layout of ml::DevPadNx::Impl (0xd8 per player entry starting at 0x18, 0x38 between the two
// connections of ml::DevPadNx::Impl::PadData); the members are unknown.
class VibrationPlayer {
public:
  VibrationPlayer();
  ~VibrationPlayer();
  void Load(const void *, size_t);
  void Play();
  void SetLoop(bool);
  bool IsLoaded() const;
  bool IsPlaying() const;
  void Stop();

  u8 unknown00[0xc0]; // Inferred role: player state; original member name unknown.
};

class VibrationNodeConnection {
public:
  VibrationNodeConnection();
  ~VibrationNodeConnection();
  void Connect(VibrationNode *, VibrationNode *);
  void SetModulation(const VibrationModulation &);
  void Disconnect();

  u8 unknown00[0x38]; // Inferred role: connection state; original member name unknown.
};

// Keyboard functions of the SDK. The names and parameter types come from the imports of the game,
// nn::hid::InitializeKeyboard() and nn::hid::GetKeyboardState(nn::hid::KeyboardState*). The layout of KeyboardState
// is unknown, so it is only forward declared.
struct KeyboardState;

void InitializeKeyboard();
void GetKeyboardState(KeyboardState *);

// Name from the import of the game nn::hid::InitializeTouchScreen(), called by ml::DevTouchNx::createDevice.
void InitializeTouchScreen();

} // namespace hid
} // namespace nn
