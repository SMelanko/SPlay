#include "PlaylistModel.h"
#include "Track.h"

#include <QDebug>

namespace splay
{

PlaylistModel::PlaylistModel(QObject* parent)
	: QAbstractTableModel(parent)
{
	mPlaylist.emplace_back("Armin van Buuren", "Shivers", 3721);
	mPlaylist.emplace_back("Aruna with Mark Etenson", "Let go (Nic Chagall remix)", 510);
	mPlaylist.emplace_back("Photographer & Susana", "Find A Way", 201);
}

int PlaylistModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant PlaylistModel::data(const QModelIndex& index, int role) const
{
	const auto row(index.row());
	const auto column(index.column());

	if (role == Qt::DisplayRole) {
		QString data(QString("Row = %1 Column = %2").arg(row).arg(column));
		switch (column) {
		case 1:
			return QVariant(mPlaylist[row].Author());
		case 2:
			return QVariant(mPlaylist[row].Title());
		case 3:
			return QVariant(mPlaylist[row].DurationStr());
		}
	}

	return QVariant();
}

Qt::ItemFlags PlaylistModel::flags(const QModelIndex& index) const
{
	auto defFlags = QAbstractTableModel::flags(index);

	if (index.isValid())
		return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defFlags;
	else
		return Qt::ItemIsDropEnabled | defFlags;
}

QVariant PlaylistModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return QLatin1String("Playing");
			case 1:
				return QLatin1String("Author");
			case 2:
				return QLatin1String("Title");
			case 3:
				return QLatin1String("Duration");
			}
		}
	}

	return QVariant();
}

int PlaylistModel::rowCount(const QModelIndex& parent) const
{
	return mPlaylist.size();
}

Qt::DropActions PlaylistModel::supportedDropActions() const
{
	return Qt::CopyAction | Qt::MoveAction;
}

} // namespace splay
