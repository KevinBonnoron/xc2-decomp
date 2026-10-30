#pragma once
#include <stddef.h>

#include "types.h"

typedef u8 NVNboolean;

// Provenance: the size is the offset of the first member after the NVNcommandBuffer at the start of
// grlib::CGLibCmdBuffer (the CGLibMemPool at 0xa0, see CGLibCmdBuffer's constructor and release);
// the contents are not known.
struct alignas(8) NVNcommandBuffer {
  u8 reserved[0xa0];
};
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

// Provenance: the sizes of NVNtexturePool and NVNsamplerPool are the distance between their offset 0x48 member
// and the end (0x68) of grlib::CGLibTexDescriptor and grlib::CGLibSamplerDescriptor (see their constructors and
// setup functions); the contents are not known. Both type names follow the public NVN API, as declared in the
// open-ead nnheaders project (https://github.com/open-ead/nnheaders, include/nvn/nvn.h), where both are 0x20 bytes.
struct alignas(8) NVNtexturePool {
  u8 reserved[0x20];
};

struct alignas(8) NVNsamplerPool {
  u8 reserved[0x20];
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

// Public NVN API enumerators, as declared in the open-ead nnheaders project (include/nvn/nvn.h).
enum NVNformat {
  NVN_FORMAT_RGBA8 = 0x25,
  NVN_FORMAT_DEPTH24_STENCIL8 = 0x35,
};

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

// NVN_TEXTURE_FLAGS_DISPLAY and NVN_TEXTURE_FLAGS_LINEAR follow the public NVN API, as declared (with these values) in
// the open-ead nnheaders project (https://github.com/open-ead/nnheaders, include/nvn/nvn.h).
enum NVNtextureFlags {
  NVN_TEXTURE_FLAGS_DISPLAY = 0x1,
  NVN_TEXTURE_FLAGS_IMAGE = 0x4,
  NVN_TEXTURE_FLAGS_COMPRESSIBLE = 0x8,
  NVN_TEXTURE_FLAGS_LINEAR = 0x10,
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
// Public NVN API name, as declared in the open-ead nnheaders project (include/nvn/nvn.h).
typedef u64 NVNcommandHandle;

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
// Provenance for the command buffer lifecycle declarations below: each name is an imported function pointer
// symbol of the game (pfnc_nvnCommandBuffer... in work/syms_base.txt), and each prototype is inferred from the
// call sites in grlib::CGLibCmdBuffer (0x71007b21e4 to 0x71007b2a24).
typedef void (*PFNNVNCOMMANDBUFFERFINALIZEPROC)(NVNcommandBuffer *cmdBuf);
typedef void (*PFNNVNCOMMANDBUFFERINITIALIZEPROC)(NVNcommandBuffer *cmdBuf, NVNdevice *device);
// NVNcommandBufferMemoryEvent and the callback prototype follow the public NVN API, as declared in the open-ead
// nnheaders project (https://github.com/open-ead/nnheaders, include/nvn/nvn.h); the game's callback compares
// the event with 2.
typedef enum {
  NVN_COMMAND_BUFFER_MEMORY_EVENT_OUT_OF_COMMAND_MEMORY = 0x0,
  NVN_COMMAND_BUFFER_MEMORY_EVENT_OUT_OF_CONTROL_MEMORY = 0x1,
  NVN_COMMAND_BUFFER_MEMORY_EVENT_LARGE = 0x7FFFFFFF
} NVNcommandBufferMemoryEvent;
typedef void (*PFNNVNCOMMANDBUFFERMEMORYCALLBACKPROC)(NVNcommandBuffer *cmdBuf, NVNcommandBufferMemoryEvent event, size_t minSize, void *callbackData);
typedef void (*PFNNVNCOMMANDBUFFERSETMEMORYCALLBACKPROC)(NVNcommandBuffer *cmdBuf, PFNNVNCOMMANDBUFFERMEMORYCALLBACKPROC callback);
typedef void (*PFNNVNCOMMANDBUFFERSETMEMORYCALLBACKDATAPROC)(NVNcommandBuffer *cmdBuf, void *callbackData);
typedef void (*PFNNVNCOMMANDBUFFERADDCOMMANDMEMORYPROC)(NVNcommandBuffer *cmdBuf, const NVNmemoryPool *pool, size_t offset, size_t size);
typedef void (*PFNNVNCOMMANDBUFFERADDCONTROLMEMORYPROC)(NVNcommandBuffer *cmdBuf, void *memory, size_t size);
typedef void (*PFNNVNCOMMANDBUFFERBEGINRECORDINGPROC)(NVNcommandBuffer *cmdBuf);
typedef NVNcommandHandle (*PFNNVNCOMMANDBUFFERENDRECORDINGPROC)(NVNcommandBuffer *cmdBuf);
typedef u32 (*PFNNVNCOMMANDBUFFERGETCOMMANDMEMORYUSEDPROC)(const NVNcommandBuffer *cmdBuf);
typedef u32 (*PFNNVNCOMMANDBUFFERGETCONTROLMEMORYUSEDPROC)(const NVNcommandBuffer *cmdBuf);
typedef void (*PFNNVNCOMMANDBUFFERCALLCOMMANDSPROC)(NVNcommandBuffer *cmdBuf, int numCommands, const NVNcommandHandle *handles);
// Provenance for the texture and sampler pool declarations below: each name is an imported function pointer symbol
// of the game (pfnc_nvnTexturePool..., pfnc_nvnSamplerPool..., pfnc_nvnCommandBufferSet*Pool in
// work/syms_base.txt) and each prototype is inferred from the call sites in grlib::CGLibTexDescriptor and
// grlib::CGLibSamplerDescriptor (0x71007b2a24 to 0x71007b31ac).
typedef void (*PFNNVNTEXTUREPOOLINITIALIZEPROC)(NVNtexturePool *pool, const NVNmemoryPool *memoryPool, size_t offset, int numDescriptors);
typedef void (*PFNNVNTEXTUREPOOLFINALIZEPROC)(NVNtexturePool *pool);
typedef void (*PFNNVNTEXTUREPOOLREGISTERTEXTUREPROC)(NVNtexturePool *pool, int id, const NVNtexture *texture, const NVNtextureView *view);
typedef void (*PFNNVNTEXTUREPOOLREGISTERIMAGEPROC)(NVNtexturePool *pool, int id, const NVNtexture *texture, const NVNtextureView *view);
typedef void (*PFNNVNCOMMANDBUFFERSETTEXTUREPOOLPROC)(NVNcommandBuffer *cmdBuf, const NVNtexturePool *pool);
typedef void (*PFNNVNSAMPLERPOOLINITIALIZEPROC)(NVNsamplerPool *pool, const NVNmemoryPool *memoryPool, size_t offset, int numDescriptors);
typedef void (*PFNNVNSAMPLERPOOLFINALIZEPROC)(NVNsamplerPool *pool);
typedef void (*PFNNVNCOMMANDBUFFERSETSAMPLERPOOLPROC)(NVNcommandBuffer *cmdBuf, const NVNsamplerPool *pool);
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
extern PFNNVNCOMMANDBUFFERFINALIZEPROC pfnc_nvnCommandBufferFinalize;
extern PFNNVNCOMMANDBUFFERINITIALIZEPROC pfnc_nvnCommandBufferInitialize;
extern PFNNVNCOMMANDBUFFERSETMEMORYCALLBACKPROC pfnc_nvnCommandBufferSetMemoryCallback;
extern PFNNVNCOMMANDBUFFERSETMEMORYCALLBACKDATAPROC pfnc_nvnCommandBufferSetMemoryCallbackData;
extern PFNNVNCOMMANDBUFFERADDCOMMANDMEMORYPROC pfnc_nvnCommandBufferAddCommandMemory;
extern PFNNVNCOMMANDBUFFERADDCONTROLMEMORYPROC pfnc_nvnCommandBufferAddControlMemory;
extern PFNNVNCOMMANDBUFFERBEGINRECORDINGPROC pfnc_nvnCommandBufferBeginRecording;
extern PFNNVNCOMMANDBUFFERENDRECORDINGPROC pfnc_nvnCommandBufferEndRecording;
extern PFNNVNCOMMANDBUFFERGETCOMMANDMEMORYUSEDPROC pfnc_nvnCommandBufferGetCommandMemoryUsed;
extern PFNNVNCOMMANDBUFFERGETCONTROLMEMORYUSEDPROC pfnc_nvnCommandBufferGetControlMemoryUsed;
extern PFNNVNCOMMANDBUFFERCALLCOMMANDSPROC pfnc_nvnCommandBufferCallCommands;
extern PFNNVNTEXTUREPOOLINITIALIZEPROC pfnc_nvnTexturePoolInitialize;
extern PFNNVNTEXTUREPOOLFINALIZEPROC pfnc_nvnTexturePoolFinalize;
extern PFNNVNTEXTUREPOOLREGISTERTEXTUREPROC pfnc_nvnTexturePoolRegisterTexture;
extern PFNNVNTEXTUREPOOLREGISTERIMAGEPROC pfnc_nvnTexturePoolRegisterImage;
extern PFNNVNCOMMANDBUFFERSETTEXTUREPOOLPROC pfnc_nvnCommandBufferSetTexturePool;
extern PFNNVNSAMPLERPOOLINITIALIZEPROC pfnc_nvnSamplerPoolInitialize;
extern PFNNVNSAMPLERPOOLFINALIZEPROC pfnc_nvnSamplerPoolFinalize;
extern PFNNVNCOMMANDBUFFERSETSAMPLERPOOLPROC pfnc_nvnCommandBufferSetSamplerPool;
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

inline void nvnCommandBufferFinalize(NVNcommandBuffer *cmdBuf) { pfnc_nvnCommandBufferFinalize(cmdBuf); }

inline void nvnCommandBufferInitialize(NVNcommandBuffer *cmdBuf, NVNdevice *device) { pfnc_nvnCommandBufferInitialize(cmdBuf, device); }

inline void nvnCommandBufferSetMemoryCallback(NVNcommandBuffer *cmdBuf, PFNNVNCOMMANDBUFFERMEMORYCALLBACKPROC callback) { pfnc_nvnCommandBufferSetMemoryCallback(cmdBuf, callback); }

inline void nvnCommandBufferSetMemoryCallbackData(NVNcommandBuffer *cmdBuf, void *callbackData) { pfnc_nvnCommandBufferSetMemoryCallbackData(cmdBuf, callbackData); }

inline void nvnCommandBufferAddCommandMemory(NVNcommandBuffer *cmdBuf, const NVNmemoryPool *pool, size_t offset, size_t size) { pfnc_nvnCommandBufferAddCommandMemory(cmdBuf, pool, offset, size); }

inline void nvnCommandBufferAddControlMemory(NVNcommandBuffer *cmdBuf, void *memory, size_t size) { pfnc_nvnCommandBufferAddControlMemory(cmdBuf, memory, size); }

inline void nvnCommandBufferBeginRecording(NVNcommandBuffer *cmdBuf) { pfnc_nvnCommandBufferBeginRecording(cmdBuf); }

inline NVNcommandHandle nvnCommandBufferEndRecording(NVNcommandBuffer *cmdBuf) { return pfnc_nvnCommandBufferEndRecording(cmdBuf); }

inline u32 nvnCommandBufferGetCommandMemoryUsed(const NVNcommandBuffer *cmdBuf) { return pfnc_nvnCommandBufferGetCommandMemoryUsed(cmdBuf); }

inline u32 nvnCommandBufferGetControlMemoryUsed(const NVNcommandBuffer *cmdBuf) { return pfnc_nvnCommandBufferGetControlMemoryUsed(cmdBuf); }

inline void nvnCommandBufferCallCommands(NVNcommandBuffer *cmdBuf, int numCommands, const NVNcommandHandle *handles) { pfnc_nvnCommandBufferCallCommands(cmdBuf, numCommands, handles); }

inline void nvnTexturePoolInitialize(NVNtexturePool *pool, const NVNmemoryPool *memoryPool, size_t offset, int numDescriptors) {
  pfnc_nvnTexturePoolInitialize(pool, memoryPool, offset, numDescriptors);
}

inline void nvnTexturePoolFinalize(NVNtexturePool *pool) { pfnc_nvnTexturePoolFinalize(pool); }

inline void nvnTexturePoolRegisterTexture(NVNtexturePool *pool, int id, const NVNtexture *texture, const NVNtextureView *view) { pfnc_nvnTexturePoolRegisterTexture(pool, id, texture, view); }

inline void nvnTexturePoolRegisterImage(NVNtexturePool *pool, int id, const NVNtexture *texture, const NVNtextureView *view) { pfnc_nvnTexturePoolRegisterImage(pool, id, texture, view); }

inline void nvnCommandBufferSetTexturePool(NVNcommandBuffer *cmdBuf, const NVNtexturePool *pool) { pfnc_nvnCommandBufferSetTexturePool(cmdBuf, pool); }

inline void nvnSamplerPoolInitialize(NVNsamplerPool *pool, const NVNmemoryPool *memoryPool, size_t offset, int numDescriptors) {
  pfnc_nvnSamplerPoolInitialize(pool, memoryPool, offset, numDescriptors);
}

inline void nvnSamplerPoolFinalize(NVNsamplerPool *pool) { pfnc_nvnSamplerPoolFinalize(pool); }

inline void nvnCommandBufferSetSamplerPool(NVNcommandBuffer *cmdBuf, const NVNsamplerPool *pool) { pfnc_nvnCommandBufferSetSamplerPool(cmdBuf, pool); }

// Provenance for the declarations below: every name, enumerator and prototype is the public NVN API, as declared in the
// open-ead nnheaders project (https://github.com/open-ead/nnheaders, include/nvn/nvn.h), where the opaque structures
// have the same sizes; each function is called by the game through the imported pfnc_ pointer of the same name
// (work/syms_base.txt).
struct alignas(8) NVNmemoryPool {
  u8 reserved[0x100];
};

struct alignas(8) NVNtexture {
  u8 reserved[0xc0];
};

struct NVNvertexAttribState {
  u8 reserved[0x4];
};

struct alignas(8) NVNdeviceBuilder {
  u8 reserved[0x40];
};

struct alignas(8) NVNmemoryPoolBuilder {
  u8 reserved[0x40];
};

struct NVNshaderData {
  NVNbufferAddress data;
  const void *control;
};

struct alignas(8) NVNqueueBuilder {
  u8 reserved[0x40];
};

struct alignas(8) NVNqueue {
  u8 reserved[0x2000];
};

struct alignas(8) NVNsync {
  u8 reserved[0x40];
};

struct alignas(8) NVNwindow {
  u8 reserved[0x180];
};

struct alignas(8) NVNwindowBuilder {
  u8 reserved[0x40];
};

struct alignas(8) NVNsamplerBuilder {
  u8 reserved[0x60];
};

struct alignas(8) NVNsampler {
  u8 reserved[0x30];
};

typedef void *NVNnativeWindow;

enum NVNdepthMode {
  NVN_DEPTH_MODE_NEAR_IS_MINUS_W = 0x0,
  NVN_DEPTH_MODE_NEAR_IS_ZERO = 0x1,
};

enum NVNwindowOriginMode {
  NVN_WINDOW_ORIGIN_MODE_LOWER_LEFT = 0x0,
  NVN_WINDOW_ORIGIN_MODE_UPPER_LEFT = 0x1,
};

enum NVNsyncCondition {
  NVN_SYNC_CONDITION_ALL_GPU_COMMANDS_COMPLETE = 0x0,
  NVN_SYNC_CONDITION_GRAPHICS_WORLD_SPACE_COMPLETE = 0x1,
};

enum NVNsyncWaitResult {
  NVN_SYNC_WAIT_RESULT_ALREADY_SIGNALED = 0x0,
  NVN_SYNC_WAIT_RESULT_CONDITION_SATISFIED = 0x1,
  NVN_SYNC_WAIT_RESULT_TIMEOUT_EXPIRED = 0x2,
  NVN_SYNC_WAIT_RESULT_FAILED = 0x3,
};

enum NVNwindowAcquireTextureResult {
  NVN_WINDOW_ACQUIRE_TEXTURE_RESULT_SUCCESS = 0x0,
  NVN_WINDOW_ACQUIRE_TEXTURE_RESULT_NATIVE_ERROR = 0x1,
};

enum NVNcompareMode {
  NVN_COMPARE_MODE_NONE = 0x0,
  NVN_COMPARE_MODE_COMPARE_R_TO_TEXTURE = 0x1,
};

enum NVNcompareFunc {
  NVN_COMPARE_FUNC_NEVER = 0x1,
  NVN_COMPARE_FUNC_LESS = 0x2,
  NVN_COMPARE_FUNC_EQUAL = 0x3,
  NVN_COMPARE_FUNC_LEQUAL = 0x4,
  NVN_COMPARE_FUNC_GREATER = 0x5,
  NVN_COMPARE_FUNC_NOTEQUAL = 0x6,
  NVN_COMPARE_FUNC_GEQUAL = 0x7,
  NVN_COMPARE_FUNC_ALWAYS = 0x8,
};

enum NVNminFilter {
  NVN_MIN_FILTER_NEAREST = 0x0,
  NVN_MIN_FILTER_LINEAR = 0x1,
  NVN_MIN_FILTER_NEAREST_MIPMAP_NEAREST = 0x2,
  NVN_MIN_FILTER_LINEAR_MIPMAP_NEAREST = 0x3,
  NVN_MIN_FILTER_NEAREST_MIPMAP_LINEAR = 0x4,
  NVN_MIN_FILTER_LINEAR_MIPMAP_LINEAR = 0x5,
};

enum NVNmagFilter {
  NVN_MAG_FILTER_NEAREST = 0x0,
  NVN_MAG_FILTER_LINEAR = 0x1,
};

enum NVNwrapMode {
  NVN_WRAP_MODE_CLAMP = 0x0,
  NVN_WRAP_MODE_REPEAT = 0x1,
  NVN_WRAP_MODE_MIRROR_CLAMP = 0x2,
  NVN_WRAP_MODE_MIRROR_CLAMP_TO_EDGE = 0x3,
  NVN_WRAP_MODE_MIRROR_CLAMP_TO_BORDER = 0x4,
  NVN_WRAP_MODE_CLAMP_TO_BORDER = 0x5,
  NVN_WRAP_MODE_MIRRORED_REPEAT = 0x6,
  NVN_WRAP_MODE_CLAMP_TO_EDGE = 0x7,
};

enum NVNtextureDepthStencilMode {
  NVN_TEXTURE_DEPTH_STENCIL_MODE_DEPTH = 0x0,
  NVN_TEXTURE_DEPTH_STENCIL_MODE_STENCIL = 0x1,
};

enum NVNtextureSwizzle {
  NVN_TEXTURE_SWIZZLE_ZERO = 0x0,
  NVN_TEXTURE_SWIZZLE_ONE = 0x1,
  NVN_TEXTURE_SWIZZLE_R = 0x2,
  NVN_TEXTURE_SWIZZLE_G = 0x3,
  NVN_TEXTURE_SWIZZLE_B = 0x4,
  NVN_TEXTURE_SWIZZLE_A = 0x5,
};

enum NVNdeviceInfo {
  NVN_DEVICE_INFO_API_MAJOR_VERSION = 0x0,
  NVN_DEVICE_INFO_API_MINOR_VERSION = 0x1,
  NVN_DEVICE_INFO_UNIFORM_BUFFER_BINDINGS_PER_STAGE = 0x2,
  NVN_DEVICE_INFO_MAX_UNIFORM_BUFFER_SIZE = 0x3,
  NVN_DEVICE_INFO_UNIFORM_BUFFER_ALIGNMENT = 0x4,
  NVN_DEVICE_INFO_COLOR_BUFFER_BINDINGS = 0x5,
  NVN_DEVICE_INFO_VERTEX_BUFFER_BINDINGS = 0x6,
  NVN_DEVICE_INFO_TRANSFORM_FEEDBACK_BUFFER_BINDINGS = 0x7,
  NVN_DEVICE_INFO_SHADER_STORAGE_BUFFER_BINDINGS_PER_STAGE = 0x8,
  NVN_DEVICE_INFO_TEXTURE_BINDINGS_PER_STAGE = 0x9,
  NVN_DEVICE_INFO_COUNTER_ALIGNMENT = 0xA,
  NVN_DEVICE_INFO_TRANSFORM_FEEDBACK_BUFFER_ALIGNMENT = 0xB,
  NVN_DEVICE_INFO_TRANSFORM_FEEDBACK_CONTROL_ALIGNMENT = 0xC,
  NVN_DEVICE_INFO_INDIRECT_DRAW_ALIGNMENT = 0xD,
  NVN_DEVICE_INFO_VERTEX_ATTRIBUTES = 0xE,
  NVN_DEVICE_INFO_TEXTURE_DESCRIPTOR_SIZE = 0xF,
  NVN_DEVICE_INFO_SAMPLER_DESCRIPTOR_SIZE = 0x10,
  NVN_DEVICE_INFO_RESERVED_TEXTURE_DESCRIPTORS = 0x11,
  NVN_DEVICE_INFO_RESERVED_SAMPLER_DESCRIPTORS = 0x12,
  NVN_DEVICE_INFO_COMMAND_BUFFER_COMMAND_ALIGNMENT = 0x13,
  NVN_DEVICE_INFO_COMMAND_BUFFER_CONTROL_ALIGNMENT = 0x14,
  NVN_DEVICE_INFO_COMMAND_BUFFER_MIN_COMMAND_SIZE = 0x15,
  NVN_DEVICE_INFO_COMMAND_BUFFER_MIN_CONTROL_SIZE = 0x16,
  NVN_DEVICE_INFO_SHADER_SCRATCH_MEMORY_SCALE_FACTOR_MINIMUM = 0x17,
  NVN_DEVICE_INFO_SHADER_SCRATCH_MEMORY_SCALE_FACTOR_RECOMMENDED = 0x18,
  NVN_DEVICE_INFO_SHADER_SCRATCH_MEMORY_ALIGNMENT = 0x19,
  NVN_DEVICE_INFO_SHADER_SCRATCH_MEMORY_GRANULARITY = 0x1A,
  NVN_DEVICE_INFO_MAX_TEXTURE_ANISOTROPY = 0x1B,
  NVN_DEVICE_INFO_MAX_COMPUTE_WORK_GROUP_SIZE_X = 0x1C,
  NVN_DEVICE_INFO_MAX_COMPUTE_WORK_GROUP_SIZE_Y = 0x1D,
  NVN_DEVICE_INFO_MAX_COMPUTE_WORK_GROUP_SIZE_Z = 0x1E,
  NVN_DEVICE_INFO_MAX_COMPUTE_WORK_GROUP_SIZE_THREADS = 0x1F,
  NVN_DEVICE_INFO_MAX_COMPUTE_DISPATCH_WORK_GROUPS_X = 0x20,
  NVN_DEVICE_INFO_MAX_COMPUTE_DISPATCH_WORK_GROUPS_Y = 0x21,
  NVN_DEVICE_INFO_MAX_COMPUTE_DISPATCH_WORK_GROUPS_Z = 0x22,
  NVN_DEVICE_INFO_IMAGE_BINDINGS_PER_STAGE = 0x23,
  NVN_DEVICE_INFO_MAX_TEXTURE_POOL_SIZE = 0x24,
  NVN_DEVICE_INFO_MAX_SAMPLER_POOL_SIZE = 0x25,
  NVN_DEVICE_INFO_MAX_VIEWPORTS = 0x26,
  NVN_DEVICE_INFO_MEMPOOL_TEXTURE_OBJECT_PAGE_ALIGNMENT = 0x27,
  NVN_DEVICE_INFO_SUPPORTS_MIN_MAX_FILTERING = 0x28,
  NVN_DEVICE_INFO_SUPPORTS_STENCIL8_FORMAT = 0x29,
  NVN_DEVICE_INFO_SUPPORTS_ASTC_FORMATS = 0x2A,
  NVN_DEVICE_INFO_L2_SIZE = 0x2B,
  NVN_DEVICE_INFO_MAX_TEXTURE_LEVELS = 0x2C,
  NVN_DEVICE_INFO_MAX_TEXTURE_LAYERS = 0x2D,
  NVN_DEVICE_INFO_GLSLC_MAX_SUPPORTED_GPU_CODE_MAJOR_VERSION = 0x2E,
  NVN_DEVICE_INFO_GLSLC_MIN_SUPPORTED_GPU_CODE_MAJOR_VERSION = 0x2F,
  NVN_DEVICE_INFO_GLSLC_MAX_SUPPORTED_GPU_CODE_MINOR_VERSION = 0x30,
  NVN_DEVICE_INFO_GLSLC_MIN_SUPPORTED_GPU_CODE_MINOR_VERSION = 0x31,
  NVN_DEVICE_INFO_SUPPORTS_CONSERVATIVE_RASTER = 0x32,
  NVN_DEVICE_INFO_SUBPIXEL_BITS = 0x33,
  NVN_DEVICE_INFO_MAX_SUBPIXEL_BIAS_BITS = 0x34,
  NVN_DEVICE_INFO_INDIRECT_DISPATCH_ALIGNMENT = 0x35,
  NVN_DEVICE_INFO_ZCULL_SAVE_RESTORE_ALIGNMENT = 0x36,
  NVN_DEVICE_INFO_SHADER_SCRATCH_MEMORY_COMPUTE_SCALE_FACTOR_MINIMUM = 0x37,
  NVN_DEVICE_INFO_LINEAR_TEXTURE_STRIDE_ALIGNMENT = 0x38,
  NVN_DEVICE_INFO_LINEAR_RENDER_TARGET_STRIDE_ALIGNMENT = 0x39,
  NVN_DEVICE_INFO_MEMORY_POOL_PAGE_SIZE = 0x3A,
  NVN_DEVICE_INFO_SUPPORTS_ZERO_FROM_UNMAPPED_VIRTUAL_POOL_PAGES = 0x3B,
  NVN_DEVICE_INFO_UNIFORM_BUFFER_UPDATE_ALIGNMENT = 0x3C,
  NVN_DEVICE_INFO_MAX_TEXTURE_SIZE = 0x3D,
  NVN_DEVICE_INFO_MAX_BUFFER_TEXTURE_SIZE = 0x3E,
  NVN_DEVICE_INFO_MAX_3D_TEXTURE_SIZE = 0x3F,
  NVN_DEVICE_INFO_MAX_CUBE_MAP_TEXTURE_SIZE = 0x40,
  NVN_DEVICE_INFO_MAX_RECTANGLE_TEXTURE_SIZE = 0x41,
  NVN_DEVICE_INFO_SUPPORTS_PASSTHROUGH_GEOMETRY_SHADERS = 0x42,
  NVN_DEVICE_INFO_SUPPORTS_VIEWPORT_SWIZZLE = 0x43,
  NVN_DEVICE_INFO_SUPPORTS_SPARSE_TILED_PACKAGED_TEXTURES = 0x44,
  NVN_DEVICE_INFO_SUPPORTS_ADVANCED_BLEND_MODES = 0x45,
  NVN_DEVICE_INFO_MAX_PRESENT_INTERVAL = 0x46,
  NVN_DEVICE_INFO_SUPPORTS_DRAW_TEXTURE = 0x47,
  NVN_DEVICE_INFO_SUPPORTS_TARGET_INDEPENDENT_RASTERIZATION = 0x48,
  NVN_DEVICE_INFO_SUPPORTS_FRAGMENT_COVERAGE_TO_COLOR = 0x49,
  NVN_DEVICE_INFO_SUPPORTS_POST_DEPTH_COVERAGE = 0x4A,
  NVN_DEVICE_INFO_SUPPORTS_IMAGES_USING_TEXTURE_HANDLES = 0x4B,
  NVN_DEVICE_INFO_SUPPORTS_SAMPLE_LOCATIONS = 0x4C,
  NVN_DEVICE_INFO_MAX_SAMPLE_LOCATION_TABLE_ENTRIES = 0x4D,
  NVN_DEVICE_INFO_SHADER_CODE_MEMORY_POOL_PADDING_SIZE = 0x4E,
  NVN_DEVICE_INFO_MAX_PATCH_SIZE = 0x4F,
  NVN_DEVICE_INFO_QUEUE_COMMAND_MEMORY_GRANULARITY = 0x50,
  NVN_DEVICE_INFO_QUEUE_COMMAND_MEMORY_MIN_SIZE = 0x51,
  NVN_DEVICE_INFO_QUEUE_COMMAND_MEMORY_DEFAULT_SIZE = 0x52,
  NVN_DEVICE_INFO_QUEUE_COMPUTE_MEMORY_GRANULARITY = 0x53,
  NVN_DEVICE_INFO_QUEUE_COMPUTE_MEMORY_MIN_SIZE = 0x54,
  NVN_DEVICE_INFO_QUEUE_COMPUTE_MEMORY_DEFAULT_SIZE = 0x55,
  NVN_DEVICE_INFO_QUEUE_COMMAND_MEMORY_MIN_FLUSH_THRESHOLD = 0x56,
  NVN_DEVICE_INFO_SUPPORTS_FRAGMENT_SHADER_INTERLOCK = 0x57,
  NVN_DEVICE_INFO_MAX_TEXTURES_PER_WINDOW = 0x58,
  NVN_DEVICE_INFO_MIN_TEXTURES_PER_WINDOW = 0x59,
  NVN_DEVICE_INFO_SUPPORTS_DEBUG_LAYER = 0x5A,
  NVN_DEVICE_INFO_QUEUE_CONTROL_MEMORY_MIN_SIZE = 0x5B,
  NVN_DEVICE_INFO_QUEUE_CONTROL_MEMORY_DEFAULT_SIZE = 0x5C,
  NVN_DEVICE_INFO_QUEUE_CONTROL_MEMORY_GRANULARITY = 0x5D,
  NVN_DEVICE_INFO_SEPARATE_TEXTURE_BINDINGS_PER_STAGE = 0x5E,
  NVN_DEVICE_INFO_SEPARATE_SAMPLER_BINDINGS_PER_STAGE = 0x5F,
  NVN_DEVICE_INFO_DEBUG_GROUPS_MAX_DOMAIN_ID = 0x60,
  NVN_DEVICE_INFO_EVENTS_SUPPORT_REDUCTION_OPERATIONS = 0x61,
};

typedef void (*PFNNVNCOMMANDBUFFERDRAWARRAYSPROC)(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, int first, int count);
typedef void (*PFNNVNCOMMANDBUFFERDRAWARRAYSINDIRECTPROC)(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNbufferAddress indirectBuffer);
typedef void (*PFNNVNCOMMANDBUFFERDRAWARRAYSINSTANCEDPROC)(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, int first, int count, int baseInstance, int instanceCount);
typedef void (*PFNNVNCOMMANDBUFFERMULTIDRAWARRAYSINDIRECTCOUNTPROC)(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNbufferAddress indirectBuffer, NVNbufferAddress parameterBuffer,
                                                                    int maxDrawCount, ptrdiff_t stride);
typedef void (*PFNNVNCOMMANDBUFFERMULTIDRAWELEMENTSINDIRECTCOUNTPROC)(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNindexType type, NVNbufferAddress indexBuffer, NVNbufferAddress indirectBuffer,
                                                                      NVNbufferAddress parameterBuffer, int maxDrawCount, ptrdiff_t stride);
typedef void (*PFNNVNCOMMANDBUFFERSETDEPTHRANGEPROC)(NVNcommandBuffer *cmdBuf, float n, float f);
typedef void (*PFNNVNCOMMANDBUFFERSETSHADERSCRATCHMEMORYPROC)(NVNcommandBuffer *cmdBuf, const NVNmemoryPool *pool, ptrdiff_t offset, size_t size);
typedef void (*PFNNVNDEVICEBUILDERSETDEFAULTSPROC)(NVNdeviceBuilder *builder);
typedef void (*PFNNVNDEVICEBUILDERSETFLAGSPROC)(NVNdeviceBuilder *builder, int flags);
typedef void (*PFNNVNDEVICEFINALIZEPROC)(NVNdevice *device);
typedef NVNimageHandle (*PFNNVNDEVICEGETIMAGEHANDLEPROC)(const NVNdevice *device, int imageID);
typedef void (*PFNNVNDEVICEGETINTEGERPROC)(const NVNdevice *device, NVNdeviceInfo pname, int *v);
typedef NVNtextureHandle (*PFNNVNDEVICEGETTEXTUREHANDLEPROC)(const NVNdevice *device, int textureID, int samplerID);
typedef NVNboolean (*PFNNVNDEVICEINITIALIZEPROC)(NVNdevice *device, const NVNdeviceBuilder *builder);
typedef NVNboolean (*PFNNVNDEVICEREGISTERFASTCLEARCOLORPROC)(NVNdevice *device, const float *color, NVNformat format);
typedef NVNboolean (*PFNNVNDEVICEREGISTERFASTCLEARDEPTHPROC)(NVNdevice *device, float depth);
typedef void (*PFNNVNDEVICESETDEPTHMODEPROC)(NVNdevice *device, NVNdepthMode mode);
typedef void (*PFNNVNDEVICESETWINDOWORIGINMODEPROC)(NVNdevice *device, NVNwindowOriginMode mode);
typedef void (*PFNNVNMEMORYPOOLBUILDERSETDEFAULTSPROC)(NVNmemoryPoolBuilder *builder);
typedef void (*PFNNVNMEMORYPOOLBUILDERSETDEVICEPROC)(NVNmemoryPoolBuilder *builder, NVNdevice *device);
typedef void (*PFNNVNMEMORYPOOLBUILDERSETFLAGSPROC)(NVNmemoryPoolBuilder *builder, int flags);
typedef void (*PFNNVNMEMORYPOOLBUILDERSETSTORAGEPROC)(NVNmemoryPoolBuilder *builder, void *memory, size_t size);
typedef NVNboolean (*PFNNVNMEMORYPOOLINITIALIZEPROC)(NVNmemoryPool *pool, const NVNmemoryPoolBuilder *builder);
typedef NVNboolean (*PFNNVNPROGRAMINITIALIZEPROC)(NVNprogram *program, NVNdevice *device);
typedef NVNboolean (*PFNNVNPROGRAMSETSHADERSPROC)(NVNprogram *program, int count, const NVNshaderData *stageData);
typedef void (*PFNNVNQUEUEBUILDERSETCOMMANDFLUSHTHRESHOLDPROC)(NVNqueueBuilder *builder, size_t threshold);
typedef void (*PFNNVNQUEUEBUILDERSETCOMMANDMEMORYSIZEPROC)(NVNqueueBuilder *builder, size_t size);
typedef void (*PFNNVNQUEUEBUILDERSETDEFAULTSPROC)(NVNqueueBuilder *builder);
typedef void (*PFNNVNQUEUEBUILDERSETDEVICEPROC)(NVNqueueBuilder *builder, NVNdevice *device);
typedef void (*PFNNVNQUEUEFENCESYNCPROC)(NVNqueue *queue, NVNsync *sync, NVNsyncCondition condition, int flags);
typedef void (*PFNNVNQUEUEFINALIZEPROC)(NVNqueue *queue);
typedef NVNboolean (*PFNNVNQUEUEINITIALIZEPROC)(NVNqueue *queue, const NVNqueueBuilder *builder);
typedef void (*PFNNVNQUEUEPRESENTTEXTUREPROC)(NVNqueue *queue, NVNwindow *window, int textureIndex);
typedef void (*PFNNVNQUEUESUBMITCOMMANDSPROC)(NVNqueue *queue, int numCommands, const NVNcommandHandle *handles);
typedef void (*PFNNVNSAMPLERBUILDERSETBORDERCOLORPROC)(NVNsamplerBuilder *builder, const float *borderColor);
typedef void (*PFNNVNSAMPLERBUILDERSETCOMPAREPROC)(NVNsamplerBuilder *builder, NVNcompareMode mode, NVNcompareFunc func);
typedef void (*PFNNVNSAMPLERBUILDERSETDEFAULTSPROC)(NVNsamplerBuilder *builder);
typedef void (*PFNNVNSAMPLERBUILDERSETDEVICEPROC)(NVNsamplerBuilder *builder, NVNdevice *device);
typedef void (*PFNNVNSAMPLERBUILDERSETLODBIASPROC)(NVNsamplerBuilder *builder, float bias);
typedef void (*PFNNVNSAMPLERBUILDERSETLODCLAMPPROC)(NVNsamplerBuilder *builder, float min, float max);
typedef void (*PFNNVNSAMPLERBUILDERSETMAXANISOTROPYPROC)(NVNsamplerBuilder *builder, float maxAniso);
typedef void (*PFNNVNSAMPLERBUILDERSETMINMAGFILTERPROC)(NVNsamplerBuilder *builder, NVNminFilter min, NVNmagFilter mag);
typedef void (*PFNNVNSAMPLERBUILDERSETWRAPMODEPROC)(NVNsamplerBuilder *builder, NVNwrapMode s, NVNwrapMode t, NVNwrapMode r);
typedef void (*PFNNVNSAMPLERFINALIZEPROC)(NVNsampler *sampler);
typedef NVNboolean (*PFNNVNSAMPLERINITIALIZEPROC)(NVNsampler *sampler, const NVNsamplerBuilder *builder);
typedef void (*PFNNVNSAMPLERPOOLREGISTERSAMPLERPROC)(const NVNsamplerPool *pool, int id, const NVNsampler *sampler);
typedef void (*PFNNVNSYNCFINALIZEPROC)(NVNsync *sync);
typedef NVNboolean (*PFNNVNSYNCINITIALIZEPROC)(NVNsync *sync, NVNdevice *device);
typedef NVNsyncWaitResult (*PFNNVNSYNCWAITPROC)(const NVNsync *sync, u64 timeoutNs);
typedef void (*PFNNVNTEXTUREBUILDERSETDEPTHSTENCILMODEPROC)(NVNtextureBuilder *builder, NVNtextureDepthStencilMode mode);
typedef void (*PFNNVNTEXTUREBUILDERSETPACKAGEDTEXTUREDATAPROC)(NVNtextureBuilder *builder, const void *data);
typedef void (*PFNNVNTEXTUREBUILDERSETSTORAGEPROC)(NVNtextureBuilder *builder, NVNmemoryPool *pool, ptrdiff_t offset);
typedef void (*PFNNVNTEXTUREBUILDERSETSTRIDEPROC)(NVNtextureBuilder *builder, ptrdiff_t stride);
typedef void (*PFNNVNTEXTUREBUILDERSETSWIZZLEPROC)(NVNtextureBuilder *builder, NVNtextureSwizzle r, NVNtextureSwizzle g, NVNtextureSwizzle b, NVNtextureSwizzle a);
typedef NVNboolean (*PFNNVNTEXTUREINITIALIZEPROC)(NVNtexture *texture, const NVNtextureBuilder *builder);
typedef void (*PFNNVNTEXTUREVIEWSETDEFAULTSPROC)(NVNtextureView *view);
typedef void (*PFNNVNTEXTUREVIEWSETFORMATPROC)(NVNtextureView *view, NVNformat format);
typedef void (*PFNNVNTEXTUREVIEWSETLAYERSPROC)(NVNtextureView *view, int minLayer, int numLayers);
typedef void (*PFNNVNTEXTUREVIEWSETLEVELSPROC)(NVNtextureView *view, int baseLevel, int numLevels);
typedef void (*PFNNVNTEXTUREVIEWSETTARGETPROC)(NVNtextureView *view, NVNtextureTarget target);
typedef void (*PFNNVNVERTEXATTRIBSTATESETDEFAULTSPROC)(NVNvertexAttribState *attrib);
typedef void (*PFNNVNVERTEXATTRIBSTATESETFORMATPROC)(NVNvertexAttribState *attrib, NVNformat format, ptrdiff_t relativeOffset);
typedef void (*PFNNVNVERTEXATTRIBSTATESETSTREAMINDEXPROC)(NVNvertexAttribState *attrib, int streamIndex);
typedef NVNwindowAcquireTextureResult (*PFNNVNWINDOWACQUIRETEXTUREPROC)(NVNwindow *window, NVNsync *textureAvailableSync, int *textureIndex);
typedef void (*PFNNVNWINDOWBUILDERSETDEFAULTSPROC)(NVNwindowBuilder *builder);
typedef void (*PFNNVNWINDOWBUILDERSETDEVICEPROC)(NVNwindowBuilder *builder, NVNdevice *device);
typedef void (*PFNNVNWINDOWBUILDERSETNATIVEWINDOWPROC)(NVNwindowBuilder *builder, NVNnativeWindow nativeWindow);
typedef void (*PFNNVNWINDOWBUILDERSETTEXTURESPROC)(NVNwindowBuilder *builder, int numTextures, NVNtexture *const *textures);
typedef void (*PFNNVNWINDOWFINALIZEPROC)(NVNwindow *window);
typedef NVNboolean (*PFNNVNWINDOWINITIALIZEPROC)(NVNwindow *window, const NVNwindowBuilder *builder);

extern "C" {
extern PFNNVNCOMMANDBUFFERDRAWARRAYSPROC pfnc_nvnCommandBufferDrawArrays;
extern PFNNVNCOMMANDBUFFERDRAWARRAYSINDIRECTPROC pfnc_nvnCommandBufferDrawArraysIndirect;
extern PFNNVNCOMMANDBUFFERDRAWARRAYSINSTANCEDPROC pfnc_nvnCommandBufferDrawArraysInstanced;
extern PFNNVNCOMMANDBUFFERMULTIDRAWARRAYSINDIRECTCOUNTPROC pfnc_nvnCommandBufferMultiDrawArraysIndirectCount;
extern PFNNVNCOMMANDBUFFERMULTIDRAWELEMENTSINDIRECTCOUNTPROC pfnc_nvnCommandBufferMultiDrawElementsIndirectCount;
extern PFNNVNCOMMANDBUFFERSETDEPTHRANGEPROC pfnc_nvnCommandBufferSetDepthRange;
extern PFNNVNCOMMANDBUFFERSETSHADERSCRATCHMEMORYPROC pfnc_nvnCommandBufferSetShaderScratchMemory;
extern PFNNVNDEVICEBUILDERSETDEFAULTSPROC pfnc_nvnDeviceBuilderSetDefaults;
extern PFNNVNDEVICEBUILDERSETFLAGSPROC pfnc_nvnDeviceBuilderSetFlags;
extern PFNNVNDEVICEFINALIZEPROC pfnc_nvnDeviceFinalize;
extern PFNNVNDEVICEGETIMAGEHANDLEPROC pfnc_nvnDeviceGetImageHandle;
extern PFNNVNDEVICEGETINTEGERPROC pfnc_nvnDeviceGetInteger;
extern PFNNVNDEVICEGETTEXTUREHANDLEPROC pfnc_nvnDeviceGetTextureHandle;
extern PFNNVNDEVICEINITIALIZEPROC pfnc_nvnDeviceInitialize;
extern PFNNVNDEVICEREGISTERFASTCLEARCOLORPROC pfnc_nvnDeviceRegisterFastClearColor;
extern PFNNVNDEVICEREGISTERFASTCLEARDEPTHPROC pfnc_nvnDeviceRegisterFastClearDepth;
extern PFNNVNDEVICESETDEPTHMODEPROC pfnc_nvnDeviceSetDepthMode;
extern PFNNVNDEVICESETWINDOWORIGINMODEPROC pfnc_nvnDeviceSetWindowOriginMode;
extern PFNNVNMEMORYPOOLBUILDERSETDEFAULTSPROC pfnc_nvnMemoryPoolBuilderSetDefaults;
extern PFNNVNMEMORYPOOLBUILDERSETDEVICEPROC pfnc_nvnMemoryPoolBuilderSetDevice;
extern PFNNVNMEMORYPOOLBUILDERSETFLAGSPROC pfnc_nvnMemoryPoolBuilderSetFlags;
extern PFNNVNMEMORYPOOLBUILDERSETSTORAGEPROC pfnc_nvnMemoryPoolBuilderSetStorage;
extern PFNNVNMEMORYPOOLINITIALIZEPROC pfnc_nvnMemoryPoolInitialize;
extern PFNNVNPROGRAMINITIALIZEPROC pfnc_nvnProgramInitialize;
extern PFNNVNPROGRAMSETSHADERSPROC pfnc_nvnProgramSetShaders;
extern PFNNVNQUEUEBUILDERSETCOMMANDFLUSHTHRESHOLDPROC pfnc_nvnQueueBuilderSetCommandFlushThreshold;
extern PFNNVNQUEUEBUILDERSETCOMMANDMEMORYSIZEPROC pfnc_nvnQueueBuilderSetCommandMemorySize;
extern PFNNVNQUEUEBUILDERSETDEFAULTSPROC pfnc_nvnQueueBuilderSetDefaults;
extern PFNNVNQUEUEBUILDERSETDEVICEPROC pfnc_nvnQueueBuilderSetDevice;
extern PFNNVNQUEUEFENCESYNCPROC pfnc_nvnQueueFenceSync;
extern PFNNVNQUEUEFINALIZEPROC pfnc_nvnQueueFinalize;
extern PFNNVNQUEUEINITIALIZEPROC pfnc_nvnQueueInitialize;
extern PFNNVNQUEUEPRESENTTEXTUREPROC pfnc_nvnQueuePresentTexture;
extern PFNNVNQUEUESUBMITCOMMANDSPROC pfnc_nvnQueueSubmitCommands;
extern PFNNVNSAMPLERBUILDERSETBORDERCOLORPROC pfnc_nvnSamplerBuilderSetBorderColor;
extern PFNNVNSAMPLERBUILDERSETCOMPAREPROC pfnc_nvnSamplerBuilderSetCompare;
extern PFNNVNSAMPLERBUILDERSETDEFAULTSPROC pfnc_nvnSamplerBuilderSetDefaults;
extern PFNNVNSAMPLERBUILDERSETDEVICEPROC pfnc_nvnSamplerBuilderSetDevice;
extern PFNNVNSAMPLERBUILDERSETLODBIASPROC pfnc_nvnSamplerBuilderSetLodBias;
extern PFNNVNSAMPLERBUILDERSETLODCLAMPPROC pfnc_nvnSamplerBuilderSetLodClamp;
extern PFNNVNSAMPLERBUILDERSETMAXANISOTROPYPROC pfnc_nvnSamplerBuilderSetMaxAnisotropy;
extern PFNNVNSAMPLERBUILDERSETMINMAGFILTERPROC pfnc_nvnSamplerBuilderSetMinMagFilter;
extern PFNNVNSAMPLERBUILDERSETWRAPMODEPROC pfnc_nvnSamplerBuilderSetWrapMode;
extern PFNNVNSAMPLERFINALIZEPROC pfnc_nvnSamplerFinalize;
extern PFNNVNSAMPLERINITIALIZEPROC pfnc_nvnSamplerInitialize;
extern PFNNVNSAMPLERPOOLREGISTERSAMPLERPROC pfnc_nvnSamplerPoolRegisterSampler;
extern PFNNVNSYNCFINALIZEPROC pfnc_nvnSyncFinalize;
extern PFNNVNSYNCINITIALIZEPROC pfnc_nvnSyncInitialize;
extern PFNNVNSYNCWAITPROC pfnc_nvnSyncWait;
extern PFNNVNTEXTUREBUILDERSETDEPTHSTENCILMODEPROC pfnc_nvnTextureBuilderSetDepthStencilMode;
extern PFNNVNTEXTUREBUILDERSETPACKAGEDTEXTUREDATAPROC pfnc_nvnTextureBuilderSetPackagedTextureData;
extern PFNNVNTEXTUREBUILDERSETSTORAGEPROC pfnc_nvnTextureBuilderSetStorage;
extern PFNNVNTEXTUREBUILDERSETSTRIDEPROC pfnc_nvnTextureBuilderSetStride;
extern PFNNVNTEXTUREBUILDERSETSWIZZLEPROC pfnc_nvnTextureBuilderSetSwizzle;
extern PFNNVNTEXTUREINITIALIZEPROC pfnc_nvnTextureInitialize;
extern PFNNVNTEXTUREVIEWSETDEFAULTSPROC pfnc_nvnTextureViewSetDefaults;
extern PFNNVNTEXTUREVIEWSETFORMATPROC pfnc_nvnTextureViewSetFormat;
extern PFNNVNTEXTUREVIEWSETLAYERSPROC pfnc_nvnTextureViewSetLayers;
extern PFNNVNTEXTUREVIEWSETLEVELSPROC pfnc_nvnTextureViewSetLevels;
extern PFNNVNTEXTUREVIEWSETTARGETPROC pfnc_nvnTextureViewSetTarget;
extern PFNNVNVERTEXATTRIBSTATESETDEFAULTSPROC pfnc_nvnVertexAttribStateSetDefaults;
extern PFNNVNVERTEXATTRIBSTATESETFORMATPROC pfnc_nvnVertexAttribStateSetFormat;
extern PFNNVNVERTEXATTRIBSTATESETSTREAMINDEXPROC pfnc_nvnVertexAttribStateSetStreamIndex;
extern PFNNVNWINDOWACQUIRETEXTUREPROC pfnc_nvnWindowAcquireTexture;
extern PFNNVNWINDOWBUILDERSETDEFAULTSPROC pfnc_nvnWindowBuilderSetDefaults;
extern PFNNVNWINDOWBUILDERSETDEVICEPROC pfnc_nvnWindowBuilderSetDevice;
extern PFNNVNWINDOWBUILDERSETNATIVEWINDOWPROC pfnc_nvnWindowBuilderSetNativeWindow;
extern PFNNVNWINDOWBUILDERSETTEXTURESPROC pfnc_nvnWindowBuilderSetTextures;
extern PFNNVNWINDOWFINALIZEPROC pfnc_nvnWindowFinalize;
extern PFNNVNWINDOWINITIALIZEPROC pfnc_nvnWindowInitialize;
}

inline void nvnCommandBufferDrawArrays(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, int first, int count) { pfnc_nvnCommandBufferDrawArrays(cmdBuf, mode, first, count); }

inline void nvnCommandBufferDrawArraysIndirect(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNbufferAddress indirectBuffer) {
  pfnc_nvnCommandBufferDrawArraysIndirect(cmdBuf, mode, indirectBuffer);
}

inline void nvnCommandBufferDrawArraysInstanced(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, int first, int count, int baseInstance, int instanceCount) {
  pfnc_nvnCommandBufferDrawArraysInstanced(cmdBuf, mode, first, count, baseInstance, instanceCount);
}

inline void nvnCommandBufferMultiDrawArraysIndirectCount(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNbufferAddress indirectBuffer, NVNbufferAddress parameterBuffer, int maxDrawCount,
                                                         ptrdiff_t stride) {
  pfnc_nvnCommandBufferMultiDrawArraysIndirectCount(cmdBuf, mode, indirectBuffer, parameterBuffer, maxDrawCount, stride);
}

inline void nvnCommandBufferMultiDrawElementsIndirectCount(NVNcommandBuffer *cmdBuf, NVNdrawPrimitive mode, NVNindexType type, NVNbufferAddress indexBuffer, NVNbufferAddress indirectBuffer,
                                                           NVNbufferAddress parameterBuffer, int maxDrawCount, ptrdiff_t stride) {
  pfnc_nvnCommandBufferMultiDrawElementsIndirectCount(cmdBuf, mode, type, indexBuffer, indirectBuffer, parameterBuffer, maxDrawCount, stride);
}

inline void nvnCommandBufferSetDepthRange(NVNcommandBuffer *cmdBuf, float n, float f) { pfnc_nvnCommandBufferSetDepthRange(cmdBuf, n, f); }

inline void nvnCommandBufferSetShaderScratchMemory(NVNcommandBuffer *cmdBuf, const NVNmemoryPool *pool, ptrdiff_t offset, size_t size) {
  pfnc_nvnCommandBufferSetShaderScratchMemory(cmdBuf, pool, offset, size);
}

inline void nvnDeviceBuilderSetDefaults(NVNdeviceBuilder *builder) { pfnc_nvnDeviceBuilderSetDefaults(builder); }

inline void nvnDeviceBuilderSetFlags(NVNdeviceBuilder *builder, int flags) { pfnc_nvnDeviceBuilderSetFlags(builder, flags); }

inline void nvnDeviceFinalize(NVNdevice *device) { pfnc_nvnDeviceFinalize(device); }

inline NVNimageHandle nvnDeviceGetImageHandle(const NVNdevice *device, int imageID) { return pfnc_nvnDeviceGetImageHandle(device, imageID); }

inline void nvnDeviceGetInteger(const NVNdevice *device, NVNdeviceInfo pname, int *v) { pfnc_nvnDeviceGetInteger(device, pname, v); }

inline NVNtextureHandle nvnDeviceGetTextureHandle(const NVNdevice *device, int textureID, int samplerID) { return pfnc_nvnDeviceGetTextureHandle(device, textureID, samplerID); }

inline NVNboolean nvnDeviceInitialize(NVNdevice *device, const NVNdeviceBuilder *builder) { return pfnc_nvnDeviceInitialize(device, builder); }

inline NVNboolean nvnDeviceRegisterFastClearColor(NVNdevice *device, const float *color, NVNformat format) { return pfnc_nvnDeviceRegisterFastClearColor(device, color, format); }

inline NVNboolean nvnDeviceRegisterFastClearDepth(NVNdevice *device, float depth) { return pfnc_nvnDeviceRegisterFastClearDepth(device, depth); }

inline void nvnDeviceSetDepthMode(NVNdevice *device, NVNdepthMode mode) { pfnc_nvnDeviceSetDepthMode(device, mode); }

inline void nvnDeviceSetWindowOriginMode(NVNdevice *device, NVNwindowOriginMode mode) { pfnc_nvnDeviceSetWindowOriginMode(device, mode); }

inline void nvnMemoryPoolBuilderSetDefaults(NVNmemoryPoolBuilder *builder) { pfnc_nvnMemoryPoolBuilderSetDefaults(builder); }

inline void nvnMemoryPoolBuilderSetDevice(NVNmemoryPoolBuilder *builder, NVNdevice *device) { pfnc_nvnMemoryPoolBuilderSetDevice(builder, device); }

inline void nvnMemoryPoolBuilderSetFlags(NVNmemoryPoolBuilder *builder, int flags) { pfnc_nvnMemoryPoolBuilderSetFlags(builder, flags); }

inline void nvnMemoryPoolBuilderSetStorage(NVNmemoryPoolBuilder *builder, void *memory, size_t size) { pfnc_nvnMemoryPoolBuilderSetStorage(builder, memory, size); }

inline NVNboolean nvnMemoryPoolInitialize(NVNmemoryPool *pool, const NVNmemoryPoolBuilder *builder) { return pfnc_nvnMemoryPoolInitialize(pool, builder); }

inline NVNboolean nvnProgramInitialize(NVNprogram *program, NVNdevice *device) { return pfnc_nvnProgramInitialize(program, device); }

inline NVNboolean nvnProgramSetShaders(NVNprogram *program, int count, const NVNshaderData *stageData) { return pfnc_nvnProgramSetShaders(program, count, stageData); }

inline void nvnQueueBuilderSetCommandFlushThreshold(NVNqueueBuilder *builder, size_t threshold) { pfnc_nvnQueueBuilderSetCommandFlushThreshold(builder, threshold); }

inline void nvnQueueBuilderSetCommandMemorySize(NVNqueueBuilder *builder, size_t size) { pfnc_nvnQueueBuilderSetCommandMemorySize(builder, size); }

inline void nvnQueueBuilderSetDefaults(NVNqueueBuilder *builder) { pfnc_nvnQueueBuilderSetDefaults(builder); }

inline void nvnQueueBuilderSetDevice(NVNqueueBuilder *builder, NVNdevice *device) { pfnc_nvnQueueBuilderSetDevice(builder, device); }

inline void nvnQueueFenceSync(NVNqueue *queue, NVNsync *sync, NVNsyncCondition condition, int flags) { pfnc_nvnQueueFenceSync(queue, sync, condition, flags); }

inline void nvnQueueFinalize(NVNqueue *queue) { pfnc_nvnQueueFinalize(queue); }

inline NVNboolean nvnQueueInitialize(NVNqueue *queue, const NVNqueueBuilder *builder) { return pfnc_nvnQueueInitialize(queue, builder); }

inline void nvnQueuePresentTexture(NVNqueue *queue, NVNwindow *window, int textureIndex) { pfnc_nvnQueuePresentTexture(queue, window, textureIndex); }

inline void nvnQueueSubmitCommands(NVNqueue *queue, int numCommands, const NVNcommandHandle *handles) { pfnc_nvnQueueSubmitCommands(queue, numCommands, handles); }

inline void nvnSamplerBuilderSetBorderColor(NVNsamplerBuilder *builder, const float *borderColor) { pfnc_nvnSamplerBuilderSetBorderColor(builder, borderColor); }

inline void nvnSamplerBuilderSetCompare(NVNsamplerBuilder *builder, NVNcompareMode mode, NVNcompareFunc func) { pfnc_nvnSamplerBuilderSetCompare(builder, mode, func); }

inline void nvnSamplerBuilderSetDefaults(NVNsamplerBuilder *builder) { pfnc_nvnSamplerBuilderSetDefaults(builder); }

inline void nvnSamplerBuilderSetDevice(NVNsamplerBuilder *builder, NVNdevice *device) { pfnc_nvnSamplerBuilderSetDevice(builder, device); }

inline void nvnSamplerBuilderSetLodBias(NVNsamplerBuilder *builder, float bias) { pfnc_nvnSamplerBuilderSetLodBias(builder, bias); }

inline void nvnSamplerBuilderSetLodClamp(NVNsamplerBuilder *builder, float min, float max) { pfnc_nvnSamplerBuilderSetLodClamp(builder, min, max); }

inline void nvnSamplerBuilderSetMaxAnisotropy(NVNsamplerBuilder *builder, float maxAniso) { pfnc_nvnSamplerBuilderSetMaxAnisotropy(builder, maxAniso); }

inline void nvnSamplerBuilderSetMinMagFilter(NVNsamplerBuilder *builder, NVNminFilter min, NVNmagFilter mag) { pfnc_nvnSamplerBuilderSetMinMagFilter(builder, min, mag); }

inline void nvnSamplerBuilderSetWrapMode(NVNsamplerBuilder *builder, NVNwrapMode s, NVNwrapMode t, NVNwrapMode r) { pfnc_nvnSamplerBuilderSetWrapMode(builder, s, t, r); }

inline void nvnSamplerFinalize(NVNsampler *sampler) { pfnc_nvnSamplerFinalize(sampler); }

inline NVNboolean nvnSamplerInitialize(NVNsampler *sampler, const NVNsamplerBuilder *builder) { return pfnc_nvnSamplerInitialize(sampler, builder); }

inline void nvnSamplerPoolRegisterSampler(const NVNsamplerPool *pool, int id, const NVNsampler *sampler) { pfnc_nvnSamplerPoolRegisterSampler(pool, id, sampler); }

inline void nvnSyncFinalize(NVNsync *sync) { pfnc_nvnSyncFinalize(sync); }

inline NVNboolean nvnSyncInitialize(NVNsync *sync, NVNdevice *device) { return pfnc_nvnSyncInitialize(sync, device); }

inline NVNsyncWaitResult nvnSyncWait(const NVNsync *sync, u64 timeoutNs) { return pfnc_nvnSyncWait(sync, timeoutNs); }

inline void nvnTextureBuilderSetDepthStencilMode(NVNtextureBuilder *builder, NVNtextureDepthStencilMode mode) { pfnc_nvnTextureBuilderSetDepthStencilMode(builder, mode); }

inline void nvnTextureBuilderSetPackagedTextureData(NVNtextureBuilder *builder, const void *data) { pfnc_nvnTextureBuilderSetPackagedTextureData(builder, data); }

inline void nvnTextureBuilderSetStorage(NVNtextureBuilder *builder, NVNmemoryPool *pool, ptrdiff_t offset) { pfnc_nvnTextureBuilderSetStorage(builder, pool, offset); }

inline void nvnTextureBuilderSetStride(NVNtextureBuilder *builder, ptrdiff_t stride) { pfnc_nvnTextureBuilderSetStride(builder, stride); }

inline void nvnTextureBuilderSetSwizzle(NVNtextureBuilder *builder, NVNtextureSwizzle r, NVNtextureSwizzle g, NVNtextureSwizzle b, NVNtextureSwizzle a) {
  pfnc_nvnTextureBuilderSetSwizzle(builder, r, g, b, a);
}

inline NVNboolean nvnTextureInitialize(NVNtexture *texture, const NVNtextureBuilder *builder) { return pfnc_nvnTextureInitialize(texture, builder); }

inline void nvnTextureViewSetDefaults(NVNtextureView *view) { pfnc_nvnTextureViewSetDefaults(view); }

inline void nvnTextureViewSetFormat(NVNtextureView *view, NVNformat format) { pfnc_nvnTextureViewSetFormat(view, format); }

inline void nvnTextureViewSetLayers(NVNtextureView *view, int minLayer, int numLayers) { pfnc_nvnTextureViewSetLayers(view, minLayer, numLayers); }

inline void nvnTextureViewSetLevels(NVNtextureView *view, int baseLevel, int numLevels) { pfnc_nvnTextureViewSetLevels(view, baseLevel, numLevels); }

inline void nvnTextureViewSetTarget(NVNtextureView *view, NVNtextureTarget target) { pfnc_nvnTextureViewSetTarget(view, target); }

inline void nvnVertexAttribStateSetDefaults(NVNvertexAttribState *attrib) { pfnc_nvnVertexAttribStateSetDefaults(attrib); }

inline void nvnVertexAttribStateSetFormat(NVNvertexAttribState *attrib, NVNformat format, ptrdiff_t relativeOffset) { pfnc_nvnVertexAttribStateSetFormat(attrib, format, relativeOffset); }

inline void nvnVertexAttribStateSetStreamIndex(NVNvertexAttribState *attrib, int streamIndex) { pfnc_nvnVertexAttribStateSetStreamIndex(attrib, streamIndex); }

inline NVNwindowAcquireTextureResult nvnWindowAcquireTexture(NVNwindow *window, NVNsync *textureAvailableSync, int *textureIndex) {
  return pfnc_nvnWindowAcquireTexture(window, textureAvailableSync, textureIndex);
}

inline void nvnWindowBuilderSetDefaults(NVNwindowBuilder *builder) { pfnc_nvnWindowBuilderSetDefaults(builder); }

inline void nvnWindowBuilderSetDevice(NVNwindowBuilder *builder, NVNdevice *device) { pfnc_nvnWindowBuilderSetDevice(builder, device); }

inline void nvnWindowBuilderSetNativeWindow(NVNwindowBuilder *builder, NVNnativeWindow nativeWindow) { pfnc_nvnWindowBuilderSetNativeWindow(builder, nativeWindow); }

inline void nvnWindowBuilderSetTextures(NVNwindowBuilder *builder, int numTextures, NVNtexture *const *textures) { pfnc_nvnWindowBuilderSetTextures(builder, numTextures, textures); }

inline void nvnWindowFinalize(NVNwindow *window) { pfnc_nvnWindowFinalize(window); }

inline NVNboolean nvnWindowInitialize(NVNwindow *window, const NVNwindowBuilder *builder) { return pfnc_nvnWindowInitialize(window, builder); }

// Provenance: public NVN API, as declared in the open-ead nnheaders project (https://github.com/open-ead/nnheaders,
// include/nvn/nvn.h for the function pointer types and nvnBootstrapLoader, include/nvn/nvn_FuncPtrBase.h for
// nvnLoadCProcs); both are C symbols of the game (work/syms_base.txt), called by grlib::CGLibDeviceObj::init.
typedef void (*PFNNVNGENERICFUNCPTRPROC)(void);
typedef PFNNVNGENERICFUNCPTRPROC (*PFNNVNDEVICEGETPROCADDRESSPROC)(const NVNdevice *device, const char *name);

extern "C" {
PFNNVNGENERICFUNCPTRPROC nvnBootstrapLoader(const char *name);
void nvnLoadCProcs(const NVNdevice *device, PFNNVNDEVICEGETPROCADDRESSPROC deviceGetProcAddress);
}
