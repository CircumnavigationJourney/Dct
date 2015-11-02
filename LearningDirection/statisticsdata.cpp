#include "statisticsdata.h"

StatisticsData::StatisticsData()
{

}

StatisticsData::~StatisticsData()
{

}

QDataStream& operator<<(QDataStream& out, const StatisticsData& statData){return out;}
QDataStream& operator>>(QDataStream& in, StatisticsData& statData)       {return in;}
