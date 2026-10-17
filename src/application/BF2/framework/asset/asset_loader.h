#pragma once
#include "ml/file_res_th.h"

namespace fw {

class AssetLoader : public ml::FileResTh {
public:
  AssetLoader();
  ~AssetLoader() override;
};

} // namespace fw
