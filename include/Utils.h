#pragma once

#ifndef _SPLAY_UTILS_H_
#define _SPLAY_UTILS_H_

#include "Types.h"

namespace utils
{

/// Converts a list of urls into a list of media content.
QList<QMediaContent> FromUrlList(const splay::AudioUrls& urls);

} // namespace utils

#endif // _SPLAY_UTILS_H_

