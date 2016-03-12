#include "PlaylistViewDelegate.h"

#include <QDebug>
#include <QPainter>

namespace splay
{

PlaylistViewDelegate::PlaylistViewDelegate(QObject* parent)
	: QStyledItemDelegate{ parent }
{
}

void PlaylistViewDelegate::OnSetNewIndex(int val)
{
	qDebug() << "PlaylistViewDelegate::SetNewIndex: " << val;
	mIndex = val;
}

void PlaylistViewDelegate::paint(QPainter* painter,
	const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	if (index.row() == mIndex && index.column() == 0) {
		qDebug() << "PlaylistViewDelegate::paint: draw playing icon";

		const auto rect = option.rect;
		int x1, y1, x2, y2;
		rect.getCoords(&x1, &y1, &x2, &y2);

		static const QPixmap pixmap{ QLatin1String(":/playing_icon") };
		static const auto sz = pixmap.size();

		auto x = (rect.width() / 2) - sz.width() / 2;
		auto y = ((y2 - y1) / 2) + y1 - sz.height() / 2 + 1;

		painter->drawPixmap(QPoint{ x, y }, pixmap);
	} else {
		QStyledItemDelegate::paint(painter, option, index);
	}
}

} // namespace splay
