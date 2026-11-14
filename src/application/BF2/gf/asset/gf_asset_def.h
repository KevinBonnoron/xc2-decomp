#pragma once

namespace gf {

struct GF_ASSET_HANDLE;

static GF_ASSET_HANDLE *const unknown018 = reinterpret_cast<GF_ASSET_HANDLE *>(-1); // Inferred role: invalid asset handle; original name unknown.

enum GfFileIdx {
  FILE_IDX_UNKNOWN_FFFFFFFF = -1, // Inferred role: file idx none; original name unknown.
  FILE_IDX_UNKNOWN_0 = 0,         // Inferred role: file idx model; original name unknown.
};

enum GfAssetType {
  ASSET_TYPE_UNKNOWN_0 = 0,   // Inferred role: asset type base; original name unknown.
  ASSET_TYPE_UNKNOWN_3 = 3,   // Inferred role: asset type map; original name unknown.
  ASSET_TYPE_UNKNOWN_4 = 4,   // Inferred role: asset type pc; original name unknown.
  ASSET_TYPE_UNKNOWN_5 = 5,   // Inferred role: asset type pc motion; original name unknown.
  ASSET_TYPE_UNKNOWN_6 = 6,   // Inferred role: asset type blade; original name unknown.
  ASSET_TYPE_UNKNOWN_7 = 7,   // Inferred role: asset type blade motion; original name unknown.
  ASSET_TYPE_UNKNOWN_8 = 8,   // Inferred role: asset type weapon; original name unknown.
  ASSET_TYPE_UNKNOWN_9 = 9,   // Inferred role: asset type weapon effect; original name unknown.
  ASSET_TYPE_UNKNOWN_10 = 10, // Inferred role: asset type enemy; original name unknown.
  ASSET_TYPE_UNKNOWN_11 = 11, // Inferred role: asset type enemy motion; original name unknown.
  ASSET_TYPE_UNKNOWN_12 = 12, // Inferred role: asset type enemy arc; original name unknown.
  ASSET_TYPE_UNKNOWN_13 = 13, // Inferred role: asset type effect; original name unknown.
  ASSET_TYPE_UNKNOWN_14 = 14, // Inferred role: asset type field object; original name unknown.
  ASSET_TYPE_UNKNOWN_15 = 15, // Inferred role: asset type map object; original name unknown.
  ASSET_TYPE_UNKNOWN_16 = 16, // Inferred role: asset type weapon motion; original name unknown.
  ASSET_TYPE_UNKNOWN_17 = 17, // Inferred role: asset type option; original name unknown.
  ASSET_TYPE_UNKNOWN_18 = 18, // Inferred role: asset type temporary; original name unknown.
  ASSET_TYPE_UNKNOWN_19 = 19, // Inferred role: asset type se; original name unknown.
};

} // namespace gf
