#ifndef SOUNDITEM_H
#define SOUNDITEM_H

#include "item/contentmodule.h"

#include <QMenu>
#include <QWidget>

class DBusSink;

namespace dtb {

namespace widgets {
class FontLabel;
class DWidgetAction;
}

namespace sound {
class SoundApplet;
class SinkInputWidget;
class SoundItem : public ContentModule
{
    Q_OBJECT

public:
    explicit SoundItem(QWidget *parent = 0);

    QMenu *menu() const;

protected:
    void wheelEvent(QWheelEvent *e) Q_DECL_OVERRIDE;

private slots:
    void refershIcon();
    void sinkChanged(DBusSink *sink);
    void handleAction(const int &action);
    void clearAllInput();
    void addNewInput(SinkInputWidget *w);

private:
    widgets::FontLabel *m_fontLabel;
    SoundApplet *m_applet;
    DBusSink *m_sinkInter;
    QMenu *m_menu;
    QAction *m_separator;
    QMap<widgets::DWidgetAction*, SinkInputWidget*> m_inputMap;
};
}
}

#endif // SOUNDITEM_H
