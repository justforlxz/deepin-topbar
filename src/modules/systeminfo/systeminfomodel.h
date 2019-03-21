#ifndef SYSTEMINFOMODEL_H
#define SYSTEMINFOMODEL_H

#include <QObject>

namespace dtb {
namespace systeminfo {
class SystemInfoModel : public QObject
{
    Q_OBJECT
public:
    explicit SystemInfoModel(QObject *parent = 0);

    int cputime() const { return m_cputime;}
    void setCputime(int cputime);

signals:
    void networkSpeedChanged(const quint64 tx, const quint64 rx);
    void cputimeChanged(int cputime);
    void memChanged(int mem, int swap);
private:
    int m_cputime;
};
}
}


#endif // SYSTEMINFOMODEL_H
