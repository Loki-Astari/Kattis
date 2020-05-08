#include "contest.h"
#include "NeuralNet.h"
#include "TestData.h"

#include <random>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <thread>

using ThorsAnvil::Contest::Timer;
using ThorsAnvil::Contest::ThreadPool;


using ThorsAnvil::Contest::AIHandWritting::NeuralNet;
using ThorsAnvil::Contest::AIHandWritting::TestData;

int main()
{
    std::default_random_engine generator(time(nullptr));
    Timer       timer;

    std::ifstream           trainingData("mnist10_train.txt");
    std::vector<TestData>   inputs;
    for(int loop = 0; loop < 60'000; ++loop) {
        inputs.emplace_back(trainingData);
    }

    std::vector<NeuralNet>      nets;
    {
        std::ifstream           netFile("nets");
        NeuralNet               load;
        while(netFile >> load) {
            nets.emplace_back(std::move(load));
            load  = NeuralNet{};
        }
    }

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

            for(auto& net: nets) {
                threadPool.addJob([&net, &inputs](){
                    for(auto const& input: inputs) {
                        net.checkNet(input.input, input.result);
                    }
                });
            }
            threadPool.waitForJobsToDrain();

            std::sort(std::begin(nets), std::end(nets), [](NeuralNet const& lhs, NeuralNet const& rhs){return lhs.getScore() > rhs.getScore();});

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

