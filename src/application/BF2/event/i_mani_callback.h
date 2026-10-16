#pragma once

namespace event {

class IManiCallback {
public:
  struct StartParam;
  struct SetParam;
  struct RenderParam;

  virtual ~IManiCallback() {}
  virtual bool OnManiStartPos(StartParam &param) { return false; }
  virtual void OnManiSetPos(SetParam &param) {}
  virtual bool OnManiStartRot(StartParam &param) { return false; }
  virtual void OnManiSetRot(SetParam &param) {}
  virtual bool OnManiStartTar(StartParam &param) { return false; }
  virtual void OnManiSetTar(SetParam &param) {}
  virtual void OnManiRender(RenderParam &param) {}
};

} // namespace event
