#pragma once
#include <stddef.h>

#include "types.h"

typedef u8 NVNboolean;

struct NVNcommandBuffer;
struct NVNmemoryPool;
struct NVNtexture;
struct NVNvertexAttribState;

struct alignas(8) NVNdevice {
  u8 reserved[0x3000];
};

struct alignas(8) NVNtextureBuilder {
  u8 reserved[0x80];
};

struct alignas(8) NVNbuffer {
  u8 reserved[0x30];
};

struct NVNcounterData {
  u64 counter;
  u64 timestamp;
};

struct alignas(8) NVNprogram {
  u8 reserved[0xc0];
};

struct alignas(8) NVNbufferBuilder {
  u8 reserved[0x40];
};

struct alignas(8) NVNblendState {
  u8 reserved[0x8];
};

struct NVNcolorState {
  u8 reserved[0x4];
};

struct alignas(8) NVNdepthStencilState {
  u8 reserved[0x8];
};

struct alignas(8) NVNvertexStreamState {
  u8 reserved[0x8];
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

enum NVNfrontFace {
  NVN_FRONT_FACE_CW,
  NVN_FRONT_FACE_CCW,
};

enum NVNface {
  NVN_FACE_NONE,
  NVN_FACE_FRONT,
  NVN_FACE_BACK,
  NVN_FACE_FRONT_AND_BACK,
};

enum NVNpolygonMode {
  NVN_POLYGON_MODE_POINT,
  NVN_POLYGON_MODE_LINE,
  NVN_POLYGON_MODE_FILL,
};

enum NVNtextureFlags {
  NVN_TEXTURE_FLAGS_IMAGE = 0x4,
  NVN_TEXTURE_FLAGS_COMPRESSIBLE = 0x8,
};

enum NVNlogicOp {};

enum NVNblendEquation {};

enum NVNblendFunc {};

enum NVNdepthFunc {
  NVN_DEPTH_FUNC_NEVER = 0x1,
  NVN_DEPTH_FUNC_LESS,
  NVN_DEPTH_FUNC_EQUAL,
  NVN_DEPTH_FUNC_LEQUAL,
  NVN_DEPTH_FUNC_GREATER,
  NVN_DEPTH_FUNC_NOTEQUAL,
  NVN_DEPTH_FUNC_GEQUAL,
  NVN_DEPTH_FUNC_ALWAYS,
};

enum NVNstencilOp {};

enum NVNcounterType {
  NVN_COUNTER_TYPE_TIMESTAMP,
  NVN_COUNTER_TYPE_SAMPLES_PASSED,
};

enum NVNdrawPrimitive {};

enum NVNshaderStage {};

enum NVNindexType {};

typedef u64 NVNbufferAddress;
typedef u64 NVNtextureHandle;
typedef u64 NVNimageHandle;

typedef void (*PFNNVNCOMMANDBUFFERCOPYBUFFERTOBUFFERPROC)(NVNcommandBuffer *cmdBuf, NVNbufferAddress src, NVNbufferAddress dst, size_t size, int copyFlags);
typedef void (*PFNNVNCOMMANDBUFFERDISPATCHCOMPUTEINDIRECTPROC)(NVNcommandBuffer *cmdBuf, NVNbufferAddress indirectBuffer);
typedef void (*PFNNVNCOMMANDBUFFERDRAWELEMENTSPROC)(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNindexType type, int count, NVNbufferAddress indexBuffer);
typedef void (*PFNNVNCOMMANDBUFFERDRAWELEMENTSINSTANCEDPROC)(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNindexType type, int count, NVNbufferAddress indexBuffer, int baseVertex,
                                                             int baseInstance, int instanceCount);
typedef void (*PFNNVNCOMMANDBUFFERDRAWELEMENTSINDIRECTPROC)(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNindexType type, NVNbufferAddress indexBuffer, NVNbufferAddress indirectBuffer);
typedef void (*PFNNVNCOMMANDBUFFERSETBLENDCOLORPROC)(NVNcommandBuffer *cmdBuf, const float *blendColor);
typedef void (*PFNNVNCOMMANDBUFFERBINDCHANNELMASKSTATEPROC)(NVNcommandBuffer *cmdBuf, const NVNchannelMaskState *channelMask);
typedef void (*PFNNVNCOMMANDBUFFERBINDPOLYGONSTATEPROC)(NVNcommandBuffer *cmdBuf, const NVNpolygonState *polygon);
typedef void (*PFNNVNCOMMANDBUFFERSETRENDERTARGETSPROC)(NVNcommandBuffer *cmdBuf, int numColors, const NVNtexture *const *colors, const NVNtextureView *const *colorViews,
                                                        const NVNtexture *depthStencil, const NVNtextureView *depthStencilView);
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
typedef void (*PFNNVNCOMMANDBUFFERBINDVERTEXSTREAMSTATEPROC)(NVNcommandBuffer *cmdBuf, int numStreams, const NVNvertexStreamState *streams);
typedef void (*PFNNVNBLENDSTATESETDEFAULTSPROC)(NVNblendState *blend);
typedef void (*PFNNVNCHANNELMASKSTATESETDEFAULTSPROC)(NVNchannelMaskState *channelMask);
typedef void (*PFNNVNCHANNELMASKSTATESETCHANNELMASKPROC)(NVNchannelMaskState *channelMask, int index, NVNboolean r, NVNboolean g, NVNboolean b, NVNboolean a);
typedef void (*PFNNVNCOLORSTATESETDEFAULTSPROC)(NVNcolorState *color);
typedef void (*PFNNVNCOLORSTATESETBLENDENABLEPROC)(NVNcolorState *color, int index, NVNboolean enable);
typedef void (*PFNNVNDEPTHSTENCILSTATESETDEFAULTSPROC)(NVNdepthStencilState *depthStencil);
typedef void (*PFNNVNPOLYGONSTATESETDEFAULTSPROC)(NVNpolygonState *polygon);
typedef void (*PFNNVNPOLYGONSTATESETCULLFACEPROC)(NVNpolygonState *polygon, NVNface face);
typedef void (*PFNNVNPOLYGONSTATESETFRONTFACEPROC)(NVNpolygonState *polygon, NVNfrontFace face);
typedef void (*PFNNVNPOLYGONSTATESETPOLYGONMODEPROC)(NVNpolygonState *polygon, NVNpolygonMode polygonMode);
typedef void (*PFNNVNVERTEXSTREAMSTATESETDEFAULTSPROC)(NVNvertexStreamState *stream);
typedef void (*PFNNVNBUFFERBUILDERSETDEVICEPROC)(NVNbufferBuilder *builder, NVNdevice *device);
typedef void (*PFNNVNBUFFERBUILDERSETDEFAULTSPROC)(NVNbufferBuilder *builder);
typedef void (*PFNNVNBUFFERBUILDERSETSTORAGEPROC)(NVNbufferBuilder *builder, NVNmemoryPool *pool, ptrdiff_t offset, size_t size);
typedef NVNboolean (*PFNNVNBUFFERINITIALIZEPROC)(NVNbuffer *buffer, const NVNbufferBuilder *builder);
typedef void (*PFNNVNBUFFERFINALIZEPROC)(NVNbuffer *buffer);
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
typedef void (*PFNNVNCOLORSTATESETLOGICOPPROC)(NVNcolorState *color, NVNlogicOp logicOp);
typedef void (*PFNNVNCOMMANDBUFFERBINDCOLORSTATEPROC)(NVNcommandBuffer *cmdBuf, const NVNcolorState *color);
typedef void (*PFNNVNBLENDSTATESETBLENDEQUATIONPROC)(NVNblendState *blend, NVNblendEquation modeRGB, NVNblendEquation modeAlpha);
typedef void (*PFNNVNBLENDSTATESETBLENDFUNCPROC)(NVNblendState *blend, NVNblendFunc srcFunc, NVNblendFunc dstFunc, NVNblendFunc srcFuncAlpha, NVNblendFunc dstFuncAlpha);
typedef void (*PFNNVNBLENDSTATESETBLENDTARGETPROC)(NVNblendState *blend, int target);
typedef void (*PFNNVNCOMMANDBUFFERBINDBLENDSTATEPROC)(NVNcommandBuffer *cmdBuf, const NVNblendState *blend);
typedef void (*PFNNVNDEPTHSTENCILSTATESETDEPTHTESTENABLEPROC)(NVNdepthStencilState *depthStencil, NVNboolean enable);
typedef void (*PFNNVNDEPTHSTENCILSTATESETDEPTHFUNCPROC)(NVNdepthStencilState *depthStencil, NVNdepthFunc func);
typedef void (*PFNNVNDEPTHSTENCILSTATESETDEPTHWRITEENABLEPROC)(NVNdepthStencilState *depthStencil, NVNboolean enable);
typedef void (*PFNNVNDEPTHSTENCILSTATESETSTENCILTESTENABLEPROC)(NVNdepthStencilState *depthStencil, NVNboolean enable);
typedef void (*PFNNVNDEPTHSTENCILSTATESETSTENCILOPPROC)(NVNdepthStencilState *depthStencil, NVNface faces, NVNstencilOp fail, NVNstencilOp depthFail, NVNstencilOp depthPass);
typedef void (*PFNNVNDEPTHSTENCILSTATESETSTENCILFUNCPROC)(NVNdepthStencilState *depthStencil, NVNface faces, NVNdepthFunc func);
typedef void (*PFNNVNCOMMANDBUFFERBINDDEPTHSTENCILSTATEPROC)(NVNcommandBuffer *cmdBuf, const NVNdepthStencilState *depthStencil);
typedef void (*PFNNVNCOMMANDBUFFERSETSTENCILREFPROC)(NVNcommandBuffer *cmdBuf, NVNface faces, int ref);
typedef void (*PFNNVNCOMMANDBUFFERSETSTENCILVALUEMASKPROC)(NVNcommandBuffer *cmdBuf, NVNface faces, int mask);
typedef void (*PFNNVNCOMMANDBUFFERSETSTENCILMASKPROC)(NVNcommandBuffer *cmdBuf, NVNface faces, int mask);
typedef void (*PFNNVNCOMMANDBUFFERCLEARCOLORPROC)(NVNcommandBuffer *cmdBuf, int index, const float *color, int mask);
typedef void (*PFNNVNCOMMANDBUFFERCLEARCOLORIPROC)(NVNcommandBuffer *cmdBuf, int index, const int *color, int mask);
typedef void (*PFNNVNCOMMANDBUFFERCLEARDEPTHSTENCILPROC)(NVNcommandBuffer *cmdBuf, float depthValue, NVNboolean depthMask, int stencilValue, int stencilMask);
typedef void (*PFNNVNCOMMANDBUFFERRESETCOUNTERPROC)(NVNcommandBuffer *cmdBuf, NVNcounterType counter);
typedef void (*PFNNVNCOMMANDBUFFERREPORTCOUNTERPROC)(NVNcommandBuffer *cmdBuf, NVNcounterType counter, NVNbufferAddress buffer);
typedef NVNbufferAddress (*PFNNVNMEMORYPOOLGETBUFFERADDRESSPROC)(const NVNmemoryPool *pool);
typedef u64 (*PFNNVNDEVICEGETTIMESTAMPINNANOSECONDSPROC)(const NVNdevice *device, const NVNcounterData *counterData);
typedef void (*PFNNVNPROGRAMFINALIZEPROC)(NVNprogram *program);
typedef void (*PFNNVNCOMMANDBUFFERBINDUNIFORMBUFFERPROC)(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int index, NVNbufferAddress buffer, size_t size);
typedef void (*PFNNVNCOMMANDBUFFERBINDSTORAGEBUFFERPROC)(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int index, NVNbufferAddress buffer, size_t size);
typedef void (*PFNNVNCOMMANDBUFFERBINDTEXTUREPROC)(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int index, NVNtextureHandle texture);
typedef void (*PFNNVNCOMMANDBUFFERBINDIMAGEPROC)(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int index, NVNimageHandle image);
typedef void (*PFNNVNCOMMANDBUFFERBINDTRANSFORMFEEDBACKBUFFERPROC)(NVNcommandBuffer *cmdBuf, int index, NVNbufferAddress buffer, size_t size);
typedef void (*PFNNVNVERTEXSTREAMSTATESETSTRIDEPROC)(NVNvertexStreamState *stream, size_t stride);
typedef void (*PFNNVNVERTEXSTREAMSTATESETDIVISORPROC)(NVNvertexStreamState *stream, int divisor);
typedef void (*PFNNVNCOMMANDBUFFERBINDVERTEXBUFFERPROC)(NVNcommandBuffer *cmdBuf, int index, NVNbufferAddress buffer, size_t size);
typedef void (*PFNNVNCOMMANDBUFFERBINDPROGRAMPROC)(NVNcommandBuffer *cmdBuf, const NVNprogram *program, int stages);
typedef void (*PFNNVNCOMMANDBUFFERBINDVERTEXATTRIBSTATEPROC)(NVNcommandBuffer *cmdBuf, int numAttribs, const NVNvertexAttribState *attribs);
typedef void (*PFNNVNCOMMANDBUFFERBEGINTRANSFORMFEEDBACKPROC)(NVNcommandBuffer *cmdBuf, NVNbufferAddress buffer);
typedef void (*PFNNVNCOMMANDBUFFERENDTRANSFORMFEEDBACKPROC)(NVNcommandBuffer *cmdBuf, NVNbufferAddress buffer);

extern "C" {
extern PFNNVNCOMMANDBUFFERSETBLENDCOLORPROC pfnc_nvnCommandBufferSetBlendColor;
extern PFNNVNCOMMANDBUFFERBINDCHANNELMASKSTATEPROC pfnc_nvnCommandBufferBindChannelMaskState;
extern PFNNVNCOMMANDBUFFERBINDPOLYGONSTATEPROC pfnc_nvnCommandBufferBindPolygonState;
extern PFNNVNCOMMANDBUFFERSETRENDERTARGETSPROC pfnc_nvnCommandBufferSetRenderTargets;
extern PFNNVNCOMMANDBUFFERDRAWELEMENTSPROC pfnc_nvnCommandBufferDrawElements;
extern PFNNVNCOMMANDBUFFERDRAWELEMENTSINSTANCEDPROC pfnc_nvnCommandBufferDrawElementsInstanced;
extern PFNNVNCOMMANDBUFFERDRAWELEMENTSINDIRECTPROC pfnc_nvnCommandBufferDrawElementsIndirect;
extern PFNNVNCOMMANDBUFFERCOPYBUFFERTOBUFFERPROC pfnc_nvnCommandBufferCopyBufferToBuffer;
extern PFNNVNCOMMANDBUFFERDISPATCHCOMPUTEINDIRECTPROC pfnc_nvnCommandBufferDispatchComputeIndirect;
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
extern PFNNVNCOMMANDBUFFERBINDVERTEXSTREAMSTATEPROC pfnc_nvnCommandBufferBindVertexStreamState;
extern PFNNVNBLENDSTATESETDEFAULTSPROC pfnc_nvnBlendStateSetDefaults;
extern PFNNVNCHANNELMASKSTATESETDEFAULTSPROC pfnc_nvnChannelMaskStateSetDefaults;
extern PFNNVNCHANNELMASKSTATESETCHANNELMASKPROC pfnc_nvnChannelMaskStateSetChannelMask;
extern PFNNVNCOLORSTATESETDEFAULTSPROC pfnc_nvnColorStateSetDefaults;
extern PFNNVNCOLORSTATESETBLENDENABLEPROC pfnc_nvnColorStateSetBlendEnable;
extern PFNNVNDEPTHSTENCILSTATESETDEFAULTSPROC pfnc_nvnDepthStencilStateSetDefaults;
extern PFNNVNPOLYGONSTATESETDEFAULTSPROC pfnc_nvnPolygonStateSetDefaults;
extern PFNNVNPOLYGONSTATESETCULLFACEPROC pfnc_nvnPolygonStateSetCullFace;
extern PFNNVNPOLYGONSTATESETFRONTFACEPROC pfnc_nvnPolygonStateSetFrontFace;
extern PFNNVNPOLYGONSTATESETPOLYGONMODEPROC pfnc_nvnPolygonStateSetPolygonMode;
extern PFNNVNVERTEXSTREAMSTATESETDEFAULTSPROC pfnc_nvnVertexStreamStateSetDefaults;
extern PFNNVNBUFFERBUILDERSETDEVICEPROC pfnc_nvnBufferBuilderSetDevice;
extern PFNNVNBUFFERBUILDERSETDEFAULTSPROC pfnc_nvnBufferBuilderSetDefaults;
extern PFNNVNBUFFERBUILDERSETSTORAGEPROC pfnc_nvnBufferBuilderSetStorage;
extern PFNNVNBUFFERINITIALIZEPROC pfnc_nvnBufferInitialize;
extern PFNNVNBUFFERFINALIZEPROC pfnc_nvnBufferFinalize;
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
extern PFNNVNCOLORSTATESETLOGICOPPROC pfnc_nvnColorStateSetLogicOp;
extern PFNNVNCOMMANDBUFFERBINDCOLORSTATEPROC pfnc_nvnCommandBufferBindColorState;
extern PFNNVNBLENDSTATESETBLENDEQUATIONPROC pfnc_nvnBlendStateSetBlendEquation;
extern PFNNVNBLENDSTATESETBLENDFUNCPROC pfnc_nvnBlendStateSetBlendFunc;
extern PFNNVNBLENDSTATESETBLENDTARGETPROC pfnc_nvnBlendStateSetBlendTarget;
extern PFNNVNCOMMANDBUFFERBINDBLENDSTATEPROC pfnc_nvnCommandBufferBindBlendState;
extern PFNNVNDEPTHSTENCILSTATESETDEPTHTESTENABLEPROC pfnc_nvnDepthStencilStateSetDepthTestEnable;
extern PFNNVNDEPTHSTENCILSTATESETDEPTHFUNCPROC pfnc_nvnDepthStencilStateSetDepthFunc;
extern PFNNVNDEPTHSTENCILSTATESETDEPTHWRITEENABLEPROC pfnc_nvnDepthStencilStateSetDepthWriteEnable;
extern PFNNVNDEPTHSTENCILSTATESETSTENCILTESTENABLEPROC pfnc_nvnDepthStencilStateSetStencilTestEnable;
extern PFNNVNDEPTHSTENCILSTATESETSTENCILOPPROC pfnc_nvnDepthStencilStateSetStencilOp;
extern PFNNVNDEPTHSTENCILSTATESETSTENCILFUNCPROC pfnc_nvnDepthStencilStateSetStencilFunc;
extern PFNNVNCOMMANDBUFFERBINDDEPTHSTENCILSTATEPROC pfnc_nvnCommandBufferBindDepthStencilState;
extern PFNNVNCOMMANDBUFFERSETSTENCILREFPROC pfnc_nvnCommandBufferSetStencilRef;
extern PFNNVNCOMMANDBUFFERSETSTENCILVALUEMASKPROC pfnc_nvnCommandBufferSetStencilValueMask;
extern PFNNVNCOMMANDBUFFERSETSTENCILMASKPROC pfnc_nvnCommandBufferSetStencilMask;
extern PFNNVNCOMMANDBUFFERCLEARCOLORPROC pfnc_nvnCommandBufferClearColor;
extern PFNNVNCOMMANDBUFFERCLEARCOLORIPROC pfnc_nvnCommandBufferClearColori;
extern PFNNVNCOMMANDBUFFERCLEARDEPTHSTENCILPROC pfnc_nvnCommandBufferClearDepthStencil;
extern PFNNVNCOMMANDBUFFERRESETCOUNTERPROC pfnc_nvnCommandBufferResetCounter;
extern PFNNVNCOMMANDBUFFERREPORTCOUNTERPROC pfnc_nvnCommandBufferReportCounter;
extern PFNNVNMEMORYPOOLGETBUFFERADDRESSPROC pfnc_nvnMemoryPoolGetBufferAddress;
extern PFNNVNDEVICEGETTIMESTAMPINNANOSECONDSPROC pfnc_nvnDeviceGetTimestampInNanoseconds;
extern PFNNVNPROGRAMFINALIZEPROC pfnc_nvnProgramFinalize;
extern PFNNVNCOMMANDBUFFERBINDUNIFORMBUFFERPROC pfnc_nvnCommandBufferBindUniformBuffer;
extern PFNNVNCOMMANDBUFFERBINDSTORAGEBUFFERPROC pfnc_nvnCommandBufferBindStorageBuffer;
extern PFNNVNCOMMANDBUFFERBINDTEXTUREPROC pfnc_nvnCommandBufferBindTexture;
extern PFNNVNCOMMANDBUFFERBINDIMAGEPROC pfnc_nvnCommandBufferBindImage;
extern PFNNVNCOMMANDBUFFERBINDTRANSFORMFEEDBACKBUFFERPROC pfnc_nvnCommandBufferBindTransformFeedbackBuffer;
extern PFNNVNVERTEXSTREAMSTATESETSTRIDEPROC pfnc_nvnVertexStreamStateSetStride;
extern PFNNVNVERTEXSTREAMSTATESETDIVISORPROC pfnc_nvnVertexStreamStateSetDivisor;
extern PFNNVNCOMMANDBUFFERBINDVERTEXBUFFERPROC pfnc_nvnCommandBufferBindVertexBuffer;
extern PFNNVNCOMMANDBUFFERBINDPROGRAMPROC pfnc_nvnCommandBufferBindProgram;
extern PFNNVNCOMMANDBUFFERBINDVERTEXATTRIBSTATEPROC pfnc_nvnCommandBufferBindVertexAttribState;
extern PFNNVNCOMMANDBUFFERBEGINTRANSFORMFEEDBACKPROC pfnc_nvnCommandBufferBeginTransformFeedback;
extern PFNNVNCOMMANDBUFFERENDTRANSFORMFEEDBACKPROC pfnc_nvnCommandBufferEndTransformFeedback;
}

inline void nvnCommandBufferSetBlendColor(NVNcommandBuffer *cmdBuf, const float *blendColor) { pfnc_nvnCommandBufferSetBlendColor(cmdBuf, blendColor); }

inline void nvnCommandBufferBindChannelMaskState(NVNcommandBuffer *cmdBuf, const NVNchannelMaskState *channelMask) { pfnc_nvnCommandBufferBindChannelMaskState(cmdBuf, channelMask); }

inline void nvnCommandBufferBindPolygonState(NVNcommandBuffer *cmdBuf, const NVNpolygonState *polygon) { pfnc_nvnCommandBufferBindPolygonState(cmdBuf, polygon); }

inline void nvnCommandBufferSetRenderTargets(NVNcommandBuffer *cmdBuf, int numColors, const NVNtexture *const *colors, const NVNtextureView *const *colorViews, const NVNtexture *depthStencil,
                                             const NVNtextureView *depthStencilView) {
  pfnc_nvnCommandBufferSetRenderTargets(cmdBuf, numColors, colors, colorViews, depthStencil, depthStencilView);
}

inline void nvnCommandBufferDrawElements(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNindexType type, int count, NVNbufferAddress indexBuffer) {
  pfnc_nvnCommandBufferDrawElements(cmdBuf, mode, type, count, indexBuffer);
}

inline void nvnCommandBufferDrawElementsInstanced(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNindexType type, int count, NVNbufferAddress indexBuffer, int baseVertex, int baseInstance,
                                                  int instanceCount) {
  pfnc_nvnCommandBufferDrawElementsInstanced(cmdBuf, mode, type, count, indexBuffer, baseVertex, baseInstance, instanceCount);
}

inline void nvnCommandBufferDrawElementsIndirect(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNindexType type, NVNbufferAddress indexBuffer, NVNbufferAddress indirectBuffer) {
  pfnc_nvnCommandBufferDrawElementsIndirect(cmdBuf, mode, type, indexBuffer, indirectBuffer);
}

inline void nvnCommandBufferCopyBufferToBuffer(NVNcommandBuffer *cmdBuf, NVNbufferAddress src, NVNbufferAddress dst, size_t size, int copyFlags) {
  pfnc_nvnCommandBufferCopyBufferToBuffer(cmdBuf, src, dst, size, copyFlags);
}

inline void nvnCommandBufferDispatchComputeIndirect(NVNcommandBuffer *cmdBuf, NVNbufferAddress indirectBuffer) { pfnc_nvnCommandBufferDispatchComputeIndirect(cmdBuf, indirectBuffer); }

inline void nvnCommandBufferSetViewport(NVNcommandBuffer *cmdBuf, int x, int y, int w, int h) { pfnc_nvnCommandBufferSetViewport(cmdBuf, x, y, w, h); }

inline void nvnCommandBufferSetScissor(NVNcommandBuffer *cmdBuf, int x, int y, int w, int h) { pfnc_nvnCommandBufferSetScissor(cmdBuf, x, y, w, h); }

inline void nvnCommandBufferSetLineWidth(NVNcommandBuffer *cmdBuf, float width) { pfnc_nvnCommandBufferSetLineWidth(cmdBuf, width); }

inline void nvnCommandBufferSetRasterizerDiscard(NVNcommandBuffer *cmdBuf, NVNboolean discard) { pfnc_nvnCommandBufferSetRasterizerDiscard(cmdBuf, discard); }

inline void nvnCommandBufferSetConservativeRasterEnable(NVNcommandBuffer *cmdBuf, NVNboolean enable) { pfnc_nvnCommandBufferSetConservativeRasterEnable(cmdBuf, enable); }

inline void nvnCommandBufferSetConservativeRasterDilate(NVNcommandBuffer *cmdBuf, float dilate) { pfnc_nvnCommandBufferSetConservativeRasterDilate(cmdBuf, dilate); }

inline void nvnCommandBufferSetSubpixelPrecisionBias(NVNcommandBuffer *cmdBuf, int xBits, int yBits) { pfnc_nvnCommandBufferSetSubpixelPrecisionBias(cmdBuf, xBits, yBits); }

inline void nvnCommandBufferDispatchCompute(NVNcommandBuffer *cmdBuf, int groupsX, int groupsY, int groupsZ) { pfnc_nvnCommandBufferDispatchCompute(cmdBuf, groupsX, groupsY, groupsZ); }

inline void nvnCommandBufferBarrier(NVNcommandBuffer *cmdBuf, int barrier) { pfnc_nvnCommandBufferBarrier(cmdBuf, barrier); }

inline void nvnCommandBufferSetTiledCacheTileSize(NVNcommandBuffer *cmdBuf, int tileWidth, int tileHeight) { pfnc_nvnCommandBufferSetTiledCacheTileSize(cmdBuf, tileWidth, tileHeight); }

inline void nvnCommandBufferSetTiledCacheAction(NVNcommandBuffer *cmdBuf, NVNtiledCacheAction action) { pfnc_nvnCommandBufferSetTiledCacheAction(cmdBuf, action); }

inline void nvnMemoryPoolFinalize(NVNmemoryPool *pool) { pfnc_nvnMemoryPoolFinalize(pool); }

inline void nvnCommandBufferBindVertexStreamState(NVNcommandBuffer *cmdBuf, int numStreams, const NVNvertexStreamState *streams) {
  pfnc_nvnCommandBufferBindVertexStreamState(cmdBuf, numStreams, streams);
}

inline void nvnBlendStateSetDefaults(NVNblendState *blend) { pfnc_nvnBlendStateSetDefaults(blend); }

inline void nvnChannelMaskStateSetDefaults(NVNchannelMaskState *channelMask) { pfnc_nvnChannelMaskStateSetDefaults(channelMask); }

inline void nvnChannelMaskStateSetChannelMask(NVNchannelMaskState *channelMask, int index, NVNboolean r, NVNboolean g, NVNboolean b, NVNboolean a) {
  pfnc_nvnChannelMaskStateSetChannelMask(channelMask, index, r, g, b, a);
}

inline void nvnColorStateSetDefaults(NVNcolorState *color) { pfnc_nvnColorStateSetDefaults(color); }

inline void nvnColorStateSetBlendEnable(NVNcolorState *color, int index, NVNboolean enable) { pfnc_nvnColorStateSetBlendEnable(color, index, enable); }

inline void nvnDepthStencilStateSetDefaults(NVNdepthStencilState *depthStencil) { pfnc_nvnDepthStencilStateSetDefaults(depthStencil); }

inline void nvnPolygonStateSetDefaults(NVNpolygonState *polygon) { pfnc_nvnPolygonStateSetDefaults(polygon); }

inline void nvnPolygonStateSetCullFace(NVNpolygonState *polygon, NVNface face) { pfnc_nvnPolygonStateSetCullFace(polygon, face); }

inline void nvnPolygonStateSetFrontFace(NVNpolygonState *polygon, NVNfrontFace face) { pfnc_nvnPolygonStateSetFrontFace(polygon, face); }

inline void nvnPolygonStateSetPolygonMode(NVNpolygonState *polygon, NVNpolygonMode polygonMode) { pfnc_nvnPolygonStateSetPolygonMode(polygon, polygonMode); }

inline void nvnVertexStreamStateSetDefaults(NVNvertexStreamState *stream) { pfnc_nvnVertexStreamStateSetDefaults(stream); }

inline void nvnBufferBuilderSetDevice(NVNbufferBuilder *builder, NVNdevice *device) { pfnc_nvnBufferBuilderSetDevice(builder, device); }

inline void nvnBufferBuilderSetDefaults(NVNbufferBuilder *builder) { pfnc_nvnBufferBuilderSetDefaults(builder); }

inline void nvnBufferBuilderSetStorage(NVNbufferBuilder *builder, NVNmemoryPool *pool, ptrdiff_t offset, size_t size) { pfnc_nvnBufferBuilderSetStorage(builder, pool, offset, size); }

inline NVNboolean nvnBufferInitialize(NVNbuffer *buffer, const NVNbufferBuilder *builder) { return pfnc_nvnBufferInitialize(buffer, builder); }

inline void nvnBufferFinalize(NVNbuffer *buffer) { pfnc_nvnBufferFinalize(buffer); }

inline void nvnTextureBuilderSetDevice(NVNtextureBuilder *builder, NVNdevice *device) { pfnc_nvnTextureBuilderSetDevice(builder, device); }

inline void nvnTextureBuilderSetDefaults(NVNtextureBuilder *builder) { pfnc_nvnTextureBuilderSetDefaults(builder); }

inline void nvnTextureBuilderSetFlags(NVNtextureBuilder *builder, int flags) { pfnc_nvnTextureBuilderSetFlags(builder, flags); }

inline void nvnTextureBuilderSetTarget(NVNtextureBuilder *builder, NVNtextureTarget target) { pfnc_nvnTextureBuilderSetTarget(builder, target); }

inline void nvnTextureBuilderSetSize1D(NVNtextureBuilder *builder, int width) { pfnc_nvnTextureBuilderSetSize1D(builder, width); }

inline void nvnTextureBuilderSetSize2D(NVNtextureBuilder *builder, int width, int height) { pfnc_nvnTextureBuilderSetSize2D(builder, width, height); }

inline void nvnTextureBuilderSetSize3D(NVNtextureBuilder *builder, int width, int height, int depth) { pfnc_nvnTextureBuilderSetSize3D(builder, width, height, depth); }

inline void nvnTextureBuilderSetLevels(NVNtextureBuilder *builder, int numLevels) { pfnc_nvnTextureBuilderSetLevels(builder, numLevels); }

inline void nvnTextureBuilderSetFormat(NVNtextureBuilder *builder, NVNformat format) { pfnc_nvnTextureBuilderSetFormat(builder, format); }

inline void nvnTextureBuilderSetDepth(NVNtextureBuilder *builder, int depth) { pfnc_nvnTextureBuilderSetDepth(builder, depth); }

inline size_t nvnTextureBuilderGetStorageSize(const NVNtextureBuilder *builder) { return pfnc_nvnTextureBuilderGetStorageSize(builder); }

inline size_t nvnTextureBuilderGetStorageAlignment(const NVNtextureBuilder *builder) { return pfnc_nvnTextureBuilderGetStorageAlignment(builder); }

inline void nvnTextureFinalize(NVNtexture *texture) { pfnc_nvnTextureFinalize(texture); }

inline void nvnColorStateSetLogicOp(NVNcolorState *color, NVNlogicOp logicOp) { pfnc_nvnColorStateSetLogicOp(color, logicOp); }

inline void nvnCommandBufferBindColorState(NVNcommandBuffer *cmdBuf, const NVNcolorState *color) { pfnc_nvnCommandBufferBindColorState(cmdBuf, color); }

inline void nvnBlendStateSetBlendEquation(NVNblendState *blend, NVNblendEquation modeRGB, NVNblendEquation modeAlpha) { pfnc_nvnBlendStateSetBlendEquation(blend, modeRGB, modeAlpha); }

inline void nvnBlendStateSetBlendFunc(NVNblendState *blend, NVNblendFunc srcFunc, NVNblendFunc dstFunc, NVNblendFunc srcFuncAlpha, NVNblendFunc dstFuncAlpha) {
  pfnc_nvnBlendStateSetBlendFunc(blend, srcFunc, dstFunc, srcFuncAlpha, dstFuncAlpha);
}

inline void nvnBlendStateSetBlendTarget(NVNblendState *blend, int target) { pfnc_nvnBlendStateSetBlendTarget(blend, target); }

inline void nvnCommandBufferBindBlendState(NVNcommandBuffer *cmdBuf, const NVNblendState *blend) { pfnc_nvnCommandBufferBindBlendState(cmdBuf, blend); }

inline void nvnDepthStencilStateSetDepthTestEnable(NVNdepthStencilState *depthStencil, NVNboolean enable) { pfnc_nvnDepthStencilStateSetDepthTestEnable(depthStencil, enable); }

inline void nvnDepthStencilStateSetDepthFunc(NVNdepthStencilState *depthStencil, NVNdepthFunc func) { pfnc_nvnDepthStencilStateSetDepthFunc(depthStencil, func); }

inline void nvnDepthStencilStateSetDepthWriteEnable(NVNdepthStencilState *depthStencil, NVNboolean enable) { pfnc_nvnDepthStencilStateSetDepthWriteEnable(depthStencil, enable); }

inline void nvnDepthStencilStateSetStencilTestEnable(NVNdepthStencilState *depthStencil, NVNboolean enable) { pfnc_nvnDepthStencilStateSetStencilTestEnable(depthStencil, enable); }

inline void nvnDepthStencilStateSetStencilOp(NVNdepthStencilState *depthStencil, NVNface faces, NVNstencilOp fail, NVNstencilOp depthFail, NVNstencilOp depthPass) {
  pfnc_nvnDepthStencilStateSetStencilOp(depthStencil, faces, fail, depthFail, depthPass);
}

inline void nvnDepthStencilStateSetStencilFunc(NVNdepthStencilState *depthStencil, NVNface faces, NVNdepthFunc func) { pfnc_nvnDepthStencilStateSetStencilFunc(depthStencil, faces, func); }

inline void nvnCommandBufferBindDepthStencilState(NVNcommandBuffer *cmdBuf, const NVNdepthStencilState *depthStencil) { pfnc_nvnCommandBufferBindDepthStencilState(cmdBuf, depthStencil); }

inline void nvnCommandBufferSetStencilRef(NVNcommandBuffer *cmdBuf, NVNface faces, int ref) { pfnc_nvnCommandBufferSetStencilRef(cmdBuf, faces, ref); }

inline void nvnCommandBufferSetStencilValueMask(NVNcommandBuffer *cmdBuf, NVNface faces, int mask) { pfnc_nvnCommandBufferSetStencilValueMask(cmdBuf, faces, mask); }

inline void nvnCommandBufferSetStencilMask(NVNcommandBuffer *cmdBuf, NVNface faces, int mask) { pfnc_nvnCommandBufferSetStencilMask(cmdBuf, faces, mask); }

inline void nvnCommandBufferClearColor(NVNcommandBuffer *cmdBuf, int index, const float *color, int mask) { pfnc_nvnCommandBufferClearColor(cmdBuf, index, color, mask); }

inline void nvnCommandBufferClearColori(NVNcommandBuffer *cmdBuf, int index, const int *color, int mask) { pfnc_nvnCommandBufferClearColori(cmdBuf, index, color, mask); }

inline void nvnCommandBufferClearDepthStencil(NVNcommandBuffer *cmdBuf, float depthValue, NVNboolean depthMask, int stencilValue, int stencilMask) {
  pfnc_nvnCommandBufferClearDepthStencil(cmdBuf, depthValue, depthMask, stencilValue, stencilMask);
}

inline void nvnCommandBufferResetCounter(NVNcommandBuffer *cmdBuf, NVNcounterType counter) { pfnc_nvnCommandBufferResetCounter(cmdBuf, counter); }

inline void nvnCommandBufferReportCounter(NVNcommandBuffer *cmdBuf, NVNcounterType counter, NVNbufferAddress buffer) { pfnc_nvnCommandBufferReportCounter(cmdBuf, counter, buffer); }

inline NVNbufferAddress nvnMemoryPoolGetBufferAddress(const NVNmemoryPool *pool) { return pfnc_nvnMemoryPoolGetBufferAddress(pool); }

inline u64 nvnDeviceGetTimestampInNanoseconds(const NVNdevice *device, const NVNcounterData *counterData) { return pfnc_nvnDeviceGetTimestampInNanoseconds(device, counterData); }

inline void nvnProgramFinalize(NVNprogram *program) { pfnc_nvnProgramFinalize(program); }

inline void nvnCommandBufferBindUniformBuffer(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int index, NVNbufferAddress buffer, size_t size) {
  pfnc_nvnCommandBufferBindUniformBuffer(cmdBuf, stage, index, buffer, size);
}

inline void nvnCommandBufferBindStorageBuffer(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int index, NVNbufferAddress buffer, size_t size) {
  pfnc_nvnCommandBufferBindStorageBuffer(cmdBuf, stage, index, buffer, size);
}

inline void nvnCommandBufferBindTexture(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int index, NVNtextureHandle texture) { pfnc_nvnCommandBufferBindTexture(cmdBuf, stage, index, texture); }

inline void nvnCommandBufferBindImage(NVNcommandBuffer *cmdBuf, NVNshaderStage stage, int index, NVNimageHandle image) { pfnc_nvnCommandBufferBindImage(cmdBuf, stage, index, image); }

inline void nvnCommandBufferBindTransformFeedbackBuffer(NVNcommandBuffer *cmdBuf, int index, NVNbufferAddress buffer, size_t size) {
  pfnc_nvnCommandBufferBindTransformFeedbackBuffer(cmdBuf, index, buffer, size);
}

inline void nvnCommandBufferBeginTransformFeedback(NVNcommandBuffer *cmdBuf, NVNbufferAddress buffer) { pfnc_nvnCommandBufferBeginTransformFeedback(cmdBuf, buffer); }

inline void nvnCommandBufferEndTransformFeedback(NVNcommandBuffer *cmdBuf, NVNbufferAddress buffer) { pfnc_nvnCommandBufferEndTransformFeedback(cmdBuf, buffer); }

inline void nvnCommandBufferBindProgram(NVNcommandBuffer *cmdBuf, const NVNprogram *program, int stages) { pfnc_nvnCommandBufferBindProgram(cmdBuf, program, stages); }

inline void nvnCommandBufferBindVertexAttribState(NVNcommandBuffer *cmdBuf, int numAttribs, const NVNvertexAttribState *attribs) {
  pfnc_nvnCommandBufferBindVertexAttribState(cmdBuf, numAttribs, attribs);
}

inline void nvnVertexStreamStateSetStride(NVNvertexStreamState *stream, size_t stride) { pfnc_nvnVertexStreamStateSetStride(stream, stride); }

inline void nvnVertexStreamStateSetDivisor(NVNvertexStreamState *stream, int divisor) { pfnc_nvnVertexStreamStateSetDivisor(stream, divisor); }

inline void nvnCommandBufferBindVertexBuffer(NVNcommandBuffer *cmdBuf, int index, NVNbufferAddress buffer, size_t size) { pfnc_nvnCommandBufferBindVertexBuffer(cmdBuf, index, buffer, size); }
