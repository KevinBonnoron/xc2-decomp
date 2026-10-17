#pragma once
#include "types.h"

namespace anm {

class Binding;
class Control;
class ResASM;
struct QsTransform;
struct ResState;

struct Appendix {
  const char *name;
  const void *data;
};

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
  static const Appendix *findAppendix(const ResASM &resAsm, const char *name);
};

} // namespace anm
