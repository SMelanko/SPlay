#include "Track.h"

#include <cstdint> // For VS.

namespace splay
{

Track::Track(const QString& author, const QString& title, const int duration) NOEXCEPT
	: mAuthor(author)
	, mTitle(title)
	, mDuration(duration)
{
}

QString Track::Author() const NOEXCEPT
{
	return mAuthor;
}

QString Track::Title() const NOEXCEPT
{
	return mTitle;
}

int Track::Duration() const NOEXCEPT
{
	return mDuration;
}

QString Track::DurationStr() const NOEXCEPT
{
	Q_DECL_CONSTEXPR int16_t secsIn1Hour = 3600;
	Q_DECL_CONSTEXPR int8_t secsIn1Min = 60;

	QString durStr;

	auto hours = mDuration / secsIn1Hour;
	if (hours > 0)
		durStr += (QString::number(hours) + QLatin1Char(':'));

	auto mins = (mDuration - hours * secsIn1Hour) / secsIn1Min;
	if (hours > 0 && mins < 10)
		durStr += QLatin1Char('0');
	durStr += (QString::number(mins) + QLatin1Char(':'));

	auto secs = mDuration % secsIn1Min;
	durStr += ((secs < 10 ? "0" : "") + QString::number(secs));

	return durStr;
}

} // namespace splay
