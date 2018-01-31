#include <QKeyEvent>
#include <QMouseEvent>

#include <QApplication>
#include <QScreen>

#include "ColorPickerOverlayWidget.h"

ColorPickerOverlayWidget::ColorPickerOverlayWidget(QWidget *parent) 
	: QWidget(parent, Qt::Dialog)
	, currentColor(QColor())
{
	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
	
	// Set background to balanced gray color to reduce picked color error
	setStyleSheet("background-color: #888888");
	
	qreal overlayOpacity = 0.004f;
	setWindowOpacity(overlayOpacity);
	showFullScreen();

	setCursor(Qt::CrossCursor);

	setMouseTracking(true);
}

ColorPickerOverlayWidget::~ColorPickerOverlayWidget() {}

void ColorPickerOverlayWidget::mouseMoveEvent(QMouseEvent *ev)
{
	QScreen* screen = QGuiApplication::primaryScreen();
	int entireScreen = 0;
	QPixmap currentScreenPixmap = screen->grabWindow(entireScreen);
	QImage currentScreenImage = currentScreenPixmap.toImage();
	currentColor = currentScreenImage.pixelColor(ev->pos());
	
	emit onCursorMoved(currentColor);
}

void ColorPickerOverlayWidget::mousePressEvent(QMouseEvent *ev)
{
	if (ev->button() == Qt::LeftButton || ev->button() == Qt::MiddleButton) {
		pickColor();
	} else {
		exitWithoutPickingColor();
	}
}

void ColorPickerOverlayWidget::keyPressEvent(QKeyEvent *ev)
{
	if (ev->key() == Qt::Key_Return || ev->key() == Qt::Key_Enter) {
		pickColor();
	} else {
		exitWithoutPickingColor();
	}
}

void ColorPickerOverlayWidget::pickColor()
{
	emit onColorPicked(currentColor);
}

void ColorPickerOverlayWidget::exitWithoutPickingColor()
{
	emit onExitWithoutPickingColor();
}
