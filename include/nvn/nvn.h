#pragma once
#include "types.h"

typedef u8 NVNboolean;

struct NVNcommandBuffer;
struct NVNtexture;

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
