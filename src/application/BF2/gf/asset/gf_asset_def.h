#pragma once

namespace gf {

struct GF_ASSET_HANDLE;

static GF_ASSET_HANDLE *const INVALID_ASSET_HANDLE = reinterpret_cast<GF_ASSET_HANDLE *>(-1);

enum GfFileIdx {
  FILE_IDX_NONE = -1,
  FILE_IDX_MODEL = 0,
};

enum GfAssetType {
  ASSET_TYPE_BASE = 0,
};

} // namespace gf
