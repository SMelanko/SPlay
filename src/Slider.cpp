#include "Slider.h"

#include <QMouseEvent>

namespace splay
{

Slider::Slider(Qt::Orientation orient, QWidget* parent)
	: QSlider{ orient, parent }
{
	setCursor(Qt::PointingHandCursor);
	setFixedHeight(10);
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
	} else {
		QSlider::mousePressEvent(event);
	}
}

QString Slider::_Qss() const
{
	return QString{
		"QSlider::groove { \
			background: #e9e9e9; \
			border: 1px solid #d0d0d0; \
			border-radius: 3px; \
			height: 6px; \
		} \
		QSlider::sub-page { \
			background: #c77e35; \
			border-top: 1px solid #d0d0d0; \
			border-bottom: 1px solid #d0d0d0; \
			border-left: 1px solid #d0d0d0; \
			border-top-left-radius: 3px; \
			border-bottom-left-radius: 3px; \
		} \
		QSlider::add-page { \
			background: #fff; \
			border-top: 1px solid #d0d0d0; \
			border-bottom: 1px solid #d0d0d0; \
			border-right: 1px solid #d0d0d0; \
			border-top-right-radius: 3px; \
			border-bottom-right-radius: 3px; \
		}"};
}

} // namespace splay
