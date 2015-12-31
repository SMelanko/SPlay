#pragma once

#ifndef _SPLAY_TYPES_H_
#define _SPLAY_TYPES_H_

#include "Track.h"

#include <memory>
#include <vector>

namespace splay
{

using TrackPtr = std::unique_ptr<Track>;
using Playlist = std::vector<Track>;

}

#endif // _SPLAY_TYPES_H_
