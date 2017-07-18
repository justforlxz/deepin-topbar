#include "fontlabel.h"

#include <QFile>
#include <QFont>
#include <QFontDatabase>

FontLabel::FontLabel(QWidget *parent) : QLabel(parent)
{
    int fontId = QFontDatabase::addApplicationFont(":/segoe-mdl2-assets.ttf");
    QString fontName=QFontDatabase::applicationFontFamilies(fontId).at(0);

    m_iconFont = QFont(fontName);
}

void FontLabel::setIcon(QChar c, int size)
{
    m_iconFont.setPointSize(size);
    setFont(m_iconFont);
    setText(c);
}
