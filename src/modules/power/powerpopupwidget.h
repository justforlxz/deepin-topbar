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
class PowerModel;
class PowerPopupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PowerPopupWidget(QWidget *parent = nullptr);

    void setModel(PowerModel* model);

signals:

public slots:

private:
    widgets::SettingsGroup* m_powerSettingsGrp;
    widgets::TitleValueItem* m_sourceItem;
    widgets::SwitchWidget* m_rcentageSwitcher;
    PowerModel* m_model;
};
}
}

#endif // POWERPOPUPWIDGET_H
