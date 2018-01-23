#include "settingsdialog.h"
#include "utils/global.h"
#include "settings.h"

#include <DSettingsDialog>
using namespace dtb;

DWIDGET_USE_NAMESPACE

SettingsDialog::SettingsDialog(MainPanel *mainPanel, QWidget *parent)
    : QFrame(parent)
    , m_mainPanel(mainPanel)
{
    DSettingsDialog *dialog = new DSettingsDialog;

    dialog->updateSettings(Settings::InStance().settings());

    dialog->show();
}
