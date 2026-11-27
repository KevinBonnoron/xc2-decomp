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

// Public SDK type, as in open-ead nnheaders include/nn/util/util_BitFlagSet.h. nnheaders selects the storage with
// <type_traits>; this reconstruction names the storage of the two widths the game imports instead, so the header stays
// free of standard library includes. The storage stays uninitialized: updateNpad declares an Npad state on the stack
// and passes it to GetNpadState without zeroing it first (0x7100725a38-0x7100725a70), which a default member
// initializer would turn into extra stores.
// Inferred name; the selector only exists because this header does not include <type_traits>.
template <int N> struct BitFlagSetStorage;
template <> struct BitFlagSetStorage<32> {
  using Type = u32;
};
template <> struct BitFlagSetStorage<64> {
  using Type = u64;
};

template <int N, typename Tag> struct BitFlagSet {
  using Storage = typename BitFlagSetStorage<N>::Type;

  // The index is taken modulo the storage width, as in nnheaders.
  bool Test(int index) const { return (unknown00 & (static_cast<Storage>(1) << (index % N))) != 0; }

  BitFlagSet &Set(int index, bool isOn = true) {
    Storage mask = static_cast<Storage>(1) << (index % N);
    unknown00 = isOn ? unknown00 | mask : unknown00 & ~mask;
    return *this;
  }

  bool IsAnyOn() const { return unknown00 != 0; }

  BitFlagSet operator&(const BitFlagSet &other) const { return BitFlagSet{static_cast<Storage>(unknown00 & other.unknown00)}; }
  BitFlagSet operator|(const BitFlagSet &other) const { return BitFlagSet{static_cast<Storage>(unknown00 | other.unknown00)}; }
  bool operator==(const BitFlagSet &other) const { return unknown00 == other.unknown00; }
  bool operator!=(const BitFlagSet &other) const { return unknown00 != other.unknown00; }

  Storage unknown00; // Inferred role: flag bits; original member name unknown.
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
// The member names are the nnheaders names (open-ead nnheaders include/nn/hid.h); mAttributes and mButtons stay u32
// because the game tests them with plain 32-bit masks and never uses the flag-set API.
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

// Npad state of the SDK. The names come from open-ead nnheaders include/nn/hid.h. The game gives the button and stick
// offsets and the style bits: ml::DevPadNx::Impl::updateTpad reads the buttons with one 64-bit load at 0x08
// (0x7100725f90) and the two s32 stick pairs at 0x10 and 0x18 (0x7100726158-0x71007261a4); updateNpad keeps the state
// at sp+0x10 and the pad id at sp+0x3c (0x7100725a38-0x7100725ad0), which leaves 0x28 for the state, and tests style
// bits 0, 1 and 2 for the full-key, handheld and joy-dual states (0x7100725718-0x7100725724). The sampling number at
// 0x00 and the attribute set at 0x20 follow the nnheaders order; the game never reads them. Only the button bits the
// game tests (0 to 27) and the three styles it uses are declared.
enum class NpadButton {
  A = 0,
  B = 1,
  X = 2,
  Y = 3,
  StickL = 4,
  StickR = 5,
  L = 6,
  R = 7,
  ZL = 8,
  ZR = 9,
  Plus = 10,
  Minus = 11,
  Left = 12,
  Up = 13,
  Right = 14,
  Down = 15,
  StickLLeft = 16,
  StickLUp = 17,
  StickLRight = 18,
  StickLDown = 19,
  StickRLeft = 20,
  StickRUp = 21,
  StickRRight = 22,
  StickRDown = 23,
  LeftSL = 24,
  LeftSR = 25,
  RightSL = 26,
  RightSR = 27,
};

enum class NpadAttribute {
  IsConnected = 0,
  IsWired = 1,
  IsLeftConnected = 2,
  IsLeftWired = 3,
  IsRightConnected = 4,
  IsRightWired = 5,
};

enum class NpadStyleTag {
  NpadStyleFullKey = 0,
  NpadStyleHandheld = 1,
  NpadStyleJoyDual = 2,
};

enum class NpadJoyHoldType { Vertical, Horizontal };

using NpadButtonSet = util::BitFlagSet<64, NpadButton>;
using NpadAttributeSet = util::BitFlagSet<32, NpadAttribute>;
using NpadStyleSet = util::BitFlagSet<32, NpadStyleTag>;

struct NpadBaseState {
  u64 mSamplingNumber;
  NpadButtonSet mButtons;
  AnalogStickState mAnalogStickL;
  AnalogStickState mAnalogStickR;
  NpadAttributeSet mAttributes;
};

struct NpadFullKeyState : NpadBaseState {};
struct NpadHandheldState : NpadBaseState {};
struct NpadJoyDualState : NpadBaseState {};

static_assert(offsetof(NpadBaseState, mButtons) == 0x08, "");
static_assert(offsetof(NpadBaseState, mAnalogStickL) == 0x10, "");
static_assert(offsetof(NpadBaseState, mAnalogStickR) == 0x18, "");
static_assert(offsetof(NpadBaseState, mAttributes) == 0x20, "");
static_assert(sizeof(NpadBaseState) == 0x28, "");

void InitializeNpad();
void SetSupportedNpadIdType(const u32 *ids, u64 count);
void SetSupportedNpadStyleSet(NpadStyleSet styleSet);
// The mangled name gives no return type: the game tests the returned set bit by bit
// (0x7100725718-0x7100725724), so the return is NpadStyleSet.
NpadStyleSet GetNpadStyleSet(const u32 &id);
void GetNpadState(NpadFullKeyState *state, const u32 &id);
void GetNpadState(NpadHandheldState *state, const u32 &id);
void GetNpadState(NpadJoyDualState *state, const u32 &id);

// Not in nnheaders: the name comes from the import of the game and the parameter type from its mangled name. The game
// passes 1 (Horizontal) when it initializes the pads (0x7100725094).
void SetNpadJoyHoldType(NpadJoyHoldType holdType);

// Vibration classes of the SDK. open-ead nnheaders include/nn/hid.h (https://github.com/open-ead/nnheaders) declares
// only some of them: the class names and member functions come from the imports of the game (the __imp__ stubs of
// main_100.elf). The mangled names give the parameter types but not the return types, so every return type below
// is unverified: bool for the IsLoaded and IsPlaying predicates, void for the rest except GetVibrationDeviceHandles,
// which returns the handle count.

// Public SDK name and size, as in nnheaders: the handle is one 32-bit word. initializeVibration steps through the two
// handles by four bytes (0x7100725c30), copies a handle whole (0x7100725bec-0x7100725bf8) and never reads its
// subfields, so only that view is declared.
struct VibrationDeviceHandle {
  u32 typeValue;
};

// Public SDK names. The game fills the eight bytes with GetVibrationDeviceInfo and compares the second word with 1
// (left) and 2 (right) to pick the vibration target (0x7100725bec-0x7100725c1c); the device type is not read.
enum class VibrationDeviceType { Unknown, LinearResonantActuator, GcErm, Erm };
enum class VibrationDevicePosition { None, Left, Right };

struct VibrationDeviceInfo {
  VibrationDeviceType mDeviceType;
  VibrationDevicePosition mPosition;
};

static_assert(sizeof(VibrationDeviceHandle) == 0x04, "");
static_assert(sizeof(VibrationDeviceInfo) == 0x08, "");

// playVibration builds the 16-byte argument on the stack (0x7100726ba8-0x7100726bbc) and passes it to
// VibrationNodeConnection::SetModulation (0x7100726bfc and 0x7100726c18); the member names are unknown.
struct VibrationModulation {
  f32 unknown00[4];
};

static_assert(sizeof(VibrationModulation) == 0x10, "");

// Base of VibrationPlayer and VibrationTarget: playVibration passes both to VibrationNodeConnection::Connect without
// adjusting the pointer (0x7100726b88-0x7100726ba4), so the VibrationNode subobject starts at offset 0. No data member
// is evidenced, and the measured sizes below include it as an empty base. The static DefaultVibrationSampleInterval
// import is left out because its type is unknown (initializeVidThread loads eight bytes, 0x7100724fdc).
class VibrationNode {
public:
  static void Update();
};

// The size is the distance between the two targets of ml::DevPadNx::Impl::PadData: FixedArray<PadData, 4>'s
// constructor fills them at 0x80 and 0xc8 and the next member starts at 0x110 (0x710073b950-0x710073b97c).
class VibrationTarget : public VibrationNode {
public:
  VibrationTarget();
  ~VibrationTarget();
  void SetVibrationDeviceHandle(const VibrationDeviceHandle &);

  u8 unknown00[0x48]; // Inferred role: target state; original member name unknown.
};

static_assert(sizeof(VibrationTarget) == 0x48, "");

// The sizes come from the layout of ml::DevPadNx::Impl (0xd8 per player entry starting at 0x18, 0x38 between the two
// connections of ml::DevPadNx::Impl::PadData); the members are unknown.
class VibrationPlayer : public VibrationNode {
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

static_assert(sizeof(VibrationPlayer) == 0xc0, "");

class VibrationNodeConnection {
public:
  VibrationNodeConnection();
  ~VibrationNodeConnection();
  void Connect(VibrationNode *, VibrationNode *);
  void SetModulation(const VibrationModulation &);
  void Disconnect();

  u8 unknown00[0x38]; // Inferred role: connection state; original member name unknown.
};

static_assert(sizeof(VibrationNodeConnection) == 0x38, "");

// Not in nnheaders: the names come from the imports of the game and the parameter types from the mangled names.
// GetVibrationDeviceHandles returns the handle count, which initializeVibration stores and compares with 1
// (0x7100725ba4-0x7100725bb8).
s32 GetVibrationDeviceHandles(VibrationDeviceHandle *handles, s32 count, const u32 &id, NpadStyleSet styleSet);
void InitializeVibrationDevice(const VibrationDeviceHandle &handle);
void GetVibrationDeviceInfo(VibrationDeviceInfo *info, const VibrationDeviceHandle &handle);

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
