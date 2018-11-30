#ifndef ENTRY_H
#define ENTRY_H

#include <QWidget>
#include <QLabel>

namespace dtb {
namespace indicator {

class Entry : public QFrame
{
    Q_OBJECT
public:
    explicit Entry(QWidget *parent = 0);

    void setText(const QString &text);

private:
    QLabel *m_title;
};
}
}
#endif // ENTRY_H
