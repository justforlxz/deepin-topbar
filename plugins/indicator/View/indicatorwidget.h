#ifndef INDICATORWIDGET_H
#define INDICATORWIDGET_H

#include <QWidget>
#include <DBus/dbusdock.h>
#include <DBus/dbusdockentry.h>
#include <dpushbutton.h>

DWIDGET_USE_NAMESPACE

class IndicatorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IndicatorWidget(QWidget *parent = nullptr);
    ~IndicatorWidget();
    void initUI();

public slots:
    void closeWindow();

private slots:
    void getAllEntry();
    void addEntry(const QDBusObjectPath &entryPath, const int index);
    void removeEntry(const QString &entryID);
    void refreshActiveWindow();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    DBusDock *m_dockInter;
    QList<DBusDockEntry *> m_entryList;
    DPushButton *m_entry;
    DBusDockEntry *m_activeWindow;
    bool m_menuIsActive;
};

#endif // INDICATORWIDGET_H
