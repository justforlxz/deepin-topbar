#include "indicatorwidget.h"
#include "frame/utils/global.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QMouseEvent>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QDBusConnection>
#include "frame/utils/themeappicon.h"

namespace dtb {
namespace indicator {

IndicatorWidget::IndicatorWidget(QWidget *parent)
    : ContentModule(parent)
{
    initUI();

    m_systeminfo = new Systeminfo("com.deepin.daemon.SystemInfo", "/com/deepin/daemon/SystemInfo", QDBusConnection::sessionBus(), this);

    m_systemVersion = m_systeminfo->version();

    m_systeminfo->setSync(false);

    connect(m_systeminfo, &Systeminfo::VersionChanged, this, [=] (const QString &version){
        m_systemVersion = version;
    });

    m_dockInter = new DockInter("com.deepin.dde.daemon.Dock","/com/deepin/dde/daemon/Dock" , QDBusConnection::sessionBus(),this);

    connect(m_dockInter, &DockInter::EntryAdded, this, &IndicatorWidget::addEntry, Qt::ConnectionType::QueuedConnection);
    connect(m_dockInter, &DockInter::EntryRemoved, this, &IndicatorWidget::removeEntry, Qt::ConnectionType::QueuedConnection);

    getAllEntry();
}

IndicatorWidget::~IndicatorWidget()
{
    m_dockInter->deleteLater();
}

void IndicatorWidget::initUI()
{
    setObjectName("Indiactor");
    setStyleSheet("QLabel {color: #d3d3d3; font-size: 11pt;}");

    setWindowFlags(Qt::WindowDoesNotAcceptFocus);
    setAttribute(Qt::WA_TranslucentBackground);

    setFixedHeight(TOPHEIGHT);

    m_entry = new Entry;

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_entry, 0, Qt::AlignLeft | Qt::AlignVCenter);

    setLayout(mainLayout);
}

void IndicatorWidget::forceQuit()
{
    for (DockEntry *entry : m_entryList) {
        if (entry->isActive()) {
            entry->ForceQuit();
            return;
        }
    }
}

void IndicatorWidget::getAllEntry()
{
    for (const QDBusObjectPath &entryPath : m_dockInter->entries())
        addEntry(entryPath, m_entryList.count());
}

void IndicatorWidget::addEntry(const QDBusObjectPath &entryPath, const int index)
{
    Q_UNUSED(index);

    DockEntry *entry = new DockEntry("com.deepin.dde.daemon.Dock", entryPath.path(), QDBusConnection::sessionBus(), this);
    m_entryList.append(entry);

    connect(entry, &DockEntry::IsActiveChanged, this, &IndicatorWidget::refreshActiveWindow, Qt::UniqueConnection);
    connect(entry, &DockEntry::NameChanged, this, &IndicatorWidget::refreshActiveWindow, Qt::UniqueConnection);

    refreshActiveWindow();
}

void IndicatorWidget::removeEntry(const QString &entryID)
{
    for (auto it = m_entryList.begin(); it != m_entryList.end(); ++it) {
        if ((*it)->id() == entryID) {
            // (*it)->disconnect(); // I don't konw why crash
            (*it)->deleteLater();
            m_entryList.erase(it);
            break;
        }
    }

    refreshActiveWindow();
}

void IndicatorWidget::refreshActiveWindow()
{
    for (DockEntry *entry : m_entryList) {
        if (entry->isActive()) {
            m_entry->setText(entry->name());
            m_entry->setVisible(true);
//            emit requestBackgroundChanged(QColor(0, 0, 0, 255));
            return;
        }
    }

    m_entry->setText(m_systemVersion);
}

}
}
