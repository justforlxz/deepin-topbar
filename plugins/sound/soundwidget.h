#ifndef SoundWIDGET_H
#define SoundWIDGET_H

#include <QLabel>

class SoundWidget : public QLabel
{
    Q_OBJECT
public:
    explicit SoundWidget(QWidget *parent = 0);
};

#endif // SoundWIDGET_H
