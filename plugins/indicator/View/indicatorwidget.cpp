#include "indicatorwidget.h"
#include <QHBoxLayout>
#include <QIcon>
#include <QMouseEvent>

namespace Plugin {
namespace Indicator {

IndicatorWidget::IndicatorWidget(QWidget *parent) : QWidget(parent)
{
    initUI();

    m_dockInter = new DBusDock(this);

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
    setWindowFlags(Qt::WindowDoesNotAcceptFocus);
    setAttribute(Qt::WA_TranslucentBackground);

    m_entry = new Entry;
    m_entry->resize(QSize(23, 23));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(m_entry, 0, Qt::AlignLeft);

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
            const QIcon icon = QIcon::fromTheme(entry->icon(), QIcon::fromTheme("application-x-desktop"));
            m_entry->setNormalIcon(icon);
            m_entry->setText(entry->name());
            m_entry->setVisible(true);
            return;
        }
    }

    m_entry->setVisible(false);
}

}
}
