#include "TableWgt.h"
#include <QHeaderView>
#include <QKeyEvent>
#include <QDebug>
#include <QMimeData>

TableWgt::TableWgt(QWidget* parent)
    : QTableWidget(parent)
    , m_rowCnt(false)
    , m_sectionResized(false)
{
    // Sets the size policy of the widget to horizontal and vertical.
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //this->setItemDelegate(new ItemDelegatePaint);
    // Sets the number of columns in this model to columns.
    this->setColumnCount(4);
    // Sets the horizontal header labels using labels.
    this->setHorizontalHeaderLabels(
                QString("Playing;Author;Title;Duration").split(";"));
    // Sets additional parameters to the horizontal header.
    this->horizontalHeader()->setVisible(true);
    this->horizontalHeader()->setHighlightSections(false);
    this->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
    // Sets additional parameters to the vertical header.
    this->verticalHeader()->setVisible(false);
    this->verticalHeader()->setDefaultSectionSize(23);
    this->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
    // Sets custom widget's style sheet.
    this->setStyleSheet(this->Qss());
    // Disable possibility to edit.
    this->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
    // Alternates background color in the table.
    this->setAlternatingRowColors(true);
    // Enables rows selection.
    this->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
    // User can select a one or more rows in the play list.
    this->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);

    //
    // Drag and drop
    //
    this->setDragEnabled(true);
    this->viewport()->setAcceptDrops(true);
    this->setDefaultDropAction(Qt::TargetMoveAction);
    this->setDragDropMode(QAbstractItemView::DragDrop);
    this->setDragDropOverwriteMode(false);
    this->setDropIndicatorShown(true);

    this->insertRow(m_rowCnt++);
    QTableWidgetItem* playing = new QTableWidgetItem(">");
	playing->setTextAlignment(Qt::AlignCenter);
	this->setItem(0, 0, playing);
    this->setItem(0, 1, new QTableWidgetItem("Armin van Buuren"));
    this->setItem(0, 2, new QTableWidgetItem("Shivers"));
    this->setItem(0, 3, new QTableWidgetItem("05:22"));

    this->insertRow(m_rowCnt++);
    this->setItem(1, 1, new QTableWidgetItem("Aruna with Mark Etenson"));
    this->setItem(1, 2, new QTableWidgetItem("Let go (Nic Chagall remix)"));
    this->setItem(1, 3, new QTableWidgetItem("08:30"));

    //Photographer & Susana - Find A Way
    this->insertRow(m_rowCnt++);
    this->setItem(2, 1, new QTableWidgetItem("Photographer & Susana"));
    this->setItem(2, 2, new QTableWidgetItem("Find A Way"));
    this->setItem(2, 3, new QTableWidgetItem("05:01"));

    connect(this, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(OnDoubleCkick(QTableWidgetItem*)));
    connect(this->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(OnSectionClicked(int)));
    connect(this->horizontalHeader(), SIGNAL(sectionResized(int,int,int)), this, SLOT(OnSectionResized(int,int,int)));
}

TableWgt::~TableWgt()
{
}

bool TableWgt::dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action)
{
    QString act;
    if (Qt::CopyAction == action)
        act = "CopyAction";
    else if (Qt::MoveAction == action)
        act = "MoveAction";
    else if (Qt::LinkAction == action)
        act = "LinkAction";
    else if (Qt::ActionMask == action)
        act = "ActionMask";
    else if (Qt::TargetMoveAction == action)
        act = "TargetMoveAction";
    else if (Qt::IgnoreAction == action)
        act = "IgnoreAction";

    qDebug() << "Row = " << row << "\t"
             << "Action = " << act << "\t"
             << data->objectName();
    //data->dumpObjectInfo();

    return true;
}

void TableWgt::OnDoubleCkick(QTableWidgetItem* item)
{
    // get current track
    // delete playing indicator
    qDebug() << "Row = " << item->row();
    QTableWidgetItem* playing = new QTableWidgetItem(">");
    playing->setTextAlignment(Qt::AlignCenter);
    this->setItem(item->row(), 0, playing);
}

void TableWgt::OnSectionClicked(int index)
{
    qDebug() << "TableWgt::OnHHeaderClicked index = " << index;
}

void TableWgt::OnSectionResized(int logicalIndex, int oldSize, int newSize)
{
    if (!m_sectionResized)
        m_sectionResized = true;

    // Save table settings
    qDebug() << "TableWgt::OnSectionResized section has been resized"
             << " index = " << logicalIndex
             << " oldSize = " << oldSize
             << " newSize = " << newSize
             << " m_sectionResized = " << m_sectionResized;

    // Set flag in true
    // Then user closes program, app will check this flag
    // and if it is true, will save new section settings.
}

void TableWgt::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        qDebug() << "Key_Enter starts play current track " << currentRow();
    else if (event->key() == Qt::Key_Delete)
        qDebug() << "Key_Delete Delete track from play list " << currentRow();
    else if (event->key() == Qt::Key_Space)
        qDebug() << "Key_Space Pause " << currentRow();
    else
        QTableWidget::keyPressEvent(event);
}

QString TableWgt::Qss()
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
