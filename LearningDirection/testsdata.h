#ifndef TESTSDATA_H
#define TESTSDATA_H

#include <QDataStream>

class TestsData
{
public:
    TestsData();
    ~TestsData();
    friend QDataStream& operator<<(QDataStream& out, const TestsData& teData);
    friend QDataStream& operator>>(QDataStream& in, TestsData& teData);
};

#endif // TESTSDATA_H
