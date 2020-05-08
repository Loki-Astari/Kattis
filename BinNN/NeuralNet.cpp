#include "NeuralNet.h"
#include <iostream>

using namespace ThorsAnvil::Contest::AIHandWritting;

NeuralNet::NeuralNet()
    : weights(150, std::vector<int>(51))
{}

NeuralNet::NeuralNet(std::default_random_engine& generator)
    : weights(150, std::vector<int>(51))
{
    std::discrete_distribution<int> distribution { 1, 1};

    for(int loop = 0; loop < 150; ++loop) {
        for(int w = 0; w < 51; ++w) {
            weights[loop][w] = distribution(generator) ? -1 : 1;
        }
    }
}

void NeuralNet::overwriteWith(NeuralNet const& parent, std::default_random_engine& generator, int mods)
{
    weights = parent.weights;

    //std::uniform_int_distribution  w1(0, 14);
    std::uniform_int_distribution  w1(0, 149);
    std::uniform_int_distribution  w2(0, 50);

    //auto    min = std::min_element(std::begin(parent.best), std::end(parent.best));
    //auto    choice = (min - std::begin(parent.best)) * 15;
    int choice = 0;

    for(int loop = 0; loop < mods; ++loop) {
        int i1 = w1(generator);
        int i2 = w2(generator);
        int r  = weights[choice + i1][i2] < 0 ? 1 : -1;


        weights[choice + i1][i2] = r;
    }
}

std::vector<int> NeuralNet::runNetwork(std::vector<int> const& input, int expected)
{
    std::vector<int>                layer1(150);
    std::vector<int>                layer1S(150);
    std::vector<int>                layer2(10);
    std::vector<int>                layer3(1);

    // Calculate Layer 1
    for(int layer1Loop = 0; layer1Loop < 150; ++layer1Loop) {
        layer1[layer1Loop]  = 0;
        for(int inLoop = 0; inLoop < 51; ++inLoop) {
            layer1[layer1Loop] += weights[layer1Loop][inLoop] * input[inLoop];
        }
    }
    for(int layer1Loop = 0; layer1Loop < 150; ++layer1Loop) {
        layer1S[layer1Loop] = layer1[layer1Loop] > 0 ? +1 : -1;
    }

    // Calculate Layer 2
    for(int layer2Loop = 0; layer2Loop < 10; ++layer2Loop) {
        layer2[layer2Loop] = 0;
        for(int loop = 0; loop < 15; ++loop) {
            layer2[layer2Loop] += layer1[layer2Loop * 15 + loop];
        }
    }

    auto maxElement    = std::max_element(std::begin(layer2), std::end(layer2));
    layer3[0] = maxElement - std::begin(layer2);

    return layer3;
}

void NeuralNet::print(std::ostream& str) const
{
    for(int loop = 0; loop < 150; ++loop) {
        for(int w = 0; w < 51; ++w) {
            str << std::setw(2) << weights[loop][w] << " ";
        }
        str << "\n";
    }
}

void NeuralNet::load(std::istream& str)
{
    for(int loop = 0; loop < 150; ++loop) {
        for(int w = 0; w < 51; ++w) {
            str >> weights[loop][w];
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

    std::vector<int> output = network->runNetwork(input, expected);

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

std::string NeuralNetStats::dispBest() const
{
    std::stringstream str;
    for(auto val: best) {
        str << std::setw(8) << val;
    }
    str << "  " << std::setprecision(5) << std::setw(6) << std::left << std::setfill('0') << ((correct * 100.0) / count);
    return str.str();
}

