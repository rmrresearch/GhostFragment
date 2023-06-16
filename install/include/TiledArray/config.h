/*
 *  This file is a part of TiledArray.
 *  Copyright (C) 2013  Virginia Tech
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef TILEDARRAY_CONFIG_H__INCLUDED
#define TILEDARRAY_CONFIG_H__INCLUDED

#include <madness/madness_config.h>

#define TILEDARRAY_PACKAGE_URL "https://github.com/ValeevGroup/tiledarray"

/* detect C++ compiler id:
- ids taken from CMake
- macros are discussed at https://sourceforge.net/p/predef/wiki/Compilers/
*/
#define TILEDARRAY_CXX_COMPILER_ID_GNU 0
#define TILEDARRAY_CXX_COMPILER_ID_Clang 1
#define TILEDARRAY_CXX_COMPILER_ID_AppleClang 2
#define TILEDARRAY_CXX_COMPILER_ID_XLClang 3
#define TILEDARRAY_CXX_COMPILER_ID_Intel 4
#if defined(__INTEL_COMPILER_BUILD_DATE)  /* macros like __ICC and even __INTEL_COMPILER can be affected by command options like -no-icc */
# define TILEDARRAY_CXX_COMPILER_ID TILEDARRAY_CXX_COMPILER_ID_Intel
# define TILEDARRAY_CXX_COMPILER_IS_ICC 1
#endif
#if defined(__clang__) && !defined(TILEDARRAY_CXX_COMPILER_IS_ICC)
# define TILEDARRAY_CXX_COMPILER_IS_CLANG 1
# if defined(__apple_build_version__)
#  define TILEDARRAY_CXX_COMPILER_ID TILEDARRAY_CXX_COMPILER_ID_AppleClang
# elif defined(__ibmxl__)
#  define TILEDARRAY_CXX_COMPILER_ID TILEDARRAY_CXX_COMPILER_ID_XLClang
# else
#  define TILEDARRAY_CXX_COMPILER_ID TILEDARRAY_CXX_COMPILER_ID_Clang
# endif
#endif
#if defined(__GNUG__) && !defined(TILEDARRAY_CXX_COMPILER_IS_ICC) && !defined(TILEDARRAY_CXX_COMPILER_IS_CLANG)
# define TILEDARRAY_CXX_COMPILER_ID TILEDARRAY_CXX_COMPILER_ID_GNU
# define TILEDARRAY_CXX_COMPILER_IS_GCC 1
#endif


/* Defines the default error checking behavior */
#define TA_ASSERT_THROW 2
#define TA_ASSERT_ABORT 3
#define TA_ASSERT_IGNORE 4
#define TA_ASSERT_POLICY TA_ASSERT_THROW

/* define if compiler supports long double, the value is sizeof(long double) */
#define TILEDARRAY_HAS_LONG_DOUBLE 1

/* define if compiler supports long long, the value is sizeof(long long) */
#define TILEDARRAY_HAS_LONG_LONG 1

/* Define the default alignment for arrays required by vector operations. */
#define TILEDARRAY_ALIGNMENT 16

/* Define the size of the CPU L1 cache lines. */
#define TILEDARRAY_CACHELINE_SIZE 64

/* Define if TA has enabled ScaLAPACK Bindings */
#define TILEDARRAY_HAS_SCALAPACK 1

/* Define if TiledArray configured with CUDA support */
/* #undef TILEDARRAY_HAS_CUDA */
/* #undef TILEDARRAY_CHECK_CUDA_ERROR */

/* Is TA::Tensor memory profiling enabled? */
/* #undef TA_TENSOR_MEM_PROFILE */

/* Use preprocessor to check if BTAS is available */
#ifndef TILEDARRAY_HAS_BTAS
#ifdef __has_include
#if __has_include(<btas/features.h>)
#include <btas/features.h>
#if BTAS_IS_USABLE
#define TILEDARRAY_HAS_BTAS 1
#endif  // BTAS_IS_USABLE
#endif  // __has_include(<btas/features.h>)
#endif  // __has_include
#endif  // !defined(TILEDARRAY_HAS_BTAS)
#if defined(TILEDARRAY_HAS_BTAS) && defined(BTAS_HAS_INTEL_MKL)
#  define TILEDARRAY_HAS_INTEL_MKL
#endif

/* Add macro TILEDARRAY_FORCE_INLINE which does as the name implies. */
#if defined(_MSC_VER) || defined(TILEDARRAY_CXX_COMPILER_IS_ICC)

#define TILEDARRAY_FORCE_INLINE __forceinline

#elif defined(TILEDARRAY_CXX_COMPILER_IS_CLANG)

#define TILEDARRAY_FORCE_INLINE __attribute__((always_inline)) inline

#elif defined(TILEDARRAY_CXX_COMPILER_IS_GCC)

#if (__GNUC__ >= 4)
#define TILEDARRAY_FORCE_INLINE __attribute__((always_inline)) inline
#else
#define TILEDARRAY_FORCE_INLINE inline
#endif // (__GNUC__ >= 4)

#else

#define TILEDARRAY_FORCE_INLINE inline

#endif

/* Add macro TILEDARRAY_ALIGNED_STORAGE which forces alignment of variables */
#if defined(__clang__) || defined(__GNUC__) || defined(__PGI) || defined(__IBMCPP__) || defined(__ARMCC_VERSION)

#define TILEDARRAY_ALIGNED_STORAGE __attribute__((aligned(TILEDARRAY_ALIGNMENT)))

#elif (defined _MSC_VER)

#define TILEDARRAY_ALIGNED_STORAGE __declspec(align(TILEDARRAY_ALIGNMENT))

#else

#define TILEDARRAY_ALIGNED_STORAGE
#warning FIXME!!! TiledArray alignment attribute is not defined for this platform.

#endif

/* Defines the 1-index type used by TiledArray */
#if !defined(TA_1INDEX_TYPE)
#  define TA_SIGNED_1INDEX_TYPE 1
#  if defined(TA_SIGNED_1INDEX_TYPE)
#    define TA_1INDEX_TYPE std::int64_t
#  else
#    define TA_1INDEX_TYPE std::uint64_t
#  endif
#endif

/* Specifies the rank for up to which to use Small Object Optimization for metadata (e.g. Range, Range::index, etc.) */
#define TA_MAX_SOO_RANK_METADATA 8

/* Enables tracing MADNESS tasks in TiledArray */
/* #undef TILEDARRAY_ENABLE_TASK_DEBUG_TRACE */

/* Enables logging of TiledArray tile ops */
/* #undef TA_ENABLE_TILE_OPS_LOGGING */
#define TA_TILE_OPS_LOG_LEVEL 0

/* ----------- pragma helpers ---------------*/
#define TILEDARRAY_PRAGMA(x) _Pragma(#x)
/* same as TILEDARRAY_PRAGMA(x), but expands x */
#define TILEDARRAY_XPRAGMA(x) TILEDARRAY_PRAGMA(x)
/* "concats" a and b with a space in between */
#define TILEDARRAY_CONCAT(a,b) a b
#if defined(TILEDARRAY_CXX_COMPILER_IS_CLANG)
#define TILEDARRAY_PRAGMA_CLANG(x) TILEDARRAY_XPRAGMA( TILEDARRAY_CONCAT(clang,x) )
#else
#define TILEDARRAY_PRAGMA_CLANG(x)
#endif
#if defined(TILEDARRAY_CXX_COMPILER_IS_GCC)
#define TILEDARRAY_PRAGMA_GCC(x) TILEDARRAY_XPRAGMA( TILEDARRAY_CONCAT(GCC,x) )
#else
#define TILEDARRAY_PRAGMA_GCC(x)
#endif

#endif // TILEDARRAY_CONFIG_H__INCLUDED
