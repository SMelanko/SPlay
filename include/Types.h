#pragma once

#ifndef _SPLAY_TYPES_H_
#define _SPLAY_TYPES_H_

#include "Track.h"

#include <memory>
#include <vector>

namespace splay
{

using Playlist = std::vector<Track>;
using RowsList = std::vector<int>;

}

#endif // _SPLAY_TYPES_H_
