#ifndef THORSANVIL_CONTEST_AI_HAND_WRITTING_TEST_DATA_H
#define THORSANVIL_CONTEST_AI_HAND_WRITTING_TEST_DATA_H

#include <istream>

namespace ThorsAnvil::Contest::AIHandWritting
{

struct TestData
{
    std::vector<int>    input;
    int                 result;

    TestData(std::istream& str)
        : input(51)
    {
        for (auto& val: input) {
            str >> val;
        }
        str >> result;
    }
};

}

#endif
