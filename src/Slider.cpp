#include "Slider.h"

#include <QDebug>
#include <QMouseEvent>

namespace splay
{

Slider::Slider(Qt::Orientation orient, QWidget* parent)
	: QSlider{ orient, parent }
{
	setCursor(Qt::PointingHandCursor);
	setFixedHeight(10); // For Windows.
	setToolTip(tr("Seek"));
	setStyleSheet(_Qss());
}

void Slider::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		const auto val = minimum() +
			((maximum()- minimum()) * event->x()) / width();
		setValue(val);

		event->accept();
	}
	else {
		QSlider::mousePressEvent(event);
	}
}

QString Slider::_Qss() const
{
	return QString{
		"QSlider::groove:horizontal { \
			border: 1px solid #bbb; \
			background: #e3e3e3; \
			height: 5px; \
			border-radius: 2px; \
		} \
		QSlider::sub-page:horizontal { \
			background: qlineargradient(x1: 0, y1: 0.2, x2: 1, y2: 1, \
				stop: 0 #9abee3, stop: 1 #356ccc); \
			border-top: 1px solid #bbb; \
			border-bottom: 1px solid #bbb; \
			border-left: 1px solid #bbb; \
			border-top-left-radius: 2px; \
			border-bottom-left-radius: 2px; \
		} \
		QSlider::add-page:horizontal { \
			background: #fff; \
			border-top: 1px solid #bbb; \
			border-bottom: 1px solid #bbb; \
			border-right: 1px solid #bbb; \
			border-top-right-radius: 2px; \
			border-bottom-right-radius: 2px; \
		}"};
}

}
