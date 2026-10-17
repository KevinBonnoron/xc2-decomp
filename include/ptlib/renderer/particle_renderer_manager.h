#pragma once

namespace ptlib {

struct DrDrawWorkInfoEF;
struct FxParam;

namespace emitter {
struct EmitterArg;
class EmitterManager;
class EmitterObj;
} // namespace emitter

namespace renderer {

class RenderManager {
public:
  static RenderManager *get();
  static RenderManager *&getPtr();
  void setDrInfo(const DrDrawWorkInfoEF *info);
  void setEmitterDraw(emitter::EmitterObj *emitter, emitter::EmitterArg *arg);
  void fxcore_setup_target();
  void draw(emitter::EmitterManager &emitterManager, FxParam &fxParam, int priority, int isTranslucent);
};

} // namespace renderer
} // namespace ptlib
