#include "testsdata.h"

TestsData::TestsData()
{

}

TestsData::~TestsData()
{

}

QDataStream& operator<<(QDataStream& out, const TestsData& teData) {return out;}
QDataStream& operator>>(QDataStream& in, TestsData& teData) {return in;}
