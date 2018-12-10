#ifndef SOUNDITEM_H
#define SOUNDITEM_H

#include "frame/item/contentmodule.h"
#include "dbus/dbusinterface.h"
#include "dbus/dbusmediaplayer2.h"
#include <QMenu>
#include <QWidget>
#include <QScrollArea>
#include <dtickeffect.h>

DWIDGET_USE_NAMESPACE

using DBusMPRIS = DBusMediaPlayer2;

class DBusSink;
class QLabel;

namespace dtb {

namespace widgets {
class DWidgetAction;
}

namespace sound {
class SoundApplet;
class SinkInputWidget;
class MediaControl;
class SoundItem : public ContentModule
{
    Q_OBJECT

public:
    explicit SoundItem(QWidget *parent = 0);

    QMenu *menu() const;
    bool isSoundItem(const QPoint &cursor) const;

signals:
    void requestHidePopupWindow();

protected:
    void wheelEvent(QWheelEvent *e) Q_DECL_OVERRIDE;

private slots:
    void refershIcon();
    void sinkChanged(DBusSink *sink);
    void handleAction(const int &action);
    void clearAllInput();
    void addNewInput(SinkInputWidget *w);

    void initMpris();
    void removeMPRISPath(const QString &path);
    void loadMPRISPath(const QString &path);
    void onNameOwnerChanged(const QString &name, const QString &oldOwner, const QString &newOwner);
private:
    QScrollArea *m_tickScrollArea;
    QLabel *m_mprisTitle;
    DTickEffect *m_tickEffect;
    QLabel *m_fontLabel;
    DBusMediaPlayer2 *m_mprisInter;
    DBusInterface *m_dbusInter;
    QPointer<MediaControl> m_mediaControl;
    QString m_lastPath;
    QStringList m_mprisPaths;
    widgets::DWidgetAction *m_appletAction;
    SoundApplet *m_applet;
    DBusSink *m_sinkInter;
    QMenu *m_menu;
    QAction *m_separator;
    QMap<widgets::DWidgetAction*, SinkInputWidget*> m_inputMap;
};
}
}

#endif // SOUNDITEM_H
