#pragma once

namespace ml {
struct MdsMdlVertexFmt;

class DrResMdoVertex {
public:
  bool getVertexInfo(int index, const MdsMdlVertexFmt **format, int *count);
};

} // namespace ml
