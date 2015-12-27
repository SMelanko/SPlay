#pragma once

#ifndef _SPLAY_TRACK_H_
#define _SPLAY_TRACK_H_

#include "Common.h"

#include <QString>

namespace splay
{

class Track
{
public:
	//! Constructor.
	Track() /* NOEXCEPT */ = default;
	Track(const QString& author, const QString& title, const int duration) NOEXCEPT;
	//! Destructor.
	~Track() /* NOEXCEPT */ = default;

public:
	//! Returns the author's name.
	QString Author() const NOEXCEPT;
	//! Returns the track's title.
	QString Title() const NOEXCEPT;
	//! Returns the track's duration in seconds.
	int Duration() const NOEXCEPT;
	//! Returns the track's duration in format "hours:minutes:seconds".
	QString DurationStr() const NOEXCEPT;

private:
	//! Author.
	QString mAuthor;
	//! Title.
	QString mTitle;
	//! Duration in the seconds.
	int mDuration;
};

} // namespace splay

#endif // _SPLAY_TRACK_H_
