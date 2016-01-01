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
	mData.emplace_back(Track("0 Markus Schulz feat. Delacey", "Destiny", 110));
	mData.emplace_back(Track("1 Photographer & Susana", "Find A Way", 109));
	mData.emplace_back(Track("2 MaRLo feat. Jano", "The Dreamers", 108));
	mData.emplace_back(Track("3 Matt Darey feat. Kate Louise Smith", "See The Sun (Dan Stone Rework)", 107));
	mData.emplace_back(Track("4 Above & Beyond feat. Zoe Johnston", "We're All We Need", 106));
	mData.emplace_back(Track("5 Omnia feat. Tilde", "For The First Time", 105));
	mData.emplace_back(Track("6 Armin van Buuren feat. Eric Vloeimans", "Embrace", 104));
	mData.emplace_back(Track("7 Armin van Buuren pres. Rising Star feat. Betsie Larkin", "Safe Inside You", 103));
	mData.emplace_back(Track("8 Armin van Buuren & Jean Michel-Jarre", "Stardust (Armin van Buuren pres. Rising Star Remix", 102));
	mData.emplace_back(Track("9 Ferry Corsten pres. Gouryella", "Anahera", 101));
}

int PlaylistModel::columnCount(const QModelIndex& parent) const
{
	// Note! When implementing a table based model,
	// columnCount() should return 0 when the parent is valid.
	return parent.isValid() ? 0 : 4;
}

QVariant PlaylistModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid()) {
		return QVariant();
	}

	const auto row(index.row());
	const auto column(index.column());

	if (row >= static_cast<int>(mData.size())) {
		return QVariant();
	}

	if (role == Qt::DisplayRole) {
		switch (column) {
		case 1:
			return QVariant(mData[row].Author());
		case 2:
			return QVariant(mData[row].Title());
		case 3:
			return QVariant(mData[row].DurationStr());
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

QStringList PlaylistModel::mimeTypes() const
{
	QStringList types;
	types << "application/splay-track";
	return types;
}

void PlaylistModel::OnInsert(QStringList list)
{
	const QModelIndex parent = QModelIndex();
	const auto row = mData.size();
	const auto cnt = list.size();

	beginInsertRows(parent, row, row + cnt - 1);

	for (const auto& path : list) {
		mData.emplace_back(Track(path, "qwe", 123));
	}

	endInsertRows();
}

void PlaylistModel::OnMove(RowsList selectedRows, int dest)
{
	qDebug() << "PlaylistModel::OnMove: number = " << selectedRows.size() << " dest = " << dest;

	const QModelIndex parent = QModelIndex();
	// Number of rows for the moving.
	const auto num(static_cast<int>(selectedRows.size()));

	auto res = beginMoveRows(parent, selectedRows[0], selectedRows[num - 1], parent, dest);

	if (!res) {
		qDebug() << "PlaylistModel::OnMove: Result is " << res;
		return;
	}

	// Copy rows whose have been moved into the temporary vector.
	Playlist tmp(num);
	for (int i = 0; i < num; ++i) {
		tmp[i] = mData[selectedRows[i]];
	}
	// Delete moved rows from current playlist.
	for (const auto& row : selectedRows) {
		mData.erase(std::begin(mData) + row);
	}

	if (dest > static_cast<int>(mData.size()))
		dest = mData.size();

	int coef = 0;
	if (selectedRows[0] < dest) {
		coef = -1;
	}

	// Move selected rows to the destination.
	mData.insert(std::begin(mData) + dest + coef, std::begin(tmp), std::end(tmp));

	endMoveRows();
}

void PlaylistModel::OnRemove(RowsList selectedRows)
{
	int coef = 0;

	// coef var is used for the correction. We should update
	// values in the list of selected rows after erasing,
	// since size of list on every iteration decreasing.

	Q_EMIT layoutAboutToBeChanged();

	auto oldModelIndex = QModelIndex();

	for (const auto& row : selectedRows) {
		mData.erase(std::cbegin(mData) + row - coef);
		++coef;
	}

	changePersistentIndex(oldModelIndex, QModelIndex());

	Q_EMIT layoutChanged();
}

int PlaylistModel::rowCount(const QModelIndex& parent) const
{
	// Note! When implementing a table based model,
	// rowCount() should return 0 when the parent is valid.
	return parent.isValid() ? 0 : mData.size();
}

Qt::DropActions PlaylistModel::supportedDropActions() const
{
	return Qt::CopyAction | Qt::MoveAction;
}

} // namespace splay
