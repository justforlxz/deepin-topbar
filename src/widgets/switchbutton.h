#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QWidget>

namespace dtb {
namespace widgets {
class SwitchButton : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchButton(QWidget *parent = nullptr);

signals:
    void stateChanged(bool state) const;

public slots:
};
}
}

#endif // SWITCHBUTTON_H
