#pragma once
#include <stddef.h>

#include "types.h"

typedef u8 NVNboolean;

struct NVNcommandBuffer;
struct NVNmemoryPool;
struct NVNtexture;

struct NVNdevice {
  u8 reserved[0x3000];
};

struct NVNtextureBuilder {
  u8 reserved[0x80];
};

struct NVNtextureView {
  u8 reserved[0x28];
};

struct NVNchannelMaskState {
  u8 reserved[0x4];
};

struct NVNpolygonState {
  u8 reserved[0x4];
};

enum NVNtiledCacheAction {};

enum NVNtextureTarget {
  NVN_TEXTURE_TARGET_1D,
  NVN_TEXTURE_TARGET_2D,
  NVN_TEXTURE_TARGET_3D,
  NVN_TEXTURE_TARGET_1D_ARRAY,
  NVN_TEXTURE_TARGET_2D_ARRAY,
  NVN_TEXTURE_TARGET_2D_MULTISAMPLE,
  NVN_TEXTURE_TARGET_2D_MULTISAMPLE_ARRAY,
  NVN_TEXTURE_TARGET_RECTANGLE,
  NVN_TEXTURE_TARGET_CUBEMAP,
  NVN_TEXTURE_TARGET_CUBEMAP_ARRAY,
  NVN_TEXTURE_TARGET_BUFFER,
};

enum NVNformat {};

enum NVNtextureFlags {
  NVN_TEXTURE_FLAGS_IMAGE = 0x4,
  NVN_TEXTURE_FLAGS_COMPRESSIBLE = 0x8,
};

typedef void (*PFNNVNCOMMANDBUFFERSETBLENDCOLORPROC)(NVNcommandBuffer *cmdBuf, const float *blendColor);
typedef void (*PFNNVNCOMMANDBUFFERBINDCHANNELMASKSTATEPROC)(NVNcommandBuffer *cmdBuf, const NVNchannelMaskState *channelMask);
typedef void (*PFNNVNCOMMANDBUFFERBINDPOLYGONSTATEPROC)(NVNcommandBuffer *cmdBuf, const NVNpolygonState *polygon);
typedef void (*PFNNVNCOMMANDBUFFERSETRENDERTARGETSPROC)(NVNcommandBuffer *cmdBuf, int numColors, const NVNtexture *const *colors,
                                                        const NVNtextureView *const *colorViews, const NVNtexture *depthStencil,
                                                        const NVNtextureView *depthStencilView);
typedef void (*PFNNVNCOMMANDBUFFERSETVIEWPORTPROC)(NVNcommandBuffer *cmdBuf, int x, int y, int w, int h);
typedef void (*PFNNVNCOMMANDBUFFERSETSCISSORPROC)(NVNcommandBuffer *cmdBuf, int x, int y, int w, int h);
typedef void (*PFNNVNCOMMANDBUFFERSETLINEWIDTHPROC)(NVNcommandBuffer *cmdBuf, float width);
typedef void (*PFNNVNCOMMANDBUFFERSETRASTERIZERDISCARDPROC)(NVNcommandBuffer *cmdBuf, NVNboolean discard);
typedef void (*PFNNVNCOMMANDBUFFERSETCONSERVATIVERASTERENABLEPROC)(NVNcommandBuffer *cmdBuf, NVNboolean enable);
typedef void (*PFNNVNCOMMANDBUFFERSETCONSERVATIVERASTERDILATEPROC)(NVNcommandBuffer *cmdBuf, float dilate);
typedef void (*PFNNVNCOMMANDBUFFERSETSUBPIXELPRECISIONBIASPROC)(NVNcommandBuffer *cmdBuf, int xBits, int yBits);
typedef void (*PFNNVNCOMMANDBUFFERDISPATCHCOMPUTEPROC)(NVNcommandBuffer *cmdBuf, int groupsX, int groupsY, int groupsZ);
typedef void (*PFNNVNCOMMANDBUFFERBARRIERPROC)(NVNcommandBuffer *cmdBuf, int barrier);
typedef void (*PFNNVNCOMMANDBUFFERSETTILEDCACHETILESIZEPROC)(NVNcommandBuffer *cmdBuf, int tileWidth, int tileHeight);
typedef void (*PFNNVNCOMMANDBUFFERSETTILEDCACHEACTIONPROC)(NVNcommandBuffer *cmdBuf, NVNtiledCacheAction action);
typedef void (*PFNNVNMEMORYPOOLFINALIZEPROC)(NVNmemoryPool *pool);
typedef void (*PFNNVNTEXTUREBUILDERSETDEVICEPROC)(NVNtextureBuilder *builder, NVNdevice *device);
typedef void (*PFNNVNTEXTUREBUILDERSETDEFAULTSPROC)(NVNtextureBuilder *builder);
typedef void (*PFNNVNTEXTUREBUILDERSETFLAGSPROC)(NVNtextureBuilder *builder, int flags);
typedef void (*PFNNVNTEXTUREBUILDERSETTARGETPROC)(NVNtextureBuilder *builder, NVNtextureTarget target);
typedef void (*PFNNVNTEXTUREBUILDERSETSIZE1DPROC)(NVNtextureBuilder *builder, int width);
typedef void (*PFNNVNTEXTUREBUILDERSETSIZE2DPROC)(NVNtextureBuilder *builder, int width, int height);
typedef void (*PFNNVNTEXTUREBUILDERSETSIZE3DPROC)(NVNtextureBuilder *builder, int width, int height, int depth);
typedef void (*PFNNVNTEXTUREBUILDERSETLEVELSPROC)(NVNtextureBuilder *builder, int numLevels);
typedef void (*PFNNVNTEXTUREBUILDERSETFORMATPROC)(NVNtextureBuilder *builder, NVNformat format);
typedef void (*PFNNVNTEXTUREBUILDERSETDEPTHPROC)(NVNtextureBuilder *builder, int depth);
typedef size_t (*PFNNVNTEXTUREBUILDERGETSTORAGESIZEPROC)(const NVNtextureBuilder *builder);
typedef size_t (*PFNNVNTEXTUREBUILDERGETSTORAGEALIGNMENTPROC)(const NVNtextureBuilder *builder);
typedef void (*PFNNVNTEXTUREFINALIZEPROC)(NVNtexture *texture);

extern "C" {
extern PFNNVNCOMMANDBUFFERSETBLENDCOLORPROC pfnc_nvnCommandBufferSetBlendColor;
extern PFNNVNCOMMANDBUFFERBINDCHANNELMASKSTATEPROC pfnc_nvnCommandBufferBindChannelMaskState;
extern PFNNVNCOMMANDBUFFERBINDPOLYGONSTATEPROC pfnc_nvnCommandBufferBindPolygonState;
extern PFNNVNCOMMANDBUFFERSETRENDERTARGETSPROC pfnc_nvnCommandBufferSetRenderTargets;
extern PFNNVNCOMMANDBUFFERSETVIEWPORTPROC pfnc_nvnCommandBufferSetViewport;
extern PFNNVNCOMMANDBUFFERSETSCISSORPROC pfnc_nvnCommandBufferSetScissor;
extern PFNNVNCOMMANDBUFFERSETLINEWIDTHPROC pfnc_nvnCommandBufferSetLineWidth;
extern PFNNVNCOMMANDBUFFERSETRASTERIZERDISCARDPROC pfnc_nvnCommandBufferSetRasterizerDiscard;
extern PFNNVNCOMMANDBUFFERSETCONSERVATIVERASTERENABLEPROC pfnc_nvnCommandBufferSetConservativeRasterEnable;
extern PFNNVNCOMMANDBUFFERSETCONSERVATIVERASTERDILATEPROC pfnc_nvnCommandBufferSetConservativeRasterDilate;
extern PFNNVNCOMMANDBUFFERSETSUBPIXELPRECISIONBIASPROC pfnc_nvnCommandBufferSetSubpixelPrecisionBias;
extern PFNNVNCOMMANDBUFFERDISPATCHCOMPUTEPROC pfnc_nvnCommandBufferDispatchCompute;
extern PFNNVNCOMMANDBUFFERBARRIERPROC pfnc_nvnCommandBufferBarrier;
extern PFNNVNCOMMANDBUFFERSETTILEDCACHETILESIZEPROC pfnc_nvnCommandBufferSetTiledCacheTileSize;
extern PFNNVNCOMMANDBUFFERSETTILEDCACHEACTIONPROC pfnc_nvnCommandBufferSetTiledCacheAction;
extern PFNNVNMEMORYPOOLFINALIZEPROC pfnc_nvnMemoryPoolFinalize;
extern PFNNVNTEXTUREBUILDERSETDEVICEPROC pfnc_nvnTextureBuilderSetDevice;
extern PFNNVNTEXTUREBUILDERSETDEFAULTSPROC pfnc_nvnTextureBuilderSetDefaults;
extern PFNNVNTEXTUREBUILDERSETFLAGSPROC pfnc_nvnTextureBuilderSetFlags;
extern PFNNVNTEXTUREBUILDERSETTARGETPROC pfnc_nvnTextureBuilderSetTarget;
extern PFNNVNTEXTUREBUILDERSETSIZE1DPROC pfnc_nvnTextureBuilderSetSize1D;
extern PFNNVNTEXTUREBUILDERSETSIZE2DPROC pfnc_nvnTextureBuilderSetSize2D;
extern PFNNVNTEXTUREBUILDERSETSIZE3DPROC pfnc_nvnTextureBuilderSetSize3D;
extern PFNNVNTEXTUREBUILDERSETLEVELSPROC pfnc_nvnTextureBuilderSetLevels;
extern PFNNVNTEXTUREBUILDERSETFORMATPROC pfnc_nvnTextureBuilderSetFormat;
extern PFNNVNTEXTUREBUILDERSETDEPTHPROC pfnc_nvnTextureBuilderSetDepth;
extern PFNNVNTEXTUREBUILDERGETSTORAGESIZEPROC pfnc_nvnTextureBuilderGetStorageSize;
extern PFNNVNTEXTUREBUILDERGETSTORAGEALIGNMENTPROC pfnc_nvnTextureBuilderGetStorageAlignment;
extern PFNNVNTEXTUREFINALIZEPROC pfnc_nvnTextureFinalize;
}

inline void nvnCommandBufferSetBlendColor(NVNcommandBuffer *cmdBuf, const float *blendColor) {
  pfnc_nvnCommandBufferSetBlendColor(cmdBuf, blendColor);
}

inline void nvnCommandBufferBindChannelMaskState(NVNcommandBuffer *cmdBuf, const NVNchannelMaskState *channelMask) {
  pfnc_nvnCommandBufferBindChannelMaskState(cmdBuf, channelMask);
}

inline void nvnCommandBufferBindPolygonState(NVNcommandBuffer *cmdBuf, const NVNpolygonState *polygon) {
  pfnc_nvnCommandBufferBindPolygonState(cmdBuf, polygon);
}

inline void nvnCommandBufferSetRenderTargets(NVNcommandBuffer *cmdBuf, int numColors, const NVNtexture *const *colors,
                                             const NVNtextureView *const *colorViews, const NVNtexture *depthStencil,
                                             const NVNtextureView *depthStencilView) {
  pfnc_nvnCommandBufferSetRenderTargets(cmdBuf, numColors, colors, colorViews, depthStencil, depthStencilView);
}

inline void nvnCommandBufferSetViewport(NVNcommandBuffer *cmdBuf, int x, int y, int w, int h) {
  pfnc_nvnCommandBufferSetViewport(cmdBuf, x, y, w, h);
}

inline void nvnCommandBufferSetScissor(NVNcommandBuffer *cmdBuf, int x, int y, int w, int h) { pfnc_nvnCommandBufferSetScissor(cmdBuf, x, y, w, h); }

inline void nvnCommandBufferSetLineWidth(NVNcommandBuffer *cmdBuf, float width) { pfnc_nvnCommandBufferSetLineWidth(cmdBuf, width); }

inline void nvnCommandBufferSetRasterizerDiscard(NVNcommandBuffer *cmdBuf, NVNboolean discard) {
  pfnc_nvnCommandBufferSetRasterizerDiscard(cmdBuf, discard);
}

inline void nvnCommandBufferSetConservativeRasterEnable(NVNcommandBuffer *cmdBuf, NVNboolean enable) {
  pfnc_nvnCommandBufferSetConservativeRasterEnable(cmdBuf, enable);
}

inline void nvnCommandBufferSetConservativeRasterDilate(NVNcommandBuffer *cmdBuf, float dilate) {
  pfnc_nvnCommandBufferSetConservativeRasterDilate(cmdBuf, dilate);
}

inline void nvnCommandBufferSetSubpixelPrecisionBias(NVNcommandBuffer *cmdBuf, int xBits, int yBits) {
  pfnc_nvnCommandBufferSetSubpixelPrecisionBias(cmdBuf, xBits, yBits);
}

inline void nvnCommandBufferDispatchCompute(NVNcommandBuffer *cmdBuf, int groupsX, int groupsY, int groupsZ) {
  pfnc_nvnCommandBufferDispatchCompute(cmdBuf, groupsX, groupsY, groupsZ);
}

inline void nvnCommandBufferBarrier(NVNcommandBuffer *cmdBuf, int barrier) { pfnc_nvnCommandBufferBarrier(cmdBuf, barrier); }

inline void nvnCommandBufferSetTiledCacheTileSize(NVNcommandBuffer *cmdBuf, int tileWidth, int tileHeight) {
  pfnc_nvnCommandBufferSetTiledCacheTileSize(cmdBuf, tileWidth, tileHeight);
}

inline void nvnCommandBufferSetTiledCacheAction(NVNcommandBuffer *cmdBuf, NVNtiledCacheAction action) {
  pfnc_nvnCommandBufferSetTiledCacheAction(cmdBuf, action);
}

inline void nvnMemoryPoolFinalize(NVNmemoryPool *pool) { pfnc_nvnMemoryPoolFinalize(pool); }

inline void nvnTextureBuilderSetDevice(NVNtextureBuilder *builder, NVNdevice *device) { pfnc_nvnTextureBuilderSetDevice(builder, device); }

inline void nvnTextureBuilderSetDefaults(NVNtextureBuilder *builder) { pfnc_nvnTextureBuilderSetDefaults(builder); }

inline void nvnTextureBuilderSetFlags(NVNtextureBuilder *builder, int flags) { pfnc_nvnTextureBuilderSetFlags(builder, flags); }

inline void nvnTextureBuilderSetTarget(NVNtextureBuilder *builder, NVNtextureTarget target) { pfnc_nvnTextureBuilderSetTarget(builder, target); }

inline void nvnTextureBuilderSetSize1D(NVNtextureBuilder *builder, int width) { pfnc_nvnTextureBuilderSetSize1D(builder, width); }

inline void nvnTextureBuilderSetSize2D(NVNtextureBuilder *builder, int width, int height) { pfnc_nvnTextureBuilderSetSize2D(builder, width, height); }

inline void nvnTextureBuilderSetSize3D(NVNtextureBuilder *builder, int width, int height, int depth) {
  pfnc_nvnTextureBuilderSetSize3D(builder, width, height, depth);
}

inline void nvnTextureBuilderSetLevels(NVNtextureBuilder *builder, int numLevels) { pfnc_nvnTextureBuilderSetLevels(builder, numLevels); }

inline void nvnTextureBuilderSetFormat(NVNtextureBuilder *builder, NVNformat format) { pfnc_nvnTextureBuilderSetFormat(builder, format); }

inline void nvnTextureBuilderSetDepth(NVNtextureBuilder *builder, int depth) { pfnc_nvnTextureBuilderSetDepth(builder, depth); }

inline size_t nvnTextureBuilderGetStorageSize(const NVNtextureBuilder *builder) { return pfnc_nvnTextureBuilderGetStorageSize(builder); }

inline size_t nvnTextureBuilderGetStorageAlignment(const NVNtextureBuilder *builder) { return pfnc_nvnTextureBuilderGetStorageAlignment(builder); }

inline void nvnTextureFinalize(NVNtexture *texture) { pfnc_nvnTextureFinalize(texture); }
