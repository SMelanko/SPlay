#include "PlaylistView.h"

#include <QHeaderView>
#include <QKeyEvent>
#include <QMimeData>
#include <QDebug>

namespace splay
{

PlaylistView::PlaylistView(QWidget* parent)
	: QTableView{ parent }
	, mSectionResized{ false }
{
	_SetUpHorizontalHeader();
	_SetUpVerticalHeader();
	_SetUpDragAndDrop();

	// Alternate background color in the table.
	setAlternatingRowColors(true);
	// Disable possibility for editing rows.
	setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
	// Enable rows selection.
	setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	// User can select a one or more rows in the play list.
	setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);
	// Set the size policy of the widget to horizontal and vertical.
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	// Set custom widget style sheet.
	setStyleSheet(_Qss());

	connect(this, &QTableView::doubleClicked,
		this, &PlaylistView::OnDoubleCkicked);
	connect(horizontalHeader(), &QHeaderView::sectionClicked,
		this, &PlaylistView::OnSectionClicked);
	connect(horizontalHeader(), &QHeaderView::sectionResized,
		this, &PlaylistView::OnSectionResized);
}

void PlaylistView::dragEnterEvent(QDragEnterEvent* event)
{
	qDebug() << "PlaylistView::dragEnterEvent";
	event->acceptProposedAction();
}

void PlaylistView::dragLeaveEvent(QDragLeaveEvent* event)
{
	qDebug() << "PlaylistView::dragLeaveEvent";
	event->accept();
}

void PlaylistView::dropEvent(QDropEvent* event)
{
	if (event->mimeData()->hasFormat(QLatin1String("application/splay-track"))) {
		qDebug() << "PlaylistView::dropEvent: internal drop event";

		const auto pos(event->pos());
		const auto dest(indexAt(pos).row());

		qDebug() << "PlaylistView::dropEvent: drop pos = " << pos << " dest = " << dest;

		event->setDropAction(Qt::MoveAction);
		event->accept();

		Q_EMIT Move(_GetSelectedRows(), dest);
	} else {
		event->acceptProposedAction();

		Q_EMIT Insert(event->mimeData()->urls());
	}
}

void PlaylistView::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
		if (selectionModel()->hasSelection()) {
			auto rows = selectionModel()->selectedRows();
			if (rows.size() == 1) {
				Q_EMIT MediaIndexChanged(currentIndex().row());
				selectionModel()->clearSelection();
			}
		}
	} else if (event->key() == Qt::Key_Delete) {
		if (selectionModel()->hasSelection()) {
			Q_EMIT Remove(_GetSelectedRows());
			selectionModel()->clearSelection();
		}
	} else if (event->key() == Qt::Key_Space) {
		qDebug() << "PlaylistView::keyPressEvent: pause " << currentIndex().row();
	} else {
		QTableView::keyPressEvent(event);
	}
}

void PlaylistView::OnDoubleCkicked(const QModelIndex& index)
{
	qDebug() << "PlaylistView::OnDoubleCkick: row = " << index.row();
	Q_EMIT MediaIndexChanged(index.row());
}

void PlaylistView::OnSectionClicked(int index)
{
	qDebug() << "PlaylistView::OnSectionClicked: index = " << index;
}

void PlaylistView::OnSectionResized(int logicalIndex, int oldSize, int newSize)
{
	if (!mSectionResized)
		mSectionResized = true;

	// Save table settings
	qDebug() << "PlaylistView::OnSectionResized: "
		<< " index = " << logicalIndex
		<< " oldSize = " << oldSize
		<< " newSize = " << newSize
		<< " m_sectionResized = " << mSectionResized;

	// Set flag in true
	// Then user closes program, app will check this flag
	// and if it is true, will save new section settings.
}

RowList PlaylistView::_GetSelectedRows() const Q_DECL_NOEXCEPT
{
	const auto indexes = selectionModel()->selectedRows();
	RowList selectedRows(indexes.size());

	for (const auto& index : indexes) {
		selectedRows.push_back(index.row());
	}

	if (selectedRows.size() > 1) {
		std::sort(selectedRows.begin(), selectedRows.end());
	}

	return selectedRows;
}

void PlaylistView::_SetUpHorizontalHeader() Q_DECL_NOEXCEPT
{
	auto hh = horizontalHeader();
	hh->setHighlightSections(false);
	hh->setSectionsMovable(true);
	hh->setVisible(true);
	setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
}

void PlaylistView::_SetUpDragAndDrop() Q_DECL_NOEXCEPT
{
	// Enable drop events in the current widget area.
	setDragEnabled(true);
	setAcceptDrops(true);
	setDragDropMode(QTableView::InternalMove);
	setDropIndicatorShown(true);
}

void PlaylistView::_SetUpVerticalHeader() Q_DECL_NOEXCEPT
{
	auto vh = verticalHeader();
	vh->setDefaultSectionSize(23);
	vh->setVisible(false);
	setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
}

QString PlaylistView::_Qss() const Q_DECL_NOEXCEPT
{
	return QStringLiteral(
		"QHeaderView {"
			"background-color: #357ec7;"
			"font-size: 14px;"
		"}"
		"QHeaderView::section {"
			"color: #fff;"
			"border: 1px solid #357ec7;"
			"background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
				"stop: 0 #357ec7, stop: 0.5 #4387ff,"
				"stop: 0.6 #4387ff, stop: 1 #357ec7);"
		"}"
		"QTableView {"
			"border: 1px solid #357ec7;"
			"border-radius: 2px;"
			"gridline-color: #d0d0d0;"
			"font-size: 12px;"
		"}"
		"QScrollBar {"
			"background: #e9e9e9;"
			"border: none;"
			"border-radius: 3px;"
			"height: 9px;"
			"width: 9px;"
			"margin: 1px;"
		"}"
		"QScrollBar::handle {"
			"background: #d0d0d0;"
			"border-radius: 3px;"
			"min-width: 20px;"
			"min-height: 20px;"
		"}"
		"QScrollBar::handle::hover {"
			"background: #c3c3c3;"
		"}"
		"QScrollBar::add-line, QScrollBar::sub-line {"
			"background: none;"
			"border: none;"
		"}"
		"QScrollBar::add-page, QScrollBar::sub-page {"
			"background: none;"
		"}");
}

} // namespace splay
