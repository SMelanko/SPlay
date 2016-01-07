#pragma once

#ifndef _SPLAY_TRACK_H_
#define _SPLAY_TRACK_H_

#include <QString>

namespace splay
{

class Track
{
public:
	//! Constructor.
	Track() /*Q_DECL_NOEXCEPT*/ = default;
	Track(const QString& author, const QString& title, const int duration);
	//! Destructor.
	~Track() /*Q_DECL_NOEXCEPT*/ = default;
	//! Move.
	//Track(Track&&) NOEXCEPT = default;
	//Track& operator=(Track&&) NOEXCEPT = default;

public:
	//! Returns the author's name.
	QString Author() const Q_DECL_NOEXCEPT;
	//! Returns the track's title.
	QString Title() const Q_DECL_NOEXCEPT;
	//! Returns the track's duration in seconds.
	int Duration() const Q_DECL_NOEXCEPT;
	//! Returns the track's duration in format "hours:minutes:seconds".
	QString DurationStr() const Q_DECL_NOEXCEPT;

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
