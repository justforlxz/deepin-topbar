#ifndef FONTLABEL_H
#define FONTLABEL_H

#include <QLabel>

class FontLabel : public QLabel
{
    Q_OBJECT
public:
    explicit FontLabel(QWidget *parent = 0);
    void setIcon(const QChar c, int size);

private:
    QFont m_iconFont;
};

#endif // FONTLABEL_H
