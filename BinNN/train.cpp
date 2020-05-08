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

using ThorsAnvil::Contest::Timer;
using ThorsAnvil::Contest::ThreadPool;


using ThorsAnvil::Contest::AIHandWritting::NeuralNet;
using ThorsAnvil::Contest::AIHandWritting::NeuralNetStats;
using ThorsAnvil::Contest::AIHandWritting::TestData;

void neuralNetsRun(ThreadPool& threadPool, std::vector<NeuralNetStats>& netStats, std::vector<TestData> const& inputs);
void nerualNetEvolve(std::vector<NeuralNetStats>& netStats, std::default_random_engine& generator);
void nerualNetsInfoDump(std::vector<NeuralNetStats> const& netStats);

int main()
{
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
        best << netStats[0].getScore() << netStats[0].dispBest() << "\n";
    }

    ThreadPool     threadPool(4);

    for(int uptrain = 0; uptrain < 1; ++uptrain) {
        for(int train = 0; train < 2; ++train) {
            Timer       time;

            neuralNetsRun(threadPool, netStats, inputs);

            std::sort(std::begin(netStats), std::end(netStats), [](NeuralNetStats const& lhs, NeuralNetStats const& rhs){return lhs.getScore() > rhs.getScore();});

            nerualNetsInfoDump(netStats);

            nerualNetEvolve(netStats, generator);

            for(auto& net: netStats) {
                net.validate(inputs.size());
            }
        }
        std::ofstream best("best", std::ios::app);
        best << netStats[0].getScore() << netStats[0].dispBest() << "\n";

        std::ofstream   netFile("nets");
        for(auto const& net: netStats) {
            netFile << net.getNetwork();
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

void nerualNetsInfoDump(std::vector<NeuralNetStats> const& netStats)
{
    std::cout << "Best: " << netStats[0].getScore() << netStats[0].dispBest() << "\n";
    std::cout << "2nd:  " << netStats[1].getScore() << netStats[1].dispBest() << "\n";
    std::cout << "3rd:  " << netStats[2].getScore() << netStats[2].dispBest() << "\n";
    std::cout << "4th:  " << netStats[3].getScore() << netStats[3].dispBest() << "\n";
    std::cout << "5th:  " << netStats[4].getScore() << netStats[4].dispBest() << "\n";
    std::cout << "25%:  " << netStats[25].getScore() << netStats[25].dispBest() << "\n";
    std::cout << "25%:  " << netStats[25].getScore() << netStats[25].dispBest() << "\n";
    std::cout << "50%:  " << netStats[50].getScore() << netStats[50].dispBest() << "\n";
    std::cout << "75%:  " << netStats[75].getScore() << netStats[75].dispBest() << "\n";
    std::cout << "99%:  " << netStats[99].getScore() << netStats[99].dispBest() << "\n";
}

