#pragma once

namespace grlib {
class CGLibDecShader;
class CGLibDecShdExtTbl;
class CGLibVtxFetch;

class CGLibCtlShader {
public:
  static void setShader(CGLibDecShader &shader, CGLibVtxFetch &fetch);
  static void setShader(CGLibDecShdExtTbl &shader, CGLibVtxFetch &fetch);
};

} // namespace grlib
