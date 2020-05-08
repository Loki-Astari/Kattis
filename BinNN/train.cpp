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
using ThorsAnvil::Contest::AIHandWritting::TestData;

void neuralNetsRun(ThreadPool& threadPool, std::vector<NeuralNet>& nets, std::vector<TestData> const& inputs);
void nerualNetEvolve(std::vector<NeuralNet>& nets, std::default_random_engine& generator);
void nerualNetsInfoDump(std::vector<NeuralNet> const& nets);

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

    {
        for(auto const& input: inputs) {
            nets[0].checkNet(input.input, input.result);
        }
        nets[0].age();
        std::ofstream best("best", std::ios::app);
        best << nets[0].getScore() << nets[0].dispBest() << "\n";
    }

    ThreadPool     threadPool(4);

    for(int uptrain = 0; uptrain < 1; ++uptrain) {
        for(int train = 0; train < 2; ++train) {
            Timer       time;

            neuralNetsRun(threadPool, nets, inputs);

            std::sort(std::begin(nets), std::end(nets), [](NeuralNet const& lhs, NeuralNet const& rhs){return lhs.getScore() > rhs.getScore();});

            nerualNetsInfoDump(nets);

            nerualNetEvolve(nets, generator);

            for(auto& net: nets) {
                net.validate(inputs.size());
            }
        }
        std::ofstream best("best", std::ios::app);
        best << nets[0].getScore() << nets[0].dispBest() << "\n";

        std::ofstream   netFile("nets");
        for(auto const& net: nets) {
            netFile << net;
        }
    }

}

void neuralNetsRun(ThreadPool& threadPool, std::vector<NeuralNet>& nets, std::vector<TestData> const& inputs)
{
    for(auto& net: nets) {
        threadPool.addJob([&net, &inputs](){
            for(auto const& input: inputs) {
                net.checkNet(input.input, input.result);
            }
        });
    }
    threadPool.waitForJobsToDrain();
}

void nerualNetEvolve(std::vector<NeuralNet>& nets, std::default_random_engine& generator)
{
    std::uniform_int_distribution  rand(0, 40);
    int parent = 0;
    for(int loop = 0; loop < nets.size(); ++loop) {
        if (loop > rand(generator)) {

            nets[loop].overwriteWith(nets[parent % (nets.size() / 2)], generator, parent / (nets.size() / 2) + 1);
            ++parent;
        }
        else {
            nets[loop].age();
        }
    }
}

void nerualNetsInfoDump(std::vector<NeuralNet> const& nets)
{
    std::cout << "Best: " << nets[0].getScore() << nets[0].dispBest() << "\n";
    std::cout << "2nd:  " << nets[1].getScore() << nets[1].dispBest() << "\n";
    std::cout << "3rd:  " << nets[2].getScore() << nets[2].dispBest() << "\n";
    std::cout << "4th:  " << nets[3].getScore() << nets[3].dispBest() << "\n";
    std::cout << "5th:  " << nets[4].getScore() << nets[4].dispBest() << "\n";
    std::cout << "25%:  " << nets[25].getScore() << nets[25].dispBest() << "\n";
    std::cout << "25%:  " << nets[25].getScore() << nets[25].dispBest() << "\n";
    std::cout << "50%:  " << nets[50].getScore() << nets[50].dispBest() << "\n";
    std::cout << "75%:  " << nets[75].getScore() << nets[75].dispBest() << "\n";
    std::cout << "99%:  " << nets[99].getScore() << nets[99].dispBest() << "\n";
}

