#include "indicatorwidget.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QMouseEvent>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QDBusConnection>
#include "themeappicon.h"

namespace Plugin {
namespace Indicator {

IndicatorWidget::IndicatorWidget(QWidget *parent) : QWidget(parent)
{
    initUI();

    m_systeminfo = new systeminfo("com.deepin.daemon.SystemInfo", "/com/deepin/daemon/SystemInfo",
                                  QDBusConnection::sessionBus(), this);

    m_systemVersion = m_systeminfo->version();

    m_systeminfo->setSync(false);
    
    connect(m_systeminfo, &systeminfo::VersionChanged, this, [=] (const QString &version){
        m_systemVersion = version;
    });
    
    m_dockInter = new DBusDock(this);
    m_smallWatcher= new QFutureWatcher<QPixmap>(this);

    connect(m_dockInter, &DBusDock::EntryAdded, this, &IndicatorWidget::addEntry);
    connect(m_dockInter, &DBusDock::EntryRemoved, this, &IndicatorWidget::removeEntry);

    connect(m_smallWatcher, &QFutureWatcher<QPixmap>::finished, this, &IndicatorWidget::refreshIcon);

    getAllEntry();
}

IndicatorWidget::~IndicatorWidget()
{
    m_dockInter->deleteLater();
}

void IndicatorWidget::initUI()
{
    setWindowFlags(Qt::WindowDoesNotAcceptFocus);
    setAttribute(Qt::WA_TranslucentBackground);

    setFixedSize(QSize(200, 26));

    m_entry = new Entry;

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_entry, 0, Qt::AlignLeft | Qt::AlignVCenter);

    setLayout(mainLayout);
}

void IndicatorWidget::getAllEntry()
{
    for (const QDBusObjectPath &entryPath : m_dockInter->entries())
        addEntry(entryPath, m_entryList.count());
}

void IndicatorWidget::addEntry(const QDBusObjectPath &entryPath, const int index)
{
    Q_UNUSED(index);

    DBusDockEntry *entry = new DBusDockEntry(entryPath.path());
    m_entryList.append(entry);

    connect(entry, &DBusDockEntry::ActiveChanged, this, &IndicatorWidget::refreshActiveWindow, Qt::UniqueConnection);
    connect(entry, &DBusDockEntry::TitlesChanged, this, &IndicatorWidget::refreshActiveWindow, Qt::UniqueConnection);

    refreshActiveWindow();
}

void IndicatorWidget::removeEntry(const QString &entryID)
{
    for (int i = 0; i != m_entryList.count(); i++) {
        if (m_entryList.at(i)->id() == entryID) {
            DBusDockEntry *entry = m_entryList.at(i);
            m_entryList.removeAt(i);
            entry->disconnect();
            entry->deleteLater();
            break;
        }
    }

    refreshActiveWindow();
}

void IndicatorWidget::refreshActiveWindow()
{
    for (DBusDockEntry *entry : m_entryList) {
        if (entry->active()) {
            m_smallWatcher->cancel();
            m_smallWatcher->setFuture(QtConcurrent::run(ThemeAppIcon::getIcon, entry->icon()));
            m_entry->setText(windowTitle(entry->titles()));
            m_entry->setVisible(true);
            return;
        }
    }

    m_entry->setText(m_systemVersion);
    m_entry->setNormalIcon(QIcon::fromTheme("dde"));
}

void IndicatorWidget::refreshIcon()
{
    m_entry->setNormalIcon(QIcon(m_smallWatcher->result()));
}

const QString IndicatorWidget::windowTitle(const WindowDict &infos)
{
    for (auto it(infos.cbegin()); it != infos.cend(); ++it)
    {
        return it.value();
    }

    return QString();
}

}
}
