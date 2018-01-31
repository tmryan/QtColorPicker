#include <QtGui/QFocusEvent>
#include <QtWidgets/QLabel>

#include <TitledTextDisplay.h>

TitledTextDisplay::TitledTextDisplay(QString title, QWidget *parent)
	: QLineEdit(parent)
{
	titleLabel = new QLabel(this);
}

TitledTextDisplay::~TitledTextDisplay()
{
	delete titleLabel;
}

void TitledTextDisplay::focusInEvent(QFocusEvent *ev)
{

}
