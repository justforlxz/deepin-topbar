#ifndef ENTRY_H
#define ENTRY_H

#include <QWidget>
#include <QLabel>

class Entry : public QWidget
{
    Q_OBJECT
public:
    explicit Entry(QWidget *parent = 0);

    void setNormalIcon(const QIcon &normalIcon);
    void setText(const QString &text);

private:
    QLabel *m_normalIcon;
    QLabel *m_title;
};

#endif // ENTRY_H
