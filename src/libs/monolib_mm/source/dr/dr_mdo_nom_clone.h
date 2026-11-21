#pragma once

namespace ml {
class DrMdoCtlNom;

class DrMdoNomClone {
public:
  bool cloneMdlObj(DrMdoCtlNom *clone, const DrMdoCtlNom *source);
  DrMdoNomClone();
  ~DrMdoNomClone();
};

} // namespace ml
