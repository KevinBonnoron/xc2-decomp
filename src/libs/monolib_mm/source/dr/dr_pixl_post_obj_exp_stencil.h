#pragma once

namespace ml {

class DrMan;

class DrPixlPostObjExpStencil {
public:
  DrPixlPostObjExpStencil(DrMan *drMan);
  ~DrPixlPostObjExpStencil();
  void render();
  void update();

  DrMan *unknown00; // Inferred role: driver manager; original member name unknown.
};

} // namespace ml
