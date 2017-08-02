#ifndef AccountWIDGET_H
#define AccountWIDGET_H

#include <QLabel>

class FontLabel;

class AccountWidget : public QLabel
{
    Q_OBJECT
public:
    explicit AccountWidget(QWidget *parent = 0);

protected:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    FontLabel *m_AccountIcon;
};

#endif // AccountWIDGET_H
