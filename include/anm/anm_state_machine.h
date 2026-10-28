#pragma once
#include <stddef.h>

#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/map.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

class AdditiveInfo;
class AsmBlender;
class ResASM;
class ResStateData;
class Variable;
struct InterpolateInfo;
class AsmListener;
class AsmState;
class StringPtr;

enum StartFrameType {
  START_FRAME_TYPE_UNKNOWN_0,
  START_FRAME_TYPE_UNKNOWN_1,
};
enum InterpolateType {
  INTERPOLATE_TYPE_UNKNOWN_0,
  INTERPOLATE_TYPE_UNKNOWN_1,
};
enum InterpolateCurve {
  INTERPOLATE_CURVE_UNKNOWN_0,
  INTERPOLATE_CURVE_UNKNOWN_1,
};

class StateMachine {
public:
  StateMachine();
  ~StateMachine();
  void setup(const ResASM &resAsm, u32 layer, mm::mtl::IAllocator &allocator);
  AsmState *createState(const ResStateData &resStateData);
  void cleanup();
  void update(f32 deltaTime);
  void updateFrame(f32 deltaTime);
  void resetInterpolate();
  bool executeCmd(const char *command);
  bool setState(const char *state, StartFrameType startFrame = START_FRAME_TYPE_UNKNOWN_0);
  void clearState();
  bool resetState(const char *state, StartFrameType startFrame = START_FRAME_TYPE_UNKNOWN_0);
  const char *getStateName() const;
  u64 getAttribute(u32 index) const;
  bool isEnd() const;
  bool isLoop() const;
  void setLocalTime(f32 time);
  f32 getLocalTime() const;
  void setSpeed(f32 speed);
  f32 getSpeed() const;
  bool doEaseInAdditive(const char *state, f32 time, f32 weight = 1.0f, InterpolateType type = static_cast<InterpolateType>(1), InterpolateCurve curve = static_cast<InterpolateCurve>(0));
  bool doEaseOutAdditive(const char *state, f32 time, InterpolateType type = static_cast<InterpolateType>(1), InterpolateCurve curve = static_cast<InterpolateCurve>(0));
  void clearAdditiveState();
  bool setAdditiveStateWeight(const char *state, f32 weight);
  bool setAdditiveStateSpeed(const char *state, f32 speed);

  mm::mtl::IntrusivePtr<AsmState> unknown00;       // Inferred role: state; original member name unknown.
  mm::mtl::IntrusivePtr<AsmState> unknown08;       // Inferred role: next state; original member name unknown.
  mm::mtl::Map<StringPtr, AdditiveInfo> unknown10; // Inferred role: additive states by name; original member name unknown.
  const InterpolateInfo *unknown28;                // Inferred role: p interpolate info; original member name unknown.
  f32 unknown30;                                   // Inferred role: interpolate time; original member name unknown.
  u8 _34[0x38 - 0x34];
  mm::mtl::Map<StringPtr, mm::mtl::IntrusivePtr<AsmState>> unknown38; // Inferred role: states by name; original member name unknown.
  AsmListener *unknown50;                                             // Inferred role: listener; original member name unknown.
  AsmBlender *unknown58;                                              // Inferred role: p blender; original member name unknown.
  mm::mtl::Vector<Variable> *unknown60;                               // Inferred role: p variables; original member name unknown.
  mm::mtl::IAllocator *unknown68;                                     // Inferred role: allocator; original member name unknown.
};

static_assert(offsetof(StateMachine, unknown10) == 0x10, "");
static_assert(offsetof(StateMachine, unknown28) == 0x28, "");
static_assert(offsetof(StateMachine, unknown30) == 0x30, "");
static_assert(offsetof(StateMachine, unknown38) == 0x38, "");
static_assert(offsetof(StateMachine, unknown50) == 0x50, "");
static_assert(offsetof(StateMachine, unknown58) == 0x58, "");
static_assert(offsetof(StateMachine, unknown60) == 0x60, "");
static_assert(offsetof(StateMachine, unknown68) == 0x68, "");
static_assert(sizeof(StateMachine) == 0x70, "");

} // namespace anm
