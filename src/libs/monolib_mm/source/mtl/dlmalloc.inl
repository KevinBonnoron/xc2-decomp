// Memory allocator embedded by Monolith Soft in monolib_mm: the game's assertion strings name this file
// `C:/Monolithsoft/BF2/prog/libs/monolib_mm/proj/windows/../../source\mtl/dlmalloc.inl`. It is included by mtl_mem_manager.cpp.
//
// Provenance: this is dlmalloc 2.8.6 (29 Aug 2012) by Doug Lea, released to the public domain (CC0,
// http://creativecommons.org/publicdomain/zero/1.0/); the public source is ftp://gee.cs.oswego.edu/pub/misc/malloc.c.
// The names of the functions, static helpers, structs, members and macros below come from that public source, not from the
// game's symbols (the game only exports the mspace_ functions and create_mspace, destroy_mspace; mspace_set_stats is Monolith's).
// Only the code the game compiles is kept, in the order of the original. The configuration macros are deduced from the
// machine code; the game's own header is not known:
//   ONLY_MSPACES 1 (no dl-prefixed malloc), FOOTERS 1 (the prev_foot of the chunk after an in use chunk holds mstate ^ mparams.magic),
//   HAVE_MMAP 0 and HAVE_MORECORE 0 (sys_alloc never obtains memory), USE_LOCKS 0 (no lock in malloc_state: seg is at 0x378),
//   DEBUG 0 (the check_ functions are compiled out) with the assert of the C library (a failure calls __assert_fail),
//   MALLOC_FAILURE_ACTION empty, default alignment (16), granularity (64 KiB) and trim threshold (2 MiB), page size 4096 (the
//   fallback of malloc_getpagesize); every other option keeps the default of 2.8.6.
// Differences from the public source that the machine code shows: create_mspace and create_mspace_with_base have no `locked`
// parameter (DlAllocator::create calls the latter with two arguments), the corruption action does nothing (instead of
// reset_on_error), `extp` is the name of the space (set to "" by init_user_mstate and by mspace_set_stats, which does not exist
// in dlmalloc), the magic of init_mparams is a constant instead of time(0) ^ 0x55555555, and the `goto postaction` and
// `goto erroraction` of mspace_malloc and mspace_free are returns (POSTACTION and USAGE_ERROR_ACTION are empty here).
// Evidence for the version: mspace_footprint_limit, mspace_set_footprint_limit, mspace_bulk_free and mspace_track_large_chunks
// exist (2.8.5 and later); mspace_realloc_in_place, mspace_bulk_free, mspace_footprint_limit and mspace_set_footprint_limit have no
// extern "C" prototype in the 2.8.6 header excerpt, which is why their game symbols are C++ mangled; every function below
// compiles to the game's machine code with clang 3.9.1.

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DLMALLOC_VERSION 20806
#define DLMALLOC_EXPORT extern

#define MAX_SIZE_T (~(size_t)0)
#define MALLOC_ALIGNMENT ((size_t)(2 * sizeof(void *)))
#define HAVE_MMAP 0
#define HAVE_MORECORE 0
#define MORECORE_CONTIGUOUS 0
#define NO_SEGMENT_TRAVERSAL 0
#define DEFAULT_GRANULARITY ((size_t)64U * (size_t)1024U)
#define DEFAULT_TRIM_THRESHOLD ((size_t)2U * (size_t)1024U * (size_t)1024U)
#define DEFAULT_MMAP_THRESHOLD MAX_SIZE_T
#define MAX_RELEASE_CHECK_RATE MAX_SIZE_T
#define ABORT abort()
#define MALLOC_FAILURE_ACTION
#define M_TRIM_THRESHOLD (-1)
#define M_GRANULARITY (-2)
#define M_MMAP_THRESHOLD (-3)
#define malloc_getpagesize ((size_t)4096U)

#define MALLINFO_FIELD_TYPE size_t
struct mallinfo {
  MALLINFO_FIELD_TYPE arena;    /* non-mmapped space allocated from system */
  MALLINFO_FIELD_TYPE ordblks;  /* number of free chunks */
  MALLINFO_FIELD_TYPE smblks;   /* always 0 */
  MALLINFO_FIELD_TYPE hblks;    /* always 0 */
  MALLINFO_FIELD_TYPE hblkhd;   /* space in mmapped regions */
  MALLINFO_FIELD_TYPE usmblks;  /* maximum total allocated space */
  MALLINFO_FIELD_TYPE fsmblks;  /* always 0 */
  MALLINFO_FIELD_TYPE uordblks; /* total allocated space */
  MALLINFO_FIELD_TYPE fordblks; /* total free space */
  MALLINFO_FIELD_TYPE keepcost; /* releasable (via malloc_trim) space */
};

typedef void *mspace;

extern "C" {
DLMALLOC_EXPORT mspace create_mspace(size_t capacity);
DLMALLOC_EXPORT size_t destroy_mspace(mspace msp);
DLMALLOC_EXPORT mspace create_mspace_with_base(void *base, size_t capacity);
DLMALLOC_EXPORT int mspace_track_large_chunks(mspace msp, int enable);
DLMALLOC_EXPORT void *mspace_malloc(mspace msp, size_t bytes);
DLMALLOC_EXPORT void mspace_free(mspace msp, void *mem);
DLMALLOC_EXPORT void *mspace_realloc(mspace msp, void *mem, size_t newsize);
DLMALLOC_EXPORT void *mspace_calloc(mspace msp, size_t n_elements, size_t elem_size);
DLMALLOC_EXPORT void *mspace_memalign(mspace msp, size_t alignment, size_t bytes);
DLMALLOC_EXPORT void **mspace_independent_calloc(mspace msp, size_t n_elements, size_t elem_size, void *chunks[]);
DLMALLOC_EXPORT void **mspace_independent_comalloc(mspace msp, size_t n_elements, size_t sizes[], void *chunks[]);
DLMALLOC_EXPORT size_t mspace_footprint(mspace msp);
DLMALLOC_EXPORT size_t mspace_max_footprint(mspace msp);
DLMALLOC_EXPORT struct mallinfo mspace_mallinfo(mspace msp);
DLMALLOC_EXPORT size_t mspace_usable_size(const void *mem);
DLMALLOC_EXPORT void mspace_malloc_stats(mspace msp);
DLMALLOC_EXPORT int mspace_trim(mspace msp, size_t pad);
DLMALLOC_EXPORT int mspace_mallopt(int, int);
}

#define DEBUG 0

#define SIZE_T_SIZE (sizeof(size_t))
#define SIZE_T_BITSIZE (sizeof(size_t) << 3)

#define SIZE_T_ZERO ((size_t)0)
#define SIZE_T_ONE ((size_t)1)
#define SIZE_T_TWO ((size_t)2)
#define SIZE_T_FOUR ((size_t)4)
#define TWO_SIZE_T_SIZES (SIZE_T_SIZE << 1)
#define FOUR_SIZE_T_SIZES (SIZE_T_SIZE << 2)
#define SIX_SIZE_T_SIZES (FOUR_SIZE_T_SIZES + TWO_SIZE_T_SIZES)
#define HALF_MAX_SIZE_T (MAX_SIZE_T / 2U)

#define CHUNK_ALIGN_MASK (MALLOC_ALIGNMENT - SIZE_T_ONE)

/* True if address a has acceptable alignment */
#define is_aligned(A) (((size_t)((A)) & (CHUNK_ALIGN_MASK)) == 0)

/* the number of bytes to offset an address to align it */
#define align_offset(A) ((((size_t)(A) & CHUNK_ALIGN_MASK) == 0) ? 0 : ((MALLOC_ALIGNMENT - ((size_t)(A) & CHUNK_ALIGN_MASK)) & CHUNK_ALIGN_MASK))

#define MFAIL ((void *)(MAX_SIZE_T))
#define CMFAIL ((char *)(MFAIL))

#define CALL_MORECORE(S) MFAIL

#define USE_MMAP_BIT (SIZE_T_ZERO)
#define MMAP(s) MFAIL
#define MUNMAP(a, s) (-1)
#define DIRECT_MMAP(s) MFAIL
#define CALL_DIRECT_MMAP(s) DIRECT_MMAP(s)
#define CALL_MMAP(s) MMAP(s)
#define CALL_MUNMAP(a, s) MUNMAP((a), (s))
#define CALL_MREMAP(addr, osz, nsz, mv) MFAIL

#define USE_NONCONTIGUOUS_BIT (4U)

/* segment bit set in create_mspace_with_base */
#define EXTERN_BIT (8U)

#define USE_LOCK_BIT (0U)
#define INITIAL_LOCK(l) (0)
#define DESTROY_LOCK(l) (0)
#define ACQUIRE_MALLOC_GLOBAL_LOCK()
#define RELEASE_MALLOC_GLOBAL_LOCK()

struct malloc_chunk {
  size_t prev_foot;        /* Size of previous chunk (if free).  */
  size_t head;             /* Size and inuse bits. */
  struct malloc_chunk *fd; /* double links -- used only if free. */
  struct malloc_chunk *bk;
};

typedef struct malloc_chunk mchunk;
typedef struct malloc_chunk *mchunkptr;
typedef struct malloc_chunk *sbinptr; /* The type of bins of chunks */
typedef unsigned int bindex_t;        /* Described below */
typedef unsigned int binmap_t;        /* Described below */
typedef unsigned int flag_t;          /* The type of various bit flag sets */

/* ------------------- Chunks sizes and alignments ----------------------- */

#define MCHUNK_SIZE (sizeof(mchunk))

#define CHUNK_OVERHEAD (TWO_SIZE_T_SIZES)

/* MMapped chunks need a second word of overhead ... */
#define MMAP_CHUNK_OVERHEAD (TWO_SIZE_T_SIZES)
/* ... and additional padding for fake next-chunk at foot */
#define MMAP_FOOT_PAD (FOUR_SIZE_T_SIZES)

/* The smallest size we can malloc is an aligned minimal chunk */
#define MIN_CHUNK_SIZE ((MCHUNK_SIZE + CHUNK_ALIGN_MASK) & ~CHUNK_ALIGN_MASK)

/* conversion from malloc headers to user pointers, and back */
#define chunk2mem(p) ((void *)((char *)(p) + TWO_SIZE_T_SIZES))
#define mem2chunk(mem) ((mchunkptr)((char *)(mem) - TWO_SIZE_T_SIZES))
/* chunk associated with aligned address A */
#define align_as_chunk(A) (mchunkptr)((A) + align_offset(chunk2mem(A)))

/* Bounds on request (not chunk) sizes. */
#define MAX_REQUEST ((-MIN_CHUNK_SIZE) << 2)
#define MIN_REQUEST (MIN_CHUNK_SIZE - CHUNK_OVERHEAD - SIZE_T_ONE)

/* pad request bytes into a usable size */
#define pad_request(req) (((req) + CHUNK_OVERHEAD + CHUNK_ALIGN_MASK) & ~CHUNK_ALIGN_MASK)

/* pad request, checking for minimum (but not maximum) */
#define request2size(req) (((req) < MIN_REQUEST) ? MIN_CHUNK_SIZE : pad_request(req))

/* ------------------ Operations on head and foot fields ----------------- */

#define PINUSE_BIT (SIZE_T_ONE)
#define CINUSE_BIT (SIZE_T_TWO)
#define FLAG4_BIT (SIZE_T_FOUR)
#define INUSE_BITS (PINUSE_BIT | CINUSE_BIT)
#define FLAG_BITS (PINUSE_BIT | CINUSE_BIT | FLAG4_BIT)

/* Head value for fenceposts */
#define FENCEPOST_HEAD (INUSE_BITS | SIZE_T_SIZE)

/* extraction of fields from head words */
#define cinuse(p) ((p)->head & CINUSE_BIT)
#define pinuse(p) ((p)->head & PINUSE_BIT)
#define flag4inuse(p) ((p)->head & FLAG4_BIT)
#define is_inuse(p) (((p)->head & INUSE_BITS) != PINUSE_BIT)
#define is_mmapped(p) (((p)->head & INUSE_BITS) == 0)

#define chunksize(p) ((p)->head & ~(FLAG_BITS))

#define clear_pinuse(p) ((p)->head &= ~PINUSE_BIT)
#define set_flag4(p) ((p)->head |= FLAG4_BIT)
#define clear_flag4(p) ((p)->head &= ~FLAG4_BIT)

/* Treat space at ptr +/- offset as a chunk */
#define chunk_plus_offset(p, s) ((mchunkptr)(((char *)(p)) + (s)))
#define chunk_minus_offset(p, s) ((mchunkptr)(((char *)(p)) - (s)))

/* Ptr to next or previous physical malloc_chunk. */
#define next_chunk(p) ((mchunkptr)(((char *)(p)) + ((p)->head & ~FLAG_BITS)))
#define prev_chunk(p) ((mchunkptr)(((char *)(p)) - ((p)->prev_foot)))

/* extract next chunk's pinuse bit */
#define next_pinuse(p) ((next_chunk(p)->head) & PINUSE_BIT)

/* Get/set size at footer */
#define get_foot(p, s) (((mchunkptr)((char *)(p) + (s)))->prev_foot)
#define set_foot(p, s) (((mchunkptr)((char *)(p) + (s)))->prev_foot = (s))

/* Set size, pinuse bit, and foot */
#define set_size_and_pinuse_of_free_chunk(p, s) ((p)->head = (s | PINUSE_BIT), set_foot(p, s))

/* Set size, pinuse bit, foot, and clear next pinuse */
#define set_free_with_pinuse(p, s, n) (clear_pinuse(n), set_size_and_pinuse_of_free_chunk(p, s))

/* Get the internal overhead associated with chunk p */
#define overhead_for(p) (is_mmapped(p) ? MMAP_CHUNK_OVERHEAD : CHUNK_OVERHEAD)

/* Return true if malloced space is not necessarily cleared */
#define calloc_must_clear(p) (!is_mmapped(p))

/* ---------------------- Overlaid data structures ----------------------- */

struct malloc_tree_chunk {
  /* The first four fields must be compatible with malloc_chunk */
  size_t prev_foot;
  size_t head;
  struct malloc_tree_chunk *fd;
  struct malloc_tree_chunk *bk;

  struct malloc_tree_chunk *child[2];
  struct malloc_tree_chunk *parent;
  bindex_t index;
};

typedef struct malloc_tree_chunk tchunk;
typedef struct malloc_tree_chunk *tchunkptr;
typedef struct malloc_tree_chunk *tbinptr; /* The type of bins of trees */

/* A little helper macro for trees */
#define leftmost_child(t) ((t)->child[0] != 0 ? (t)->child[0] : (t)->child[1])

/* ----------------------------- Segments -------------------------------- */

struct malloc_segment {
  char *base;                  /* base address */
  size_t size;                 /* allocated size */
  struct malloc_segment *next; /* ptr to next segment */
  flag_t sflags;               /* mmap and extern flag */
};

#define is_mmapped_segment(S) ((S)->sflags & USE_MMAP_BIT)
#define is_extern_segment(S) ((S)->sflags & EXTERN_BIT)

typedef struct malloc_segment msegment;
typedef struct malloc_segment *msegmentptr;

/* ---------------------------- malloc_state ----------------------------- */

/* Bin types, widths and sizes */
#define NSMALLBINS (32U)
#define NTREEBINS (32U)
#define SMALLBIN_SHIFT (3U)
#define SMALLBIN_WIDTH (SIZE_T_ONE << SMALLBIN_SHIFT)
#define TREEBIN_SHIFT (8U)
#define MIN_LARGE_SIZE (SIZE_T_ONE << TREEBIN_SHIFT)
#define MAX_SMALL_SIZE (MIN_LARGE_SIZE - SIZE_T_ONE)
#define MAX_SMALL_REQUEST (MAX_SMALL_SIZE - CHUNK_ALIGN_MASK - CHUNK_OVERHEAD)

struct malloc_state {
  binmap_t smallmap;
  binmap_t treemap;
  size_t dvsize;
  size_t topsize;
  char *least_addr;
  mchunkptr dv;
  mchunkptr top;
  size_t trim_check;
  size_t release_checks;
  size_t magic;
  mchunkptr smallbins[(NSMALLBINS + 1) * 2];
  tbinptr treebins[NTREEBINS];
  size_t footprint;
  size_t max_footprint;
  size_t footprint_limit; /* zero means no limit */
  flag_t mflags;
  msegment seg;
  const char *extp; /* dlmalloc: void *extp, unused but available for extensions; Monolith keeps the name of the space here (mspace_set_stats) */
  size_t exts;
};

typedef struct malloc_state *mstate;

/* ------------- Global malloc_state and malloc_params ------------------- */

struct malloc_params {
  size_t magic;
  size_t page_size;
  size_t granularity;
  size_t mmap_threshold;
  size_t trim_threshold;
  flag_t default_mflags;
};

static struct malloc_params mparams;

/* Ensure mparams initialized */
#define ensure_initialization() (void)(mparams.magic != 0 || init_mparams())

/* ---------------------------- system alloc setup ------------------------- */

/* Operations on mflags */

#define is_initialized(M) ((M)->top != 0)

#define use_lock(M) ((M)->mflags & USE_LOCK_BIT)
#define enable_lock(M) ((M)->mflags |= USE_LOCK_BIT)
#define disable_lock(M)

#define use_mmap(M) ((M)->mflags & USE_MMAP_BIT)
#define enable_mmap(M) ((M)->mflags |= USE_MMAP_BIT)
#define disable_mmap(M)

#define use_noncontiguous(M) ((M)->mflags & USE_NONCONTIGUOUS_BIT)
#define disable_contiguous(M) ((M)->mflags |= USE_NONCONTIGUOUS_BIT)

/* page-align a size */
#define page_align(S) (((S) + (mparams.page_size - SIZE_T_ONE)) & ~(mparams.page_size - SIZE_T_ONE))

/* granularity-align a size */
#define granularity_align(S) (((S) + (mparams.granularity - SIZE_T_ONE)) & ~(mparams.granularity - SIZE_T_ONE))

/* For mmap, use granularity alignment on windows, else page-align */
#define mmap_align(S) page_align(S)

/* For sys_alloc, enough padding to ensure can malloc request on success */
#define SYS_ALLOC_PADDING (TOP_FOOT_SIZE + MALLOC_ALIGNMENT)

#define is_page_aligned(S) (((size_t)(S) & (mparams.page_size - SIZE_T_ONE)) == 0)
#define is_granularity_aligned(S) (((size_t)(S) & (mparams.granularity - SIZE_T_ONE)) == 0)

/*  True if segment S holds address A */
#define segment_holds(S, A) ((char *)(A) >= S->base && (char *)(A) < S->base + S->size)

/* Return segment holding given address */
static msegmentptr segment_holding(mstate m, char *addr) {
  msegmentptr sp = &m->seg;
  for (;;) {
    if (addr >= sp->base && addr < sp->base + sp->size)
      return sp;
    if ((sp = sp->next) == 0)
      return 0;
  }
}

/* Return true if segment contains a segment link */
static int has_segment_link(mstate m, msegmentptr ss) {
  msegmentptr sp = &m->seg;
  for (;;) {
    if ((char *)sp >= ss->base && (char *)sp < ss->base + ss->size)
      return 1;
    if ((sp = sp->next) == 0)
      return 0;
  }
}

#define should_trim(M, s) ((s) > (M)->trim_check)

/*
  TOP_FOOT_SIZE is padding at the end of a segment, including space
  that may be needed to place segment records and fenceposts when new
  noncontiguous segments are added.
*/
#define TOP_FOOT_SIZE (align_offset(chunk2mem(0)) + pad_request(sizeof(struct malloc_segment)) + MIN_CHUNK_SIZE)

/* -------------------------------  Hooks -------------------------------- */

#define PREACTION(M) (0)
#define POSTACTION(M)

/* ---------------------------- Debugging Support ------------------------ */

#define check_free_chunk(M, P)
#define check_inuse_chunk(M, P)
#define check_malloced_chunk(M, P, N)
#define check_mmapped_chunk(M, P)
#define check_malloc_state(M)
#define check_top_chunk(M, P)

/* ---------------------------- Indexing Bins ---------------------------- */

#define is_small(s) (((s) >> SMALLBIN_SHIFT) < NSMALLBINS)
#define small_index(s) (bindex_t)((s) >> SMALLBIN_SHIFT)
#define small_index2size(i) ((i) << SMALLBIN_SHIFT)
#define MIN_SMALL_INDEX (small_index(MIN_CHUNK_SIZE))

/* addressing by index. See above about smallbin repositioning */
#define smallbin_at(M, i) ((sbinptr)((char *)&((M)->smallbins[(i) << 1])))
#define treebin_at(M, i) (&((M)->treebins[i]))

/* Compute index for size. */
#define compute_tree_index(S, I)                                                                                                                                                                       \
  {                                                                                                                                                                                                    \
    size_t X = S >> TREEBIN_SHIFT;                                                                                                                                                                     \
    if (X == 0)                                                                                                                                                                                        \
      I = 0;                                                                                                                                                                                           \
    else if (X > 0xFFFF)                                                                                                                                                                               \
      I = NTREEBINS - 1;                                                                                                                                                                               \
    else {                                                                                                                                                                                             \
      unsigned int Y = (unsigned int)X;                                                                                                                                                                \
      unsigned int N = ((Y - 0x100) >> 16) & 8;                                                                                                                                                        \
      unsigned int K = (((Y <<= N) - 0x1000) >> 16) & 4;                                                                                                                                               \
      N += K;                                                                                                                                                                                          \
      N += K = (((Y <<= K) - 0x4000) >> 16) & 2;                                                                                                                                                       \
      K = 14 - N + ((Y <<= K) >> 15);                                                                                                                                                                  \
      I = (K << 1) + ((S >> (K + (TREEBIN_SHIFT - 1)) & 1));                                                                                                                                           \
    }                                                                                                                                                                                                  \
  }

/* Shift placing maximum resolved bit in a treebin at i as sign bit */
#define leftshift_for_tree_index(i) ((i == NTREEBINS - 1) ? 0 : ((SIZE_T_BITSIZE - SIZE_T_ONE) - (((i) >> 1) + TREEBIN_SHIFT - 2)))

/* ------------------------ Operations on bin maps ----------------------- */

/* bit corresponding to given index */
#define idx2bit(i) ((binmap_t)(1) << (i))

/* Mark/Clear bits with given index */
#define mark_smallmap(M, i) ((M)->smallmap |= idx2bit(i))
#define clear_smallmap(M, i) ((M)->smallmap &= ~idx2bit(i))
#define smallmap_is_marked(M, i) ((M)->smallmap & idx2bit(i))

#define mark_treemap(M, i) ((M)->treemap |= idx2bit(i))
#define clear_treemap(M, i) ((M)->treemap &= ~idx2bit(i))
#define treemap_is_marked(M, i) ((M)->treemap & idx2bit(i))

/* isolate the least set bit of a bitmap */
#define least_bit(x) ((x) & -(x))

/* mask with all bits to left of least bit of x on */
#define left_bits(x) ((x << 1) | -(x << 1))

/* index corresponding to given bit. */
#define compute_bit2idx(X, I)                                                                                                                                                                          \
  {                                                                                                                                                                                                    \
    unsigned int Y = X - 1;                                                                                                                                                                            \
    unsigned int K = Y >> (16 - 4) & 16;                                                                                                                                                               \
    unsigned int N = K;                                                                                                                                                                                \
    Y >>= K;                                                                                                                                                                                           \
    N += K = Y >> (8 - 3) & 8;                                                                                                                                                                         \
    Y >>= K;                                                                                                                                                                                           \
    N += K = Y >> (4 - 2) & 4;                                                                                                                                                                         \
    Y >>= K;                                                                                                                                                                                           \
    N += K = Y >> (2 - 1) & 2;                                                                                                                                                                         \
    Y >>= K;                                                                                                                                                                                           \
    N += K = Y >> (1 - 0) & 1;                                                                                                                                                                         \
    Y >>= K;                                                                                                                                                                                           \
    I = (bindex_t)(N + Y);                                                                                                                                                                             \
  }

/* ----------------------- Runtime Check Support ------------------------- */

/* Check if address a is at least as high as any from MORECORE or MMAP */
#define ok_address(M, a) ((char *)(a) >= (M)->least_addr)
/* Check if address of next chunk n is higher than base chunk p */
#define ok_next(p, n) ((char *)(p) < (char *)(n))
/* Check if p has inuse status */
#define ok_inuse(p) is_inuse(p)
/* Check if p has its pinuse bit on */
#define ok_pinuse(p) pinuse(p)

/* Check if (alleged) mstate m has expected magic field */
#define ok_magic(M) ((M)->magic == mparams.magic)

/* In gcc, use __builtin_expect to minimize impact of checks */
#define RTCHECK(e) __builtin_expect(e, 1)

/* macros to set up inuse chunks with or without footers */

#define mark_inuse_foot(M, p, s) (((mchunkptr)((char *)(p) + (s)))->prev_foot = ((size_t)(M) ^ mparams.magic))

#define get_mstate_for(p) ((mstate)(((mchunkptr)((char *)(p) + (chunksize(p))))->prev_foot ^ mparams.magic))

#define set_inuse(M, p, s) ((p)->head = (((p)->head & PINUSE_BIT) | s | CINUSE_BIT), (((mchunkptr)(((char *)(p)) + (s)))->head |= PINUSE_BIT), mark_inuse_foot(M, p, s))

#define set_inuse_and_pinuse(M, p, s) ((p)->head = (s | PINUSE_BIT | CINUSE_BIT), (((mchunkptr)(((char *)(p)) + (s)))->head |= PINUSE_BIT), mark_inuse_foot(M, p, s))

#define set_size_and_pinuse_of_inuse_chunk(M, p, s) ((p)->head = (s | PINUSE_BIT | CINUSE_BIT), mark_inuse_foot(M, p, s))

/* ---------------------------- setting mparams -------------------------- */

/* corruption and usage errors are ignored (dlmalloc's PROCEED_ON_ERROR resets the space on corruption) */
#define CORRUPTION_ERROR_ACTION(m)
#define USAGE_ERROR_ACTION(m, p)

/* Initialize mparams */
static int init_mparams(void) {
  ACQUIRE_MALLOC_GLOBAL_LOCK();
  if (mparams.magic == 0) {
    size_t magic;
    size_t psize;
    size_t gsize;

    psize = malloc_getpagesize;
    gsize = ((DEFAULT_GRANULARITY != 0) ? DEFAULT_GRANULARITY : psize);

    /* Sanity-check configuration:
       size_t must be unsigned and as wide as pointer type.
       ints must be at least 4 bytes.
       alignment must be at least 8.
       Alignment, min chunk size, and page size must all be powers of 2.
    */
    if ((sizeof(size_t) != sizeof(char *)) || (MAX_SIZE_T < MIN_CHUNK_SIZE) || (sizeof(int) < 4) || (MALLOC_ALIGNMENT < (size_t)8U) || ((MALLOC_ALIGNMENT & (MALLOC_ALIGNMENT - SIZE_T_ONE)) != 0) ||
        ((MCHUNK_SIZE & (MCHUNK_SIZE - SIZE_T_ONE)) != 0) || ((gsize & (gsize - SIZE_T_ONE)) != 0) || ((psize & (psize - SIZE_T_ONE)) != 0))
      ABORT;
    mparams.granularity = gsize;
    mparams.page_size = psize;
    mparams.mmap_threshold = DEFAULT_MMAP_THRESHOLD;
    mparams.trim_threshold = DEFAULT_TRIM_THRESHOLD;
    mparams.default_mflags = USE_LOCK_BIT | USE_MMAP_BIT | USE_NONCONTIGUOUS_BIT;

    {
      // The game stores this constant where dlmalloc has `(size_t)(time(0) ^ (size_t)0x55555555U)`.
      magic = (size_t)0x520e9848U;
      magic |= (size_t)8U;  /* ensure nonzero */
      magic &= ~(size_t)7U; /* improve chances of fault for bad values */
      /* Until memory modes commonly available, use volatile-write */
      (*(volatile size_t *)(&(mparams.magic))) = magic;
    }
  }

  RELEASE_MALLOC_GLOBAL_LOCK();
  return 1;
}

/* support for mallopt */
static int change_mparam(int param_number, int value) {
  size_t val;
  ensure_initialization();
  val = (value == -1) ? MAX_SIZE_T : (size_t)value;
  switch (param_number) {
  case M_TRIM_THRESHOLD:
    mparams.trim_threshold = val;
    return 1;
  case M_GRANULARITY:
    if (val >= mparams.page_size && ((val & (val - 1)) == 0)) {
      mparams.granularity = val;
      return 1;
    } else
      return 0;
  case M_MMAP_THRESHOLD:
    mparams.mmap_threshold = val;
    return 1;
  default:
    return 0;
  }
}

static struct mallinfo internal_mallinfo(mstate m) {
  struct mallinfo nm = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  ensure_initialization();
  if (!PREACTION(m)) {
    check_malloc_state(m);
    if (is_initialized(m)) {
      size_t nfree = SIZE_T_ONE; /* top always free */
      size_t mfree = m->topsize + TOP_FOOT_SIZE;
      size_t sum = mfree;
      msegmentptr s = &m->seg;
      while (s != 0) {
        mchunkptr q = align_as_chunk(s->base);
        while (segment_holds(s, q) && q != m->top && q->head != FENCEPOST_HEAD) {
          size_t sz = chunksize(q);
          sum += sz;
          if (!is_inuse(q)) {
            mfree += sz;
            ++nfree;
          }
          q = next_chunk(q);
        }
        s = s->next;
      }

      nm.arena = sum;
      nm.ordblks = nfree;
      nm.hblkhd = m->footprint - sum;
      nm.usmblks = m->max_footprint;
      nm.uordblks = m->footprint - mfree;
      nm.fordblks = mfree;
      nm.keepcost = m->topsize;
    }

    POSTACTION(m);
  }
  return nm;
}

static void internal_malloc_stats(mstate m) {
  ensure_initialization();
  if (!PREACTION(m)) {
    size_t maxfp = 0;
    size_t fp = 0;
    size_t used = 0;
    check_malloc_state(m);
    if (is_initialized(m)) {
      msegmentptr s = &m->seg;
      maxfp = m->max_footprint;
      fp = m->footprint;
      used = fp - (m->topsize + TOP_FOOT_SIZE);

      while (s != 0) {
        mchunkptr q = align_as_chunk(s->base);
        while (segment_holds(s, q) && q != m->top && q->head != FENCEPOST_HEAD) {
          if (!is_inuse(q))
            used -= chunksize(q);
          q = next_chunk(q);
        }
        s = s->next;
      }
    }
    POSTACTION(m); /* drop lock */
    fprintf(stderr, "max system bytes = %10lu\n", (unsigned long)(maxfp));
    fprintf(stderr, "system bytes     = %10lu\n", (unsigned long)(fp));
    fprintf(stderr, "in use bytes     = %10lu\n", (unsigned long)(used));
  }
}

/* -----------------------  Operations on smallbins  ----------------------- */

/* Link a free chunk into a smallbin  */
#define insert_small_chunk(M, P, S)                                                                                                                                                                    \
  {                                                                                                                                                                                                    \
    bindex_t I = small_index(S);                                                                                                                                                                       \
    mchunkptr B = smallbin_at(M, I);                                                                                                                                                                   \
    mchunkptr F = B;                                                                                                                                                                                   \
    assert(S >= MIN_CHUNK_SIZE);                                                                                                                                                                       \
    if (!smallmap_is_marked(M, I))                                                                                                                                                                     \
      mark_smallmap(M, I);                                                                                                                                                                             \
    else if (RTCHECK(ok_address(M, B->fd)))                                                                                                                                                            \
      F = B->fd;                                                                                                                                                                                       \
    else {                                                                                                                                                                                             \
      CORRUPTION_ERROR_ACTION(M);                                                                                                                                                                      \
    }                                                                                                                                                                                                  \
    B->fd = P;                                                                                                                                                                                         \
    F->bk = P;                                                                                                                                                                                         \
    P->fd = F;                                                                                                                                                                                         \
    P->bk = B;                                                                                                                                                                                         \
  }

/* Unlink a chunk from a smallbin  */
#define unlink_small_chunk(M, P, S)                                                                                                                                                                    \
  {                                                                                                                                                                                                    \
    mchunkptr F = P->fd;                                                                                                                                                                               \
    mchunkptr B = P->bk;                                                                                                                                                                               \
    bindex_t I = small_index(S);                                                                                                                                                                       \
    assert(P != B);                                                                                                                                                                                    \
    assert(P != F);                                                                                                                                                                                    \
    assert(chunksize(P) == small_index2size(I));                                                                                                                                                       \
    if (RTCHECK(F == smallbin_at(M, I) || (ok_address(M, F) && F->bk == P))) {                                                                                                                         \
      if (B == F) {                                                                                                                                                                                    \
        clear_smallmap(M, I);                                                                                                                                                                          \
      } else if (RTCHECK(B == smallbin_at(M, I) || (ok_address(M, B) && B->fd == P))) {                                                                                                                \
        F->bk = B;                                                                                                                                                                                     \
        B->fd = F;                                                                                                                                                                                     \
      } else {                                                                                                                                                                                         \
        CORRUPTION_ERROR_ACTION(M);                                                                                                                                                                    \
      }                                                                                                                                                                                                \
    } else {                                                                                                                                                                                           \
      CORRUPTION_ERROR_ACTION(M);                                                                                                                                                                      \
    }                                                                                                                                                                                                  \
  }

/* Unlink the first chunk from a smallbin */
#define unlink_first_small_chunk(M, B, P, I)                                                                                                                                                           \
  {                                                                                                                                                                                                    \
    mchunkptr F = P->fd;                                                                                                                                                                               \
    assert(P != B);                                                                                                                                                                                    \
    assert(P != F);                                                                                                                                                                                    \
    assert(chunksize(P) == small_index2size(I));                                                                                                                                                       \
    if (B == F) {                                                                                                                                                                                      \
      clear_smallmap(M, I);                                                                                                                                                                            \
    } else if (RTCHECK(ok_address(M, F) && F->bk == P)) {                                                                                                                                              \
      F->bk = B;                                                                                                                                                                                       \
      B->fd = F;                                                                                                                                                                                       \
    } else {                                                                                                                                                                                           \
      CORRUPTION_ERROR_ACTION(M);                                                                                                                                                                      \
    }                                                                                                                                                                                                  \
  }

/* Replace dv node, binning the old one */
/* Used only when dvsize known to be small */
#define replace_dv(M, P, S)                                                                                                                                                                            \
  {                                                                                                                                                                                                    \
    size_t DVS = M->dvsize;                                                                                                                                                                            \
    assert(is_small(DVS));                                                                                                                                                                             \
    if (DVS != 0) {                                                                                                                                                                                    \
      mchunkptr DV = M->dv;                                                                                                                                                                            \
      insert_small_chunk(M, DV, DVS);                                                                                                                                                                  \
    }                                                                                                                                                                                                  \
    M->dvsize = S;                                                                                                                                                                                     \
    M->dv = P;                                                                                                                                                                                         \
  }

/* ------------------------- Operations on trees ------------------------- */

/* Insert chunk into tree */
#define insert_large_chunk(M, X, S)                                                                                                                                                                    \
  {                                                                                                                                                                                                    \
    tbinptr *H;                                                                                                                                                                                        \
    bindex_t I;                                                                                                                                                                                        \
    compute_tree_index(S, I);                                                                                                                                                                          \
    H = treebin_at(M, I);                                                                                                                                                                              \
    X->index = I;                                                                                                                                                                                      \
    X->child[0] = X->child[1] = 0;                                                                                                                                                                     \
    if (!treemap_is_marked(M, I)) {                                                                                                                                                                    \
      mark_treemap(M, I);                                                                                                                                                                              \
      *H = X;                                                                                                                                                                                          \
      X->parent = (tchunkptr)H;                                                                                                                                                                        \
      X->fd = X->bk = X;                                                                                                                                                                               \
    } else {                                                                                                                                                                                           \
      tchunkptr T = *H;                                                                                                                                                                                \
      size_t K = S << leftshift_for_tree_index(I);                                                                                                                                                     \
      for (;;) {                                                                                                                                                                                       \
        if (chunksize(T) != S) {                                                                                                                                                                       \
          tchunkptr *C = &(T->child[(K >> (SIZE_T_BITSIZE - SIZE_T_ONE)) & 1]);                                                                                                                        \
          K <<= 1;                                                                                                                                                                                     \
          if (*C != 0)                                                                                                                                                                                 \
            T = *C;                                                                                                                                                                                    \
          else if (RTCHECK(ok_address(M, C))) {                                                                                                                                                        \
            *C = X;                                                                                                                                                                                    \
            X->parent = T;                                                                                                                                                                             \
            X->fd = X->bk = X;                                                                                                                                                                         \
            break;                                                                                                                                                                                     \
          } else {                                                                                                                                                                                     \
            CORRUPTION_ERROR_ACTION(M);                                                                                                                                                                \
            break;                                                                                                                                                                                     \
          }                                                                                                                                                                                            \
        } else {                                                                                                                                                                                       \
          tchunkptr F = T->fd;                                                                                                                                                                         \
          if (RTCHECK(ok_address(M, T) && ok_address(M, F))) {                                                                                                                                         \
            T->fd = F->bk = X;                                                                                                                                                                         \
            X->fd = F;                                                                                                                                                                                 \
            X->bk = T;                                                                                                                                                                                 \
            X->parent = 0;                                                                                                                                                                             \
            break;                                                                                                                                                                                     \
          } else {                                                                                                                                                                                     \
            CORRUPTION_ERROR_ACTION(M);                                                                                                                                                                \
            break;                                                                                                                                                                                     \
          }                                                                                                                                                                                            \
        }                                                                                                                                                                                              \
      }                                                                                                                                                                                                \
    }                                                                                                                                                                                                  \
  }

/*
  Unlink steps:

  1. If x is a chained node, unlink it from its same-sized fd/bk links
     and choose its bk node as its replacement.
  2. If x was the last node of its size, but not a leaf node, it must
     be replaced with a leaf node (not merely one with an open left or
     right), to make sure that lefts and rights of descendents
     correspond properly to bit masks.  We use the rightmost descendent
     of x.  We could use any other leaf, but this is easy to locate and
     tends to counteract removal of leftmosts elsewhere, and so keeps
     paths shorter than minimally guaranteed.  This doesn't loop much
     because on average a node in a tree is near the bottom.
  3. If x is the base of a chain (i.e., has parent links) relink
     x's parent and children to x's replacement (or null if none).
*/

#define unlink_large_chunk(M, X)                                                                                                                                                                       \
  {                                                                                                                                                                                                    \
    tchunkptr XP = X->parent;                                                                                                                                                                          \
    tchunkptr R;                                                                                                                                                                                       \
    if (X->bk != X) {                                                                                                                                                                                  \
      tchunkptr F = X->fd;                                                                                                                                                                             \
      R = X->bk;                                                                                                                                                                                       \
      if (RTCHECK(ok_address(M, F) && F->bk == X && R->fd == X)) {                                                                                                                                     \
        F->bk = R;                                                                                                                                                                                     \
        R->fd = F;                                                                                                                                                                                     \
      } else {                                                                                                                                                                                         \
        CORRUPTION_ERROR_ACTION(M);                                                                                                                                                                    \
      }                                                                                                                                                                                                \
    } else {                                                                                                                                                                                           \
      tchunkptr *RP;                                                                                                                                                                                   \
      if (((R = *(RP = &(X->child[1]))) != 0) || ((R = *(RP = &(X->child[0]))) != 0)) {                                                                                                                \
        tchunkptr *CP;                                                                                                                                                                                 \
        while ((*(CP = &(R->child[1])) != 0) || (*(CP = &(R->child[0])) != 0)) {                                                                                                                       \
          R = *(RP = CP);                                                                                                                                                                              \
        }                                                                                                                                                                                              \
        if (RTCHECK(ok_address(M, RP)))                                                                                                                                                                \
          *RP = 0;                                                                                                                                                                                     \
        else {                                                                                                                                                                                         \
          CORRUPTION_ERROR_ACTION(M);                                                                                                                                                                  \
        }                                                                                                                                                                                              \
      }                                                                                                                                                                                                \
    }                                                                                                                                                                                                  \
    if (XP != 0) {                                                                                                                                                                                     \
      tbinptr *H = treebin_at(M, X->index);                                                                                                                                                            \
      if (X == *H) {                                                                                                                                                                                   \
        if ((*H = R) == 0)                                                                                                                                                                             \
          clear_treemap(M, X->index);                                                                                                                                                                  \
      } else if (RTCHECK(ok_address(M, XP))) {                                                                                                                                                         \
        if (XP->child[0] == X)                                                                                                                                                                         \
          XP->child[0] = R;                                                                                                                                                                            \
        else                                                                                                                                                                                           \
          XP->child[1] = R;                                                                                                                                                                            \
      } else                                                                                                                                                                                           \
        CORRUPTION_ERROR_ACTION(M);                                                                                                                                                                    \
      if (R != 0) {                                                                                                                                                                                    \
        if (RTCHECK(ok_address(M, R))) {                                                                                                                                                               \
          tchunkptr C0, C1;                                                                                                                                                                            \
          R->parent = XP;                                                                                                                                                                              \
          if ((C0 = X->child[0]) != 0) {                                                                                                                                                               \
            if (RTCHECK(ok_address(M, C0))) {                                                                                                                                                          \
              R->child[0] = C0;                                                                                                                                                                        \
              C0->parent = R;                                                                                                                                                                          \
            } else                                                                                                                                                                                     \
              CORRUPTION_ERROR_ACTION(M);                                                                                                                                                              \
          }                                                                                                                                                                                            \
          if ((C1 = X->child[1]) != 0) {                                                                                                                                                               \
            if (RTCHECK(ok_address(M, C1))) {                                                                                                                                                          \
              R->child[1] = C1;                                                                                                                                                                        \
              C1->parent = R;                                                                                                                                                                          \
            } else                                                                                                                                                                                     \
              CORRUPTION_ERROR_ACTION(M);                                                                                                                                                              \
          }                                                                                                                                                                                            \
        } else                                                                                                                                                                                         \
          CORRUPTION_ERROR_ACTION(M);                                                                                                                                                                  \
      }                                                                                                                                                                                                \
    }                                                                                                                                                                                                  \
  }

/* Relays to large vs small bin operations */

#define insert_chunk(M, P, S)                                                                                                                                                                          \
  if (is_small(S))                                                                                                                                                                                     \
    insert_small_chunk(M, P, S) else {                                                                                                                                                                 \
      tchunkptr TP = (tchunkptr)(P);                                                                                                                                                                   \
      insert_large_chunk(M, TP, S);                                                                                                                                                                    \
    }

#define unlink_chunk(M, P, S)                                                                                                                                                                          \
  if (is_small(S))                                                                                                                                                                                     \
    unlink_small_chunk(M, P, S) else {                                                                                                                                                                 \
      tchunkptr TP = (tchunkptr)(P);                                                                                                                                                                   \
      unlink_large_chunk(M, TP);                                                                                                                                                                       \
    }

/* Relays to internal calls to malloc/free from realloc, memalign etc */

#define internal_malloc(m, b) mspace_malloc(m, b)
#define internal_free(m, mem) mspace_free(m, mem);

/* -------------------------- mspace management -------------------------- */

/* Malloc using mmap */
static void *mmap_alloc(mstate m, size_t nb) {
  size_t mmsize = mmap_align(nb + SIX_SIZE_T_SIZES + CHUNK_ALIGN_MASK);
  if (m->footprint_limit != 0) {
    size_t fp = m->footprint + mmsize;
    if (fp <= m->footprint || fp > m->footprint_limit)
      return 0;
  }
  if (mmsize > nb) { /* Check for wrap around 0 */
    char *mm = (char *)(CALL_DIRECT_MMAP(mmsize));
    if (mm != CMFAIL) {
      size_t offset = align_offset(chunk2mem(mm));
      size_t psize = mmsize - offset - MMAP_FOOT_PAD;
      mchunkptr p = (mchunkptr)(mm + offset);
      p->prev_foot = offset;
      p->head = psize;
      mark_inuse_foot(m, p, psize);
      chunk_plus_offset(p, psize)->head = FENCEPOST_HEAD;
      chunk_plus_offset(p, psize + SIZE_T_SIZE)->head = 0;

      if (m->least_addr == 0 || mm < m->least_addr)
        m->least_addr = mm;
      if ((m->footprint += mmsize) > m->max_footprint)
        m->max_footprint = m->footprint;
      assert(is_aligned(chunk2mem(p)));
      check_mmapped_chunk(m, p);
      return chunk2mem(p);
    }
  }
  return 0;
}

/* Realloc using mmap */
static mchunkptr mmap_resize(mstate m, mchunkptr oldp, size_t nb, int flags) {
  size_t oldsize = chunksize(oldp);
  (void)flags;      /* placate people compiling -Wunused */
  if (is_small(nb)) /* Can't shrink mmap regions below small size */
    return 0;
  /* Keep old chunk if big enough but not too big */
  if (oldsize >= nb + SIZE_T_SIZE && (oldsize - nb) <= (mparams.granularity << 1))
    return oldp;
  else {
    size_t offset = oldp->prev_foot;
    size_t oldmmsize = oldsize + offset + MMAP_FOOT_PAD;
    size_t newmmsize = mmap_align(nb + SIX_SIZE_T_SIZES + CHUNK_ALIGN_MASK);
    char *cp = (char *)CALL_MREMAP((char *)oldp - offset, oldmmsize, newmmsize, flags);
    if (cp != CMFAIL) {
      mchunkptr newp = (mchunkptr)(cp + offset);
      size_t psize = newmmsize - offset - MMAP_FOOT_PAD;
      newp->head = psize;
      mark_inuse_foot(m, newp, psize);
      chunk_plus_offset(newp, psize)->head = FENCEPOST_HEAD;
      chunk_plus_offset(newp, psize + SIZE_T_SIZE)->head = 0;

      if (cp < m->least_addr)
        m->least_addr = cp;
      if ((m->footprint += newmmsize - oldmmsize) > m->max_footprint)
        m->max_footprint = m->footprint;
      check_mmapped_chunk(m, newp);
      return newp;
    }
  }
  return 0;
}

/* -------------------------- mspace management -------------------------- */

/* Initialize top chunk and its size */
static void init_top(mstate m, mchunkptr p, size_t psize) {
  /* Ensure alignment */
  size_t offset = align_offset(chunk2mem(p));
  p = (mchunkptr)((char *)p + offset);
  psize -= offset;

  m->top = p;
  m->topsize = psize;
  p->head = psize | PINUSE_BIT;
  /* set size of fake trailing chunk holding overhead space only once */
  chunk_plus_offset(p, psize)->head = TOP_FOOT_SIZE;
  m->trim_check = mparams.trim_threshold; /* reset on each update */
}

/* Initialize bins for a new mstate that is otherwise zeroed out */
static void init_bins(mstate m) {
  /* Establish circular links for smallbins */
  bindex_t i;
  for (i = 0; i < NSMALLBINS; ++i) {
    sbinptr bin = smallbin_at(m, i);
    bin->fd = bin->bk = bin;
  }
}

/* Allocate chunk and prepend remainder with chunk in successor base. */
static void *prepend_alloc(mstate m, char *newbase, char *oldbase, size_t nb) {
  mchunkptr p = align_as_chunk(newbase);
  mchunkptr oldfirst = align_as_chunk(oldbase);
  size_t psize = (char *)oldfirst - (char *)p;
  mchunkptr q = chunk_plus_offset(p, nb);
  size_t qsize = psize - nb;
  set_size_and_pinuse_of_inuse_chunk(m, p, nb);

  assert((char *)oldfirst > (char *)q);
  assert(pinuse(oldfirst));
  assert(qsize >= MIN_CHUNK_SIZE);

  /* consolidate remainder with first chunk of old base */
  if (oldfirst == m->top) {
    size_t tsize = m->topsize += qsize;
    m->top = q;
    q->head = tsize | PINUSE_BIT;
    check_top_chunk(m, q);
  } else if (oldfirst == m->dv) {
    size_t dsize = m->dvsize += qsize;
    m->dv = q;
    set_size_and_pinuse_of_free_chunk(q, dsize);
  } else {
    if (!is_inuse(oldfirst)) {
      size_t nsize = chunksize(oldfirst);
      unlink_chunk(m, oldfirst, nsize);
      oldfirst = chunk_plus_offset(oldfirst, nsize);
      qsize += nsize;
    }
    set_free_with_pinuse(q, qsize, oldfirst);
    insert_chunk(m, q, qsize);
    check_free_chunk(m, q);
  }

  check_malloced_chunk(m, chunk2mem(p), nb);
  return chunk2mem(p);
}

/* Add a segment to hold a new noncontiguous region */
static void add_segment(mstate m, char *tbase, size_t tsize, flag_t mmapped) {
  /* Determine locations and sizes of segment, fenceposts, old top */
  char *old_top = (char *)m->top;
  msegmentptr oldsp = segment_holding(m, old_top);
  char *old_end = oldsp->base + oldsp->size;
  size_t ssize = pad_request(sizeof(struct malloc_segment));
  char *rawsp = old_end - (ssize + FOUR_SIZE_T_SIZES + CHUNK_ALIGN_MASK);
  size_t offset = align_offset(chunk2mem(rawsp));
  char *asp = rawsp + offset;
  char *csp = (asp < (old_top + MIN_CHUNK_SIZE)) ? old_top : asp;
  mchunkptr sp = (mchunkptr)csp;
  msegmentptr ss = (msegmentptr)(chunk2mem(sp));
  mchunkptr tnext = chunk_plus_offset(sp, ssize);
  mchunkptr p = tnext;
  int nfences = 0;

  /* reset top to new space */
  init_top(m, (mchunkptr)tbase, tsize - TOP_FOOT_SIZE);

  /* Set up segment record */
  assert(is_aligned(ss));
  set_size_and_pinuse_of_inuse_chunk(m, sp, ssize);
  *ss = m->seg; /* Push current record */
  m->seg.base = tbase;
  m->seg.size = tsize;
  m->seg.sflags = mmapped;
  m->seg.next = ss;

  /* Insert trailing fenceposts */
  for (;;) {
    mchunkptr nextp = chunk_plus_offset(p, SIZE_T_SIZE);
    p->head = FENCEPOST_HEAD;
    ++nfences;
    if ((char *)(&(nextp->head)) < old_end)
      p = nextp;
    else
      break;
  }
  assert(nfences >= 2);

  /* Insert the rest of old top into a bin as an ordinary free chunk */
  if (csp != old_top) {
    mchunkptr q = (mchunkptr)old_top;
    size_t psize = csp - old_top;
    mchunkptr tn = chunk_plus_offset(q, psize);
    set_free_with_pinuse(q, psize, tn);
    insert_chunk(m, q, psize);
  }

  check_top_chunk(m, m->top);
}

/* -------------------------- System allocation -------------------------- */

/* Get memory from system using MORECORE or MMAP */
static void *sys_alloc(mstate m, size_t nb) {
  char *tbase = CMFAIL;
  size_t tsize = 0;
  flag_t mmap_flag = 0;
  size_t asize; /* allocation size */

  ensure_initialization();

  /* Directly map large chunks, but only if already initialized */
  if (use_mmap(m) && nb >= mparams.mmap_threshold && m->topsize != 0) {
    void *mem = mmap_alloc(m, nb);
    if (mem != 0)
      return mem;
  }

  asize = granularity_align(nb + SYS_ALLOC_PADDING);
  if (asize <= nb)
    return 0; /* wraparound */
  if (m->footprint_limit != 0) {
    size_t fp = m->footprint + asize;
    if (fp <= m->footprint || fp > m->footprint_limit)
      return 0;
  }

  /*
    Try getting memory in any of three ways (in most-preferred to
    least-preferred order):
    1. A call to MORECORE that can normally contiguously extend memory.
       (disabled if not MORECORE_CONTIGUOUS or not HAVE_MORECORE or
       or main space is mmapped or a previous contiguous call failed)
    2. A call to MMAP new space (disabled if not HAVE_MMAP).
       Note that under the default settings, if MORECORE is unable to
       fulfill a request, and HAVE_MMAP is true, then mmap is
       used as a noncontiguous system allocator. This is a useful backup
       strategy for systems with holes in address spaces -- in this case
       sbrk cannot contiguously expand the heap, but mmap may be able to
       find space.
    3. A call to MORECORE that cannot usually contiguously extend memory.
       (disabled if not HAVE_MORECORE)

   In all cases, we need to request enough bytes from system to ensure
   we can malloc nb bytes upon success, so pad with enough space for
   top_foot, plus alignment-pad to make sure we don't lose bytes if
   not on boundary, and round this up to a granularity unit.
  */

  if (MORECORE_CONTIGUOUS && !use_noncontiguous(m)) {
    char *br = CMFAIL;
    size_t ssize = asize; /* sbrk call size */
    msegmentptr ss = (m->top == 0) ? 0 : segment_holding(m, (char *)m->top);
    ACQUIRE_MALLOC_GLOBAL_LOCK();

    if (ss == 0) { /* First time through or recovery */
      char *base = (char *)CALL_MORECORE(0);
      if (base != CMFAIL) {
        size_t fp;
        /* Adjust to end on a page boundary */
        if (!is_page_aligned(base))
          ssize += (page_align((size_t)base) - (size_t)base);
        fp = m->footprint + ssize; /* recheck limits */
        if (ssize > nb && ssize < HALF_MAX_SIZE_T && (m->footprint_limit == 0 || (fp > m->footprint && fp <= m->footprint_limit)) && (br = (char *)(CALL_MORECORE(ssize))) == base) {
          tbase = base;
          tsize = ssize;
        }
      }
    } else {
      /* Subtract out existing available top space from MORECORE request. */
      ssize = granularity_align(nb - m->topsize + SYS_ALLOC_PADDING);
      /* Use mem here only if it did continuously extend old space */
      if (ssize < HALF_MAX_SIZE_T && (br = (char *)(CALL_MORECORE(ssize))) == ss->base + ss->size) {
        tbase = br;
        tsize = ssize;
      }
    }

    if (tbase == CMFAIL) { /* Cope with partial failure */
      if (br != CMFAIL) {  /* Try to use/extend the space we did get */
        if (ssize < HALF_MAX_SIZE_T && ssize < nb + SYS_ALLOC_PADDING) {
          size_t esize = granularity_align(nb + SYS_ALLOC_PADDING - ssize);
          if (esize < HALF_MAX_SIZE_T) {
            char *end = (char *)CALL_MORECORE(esize);
            if (end != CMFAIL)
              ssize += esize;
            else { /* Can't use; try to release */
              (void)CALL_MORECORE(-ssize);
              br = CMFAIL;
            }
          }
        }
      }
      if (br != CMFAIL) { /* Use the space we did get */
        tbase = br;
        tsize = ssize;
      } else
        disable_contiguous(m); /* Don't try contiguous path in the future */
    }

    RELEASE_MALLOC_GLOBAL_LOCK();
  }

  if (HAVE_MMAP && tbase == CMFAIL) { /* Try MMAP */
    char *mp = (char *)(CALL_MMAP(asize));
    if (mp != CMFAIL) {
      tbase = mp;
      tsize = asize;
      mmap_flag = USE_MMAP_BIT;
    }
  }

  if (HAVE_MORECORE && tbase == CMFAIL) { /* Try noncontiguous MORECORE */
    if (asize < HALF_MAX_SIZE_T) {
      char *br = CMFAIL;
      char *end = CMFAIL;
      ACQUIRE_MALLOC_GLOBAL_LOCK();
      br = (char *)(CALL_MORECORE(asize));
      end = (char *)(CALL_MORECORE(0));
      RELEASE_MALLOC_GLOBAL_LOCK();
      if (br != CMFAIL && end != CMFAIL && br < end) {
        size_t ssize = end - br;
        if (ssize > nb + TOP_FOOT_SIZE) {
          tbase = br;
          tsize = ssize;
        }
      }
    }
  }

  if (tbase != CMFAIL) {

    if ((m->footprint += tsize) > m->max_footprint)
      m->max_footprint = m->footprint;

    if (!is_initialized(m)) { /* first-time initialization */
      if (m->least_addr == 0 || tbase < m->least_addr)
        m->least_addr = tbase;
      m->seg.base = tbase;
      m->seg.size = tsize;
      m->seg.sflags = mmap_flag;
      m->magic = mparams.magic;
      m->release_checks = MAX_RELEASE_CHECK_RATE;
      init_bins(m);
      {
        /* Offset top by embedded malloc_state */
        mchunkptr mn = next_chunk(mem2chunk(m));
        init_top(m, mn, (size_t)((tbase + tsize) - (char *)mn) - TOP_FOOT_SIZE);
      }
    }

    else {
      /* Try to merge with an existing segment */
      msegmentptr sp = &m->seg;
      /* Only consider most recent segment if traversal suppressed */
      while (sp != 0 && tbase != sp->base + sp->size)
        sp = (NO_SEGMENT_TRAVERSAL) ? 0 : sp->next;
      if (sp != 0 && !is_extern_segment(sp) && (sp->sflags & USE_MMAP_BIT) == mmap_flag && segment_holds(sp, m->top)) { /* append */
        sp->size += tsize;
        init_top(m, m->top, m->topsize + tsize);
      } else {
        if (tbase < m->least_addr)
          m->least_addr = tbase;
        sp = &m->seg;
        while (sp != 0 && sp->base != tbase + tsize)
          sp = (NO_SEGMENT_TRAVERSAL) ? 0 : sp->next;
        if (sp != 0 && !is_extern_segment(sp) && (sp->sflags & USE_MMAP_BIT) == mmap_flag) {
          char *oldbase = sp->base;
          sp->base = tbase;
          sp->size += tsize;
          return prepend_alloc(m, tbase, oldbase, nb);
        } else
          add_segment(m, tbase, tsize, mmap_flag);
      }
    }

    if (nb < m->topsize) { /* Allocate from new or extended top space */
      size_t rsize = m->topsize -= nb;
      mchunkptr p = m->top;
      mchunkptr r = m->top = chunk_plus_offset(p, nb);
      r->head = rsize | PINUSE_BIT;
      set_size_and_pinuse_of_inuse_chunk(m, p, nb);
      check_top_chunk(m, m->top);
      check_malloced_chunk(m, chunk2mem(p), nb);
      return chunk2mem(p);
    }
  }

  MALLOC_FAILURE_ACTION;
  return 0;
}

/* -----------------------  system deallocation -------------------------- */

/* Unmap and unlink any mmapped segments that don't contain used chunks */
static size_t release_unused_segments(mstate m) {
  size_t released = 0;
  int nsegs = 0;
  msegmentptr pred = &m->seg;
  msegmentptr sp = pred->next;
  while (sp != 0) {
    char *base = sp->base;
    size_t size = sp->size;
    msegmentptr next = sp->next;
    ++nsegs;
    if (is_mmapped_segment(sp) && !is_extern_segment(sp)) {
      mchunkptr p = align_as_chunk(base);
      size_t psize = chunksize(p);
      /* Can unmap if first chunk holds entire segment and not pinned */
      if (!is_inuse(p) && (char *)p + psize >= base + size - TOP_FOOT_SIZE) {
        tchunkptr tp = (tchunkptr)p;
        assert(segment_holds(sp, (char *)sp));
        if (p == m->dv) {
          m->dv = 0;
          m->dvsize = 0;
        } else {
          unlink_large_chunk(m, tp);
        }
        if (CALL_MUNMAP(base, size) == 0) {
          released += size;
          m->footprint -= size;
          /* unlink obsoleted record */
          sp = pred;
          sp->next = next;
        } else { /* back out if cannot unmap */
          insert_large_chunk(m, tp, psize);
        }
      }
    }
    if (NO_SEGMENT_TRAVERSAL) /* scan only first segment */
      break;
    pred = sp;
    sp = next;
  }
  /* Reset check counter */
  m->release_checks = (((size_t)nsegs > (size_t)MAX_RELEASE_CHECK_RATE) ? (size_t)nsegs : (size_t)MAX_RELEASE_CHECK_RATE);
  return released;
}

static int sys_trim(mstate m, size_t pad) {
  size_t released = 0;
  ensure_initialization();
  if (pad < MAX_REQUEST && is_initialized(m)) {
    pad += TOP_FOOT_SIZE; /* ensure enough room for segment overhead */

    if (m->topsize > pad) {
      /* Shrink top space in granularity-size units, keeping at least one */
      size_t unit = mparams.granularity;
      size_t extra = ((m->topsize - pad + (unit - SIZE_T_ONE)) / unit - SIZE_T_ONE) * unit;
      msegmentptr sp = segment_holding(m, (char *)m->top);

      if (!is_extern_segment(sp)) {
        if (is_mmapped_segment(sp)) {
          if (HAVE_MMAP && sp->size >= extra && !has_segment_link(m, sp)) { /* can't shrink if pinned */
            size_t newsize = sp->size - extra;
            (void)newsize; /* placate people compiling -Wunused-variable */
            /* Prefer mremap, fall back to munmap */
            if ((CALL_MREMAP(sp->base, sp->size, newsize, 0) != MFAIL) || (CALL_MUNMAP(sp->base + newsize, extra) == 0)) {
              released = extra;
            }
          }
        } else if (HAVE_MORECORE) {
          if (extra >= HALF_MAX_SIZE_T) /* Avoid wrapping negative */
            extra = (HALF_MAX_SIZE_T) + SIZE_T_ONE - unit;
          ACQUIRE_MALLOC_GLOBAL_LOCK();
          {
            /* Make sure end of memory is where we last set it. */
            char *old_br = (char *)(CALL_MORECORE(0));
            if (old_br == sp->base + sp->size) {
              char *rel_br = (char *)(CALL_MORECORE(-extra));
              char *new_br = (char *)(CALL_MORECORE(0));
              if (rel_br != CMFAIL && new_br < old_br)
                released = old_br - new_br;
            }
          }
          RELEASE_MALLOC_GLOBAL_LOCK();
        }
      }

      if (released != 0) {
        sp->size -= released;
        m->footprint -= released;
        init_top(m, m->top, m->topsize - released);
        check_top_chunk(m, m->top);
      }
    }

    /* Unmap any unused mmapped segments */
    if (HAVE_MMAP)
      released += release_unused_segments(m);

    /* On failure, disable autotrim to avoid repeated failed future calls */
    if (released == 0 && m->topsize > m->trim_check)
      m->trim_check = MAX_SIZE_T;
  }

  return (released != 0) ? 1 : 0;
}

/* ---------------------------- malloc support --------------------------- */

/* Consolidate and bin a chunk. Differs from exported versions
   of free mainly in that the chunk need not be marked as inuse.
*/
static void dispose_chunk(mstate m, mchunkptr p, size_t psize) {
  mchunkptr next = chunk_plus_offset(p, psize);
  if (!pinuse(p)) {
    mchunkptr prev;
    size_t prevsize = p->prev_foot;
    if (is_mmapped(p)) {
      psize += prevsize + MMAP_FOOT_PAD;
      if (CALL_MUNMAP((char *)p - prevsize, psize) == 0)
        m->footprint -= psize;
      return;
    }
    prev = chunk_minus_offset(p, prevsize);
    psize += prevsize;
    p = prev;
    if (RTCHECK(ok_address(m, prev))) { /* consolidate backward */
      if (p != m->dv) {
#line 4382
        unlink_chunk(m, p, prevsize);
      } else if ((next->head & INUSE_BITS) == INUSE_BITS) {
        m->dvsize = psize;
        set_free_with_pinuse(p, psize, next);
        return;
      }
    } else {
      CORRUPTION_ERROR_ACTION(m);
      return;
    }
  }
  if (RTCHECK(ok_address(m, next))) {
    if (!cinuse(next)) { /* consolidate forward */
      if (next == m->top) {
        size_t tsize = m->topsize += psize;
        m->top = p;
        p->head = tsize | PINUSE_BIT;
        if (p == m->dv) {
          m->dv = 0;
          m->dvsize = 0;
        }
        return;
      } else if (next == m->dv) {
        size_t dsize = m->dvsize += psize;
        m->dv = p;
        set_size_and_pinuse_of_free_chunk(p, dsize);
        return;
      } else {
        size_t nsize = chunksize(next);
        psize += nsize;
#line 4416
        unlink_chunk(m, next, nsize);
        set_size_and_pinuse_of_free_chunk(p, psize);
        if (p == m->dv) {
          m->dvsize = psize;
          return;
        }
      }
    } else {
      set_free_with_pinuse(p, psize, next);
    }
#line 4427
    insert_chunk(m, p, psize);
  } else {
    CORRUPTION_ERROR_ACTION(m);
  }
}

/* ---------------------------- malloc --------------------------- */

/* allocate a large request from the best fitting chunk in a treebin */
static void *tmalloc_large(mstate m, size_t nb) {
  tchunkptr v = 0;
  size_t rsize = -nb; /* Unsigned negation */
  tchunkptr t;
  bindex_t idx;
  compute_tree_index(nb, idx);
  if ((t = *treebin_at(m, idx)) != 0) {
    /* Traverse tree for this bin looking for node with size == nb */
    size_t sizebits = nb << leftshift_for_tree_index(idx);
    tchunkptr rst = 0; /* The deepest untaken right subtree */
    for (;;) {
      tchunkptr rt;
      size_t trem = chunksize(t) - nb;
      if (trem < rsize) {
        v = t;
        if ((rsize = trem) == 0)
          break;
      }
      rt = t->child[1];
      t = t->child[(sizebits >> (SIZE_T_BITSIZE - SIZE_T_ONE)) & 1];
      if (rt != 0 && rt != t)
        rst = rt;
      if (t == 0) {
        t = rst; /* set t to least subtree holding sizes > nb */
        break;
      }
      sizebits <<= 1;
    }
  }
  if (t == 0 && v == 0) { /* set t to root of next non-empty treebin */
    binmap_t leftbits = left_bits(idx2bit(idx)) & m->treemap;
    if (leftbits != 0) {
      bindex_t i;
      binmap_t leastbit = least_bit(leftbits);
      compute_bit2idx(leastbit, i);
      t = *treebin_at(m, i);
    }
  }

  while (t != 0) { /* find smallest of tree or subtree */
    size_t trem = chunksize(t) - nb;
    if (trem < rsize) {
      rsize = trem;
      v = t;
    }
    t = leftmost_child(t);
  }

  /*  If dv is a better fit, return 0 so malloc will use it */
  if (v != 0 && rsize < (size_t)(m->dvsize - nb)) {
    if (RTCHECK(ok_address(m, v))) { /* split */
      mchunkptr r = chunk_plus_offset(v, nb);
#line 4489
      assert(chunksize(v) == rsize + nb);
      if (RTCHECK(ok_next(v, r))) {
        unlink_large_chunk(m, v);
        if (rsize < MIN_CHUNK_SIZE)
          set_inuse_and_pinuse(m, v, (rsize + nb));
        else {
          set_size_and_pinuse_of_inuse_chunk(m, v, nb);
          set_size_and_pinuse_of_free_chunk(r, rsize);
          insert_chunk(m, r, rsize);
        }
        return chunk2mem(v);
      }
    }
    CORRUPTION_ERROR_ACTION(m);
  }
  return 0;
}

/* allocate a small request from the best fitting chunk in a treebin */
static void *tmalloc_small(mstate m, size_t nb) {
  tchunkptr t, v;
  size_t rsize;
  bindex_t i;
  binmap_t leastbit = least_bit(m->treemap);
  compute_bit2idx(leastbit, i);
  v = t = *treebin_at(m, i);
  rsize = chunksize(t) - nb;

  while ((t = leftmost_child(t)) != 0) {
    size_t trem = chunksize(t) - nb;
    if (trem < rsize) {
      rsize = trem;
      v = t;
    }
  }

  if (RTCHECK(ok_address(m, v))) {
    mchunkptr r = chunk_plus_offset(v, nb);
#line 4527
    assert(chunksize(v) == rsize + nb);
    if (RTCHECK(ok_next(v, r))) {
      unlink_large_chunk(m, v);
      if (rsize < MIN_CHUNK_SIZE)
        set_inuse_and_pinuse(m, v, (rsize + nb));
      else {
        set_size_and_pinuse_of_inuse_chunk(m, v, nb);
        set_size_and_pinuse_of_free_chunk(r, rsize);
#line 4535
        replace_dv(m, r, rsize);
      }
      return chunk2mem(v);
    }
  }

  CORRUPTION_ERROR_ACTION(m);
  return 0;
}

/* Try to realloc; only in-place unless can_move true */
static mchunkptr try_realloc_chunk(mstate m, mchunkptr p, size_t nb, int can_move) {
  mchunkptr newp = 0;
  size_t oldsize = chunksize(p);
  mchunkptr next = chunk_plus_offset(p, oldsize);
  if (RTCHECK(ok_address(m, p) && ok_inuse(p) && ok_next(p, next) && ok_pinuse(next))) {
    if (is_mmapped(p)) {
      newp = mmap_resize(m, p, nb, can_move);
    } else if (oldsize >= nb) { /* already big enough */
      size_t rsize = oldsize - nb;
      if (rsize >= MIN_CHUNK_SIZE) { /* split off remainder */
        mchunkptr r = chunk_plus_offset(p, nb);
        set_inuse(m, p, nb);
        set_inuse(m, r, rsize);
        dispose_chunk(m, r, rsize);
      }
      newp = p;
    } else if (next == m->top) { /* extend into top */
      if (oldsize + m->topsize > nb) {
        size_t newsize = oldsize + m->topsize;
        size_t newtopsize = newsize - nb;
        mchunkptr newtop = chunk_plus_offset(p, nb);
        set_inuse(m, p, nb);
        newtop->head = newtopsize | PINUSE_BIT;
        m->top = newtop;
        m->topsize = newtopsize;
        newp = p;
      }
    } else if (next == m->dv) { /* extend into dv */
      size_t dvs = m->dvsize;
      if (oldsize + dvs >= nb) {
        size_t dsize = oldsize + dvs - nb;
        if (dsize >= MIN_CHUNK_SIZE) {
          mchunkptr r = chunk_plus_offset(p, nb);
          mchunkptr n = chunk_plus_offset(r, dsize);
          set_inuse(m, p, nb);
          set_size_and_pinuse_of_free_chunk(r, dsize);
          clear_pinuse(n);
          m->dvsize = dsize;
          m->dv = r;
        } else { /* exhaust dv */
          size_t newsize = oldsize + dvs;
          set_inuse(m, p, newsize);
          m->dvsize = 0;
          m->dv = 0;
        }
        newp = p;
      }
    } else if (!cinuse(next)) { /* extend into next free chunk */
      size_t nextsize = chunksize(next);
      if (oldsize + nextsize >= nb) {
        size_t rsize = oldsize + nextsize - nb;
#line 4872
        unlink_chunk(m, next, nextsize);
        if (rsize < MIN_CHUNK_SIZE) {
          size_t newsize = oldsize + nextsize;
          set_inuse(m, p, newsize);
        } else {
          mchunkptr r = chunk_plus_offset(p, nb);
          set_inuse(m, p, nb);
          set_inuse(m, r, rsize);
          dispose_chunk(m, r, rsize);
        }
        newp = p;
      }
    }
  } else {
    USAGE_ERROR_ACTION(m, chunk2mem(p));
  }
  return newp;
}

static void *internal_memalign(mstate m, size_t alignment, size_t bytes) {
  void *mem = 0;
  if (alignment < MIN_CHUNK_SIZE) /* must be at least a minimum chunk size */
    alignment = MIN_CHUNK_SIZE;
  if ((alignment & (alignment - SIZE_T_ONE)) != 0) { /* Ensure a power of 2 */
    size_t a = MALLOC_ALIGNMENT << 1;
    while (a < alignment)
      a <<= 1;
    alignment = a;
  }
  if (bytes >= MAX_REQUEST - alignment) {
    if (m != 0) { /* Test isn't needed but avoids compiler warning */
      MALLOC_FAILURE_ACTION;
    }
  } else {
    size_t nb = request2size(bytes);
    size_t req = nb + alignment + MIN_CHUNK_SIZE - CHUNK_OVERHEAD;
    mem = internal_malloc(m, req);
    if (mem != 0) {
      mchunkptr p = mem2chunk(mem);
      if (PREACTION(m))
        return 0;
      if ((((size_t)(mem)) & (alignment - 1)) != 0) { /* misaligned */
        /*
          Find an aligned spot inside chunk.  Since we need to give
          back leading space in a chunk of at least MIN_CHUNK_SIZE, if
          the first calculation places us at a spot with less than
          MIN_CHUNK_SIZE leader, we can move to the next aligned spot.
          We've allocated enough total room so that this is always
          possible.
        */
        char *br = (char *)mem2chunk((size_t)(((size_t)((char *)mem + alignment - SIZE_T_ONE)) & -alignment));
        char *pos = ((size_t)(br - (char *)(p)) >= MIN_CHUNK_SIZE) ? br : br + alignment;
        mchunkptr newp = (mchunkptr)pos;
        size_t leadsize = pos - (char *)(p);
        size_t newsize = chunksize(p) - leadsize;

        if (is_mmapped(p)) { /* For mmapped chunks, just adjust offset */
          newp->prev_foot = p->prev_foot + leadsize;
          newp->head = newsize;
        } else { /* Otherwise, give back leader, use the rest */
          set_inuse(m, newp, newsize);
          set_inuse(m, p, leadsize);
          dispose_chunk(m, p, leadsize);
        }
        p = newp;
      }

      /* Give back spare room at the end */
      if (!is_mmapped(p)) {
        size_t size = chunksize(p);
        if (size > nb + MIN_CHUNK_SIZE) {
          size_t remainder_size = size - nb;
          mchunkptr remainder = chunk_plus_offset(p, nb);
          set_inuse(m, p, nb);
          set_inuse(m, remainder, remainder_size);
          dispose_chunk(m, remainder, remainder_size);
        }
      }

      mem = chunk2mem(p);
#line 4958
      assert(chunksize(p) >= nb);
      assert(((size_t)mem & (alignment - 1)) == 0);
      check_inuse_chunk(m, p);
      POSTACTION(m);
    }
  }
  return mem;
}

/*
  Common support for independent_X routines, handling
    all of the combinations that can result.
  The opts arg has:
    bit 0 set if all elements are same size (using sizes[0])
    bit 1 set if elements should be zeroed
*/
static void **ialloc(mstate m, size_t n_elements, size_t *sizes, int opts, void *chunks[]) {

  size_t element_size;   /* chunksize of each element, if all same */
  size_t contents_size;  /* total size of elements */
  size_t array_size;     /* request size of pointer array */
  void *mem;             /* malloced aggregate space */
  mchunkptr p;           /* corresponding chunk */
  size_t remainder_size; /* remaining bytes while splitting */
  void **marray;         /* either "chunks" or malloced ptr array */
  mchunkptr array_chunk; /* chunk for malloced ptr array */
  flag_t was_enabled;    /* to disable mmap */
  size_t size;
  size_t i;

  ensure_initialization();
  /* compute array length, if needed */
  if (chunks != 0) {
    if (n_elements == 0)
      return chunks; /* nothing to do */
    marray = chunks;
    array_size = 0;
  } else {
    /* if empty req, must still return chunk representing empty array */
    if (n_elements == 0)
      return (void **)internal_malloc(m, 0);
    marray = 0;
    array_size = request2size(n_elements * (sizeof(void *)));
  }

  /* compute total element size */
  if (opts & 0x1) { /* all-same-size */
    element_size = request2size(*sizes);
    contents_size = n_elements * element_size;
  } else { /* add up all the sizes */
    element_size = 0;
    contents_size = 0;
    for (i = 0; i != n_elements; ++i)
      contents_size += request2size(sizes[i]);
  }

  size = contents_size + array_size;

  /*
     Allocate the aggregate chunk.  First disable direct-mmapping so
     malloc won't use it, since we would not be able to later
     free/realloc space internal to a segregated mmap region.
  */
  was_enabled = use_mmap(m);
  disable_mmap(m);
  mem = internal_malloc(m, size - CHUNK_OVERHEAD);
  if (was_enabled)
    enable_mmap(m);
  if (mem == 0)
    return 0;

  if (PREACTION(m))
    return 0;
  p = mem2chunk(mem);
  remainder_size = chunksize(p);

#line 5039
  assert(!is_mmapped(p));

  if (opts & 0x2) { /* optionally clear the elements */
    memset((size_t *)mem, 0, remainder_size - SIZE_T_SIZE - array_size);
  }

  /* If not provided, allocate the pointer array as final part of chunk */
  if (marray == 0) {
    size_t array_chunk_size;
    array_chunk = chunk_plus_offset(p, contents_size);
    array_chunk_size = remainder_size - contents_size;
    marray = (void **)(chunk2mem(array_chunk));
    set_size_and_pinuse_of_inuse_chunk(m, array_chunk, array_chunk_size);
    remainder_size = contents_size;
  }

  /* split out elements */
  for (i = 0;; ++i) {
    marray[i] = chunk2mem(p);
    if (i != n_elements - 1) {
      if (element_size != 0)
        size = element_size;
      else
        size = request2size(sizes[i]);
      remainder_size -= size;
      set_size_and_pinuse_of_inuse_chunk(m, p, size);
      p = chunk_plus_offset(p, size);
    } else { /* the final element absorbs any overallocation slop */
      set_size_and_pinuse_of_inuse_chunk(m, p, remainder_size);
      break;
    }
  }

  POSTACTION(m);
  return marray;
}

/* Try to free all pointers in the given array.
   Note: this could be made faster, by delaying consolidation,
   at the price of disabling some user integrity checks, We
   still optimize some consolidations by combining adjacent
   chunks before freeing, which will occur often if allocated
   with ialloc or the array is sorted.
*/
static size_t internal_bulk_free(mstate m, void *array[], size_t nelem) {
  size_t unfreed = 0;
  if (!PREACTION(m)) {
    void **a;
    void **fence = &(array[nelem]);
    for (a = array; a != fence; ++a) {
      void *mem = *a;
      if (mem != 0) {
        mchunkptr p = mem2chunk(mem);
        size_t psize = chunksize(p);
        if (get_mstate_for(p) != m) {
          ++unfreed;
          continue;
        }
        check_inuse_chunk(m, p);
        *a = 0;
        if (RTCHECK(ok_address(m, p) && ok_inuse(p))) {
          void **b = a + 1; /* try to merge with next chunk */
          mchunkptr next = next_chunk(p);
          if (b != fence && *b == chunk2mem(next)) {
            size_t newsize = chunksize(next) + psize;
            set_inuse(m, p, newsize);
            *b = chunk2mem(p);
          } else
            dispose_chunk(m, p, psize);
        } else {
          CORRUPTION_ERROR_ACTION(m);
          break;
        }
      }
    }
    if (should_trim(m, m->topsize))
      sys_trim(m, 0);
    POSTACTION(m);
  }
  return unfreed;
}

/* ----------------------------- user mspaces ---------------------------- */

static mstate init_user_mstate(char *tbase, size_t tsize) {
  size_t msize = pad_request(sizeof(struct malloc_state));
  mchunkptr mn;
  mchunkptr msp = align_as_chunk(tbase);
  mstate m = (mstate)(chunk2mem(msp));
  memset(m, 0, msize);
  (void)INITIAL_LOCK(&m->mutex);
  msp->head = (msize | INUSE_BITS);
  m->seg.base = m->least_addr = tbase;
  m->seg.size = m->footprint = m->max_footprint = tsize;
  m->magic = mparams.magic;
  m->release_checks = MAX_RELEASE_CHECK_RATE;
  m->mflags = mparams.default_mflags;
  m->extp = "";
  m->exts = 0;
  disable_contiguous(m);
  init_bins(m);
  mn = next_chunk(mem2chunk(m));
  init_top(m, mn, (size_t)((tbase + tsize) - (char *)mn) - TOP_FOOT_SIZE);
  check_top_chunk(m, m->top);
  return m;
}

mspace create_mspace(size_t capacity) {
  mstate m = 0;
  size_t msize;
  ensure_initialization();
  msize = pad_request(sizeof(struct malloc_state));
  if (capacity < (size_t)-(msize + TOP_FOOT_SIZE + mparams.page_size)) {
    size_t rs = ((capacity == 0) ? mparams.granularity : (capacity + TOP_FOOT_SIZE + msize));
    size_t tsize = granularity_align(rs);
    char *tbase = (char *)(CALL_MMAP(tsize));
    if (tbase != CMFAIL) {
      m = init_user_mstate(tbase, tsize);
      m->seg.sflags = USE_MMAP_BIT;
    }
  }
  return (mspace)m;
}

mspace create_mspace_with_base(void *base, size_t capacity) {
  mstate m = 0;
  size_t msize;
  ensure_initialization();
  msize = pad_request(sizeof(struct malloc_state));
  if (capacity > msize + TOP_FOOT_SIZE && capacity < (size_t)-(msize + TOP_FOOT_SIZE + mparams.page_size)) {
    m = init_user_mstate((char *)base, capacity);
    m->seg.sflags = EXTERN_BIT;
  }
  return (mspace)m;
}

int mspace_track_large_chunks(mspace msp, int enable) {
  int ret = 0;
  mstate ms = (mstate)msp;
  if (!PREACTION(ms)) {
    if (!use_mmap(ms)) {
      ret = 1;
    }
    if (!enable) {
      enable_mmap(ms);
    } else {
      disable_mmap(ms);
    }
    POSTACTION(ms);
  }
  return ret;
}

size_t destroy_mspace(mspace msp) {
  size_t freed = 0;
  mstate ms = (mstate)msp;
  if (ok_magic(ms)) {
    msegmentptr sp = &ms->seg;
    (void)DESTROY_LOCK(&ms->mutex); /* destroy before unmapped */
    while (sp != 0) {
      char *base = sp->base;
      size_t size = sp->size;
      flag_t flag = sp->sflags;
      (void)base; /* placate people compiling -Wunused-variable */
      sp = sp->next;
      if ((flag & USE_MMAP_BIT) && !(flag & EXTERN_BIT) && CALL_MUNMAP(base, size) == 0)
        freed += size;
    }
  } else {
    USAGE_ERROR_ACTION(ms, ms);
  }
  return freed;
}

/*
  mspace versions of routines are near-clones of the global
  versions. This is not so nice but better than the alternatives.
*/

void *mspace_malloc(mspace msp, size_t bytes) {
  mstate ms = (mstate)msp;
  if (!ok_magic(ms)) {
    USAGE_ERROR_ACTION(ms, ms);
    return 0;
  }
  if (!PREACTION(ms)) {
    void *mem;
    size_t nb;
    if (bytes <= MAX_SMALL_REQUEST) {
      bindex_t idx;
      binmap_t smallbits;
      nb = (bytes < MIN_REQUEST) ? MIN_CHUNK_SIZE : pad_request(bytes);
      idx = small_index(nb);
      smallbits = ms->smallmap >> idx;

      if ((smallbits & 0x3U) != 0) { /* Remainderless fit to a smallbin. */
        mchunkptr b, p;
        idx += ~smallbits & 1; /* Uses next bin if idx empty */
        b = smallbin_at(ms, idx);
        p = b->fd;
#line 5528
        assert(chunksize(p) == small_index2size(idx));
        unlink_first_small_chunk(ms, b, p, idx);
        set_inuse_and_pinuse(ms, p, small_index2size(idx));
        mem = chunk2mem(p);
        check_malloced_chunk(ms, mem, nb);
        return mem;
      }

      else if (nb > ms->dvsize) {
        if (smallbits != 0) { /* Use chunk in next nonempty smallbin */
          mchunkptr b, p, r;
          size_t rsize;
          bindex_t i;
          binmap_t leftbits = (smallbits << idx) & left_bits(idx2bit(idx));
          binmap_t leastbit = least_bit(leftbits);
          compute_bit2idx(leastbit, i);
          b = smallbin_at(ms, i);
          p = b->fd;
#line 5546
          assert(chunksize(p) == small_index2size(i));
          unlink_first_small_chunk(ms, b, p, i);
          rsize = small_index2size(i) - nb;
          /* Fit here cannot be remainderless if 4byte sizes */
          if (SIZE_T_SIZE != 4 && rsize < MIN_CHUNK_SIZE)
            set_inuse_and_pinuse(ms, p, small_index2size(i));
          else {
            set_size_and_pinuse_of_inuse_chunk(ms, p, nb);
            r = chunk_plus_offset(p, nb);
            set_size_and_pinuse_of_free_chunk(r, rsize);
#line 5556
            replace_dv(ms, r, rsize);
          }
          mem = chunk2mem(p);
          check_malloced_chunk(ms, mem, nb);
          return mem;
        }

        else if (ms->treemap != 0 && (mem = tmalloc_small(ms, nb)) != 0) {
          check_malloced_chunk(ms, mem, nb);
          return mem;
        }
      }
    } else if (bytes >= MAX_REQUEST)
      nb = MAX_SIZE_T; /* Too big to allocate. Force failure (in sys alloc) */
    else {
      nb = pad_request(bytes);
      if (ms->treemap != 0 && (mem = tmalloc_large(ms, nb)) != 0) {
        check_malloced_chunk(ms, mem, nb);
        return mem;
      }
    }

    if (nb <= ms->dvsize) {
      size_t rsize = ms->dvsize - nb;
      mchunkptr p = ms->dv;
      if (rsize >= MIN_CHUNK_SIZE) { /* split dv */
        mchunkptr r = ms->dv = chunk_plus_offset(p, nb);
        ms->dvsize = rsize;
        set_size_and_pinuse_of_free_chunk(r, rsize);
        set_size_and_pinuse_of_inuse_chunk(ms, p, nb);
      } else { /* exhaust dv */
        size_t dvs = ms->dvsize;
        ms->dvsize = 0;
        ms->dv = 0;
        set_inuse_and_pinuse(ms, p, dvs);
      }
      mem = chunk2mem(p);
      check_malloced_chunk(ms, mem, nb);
      return mem;
    }

    else if (nb < ms->topsize) { /* Split top */
      size_t rsize = ms->topsize -= nb;
      mchunkptr p = ms->top;
      mchunkptr r = ms->top = chunk_plus_offset(p, nb);
      r->head = rsize | PINUSE_BIT;
      set_size_and_pinuse_of_inuse_chunk(ms, p, nb);
      mem = chunk2mem(p);
      check_top_chunk(ms, ms->top);
      check_malloced_chunk(ms, mem, nb);
      return mem;
    }

    mem = sys_alloc(ms, nb);
    POSTACTION(ms);
    return mem;
  }
  return 0;
}

void mspace_free(mspace msp, void *mem) {
  if (mem != 0) {
    mchunkptr p = mem2chunk(mem);
    mstate fm = get_mstate_for(p);
    (void)msp; /* placate people compiling -Wunused */
    if (!ok_magic(fm)) {
      USAGE_ERROR_ACTION(fm, p);
      return;
    }
    if (!PREACTION(fm)) {
      check_inuse_chunk(fm, p);
      if (RTCHECK(ok_address(fm, p) && ok_inuse(p))) {
        size_t psize = chunksize(p);
        mchunkptr next = chunk_plus_offset(p, psize);
        if (!pinuse(p)) {
          size_t prevsize = p->prev_foot;
          if (is_mmapped(p)) {
            psize += prevsize + MMAP_FOOT_PAD;
            if (CALL_MUNMAP((char *)p - prevsize, psize) == 0)
              fm->footprint -= psize;
            return;
          } else {
            mchunkptr prev = chunk_minus_offset(p, prevsize);
            psize += prevsize;
            p = prev;
            if (RTCHECK(ok_address(fm, prev))) { /* consolidate backward */
              if (p != fm->dv) {
#line 5658
                unlink_chunk(fm, p, prevsize);
              } else if ((next->head & INUSE_BITS) == INUSE_BITS) {
                fm->dvsize = psize;
                set_free_with_pinuse(p, psize, next);
                return;
              }
            } else
              return;
          }
        }
        if (RTCHECK(ok_next(p, next) && ok_pinuse(next))) {
          if (!cinuse(next)) { /* consolidate forward */
            if (next == fm->top) {
              size_t tsize = fm->topsize += psize;
              fm->top = p;
              p->head = tsize | PINUSE_BIT;
              if (p == fm->dv) {
                fm->dv = 0;
                fm->dvsize = 0;
              }
              if (should_trim(fm, tsize))
                sys_trim(fm, 0);
              return;
            } else if (next == fm->dv) {
              size_t dsize = fm->dvsize += psize;
              fm->dv = p;
              set_size_and_pinuse_of_free_chunk(p, dsize);
              return;
            } else {
              size_t nsize = chunksize(next);
              psize += nsize;
#line 5701
              unlink_chunk(fm, next, nsize);
              set_size_and_pinuse_of_free_chunk(p, psize);
              if (p == fm->dv) {
                fm->dvsize = psize;
                return;
              }
            }
          } else
            set_free_with_pinuse(p, psize, next);

          if (is_small(psize)) {
#line 5713
            insert_small_chunk(fm, p, psize);
            check_free_chunk(fm, p);
          } else {
            tchunkptr tp = (tchunkptr)p;
            insert_large_chunk(fm, tp, psize);
            check_free_chunk(fm, p);
            if (--fm->release_checks == 0)
              release_unused_segments(fm);
          }
          return;
        }
      }
      USAGE_ERROR_ACTION(fm, p);
      POSTACTION(fm);
    }
  }
}

void *mspace_calloc(mspace msp, size_t n_elements, size_t elem_size) {
  void *mem;
  size_t req = 0;
  mstate ms = (mstate)msp;
  if (!ok_magic(ms)) {
    USAGE_ERROR_ACTION(ms, ms);
    return 0;
  }
  if (n_elements != 0) {
    req = n_elements * elem_size;
    if (((n_elements | elem_size) & ~(size_t)0xffff) && (req / n_elements != elem_size))
      req = MAX_SIZE_T; /* force downstream failure on overflow */
  }
  mem = internal_malloc(ms, req);
  if (mem != 0 && calloc_must_clear(mem2chunk(mem)))
    memset(mem, 0, req);
  return mem;
}

void *mspace_realloc(mspace msp, void *oldmem, size_t bytes) {
  void *mem = 0;
  if (oldmem == 0) {
    mem = mspace_malloc(msp, bytes);
  } else if (bytes >= MAX_REQUEST) {
    MALLOC_FAILURE_ACTION;
  } else {
    size_t nb = request2size(bytes);
    mchunkptr oldp = mem2chunk(oldmem);
    mstate m = get_mstate_for(oldp);
    if (!ok_magic(m)) {
      USAGE_ERROR_ACTION(m, oldmem);
      return 0;
    }
    if (!PREACTION(m)) {
      mchunkptr newp = try_realloc_chunk(m, oldp, nb, 1);
      POSTACTION(m);
      if (newp != 0) {
        check_inuse_chunk(m, newp);
        mem = chunk2mem(newp);
      } else {
        mem = mspace_malloc(m, bytes);
        if (mem != 0) {
          size_t oc = chunksize(oldp) - overhead_for(oldp);
          memcpy(mem, oldmem, (oc < bytes) ? oc : bytes);
          mspace_free(m, oldmem);
        }
      }
    }
  }
  return mem;
}

void *mspace_realloc_in_place(mspace msp, void *oldmem, size_t bytes) {
  void *mem = 0;
  if (oldmem != 0) {
    if (bytes >= MAX_REQUEST) {
      MALLOC_FAILURE_ACTION;
    } else {
      size_t nb = request2size(bytes);
      mchunkptr oldp = mem2chunk(oldmem);
      mstate m = get_mstate_for(oldp);
      (void)msp; /* placate people compiling -Wunused */
      if (!ok_magic(m)) {
        USAGE_ERROR_ACTION(m, oldmem);
        return 0;
      }
      if (!PREACTION(m)) {
        mchunkptr newp = try_realloc_chunk(m, oldp, nb, 0);
        POSTACTION(m);
        if (newp == oldp) {
          check_inuse_chunk(m, newp);
          mem = oldmem;
        }
      }
    }
  }
  return mem;
}

void *mspace_memalign(mspace msp, size_t alignment, size_t bytes) {
  mstate ms = (mstate)msp;
  if (!ok_magic(ms)) {
    USAGE_ERROR_ACTION(ms, ms);
    return 0;
  }
  if (alignment <= MALLOC_ALIGNMENT)
    return mspace_malloc(msp, bytes);
  return internal_memalign(ms, alignment, bytes);
}

void **mspace_independent_calloc(mspace msp, size_t n_elements, size_t elem_size, void *chunks[]) {
  size_t sz = elem_size; /* serves as 1-element array */
  mstate ms = (mstate)msp;
  if (!ok_magic(ms)) {
    USAGE_ERROR_ACTION(ms, ms);
    return 0;
  }
  return ialloc(ms, n_elements, &sz, 3, chunks);
}

void **mspace_independent_comalloc(mspace msp, size_t n_elements, size_t sizes[], void *chunks[]) {
  mstate ms = (mstate)msp;
  if (!ok_magic(ms)) {
    USAGE_ERROR_ACTION(ms, ms);
    return 0;
  }
  return ialloc(ms, n_elements, sizes, 0, chunks);
}

size_t mspace_bulk_free(mspace msp, void *array[], size_t nelem) { return internal_bulk_free((mstate)msp, array, nelem); }

int mspace_trim(mspace msp, size_t pad) {
  int result = 0;
  mstate ms = (mstate)msp;
  if (ok_magic(ms)) {
    if (!PREACTION(ms)) {
      result = sys_trim(ms, pad);
      POSTACTION(ms);
    }
  } else {
    USAGE_ERROR_ACTION(ms, ms);
  }
  return result;
}

void mspace_malloc_stats(mspace msp) {
  mstate ms = (mstate)msp;
  if (ok_magic(ms)) {
    internal_malloc_stats(ms);
  } else {
    USAGE_ERROR_ACTION(ms, ms);
  }
}

size_t mspace_footprint(mspace msp) {
  size_t result = 0;
  mstate ms = (mstate)msp;
  if (ok_magic(ms)) {
    result = ms->footprint;
  } else {
    USAGE_ERROR_ACTION(ms, ms);
  }
  return result;
}

size_t mspace_max_footprint(mspace msp) {
  size_t result = 0;
  mstate ms = (mstate)msp;
  if (ok_magic(ms)) {
    result = ms->max_footprint;
  } else {
    USAGE_ERROR_ACTION(ms, ms);
  }
  return result;
}

size_t mspace_footprint_limit(mspace msp) {
  size_t result = 0;
  mstate ms = (mstate)msp;
  if (ok_magic(ms)) {
    size_t maf = ms->footprint_limit;
    result = (maf == 0) ? MAX_SIZE_T : maf;
  } else {
    USAGE_ERROR_ACTION(ms, ms);
  }
  return result;
}

size_t mspace_set_footprint_limit(mspace msp, size_t bytes) {
  size_t result = 0;
  mstate ms = (mstate)msp;
  if (ok_magic(ms)) {
    if (bytes == 0)
      result = granularity_align(1); /* Use minimal size */
    if (bytes == MAX_SIZE_T)
      result = 0; /* disable */
    else
      result = granularity_align(bytes);
    ms->footprint_limit = result;
  } else {
    USAGE_ERROR_ACTION(ms, ms);
  }
  return result;
}

struct mallinfo mspace_mallinfo(mspace msp) {
  mstate ms = (mstate)msp;
  if (!ok_magic(ms)) {
    USAGE_ERROR_ACTION(ms, ms);
  }
  return internal_mallinfo(ms);
}

size_t mspace_usable_size(const void *mem) {
  if (mem != 0) {
    mchunkptr p = mem2chunk(mem);
    if (is_inuse(p))
      return chunksize(p) - overhead_for(p);
  }
  return 0;
}

int mspace_mallopt(int param_number, int value) { return change_mparam(param_number, value); }

void mspace_set_stats(mspace msp, const char *name) {
  mstate ms = (mstate)msp;
  if (ms != 0 && ok_magic(ms)) {
    ms->extp = name != 0 ? name : "no name";
  }
}
