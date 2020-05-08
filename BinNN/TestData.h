#ifndef THORSANVIL_CONTEST_AI_HAND_WRITTING_TEST_DATA_H
#define THORSANVIL_CONTEST_AI_HAND_WRITTING_TEST_DATA_H

#include <istream>

namespace ThorsAnvil::Contest::AIHandWritting
{

struct TestData
{
    std::vector<int>    input;
    int                 result;

    TestData()
        : input(51)
    {}

    friend std::istream& operator>>(std::istream& str, TestData& data)
    {
        for (auto& val: data.input) {
            str >> val;
        }
        str >> data.result;
        return str;
    }
};

}

#endif
