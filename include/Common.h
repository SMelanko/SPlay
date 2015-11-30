#pragma once

#ifndef _SPLAY_COMMON_H_
#define _SPLAY_COMMON_H_

#if defined(_MSC_FULL_VER) && _MSC_FULL_VER >= 180021114 || \
	defined(__GXX_EXPERIMENTAL_CXX0X__) && __GNUC__ * 10 + __GNUC_MINOR__ >= 46
#define NOEXCEPT noexcept
#else
#define NOEXCEPT throw()
#endif

#endif // _SPLAY_COMMON_H_
