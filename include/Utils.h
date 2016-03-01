#pragma once

#ifndef _SPLAY_UTILS_H_
#define _SPLAY_UTILS_H_

#include "Types.h"

namespace utils
{

/// Converts a list of urls into a list of media content.
QList<QMediaContent> FromUrlList(const splay::AudioUrls& urls);

/// Converts milliseconds to the hh:mm:ss format.
QString MillisecondsToHhMmSs(const qint64& millisecs);
/// Converts seconds to the hh:mm:ss format.
QString SecondsToHhMmSs(const int& secs);

} // namespace utils

#endif // _SPLAY_UTILS_H_
