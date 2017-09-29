#ifndef FONTLABEL_H
#define FONTLABEL_H

#include <QLabel>

namespace dtb {
namespace widgets {
class FontLabel : public QLabel
{
    Q_OBJECT
public:
    explicit FontLabel(QWidget *parent = 0);
    void setIcon(const QChar c, int size);

signals:
    void clicked();

protected:
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QFont m_iconFont;
};
}
}

#endif // FONTLABEL_H
