#pragma once

namespace ml {

class DevGraphCB {
public:
  virtual ~DevGraphCB();
  virtual void viBeginFrame();
  virtual void viBeforeDrawDone();
  virtual void viAfterDrawDone();
  virtual void viAfterSync();
  virtual void viAfterRenderCall();
};

} // namespace ml
