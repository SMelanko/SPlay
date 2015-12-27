#include "TableWgt.h"

#include <QHeaderView>
#include <QKeyEvent>
#include <QMimeData>
#include <QDebug>

namespace splay
{

PlaylistView::PlaylistView(QWidget* parent)
	: QTableView(parent)
	, mSectionResized(false)
{
	// Set the size policy of the widget to horizontal and vertical.
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	// Set the horizontal header labels.
	//setHorizontalHeaderLabels(QString{ "Playing;Author;Title;Duration" }.split(";"));
	// Set additional parameters to the horizontal header.
	horizontalHeader()->setVisible(true);
	horizontalHeader()->setHighlightSections(false);
	setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
	// Set additional parameters to the vertical header.
	verticalHeader()->setVisible(false);
	verticalHeader()->setDefaultSectionSize(23);
	setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
	// Set custom widget style sheet.
	//setStyleSheet(_Qss());
	// Disable possibility for editing rows.
	setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
	// Alternate background color in the table.
	setAlternatingRowColors(true);
	// Enable rows selection.
	setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	// User can select a one or more rows in the play list.
	setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);

	//
	// TODO Drag and drop.
	//
	// Enable drop events in the current widget area.
	setDragEnabled(true);
	setAcceptDrops(true);
	//setDefaultDropAction(Qt::TargetMoveAction);
	//setDragDropMode(QAbstractItemView::DragDrop);
	//setDragDropOverwriteMode(false);
	//setDropIndicatorShown(true);

	//
	// TODO Only for test.
	//
#if 0
	insertRow(rowCount());
	QTableWidgetItem* playing = new QTableWidgetItem(">");
	playing->setTextAlignment(Qt::AlignCenter);
	this->setItem(0, 0, playing);
	this->setItem(0, 1, new QTableWidgetItem("Armin van Buuren"));
	this->setItem(0, 2, new QTableWidgetItem("Shivers"));
	this->setItem(0, 3, new QTableWidgetItem("05:22"));

	this->insertRow(rowCount());
	this->setItem(1, 1, new QTableWidgetItem("Aruna with Mark Etenson"));
	this->setItem(1, 2, new QTableWidgetItem("Let go (Nic Chagall remix)"));
	this->setItem(1, 3, new QTableWidgetItem("08:30"));

	this->insertRow(rowCount());
	this->setItem(2, 1, new QTableWidgetItem("Photographer & Susana"));
	this->setItem(2, 2, new QTableWidgetItem("Find A Way"));
	this->setItem(2, 3, new QTableWidgetItem("05:01"));
#endif
	connect(this, &QTableView::doubleClicked, this, &PlaylistView::OnDoubleCkick);
	connect(horizontalHeader(), &QHeaderView::sectionClicked, this, &PlaylistView::OnSectionClicked);
	connect(horizontalHeader(), &QHeaderView::sectionResized, this, &PlaylistView::OnSectionResized);
}

PlaylistView::~PlaylistView()
{
}

void PlaylistView::dragEnterEvent(QDragEnterEvent* event)
{
	qDebug() << "Drag enter event";
	event->acceptProposedAction();
}

void PlaylistView::dragLeaveEvent(QDragLeaveEvent* event)
{
	qDebug() << "Drag leave event";
	event->accept();
}

void PlaylistView::dragMoveEvent(QDragMoveEvent* event)
{
	qDebug() << "Drag move event";
	event->acceptProposedAction();
}

void PlaylistView::dropEvent(QDropEvent* event)
{
	qDebug() << "Drop event";
	const QMimeData* mimeData = event->mimeData();
	auto urlList = mimeData->urls();
	for (const auto& url : urlList)
		qDebug() << url.fileName();
	event->acceptProposedAction();
}

void PlaylistView::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
		qDebug() << "Key_Enter starts play current track " << currentIndex().row();
	else if (event->key() == Qt::Key_Delete)
		qDebug() << "Key_Delete Delete track from play list " << currentIndex().row();
	else if (event->key() == Qt::Key_Space)
		qDebug() << "Key_Space Pause " << currentIndex().row();
	else
		QTableView::keyPressEvent(event);
}

void PlaylistView::OnDoubleCkick(const QModelIndex& index)
{
	// Get current track.
	// Delete playing indicator.
	qDebug() << "Row = " << index.row();
	//QTableWidgetItem* playing = new QTableWidgetItem(">");
	//playing->setTextAlignment(Qt::AlignCenter);
	//this->setItem(item->row(), 0, playing);
}

void PlaylistView::OnSectionClicked(int index)
{
	qDebug() << "TableWgt::OnHeaderClicked index = " << index;
}

void PlaylistView::OnSectionResized(int logicalIndex, int oldSize, int newSize)
{
	if (!mSectionResized)
		mSectionResized = true;

	// Save table settings
	qDebug() << "TableWgt::OnSectionResized section has been resized"
		<< " index = " << logicalIndex
		<< " oldSize = " << oldSize
		<< " newSize = " << newSize
		<< " m_sectionResized = " << mSectionResized;

	// Set flag in true
	// Then user closes program, app will check this flag
	// and if it is true, will save new section settings.
}

QString PlaylistView::_Qss()
{
	return QString(
		"QHeaderView {"
			"background-color: qlineargradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4287ff, stop: 1 #356ccc);"
		"}"
		"QHeaderView::section::horizontal {"
			"color: #fff;"
			"border-style: solid;"
			"background-color: qlineargradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #4287ff, stop: 1 #356ccc);"
		"}"
		"QHeaderView::section::horizontal::pressed {"
			"background-color: qlineargradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #356ccc, stop: 1 #356ccc);"
		"}"
		"QTableWidget {"
			"border: 2px solid #3873d9;"
			"border-radius: 2px;"
			"gridline-color: #d8d8d8;"
			"selection-color: #000;"
			"selection-background-color: #ccdfff;"
			"font-size: 12px;"
			"padding-top: 0px;"
		"}"
		"QScrollBar::vertical {"
			"background: #e4e4e4;"
			"border-left: 2px solid #3873d9;"
			"width: 15px;"
		"}"
		"QScrollBar::handle::vertical {"
			"background-color: qlineargradient( x1: 1, y1: 0, x2: 0, y2: 0, stop: 0 #4287ff, stop: 1 #356ccc);"
			"border-radius: 2px;"
			"min-height: 10px;"
			"margin: 1px 1px 1px 1px;"
		"}"
		"QScrollBar::add-line:vertical {"
			"background: none;"
			"height: 0px;"
			"subcontrol-position: right;"
			"subcontrol-origin: margin;"
		"}"
		"QScrollBar::sub-line::vertical {"
			"background: none;"
			"height: 0px;"
			"subcontrol-position: left;"
			"subcontrol-origin: margin;"
		"}"
		"QScrollBar::horizontal {"
			"background: #e4e4e4;"
			"border-top: 2px solid #3873d9;"
		"}"
		"QScrollBar::handle::horizontal {"
			"background-color: qlineargradient( x1: 0, y1: 1, x2: 0, y2: 0, stop: 0 #4287ff, stop: 1 #356ccc);"
			"border-radius: 2px;"
			"margin: 1px 1px 1px 1px;"
		"}"
		"QScrollBar::add-line::horizontal {"
			"background: none;"
			"height: 0px;"
			"subcontrol-position: right;"
			"subcontrol-origin: content;"
		"}"
		"QScrollBar::sub-line::horizontal {"
			"background: none;"
			"height: 0px;"
			"subcontrol-position: left;"
			"subcontrol-origin: content;"
		"}");
}

} // namespace splay
