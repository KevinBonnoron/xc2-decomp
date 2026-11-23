#pragma once

namespace ml {

class DrMan;

class DrPixlPostObjExpStencil {
public:
  DrPixlPostObjExpStencil(DrMan *drMan);
  ~DrPixlPostObjExpStencil();
  void render();
  void update();

  DrMan *m_drMan; // Inferred role: driver manager; original member name unknown.
};

} // namespace ml
