#ifndef POWERPOPUPWIDGET_H
#define POWERPOPUPWIDGET_H

#include <QWidget>

namespace dtb {
namespace widgets {
class SettingsGroup;
class TitleValueItem;
class SwitchWidget;
}
namespace power {
class PowerPopupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PowerPopupWidget(QWidget *parent = nullptr);

signals:

public slots:

private:
    widgets::SettingsGroup* m_powerSettingsGrp;
    widgets::TitleValueItem* m_sourceItem;
    widgets::SwitchWidget* m_rcentageSwitcher;
};
}
}

#endif // POWERPOPUPWIDGET_H
