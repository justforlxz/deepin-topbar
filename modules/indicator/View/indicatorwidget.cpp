#include "indicatorwidget.h"
#include "utils/global.h"

#include <QHBoxLayout>
#include <QIcon>
#include <QMouseEvent>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QDBusConnection>
#include "../themeappicon.h"

namespace dtb {
namespace indicator {

IndicatorWidget::IndicatorWidget(QWidget *parent)
    : ContentModule(parent)
{
    initUI();

    m_systeminfo = new systeminfo("com.deepin.daemon.SystemInfo", "/com/deepin/daemon/SystemInfo",
                                  QDBusConnection::sessionBus(), this);

    m_systemVersion = m_systeminfo->version();

    m_systeminfo->setSync(false);
    
    connect(m_systeminfo, &systeminfo::VersionChanged, this, [=] (const QString &version){
        m_systemVersion = version;
    });
    
    m_dockInter = new DBusDock("com.deepin.dde.daemon.Dock","/com/deepin/dde/daemon/Dock" , QDBusConnection::sessionBus(),this);

    connect(m_dockInter, &DBusDock::EntryAdded, this, &IndicatorWidget::addEntry);
    connect(m_dockInter, &DBusDock::EntryRemoved, this, &IndicatorWidget::removeEntry);

    getAllEntry();
}

IndicatorWidget::~IndicatorWidget()
{
    m_dockInter->deleteLater();
}

void IndicatorWidget::initUI()
{
    setObjectName("Indiactor");
    setStyleSheet("QLabel {color: #d3d3d3;}");

    setWindowFlags(Qt::WindowDoesNotAcceptFocus);
    setAttribute(Qt::WA_TranslucentBackground);

    setFixedSize(QSize(200, TOPHEIGHT));

    m_entry = new Entry;

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_entry, 0, Qt::AlignLeft | Qt::AlignVCenter);

    setLayout(mainLayout);
}

void IndicatorWidget::forceQuit()
{
    for (DBusDockEntry *entry : m_entryList) {
        if (entry->active()) {
            entry->HandleMenuItem("2");
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
