#ifndef TEXTTICKER_H
#define TEXTTICKER_H

#include <QLabel>

namespace Plugin {
namespace MediaControl {

class TextTicker : public QLabel
{
    Q_OBJECT
public:
    explicit TextTicker(QWidget *parent = 0);
    void setText(const QString &source);

protected:
    void paintEvent(QPaintEvent *event);
    void updateIndex();

private:
    int m_charWidth;
    int m_curIndex;
    QString m_showText;
    QTimer *m_timer;
    bool m_isFirstPlay;
    int m_moveSpeed;
};
}
}

#endif // TEXTTICKER_H
