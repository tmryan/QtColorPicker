#include <QtCore/QString>
#include <QtGui/QMouseEvent>

#include <ColorPickerOverlayWidget.h>
#include <TitleBarWidget.h>
#include <qttime.h>

QtTime::QtTime(QWidget *parent) 
	: QMainWindow(parent)
{
	ui.setupUi(this);	
	initMainWindowUi();
	initColorPickerButton();
	initPickedColorLabel();
	initTilteBarUi();
	initColorPickerOverlayUi();
	initColorValuesUi();
}

QtTime::~QtTime()
{
	delete colorPickerOverlay;
	delete titleBar;
}

bool QtTime::eventFilter(QObject *obj, QEvent *ev)
{
	bool isLineEdit = (obj == ui.lineEditHex || obj == ui.lineEditRGB || obj == ui.lineEditFloat);
	if (isLineEdit && ev->type() == QEvent::MouseButtonPress) {
		QLineEdit *lineEdit = qobject_cast<QLineEdit*>(obj);
		lineEdit->selectAll();
		return true;
	}
		
	return QMainWindow::eventFilter(obj, ev);
}

void QtTime::updateDraggedWindowPosition(const QPoint &draggedDistance)
{
	move(pos() + draggedDistance);
}

void QtTime::displayColorInfoInGUI(QColor const &color)
{
	ui.lineEditHex->setText(color.name());

	ui.lineEditRGB->setText(QString::number(color.red()) + ", " 
						  + QString::number(color.green()) + ", " 
						  + QString::number(color.blue()));
	
	QString redFloatValue = QString::number(color.redF());
	QString greenFloatValue = QString::number(color.greenF());
	QString blueFloatValue = QString::number(color.blueF());	
	redFloatValue.truncate(4);
	greenFloatValue.truncate(4);
	blueFloatValue.truncate(4);
	
	QString colorAsFloats = redFloatValue + ", " + greenFloatValue + ", " + blueFloatValue;
	ui.lineEditFloat->setText(colorAsFloats);
}

void QtTime::activateColorPickerMode()
{
	colorPickerOverlay->showFullScreen();
}

void QtTime::displayCurrentMouseoverColor(const QColor &currentColor)
{
	ui.labelPickedColor->setStyleSheet("background-color: " + currentColor.name());
	displayColorInfoInGUI(currentColor);
}

void QtTime::pickCurrentMouseoverColor(const QColor &currentColor)
{
	pickedColor = currentColor;
	colorPickerOverlay->hide();
	displayColorInfoInGUI(pickedColor);
}

void QtTime::resetColorToLastPicked()
{
	ui.labelPickedColor->setStyleSheet("background-color: " + pickedColor.name());
	colorPickerOverlay->hide();
	displayColorInfoInGUI(pickedColor);
}

void QtTime::initMainWindowUi()
{
	setWindowTitle("Color Picker");
	setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
}

void QtTime::initColorPickerButton()
{
	ui.btnActivateColorPickerMode->setToolTip("Activate color picker mode");
	connect(ui.btnActivateColorPickerMode, &QPushButton::clicked, this, &QtTime::activateColorPickerMode);
}

void QtTime::initPickedColorLabel()
{
	ui.labelPickedColor->setAutoFillBackground(true);
}

void QtTime::initTilteBarUi()
{
	int titleBarHeight = 32;
	titleBar = new TitleBarWidget("Color Picker", this, titleBarHeight);
	connect(titleBar, &TitleBarWidget::onWidgetBeingDragged, this, &QtTime::updateDraggedWindowPosition);
}

void QtTime::initColorPickerOverlayUi()
{
	colorPickerOverlay = new ColorPickerOverlayWidget(this);
	connect(colorPickerOverlay, &ColorPickerOverlayWidget::onCursorMoved, this, &QtTime::displayCurrentMouseoverColor);
	connect(colorPickerOverlay, &ColorPickerOverlayWidget::onColorPicked, this, &QtTime::pickCurrentMouseoverColor);
	connect(colorPickerOverlay, &ColorPickerOverlayWidget::onExitWithoutPickingColor, this, &QtTime::resetColorToLastPicked);
	colorPickerOverlay->hide();
}

void QtTime::initColorValuesUi()
{
	ui.lineEditHex->setReadOnly(true);
	ui.lineEditRGB->setReadOnly(true);
	ui.lineEditFloat->setReadOnly(true);
	ui.lineEditHex->installEventFilter(this);
	ui.lineEditRGB->installEventFilter(this);
	ui.lineEditFloat->installEventFilter(this);
}
