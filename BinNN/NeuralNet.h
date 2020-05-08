#ifndef THORSANVIL_CONTEST_AI_HAND_WRITTING_NEURAL_NET_H
#define THORSANVIL_CONTEST_AI_HAND_WRITTING_NEURAL_NET_H

#include <random>
#include <sstream>
#include <iomanip>

namespace ThorsAnvil::Contest::AIHandWritting
{

class NeuralNet
{
        std::vector<std::vector<int>>   weights;
        std::vector<int>                best;
        int count;
        int correct;
        int countDown;
        bool noChange;
    public:
        NeuralNet();
        NeuralNet(std::default_random_engine& generator);

        NeuralNet(NeuralNet const&)               = default;
        NeuralNet(NeuralNet&&)                    = default;
        NeuralNet& operator=(NeuralNet const&)    = default;
        NeuralNet& operator=(NeuralNet&&)         = default;

        void age();
        void overwriteWith(NeuralNet const& parent, std::default_random_engine& generator, int mods);
        void checkNet(std::vector<int> const& input, int expected);
        void validate(int score);

        int getScore() const {return correct * 100 + countDown;}

        std::string dispBest() const;
        void print(std::ostream& str) const;
        void load(std::istream& str);

        friend std::ostream& operator<<(std::ostream& str, NeuralNet const& data) {data.print(str);return str;}
        friend std::istream& operator>>(std::istream& str, NeuralNet& data)       {data.load(str);return str;}
};

}

#endif
