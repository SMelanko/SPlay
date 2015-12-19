#pragma once

#ifndef _SPLAY_TABLE_WGT_H_
#define _SPLAY_TABLE_WGT_H_

#include <QTableWidget>

class TableWgt : public QTableWidget
{
	Q_OBJECT

public:
	//! Constructor.
	explicit TableWgt(QWidget* parent = Q_NULLPTR);
	//! Destructor.
	~TableWgt();

protected:
	void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;
	bool dropMimeData(int row, int column, const QMimeData *data, Qt::DropAction action) Q_DECL_OVERRIDE;

private slots:
	void OnDoubleCkick(QTableWidgetItem* item);
	void OnSectionClicked(int index);
	void OnSectionResized(int logicalIndex, int oldSize, int newSize);

private:
	QString Qss();

private:
	int m_rowCnt;
	bool m_sectionResized;
};

#endif // _SPLAY_TABLE_WGT_H_
