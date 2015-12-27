#include "PlaylistModel.h"

#include <QDebug>

namespace splay
{

PlaylistModel::PlaylistModel(QObject* parent)
	: QAbstractTableModel{ parent }
{
}

PlaylistModel::~PlaylistModel()
{
}

int PlaylistModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant PlaylistModel::data(const QModelIndex& index, int role) const
{
	const auto row{ index.row() };
	const auto column{ index.column() };

	if (role == Qt::DisplayRole) {
		QString data{ QString{ "Row = %1 Column = %2" }.arg(row).arg(column) };
		return QVariant{ data };
	}

	return QVariant{};
}

QVariant PlaylistModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return QLatin1String{ "Playing" };
			case 1:
				return QLatin1String{ "Author" };
			case 2:
				return QLatin1String{ "Title" };
			case 3:
				return QLatin1String{ "Duration" };
			}
		}
	}

	return QVariant{};
}

int PlaylistModel::rowCount(const QModelIndex& parent) const
{
	return 2;
}

} // namespace splay
