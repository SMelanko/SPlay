#include "PlaylistModel.h"

#include <QDataStream>
#include <QDebug>
#include <QMimeData>

#include <memory>

namespace splay
{

PlaylistModel::PlaylistModel(QObject* parent)
	: QAbstractTableModel(parent)
{
	// TODO only for testing.
	mPlaylist.emplace_back(Track("0 Markus Schulz feat. Delacey", "Destiny", 110));
	mPlaylist.emplace_back(Track("1 Photographer & Susana", "Find A Way", 109));
	mPlaylist.emplace_back(Track("2 MaRLo feat. Jano", "The Dreamers", 108));
	mPlaylist.emplace_back(Track("3 Matt Darey feat. Kate Louise Smith", "See The Sun (Dan Stone Rework)", 107));
	mPlaylist.emplace_back(Track("4 Above & Beyond feat. Zoe Johnston", "We're All We Need", 106));
	mPlaylist.emplace_back(Track("5 Omnia feat. Tilde", "For The First Time", 105));
	mPlaylist.emplace_back(Track("6 Armin van Buuren feat. Eric Vloeimans", "Embrace", 104));
	mPlaylist.emplace_back(Track("7 Armin van Buuren pres. Rising Star feat. Betsie Larkin", "Safe Inside You", 103));
	mPlaylist.emplace_back(Track("8 Armin van Buuren & Jean Michel-Jarre", "Stardust (Armin van Buuren pres. Rising Star Remix", 102));
	mPlaylist.emplace_back(Track("9 Ferry Corsten pres. Gouryella", "Anahera", 101));
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
	return types;
}

void PlaylistModel::OnInsert(QStringList list)
{
	const QModelIndex parent = QModelIndex();
	const auto row = mPlaylist.size();
	const auto cnt = list.size();

	beginInsertRows(parent, row, row + cnt - 1);

	for (const auto& path : list) {
		mPlaylist.emplace_back(Track(path, "qwe", 123));
	}

	endInsertRows();
}

void PlaylistModel::OnMove(QVector<int> rows, int dest)
{
	qDebug() << "PlaylistModel::OnMove: rows " << rows << " dest = " << dest;

	const QModelIndex parent = QModelIndex();
	// Number of rows for the moving.
	const auto num(rows.size());

	auto res = beginMoveRows(parent, rows[0], rows[num - 1], parent, dest);

	if (!res) {
		qDebug() << "PlaylistModel::OnMove: Result is " << res;
		return;
	}

	// Copy rows whose have been moved into the temporary vector.
	Playlist tmp(num);
	for (int i = 0; i < num; ++i) {
		tmp[i] = mPlaylist[rows[i]];
	}
	// Delete moved rows from current playlist.
	for (const auto& row : rows) {
		mPlaylist.erase(std::begin(mPlaylist) + row);
	}

	if (dest > static_cast<int>(mPlaylist.size()))
		dest = mPlaylist.size();

	int coef = 0;
	if (rows[0] < dest) {
		coef = -1;
	}

	// Move rows to the destination.
	mPlaylist.insert(std::begin(mPlaylist) + dest + coef, std::begin(tmp), std::end(tmp));

	endMoveRows();
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
