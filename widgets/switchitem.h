#ifndef SWITCHITEM_H
#define SWITCHITEM_H

#include <QWidget>
#include <QLabel>
#include <dswitchbutton.h>

DWIDGET_USE_NAMESPACE

namespace dtb {
namespace widgets {
class SwitchItem : public QWidget {
    Q_OBJECT
public:
    explicit SwitchItem(QWidget *parent = 0);

    const QString text() const { return m_text->text(); }
    bool checked() const { return m_switch->checked(); }
    const QString value() const {return m_value; }

signals:
    void clicked(const bool state);

public slots:
    void setText(const QString &text);
    void setCheck(const bool state);
    void setValue(const QString &value);

private:
    QLabel *m_text;
    DSwitchButton *m_switch;
    QString m_value;
};
}
}

#endif // SWITCHITEM_H
