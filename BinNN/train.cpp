#include "contest.h"
#include "NeuralNet.h"
#include "TestData.h"

#include <random>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <thread>
#include <iterator>
#include <stdexcept>

using ThorsAnvil::Contest::Timer;
using ThorsAnvil::Contest::ThreadPool;


using ThorsAnvil::Contest::AIHandWritting::NeuralNet;
using ThorsAnvil::Contest::AIHandWritting::NeuralNetStats;
using ThorsAnvil::Contest::AIHandWritting::TestData;

void neuralNetsRun(ThreadPool& threadPool, std::vector<NeuralNetStats>& netStats, std::vector<TestData> const& inputs);
void nerualNetEvolve(std::vector<NeuralNetStats>& netStats, std::default_random_engine& generator);
void nerualNetsInfoDump(std::ostream& str, std::vector<NeuralNetStats> const& netStats);

int main(int argc, char* argv[])
{
    bool    validate    = false;
    int     uptrainMax  = 100;
    int     trainMax    = 100;

    std::vector<std::string>    args(argv + 1, argv + argc);
    for(int loop = 0; loop < args.size(); ++loop) {
        if (args[loop] == "--validate") {
            validate = true;
        }
        else if (args[loop].substr(0, 13) == "--uptrainMax=") {
            uptrainMax  = std::stoi(args[loop].substr(13));
        }
        else if (args[loop].substr(0, 11) == "--trainMax=") {
            trainMax    = std::stoi(args[loop].substr(11));
        }
        else {
            throw std::runtime_error("Bad Argument");
        }
    }
    if (validate) {
        uptrainMax  = 1;
        trainMax    = 1;
    }


    std::default_random_engine generator(time(nullptr));
    Timer       timer;

    std::ifstream           trainingData("mnist10_train.txt");
    std::vector<TestData>   inputs(std::istream_iterator<TestData>{trainingData}, std::istream_iterator<TestData>{});

    std::ifstream           netFile("nets");
    std::vector<NeuralNet>  nets(std::istream_iterator<NeuralNet>{netFile}, std::istream_iterator<NeuralNet>{});
    for(int loop = nets.size(); loop < 100; ++loop) {
        nets.emplace_back(generator);
    }
    std::vector<NeuralNetStats> netStats(std::begin(nets), std::end(nets));

    {
        for(auto const& input: inputs) {
            netStats[0].checkNet(input.input, input.result);
        }
        netStats[0].age();
        std::ofstream best("best", std::ios::app);
        best << netStats[0];
    }

    ThreadPool     threadPool(4);

    for(int uptrain = 0; uptrain < uptrainMax; ++uptrain) {
        for(int train = 0; train < trainMax; ++train) {
            Timer       time;

            neuralNetsRun(threadPool, netStats, inputs);

            std::sort(std::begin(netStats), std::end(netStats), [](NeuralNetStats const& lhs, NeuralNetStats const& rhs){return lhs.getScore() > rhs.getScore();});

            nerualNetsInfoDump(std::cout, netStats);
            if (validate) {
                std::ofstream   netFile("result");
                nerualNetsInfoDump(netFile, netStats);
            }

            nerualNetEvolve(netStats, generator);

            for(auto& net: netStats) {
                net.validate(inputs.size());
            }
        }
        if (!validate) {
            std::ofstream best("best", std::ios::app);
            best << netStats[0];

            std::ofstream   netFile("nets");
            for(auto const& net: netStats) {
                netFile << net.getNetwork();
            }
        }
    }
}

void neuralNetsRun(ThreadPool& threadPool, std::vector<NeuralNetStats>& netStats, std::vector<TestData> const& inputs)
{
    for(auto& net: netStats) {
        threadPool.addJob([&net, &inputs](){
            for(auto const& input: inputs) {
                net.checkNet(input.input, input.result);
            }
        });
    }
    threadPool.waitForJobsToDrain();
}

void nerualNetEvolve(std::vector<NeuralNetStats>& netStats, std::default_random_engine& generator)
{
    std::uniform_int_distribution  rand(0, 40);
    int parent = 0;
    for(int loop = 0; loop < netStats.size(); ++loop) {
        if (loop > rand(generator)) {

            netStats[loop].overwriteWith(netStats[parent % (netStats.size() / 2)].getNetwork(), generator, parent / (netStats.size() / 2) + 1);
            ++parent;
        }
        else {
            netStats[loop].age();
        }
    }
}

void nerualNetsInfoDump(std::ostream& str, std::vector<NeuralNetStats> const& netStats)
{
    str << "Best: " << netStats[0];
    str << "2nd:  " << netStats[1];
    str << "3rd:  " << netStats[2];
    str << "4th:  " << netStats[3];
    str << "5th:  " << netStats[4];
    str << "25%:  " << netStats[25];
    str << "25%:  " << netStats[25];
    str << "50%:  " << netStats[50];
    str << "75%:  " << netStats[75];
    str << "99%:  " << netStats[99];
}

