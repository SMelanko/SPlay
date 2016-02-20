#include "TableViewDelegate.h"

#include <QDebug>
#include <QPainter>

namespace splay
{

TableViewDelegate::TableViewDelegate(QObject* parent)
	: QStyledItemDelegate{ parent }
{
}

void TableViewDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,
	const QModelIndex& index) const
{
	if (index.row() == mIndex && index.column() == 0) {
		auto rect = option.rect;
		int x1, y1, x2, y2;
		rect.getCoords(&x1, &y1, &x2, &y2);

		static const QPixmap pixmap{ ":/playing_icon" };
		static const auto sz = pixmap.size();

		static auto x = (rect.width() / 2) - sz.width() / 2;
		auto y = ((y2 - y1) / 2) + y1 - sz.height() / 2 + 1;

		painter->drawPixmap(QPoint{ x, y }, pixmap);
	} else {
		QStyledItemDelegate::paint(painter, option, index);
	}
}

void TableViewDelegate::SetNewIndex(int val)
{
	qDebug() << "TableViewDelegate::SetNewIndex: Index has been changed " << val;
	mIndex = val;
}

} // namespace splay
