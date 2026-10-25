#pragma once

namespace ml {

class Scn;

enum SCNPRIO_CB {};

class IScnRender {
public:
  virtual ~IScnRender() {}
  virtual void cbPreUpdate(Scn *scn, SCNPRIO_CB priority);
  virtual void cbManipuPickOn(Scn *scn, SCNPRIO_CB priority);
  virtual void cbManipuPickOff(Scn *scn, SCNPRIO_CB priority);
  virtual void cbManipuPickMove(Scn *scn, SCNPRIO_CB priority);
  virtual void cbRenderAfter(Scn *scn, SCNPRIO_CB priority);
};

} // namespace ml
