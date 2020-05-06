#include "contest.h"
#include <random>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <thread>

using ThorsAnvil::Contest::Timer;
using ThorsAnvil::Contest::ThreadPool;

class NN
{
        std::vector<std::vector<int>>   weights;
        std::vector<int>                best;
        int count;
        int correct;
        int countDown;
        bool noChange;
    public:
        NN()
            : weights(150, std::vector<int>(51))
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
        NN(std::default_random_engine& generator)
            : weights(150, std::vector<int>(51))
            , best(10)
            , count(0)
            , correct(0)
            , countDown(99)
            , noChange(false)
        {
            std::discrete_distribution<int> distribution { 1, 1};

            for(int loop = 0; loop < 150; ++loop) {
                for(int w = 0; w < 51; ++w) {
                    weights[loop][w] = distribution(generator) ? -1 : 1;
                }
            }
            for(int loop = 0; loop < 10; ++loop) {
                best[loop] = 0;
            }
        }
        void age()
        {
            noChange = true;
            if (countDown > 0) {
                --countDown;
            }
        }
        void overwriteWith(NN const& parent, std::default_random_engine& generator, int mods)
        {
            count = 0;
            correct = 0;
            for(int loop = 0; loop < 10; ++loop) {
                best[loop] = 0;
            }
            countDown = 99;
            noChange = false;

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

        NN(NN const&)               = default;
        NN(NN&&)                    = default;
        NN& operator=(NN const&)    = default;
        NN& operator=(NN&&)         = default;

        void checkNet(std::vector<int> const& input, int expected)
        {
            if (noChange) {
                return;
            }

            std::vector<int>                layer1(150);
            std::vector<int>                layer1S(150);
            std::vector<int>                layer2(10);

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
            int actual = maxElement - std::begin(layer2);

            ++count;
            if (actual == expected) {
                ++best[actual];
                ++correct;
            }
        }
        void validate(int score)
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
        int getScore() const
        {
            return correct * 100 + countDown;;
        }
        std::string dispBest() const
        {
            std::stringstream str;
            for(auto val: best) {
                str << std::setw(8) << val;
            }
            str << "  " << std::setprecision(5) << std::setw(6) << std::left << std::setfill('0') << ((correct * 100.0) / count);
            return str.str();
        }
        void print(std::ostream& str) const
        {
            for(int loop = 0; loop < 150; ++loop) {
                for(int w = 0; w < 51; ++w) {
                    str << std::setw(2) << weights[loop][w] << " ";
                }
                str << "\n";
            }
        }
        void load(std::istream& str)
        {
            for(int loop = 0; loop < 150; ++loop) {
                for(int w = 0; w < 51; ++w) {
                    str >> weights[loop][w];
                }
            }
        }
        friend std::ostream& operator<<(std::ostream& str, NN const& data)
        {
            data.print(str);
            return str;
        }
        friend std::istream& operator>>(std::istream& str, NN& data)
        {
            data.load(str);
            return str;
        }
};

struct Input
{
    std::vector<int>    input;
    int                 result;

    Input(std::istream& str)
        : input(51)
    {
        for (auto& val: input) {
            str >> val;
        }
        str >> result;
    }
};

int main()
{
    std::default_random_engine generator(time(nullptr));
    Timer       timer;

    std::ifstream           trainingData("mnist10_train.txt");
    std::vector<Input>      inputs;
    for(int loop = 0; loop < 60'000; ++loop) {
        inputs.emplace_back(trainingData);
    }

    std::vector<NN>         nets;
    {
        std::ifstream           netFile("nets");
        NN                      load;
        while(netFile >> load) {
            nets.emplace_back(std::move(load));
            load  = NN{};
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

            std::sort(std::begin(nets), std::end(nets), [](NN const& lhs, NN const& rhs){return lhs.getScore() > rhs.getScore();});

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

