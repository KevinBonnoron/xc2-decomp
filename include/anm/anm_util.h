#pragma once
#include "anm/anm_string_ptr.h"
#include "mm_mtl/set.h"
#include "types.h"

namespace anm {

class Binding;
class Control;
class ExtraTruckSlot;
class Pose;
class ResASM;
struct QsTransform;
struct ResAppendix;
struct ResState;

enum PlayMode {
  PLAY_MODE_LOOP,
  PLAY_MODE_ONCE,
};

enum Layer {
  LAYER_INVALID = -1,
  LAYER_BASE,
  LAYER_UPPERBODY,
  LAYER_HEAD,
  LAYER_EYE,
  LAYER_MOUTH,
  LAYER_BROW,
  LAYER_EXTRA,
  LAYER_NUM,
};

class Util {
public:
  static const char *getName(const Binding &binding);
  static s32 getAnimationType(const Binding &binding);
  static PlayMode getPlayMode(const Binding &binding);
  static u8 getBlendHint(const Binding &binding);
  static u32 getFrameCount(const Binding &binding);
  static f32 getPlayBackTime(const Binding &binding);
  static bool hasLocomotion(const Binding &binding);
  static f32 getFps(const Binding &binding);
  static f32 getInvFps(const Binding &binding);
  static f32 calcLocalTime(f32 time, f32 start, f32 end, PlayMode playMode);
  static void setKeyFrame(Control &control, f32 frame);
  static bool getAsmPlaybackTime(const ResASM &resAsm, const char *state, u32 index, f32 *time);
  static const Binding *getAsmBinding(const ResASM &resAsm, const char *state, u32 index);
  static bool getAsmLocomotionReference(const ResASM &resAsm, const char *state, f32 time, u32 index, QsTransform *transform);
  static bool getAsmLocomotionDeltaReference(const ResASM &resAsm, const char *state, f32 startTime, f32 endTime, u32 index, QsTransform *transform);
  static const char *getLayerName(Layer layer);
  static Layer getLayer(const char *name);
  static const ResState *getStateResource(const ResASM &resAsm, const char *name);
  static const ResState *getSimpleStateResource(const ResASM &resAsm, const char *name);
  static const ResState *getComplexStateResource(const ResASM &resAsm, const char *name);
  static const ResState *getFrozenStateResource(const ResASM &resAsm, const char *name);
  static const ResAppendix *findAppendix(const ResASM &resAsm, const char *name);
  static void samplePoseSmartFromControl(Control *control, Pose *pose, bool localSpace);
  static void clampLimitExtraTruck(const ExtraTruckSlot &slot, u32 count, f32 *values);
  static void queryState(u32 mask, const ResASM &resAsm, mm::mtl::Set<StringPtr> *pDst);
  static void queryCmd(u32 mask, const ResASM &resAsm, mm::mtl::Set<StringPtr> *pDst);
  static void queryCmdFromStateSimple(u32 mask, const ResASM &resAsm, const StringPtr &state, mm::mtl::Set<StringPtr> *pDst);
  static bool queryStateAutoTrans(u32 mask, const ResASM &resAsm, const StringPtr &state, StringPtr *autoTrans);
  static void queryStateFromStateCmd(u32 mask, const ResASM &resAsm, const StringPtr &state, const StringPtr &cmd, mm::mtl::Set<StringPtr> *pDst);
  static void queryVariableFloat(const ResASM &resAsm, mm::mtl::Set<StringPtr> *pDst);
  static void queryVariableInt(const ResASM &resAsm, mm::mtl::Set<StringPtr> *pDst);
};

} // namespace anm
