#include "PlaylistModel.h"

#include <QDataStream>
#include <QDebug>
#include <QMimeData>

namespace splay
{

PlaylistModel::PlaylistModel(QObject* parent)
	: QAbstractTableModel(parent)
{
	// TODO only for testing.
	//mPlaylist.push_back(Track("Armin van Buuren", "Shivers", 3721));
	//mPlaylist.push_back(Track("Aruna with Mark Etenson", "Let go (Nic Chagall remix)", 510));
	//mPlaylist.push_back(Track("Photographer & Susana", "Find A Way", 201));
}

int PlaylistModel::columnCount(const QModelIndex& parent) const
{
	// Note! When implementing a table based model,
	// columnCount() should return 0 when the parent is valid.
	if (parent.isValid())
		 return 0;
	 else
		 return 4;
}

QVariant PlaylistModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();

	const auto row(index.row());
	const auto column(index.column());

	if (role == Qt::DisplayRole) {
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

void PlaylistModel::Insert(const Playlist list)
{
	const QModelIndex parent = QModelIndex();
	const auto row = mPlaylist.size();
	const auto cnt = list.size();

	beginInsertRows(parent, row, row + cnt - 1);

	foreach (const auto& track, list) {
		mPlaylist.push_back(track);
	}

	endInsertRows();
}

QMimeData* PlaylistModel::mimeData(const QModelIndexList& indexes) const
{
	QMimeData* mime(new QMimeData);
	QByteArray encodedData;

	QDataStream stream(&encodedData, QIODevice::WriteOnly);

	foreach(QModelIndex index, indexes) {
		if (index.isValid()) {
			QString text(data(index, Qt::DisplayRole).toString());
			qDebug() << text;
			stream << text;
		}
	}

	mime->setData("application/splay-track", encodedData);

	return mime;
}

QStringList PlaylistModel::mimeTypes() const
{
	QStringList types;
	types << "application/splay-track";
	//qDebug() << "PlaylistModel::mimeTypes" << types;
	return types;
}

int PlaylistModel::rowCount(const QModelIndex& parent) const
{
	// Note! When implementing a table based model,
	// rowCount() should return 0 when the parent is valid.
	if (parent.isValid())
		return 0;
	else
		return mPlaylist.size();
}

Qt::DropActions PlaylistModel::supportedDropActions() const
{
	return Qt::CopyAction | Qt::MoveAction;
}

} // namespace splay
