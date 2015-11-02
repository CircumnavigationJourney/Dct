#ifndef STATISTICSDATA_H
#define STATISTICSDATA_H
#include <QDataStream>

class StatisticsData
{
public:
    StatisticsData();
    ~StatisticsData();
    friend QDataStream& operator<<(QDataStream& out, const StatisticsData& statData);
    friend QDataStream& operator>>(QDataStream& in, StatisticsData& statData);
};

#endif // STATISTICSDATA_H
