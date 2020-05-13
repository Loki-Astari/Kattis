#include "NeuralNet.h"
#include <iostream>
#include <thread>

using namespace ThorsAnvil::Contest::AIHandWritting;

// NeuralNetGeneric

void NeuralNetGeneric::print(std::ostream& str) const
{
    for(int layer = 0; layer < weights.size(); ++layer) {
        for(int loop = 0; loop < weights[layer].size(); ++loop) {
            for(int w = 0; w < weights[layer][loop].size(); ++w) {
                str << std::setw(2) << weights[layer][loop][w] << " ";
            }
            str << "\n";
        }
    }
}



// NeuralNet

NeuralNet::NeuralNet()
    : NeuralNetGeneric({51, 150, 10},
        {
            [](int x){return x > 0 ? 1 : -1;},
            [](int x){return x;}
        },
        [](int layer, int node, int inputNode) {
            switch(layer) {
                case 0: return 1;
                case 1: return (inputNode / 15 == node) ? 1 : 0;
            }
            return 0;
        }
    )
{}

NeuralNet::NeuralNet(std::default_random_engine& generator)
    : NeuralNetGeneric({51, 150, 10},
        {
            [](int x){return x > 0 ? 1 : -1;},
            [](int x){return x;}
        },
        [distribution = std::discrete_distribution<int>{ 1, 1}, &generator](int layer, int node, int inputNode) mutable {
            switch(layer) {
                case 0: return distribution(generator) ? -1 : 1;
                case 1: return (inputNode / 15 == node) ? 1 : 0;
            }
            return 0;
        }
    )
{}

void NeuralNet::overwriteWith(NeuralNet const& parent, std::default_random_engine& generator, int mods)
{
    weights = parent.weights;

    std::uniform_int_distribution  w1(0, 149);
    std::uniform_int_distribution  w2(0, 50);

    int choice = 0;

    for(int loop = 0; loop < mods; ++loop) {
        int i1 = w1(generator);
        int i2 = w2(generator);
        int r  = weights[0][choice + i1][i2] < 0 ? 1 : -1;


        weights[0][choice + i1][i2] = r;
    }
}

std::vector<int> NeuralNet::runNetwork(std::vector<int> const& input)
{
    std::vector<int> layer2 = NeuralNetGeneric::runNetwork(input);
    auto maxElement    = std::max_element(std::begin(layer2), std::end(layer2));

    std::vector<int>                layer3(1);
    layer3[0] = maxElement - std::begin(layer2);

    return layer3;
}

void NeuralNet::load(std::istream& str)
{
    for(int loop = 0; loop < 150; ++loop) {
        for(int w = 0; w < 51; ++w) {
            str >> weights[0][loop][w];
        }
    }
}

// Stats

NeuralNetStats::NeuralNetStats(NeuralNet& network)
    : network(&network)
    , best(10)
    , count(0)
    , correct(0)
    , countDown(99)
    , noChange(false)
{
    for(int loop = 0; loop < 10; ++loop) {
        best[loop] = 0;
    }
}

void NeuralNetStats::age()
{
    noChange = true;
    if (countDown > 0) {
        --countDown;
    }
}

void NeuralNetStats::overwriteWith(NeuralNet const& parent, std::default_random_engine& generator, int mods)
{
    count = 0;
    correct = 0;
    for(int loop = 0; loop < 10; ++loop) {
        best[loop] = 0;
    }
    countDown = 99;
    noChange = false;

    network->overwriteWith(parent, generator, mods);
}

void NeuralNetStats::checkNet(std::vector<int> const& input, int expected)
{
    if (noChange) {
        return;
    }

    std::vector<int> output = network->runNetwork(input);

    ++count;
    if (output[0] == expected) {
        ++best[expected];
        ++correct;
    }
}

void NeuralNetStats::validate(int score)
{
    if (count > score) {
        std::cerr << "Error:- Reset\n";

        count = 0;
        correct = 0;
        for(int loop = 0; loop < 10; ++loop) {
            best[loop] = 0;
        }
        countDown = 99;
        noChange = false;
    }
}

void NeuralNetStats::print(std::ostream& str) const
{
    std::ios_base::fmtflags flags   = str.flags();
    std::streamsize         cPrec   = str.precision();

    str << getScore();
    for(auto val: best) {
        str << std::setw(8) << val;
    }
    str << "  "
        << std::setprecision(5) << std::setw(6) << std::left << std::setfill('0') << ((correct * 100.0) / count)
        << std::setprecision(cPrec) << std::setfill(' ')
        << "\n";
    str.flags(flags);
}

