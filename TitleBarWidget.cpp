#include <QApplication>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>

#include "TitleBarWidget.h"

TitleBarWidget::TitleBarWidget(QString title, QWidget *parent, int height) 
	: QWidget(parent)
{
	resize(parent->width(), height);

	exitButton = new QPushButton("X", this);
	exitButton->setAttribute(Qt::WA_NoMousePropagation);
	int exitButtonSize = DEFAULT_TITLEBAR_HEIGHT;
	exitButton->resize(exitButtonSize, exitButtonSize);
	exitButton->move(QPoint(width() - exitButtonSize, 0));
	exitButton->setFont(QFont("Gothic", 10));
	connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);

	titleLabel = new QLabel(title, this);
	titleLabel->resize(width() - exitButton->width(), height);
	titleLabel->setFont(QFont("MS Gothic", 12));
	titleLabel->setAlignment(Qt::AlignCenter);
}

TitleBarWidget::~TitleBarWidget() 
{
	delete exitButton;
	delete titleLabel;
}

void TitleBarWidget::mousePressEvent(QMouseEvent *ev)
{
	previousMousePosition = ev->pos();
}

void TitleBarWidget::mouseMoveEvent(QMouseEvent *ev)
{
	QPoint draggedDistance = ev->pos() - previousMousePosition;
	emit onWidgetBeingDragged(draggedDistance);
}
