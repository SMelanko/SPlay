#pragma once

#ifndef _SPLAY_TYPES_H_
#define _SPLAY_TYPES_H_

#include <vector>

#include <QMediaPlaylist>

namespace splay
{

using AudioUrls = QList<QUrl> ;
using Playlist = QMediaPlaylist;
using RowList = std::vector<int>;

}

#endif // _SPLAY_TYPES_H_
