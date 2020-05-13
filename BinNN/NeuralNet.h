#ifndef THORSANVIL_CONTEST_AI_HAND_WRITTING_NEURAL_NET_H
#define THORSANVIL_CONTEST_AI_HAND_WRITTING_NEURAL_NET_H

#include <random>
#include <iomanip>
#include <iostream>

namespace ThorsAnvil::Contest::AIHandWritting
{


class NeuralNetGeneric
{
    protected:
        std::vector<int>                            layerSize;
        std::vector<std::function<int(int)>>        sumarise;
        std::vector<std::vector<std::vector<int>>>  weights;
    public:
        NeuralNetGeneric(std::vector<int>&& pLayerSize);
        NeuralNetGeneric(std::vector<int>&& pLayerSize, std::function<int(int, int, int)>&& generator);
        NeuralNetGeneric(std::vector<int>&& pLayerSize, std::vector<std::function<int(int)>>&& sumarise, std::function<int(int, int, int)>&& generator);

        virtual std::vector<int> runNetwork(std::vector<int> const& inputParam);
    private:
        void runNetworkLayer(std::vector<int> const& input, std::vector<int>& output, int layer);

        void print(std::ostream& str) const;
        void load(std::istream& str);

        friend std::ostream& operator<<(std::ostream& str, NeuralNetGeneric const& data) {data.print(str);return str;}
        friend std::istream& operator>>(std::istream& str, NeuralNetGeneric& data)
        {
            NeuralNetGeneric    tmp(std::vector<int>(data.layerSize));
            tmp.load(str);
            if (str) {
                std::swap(data.weights, tmp.weights);
            }
            return str;
        }
};

class NeuralNet: public NeuralNetGeneric
{
    public:
        NeuralNet();
        NeuralNet(std::default_random_engine& generator);

        NeuralNet(NeuralNet const&)               = default;
        NeuralNet(NeuralNet&&)                    = default;
        NeuralNet& operator=(NeuralNet const&)    = default;
        NeuralNet& operator=(NeuralNet&&)         = default;

        void overwriteWith(NeuralNet const& parent, std::default_random_engine& generator, int mods);
        virtual std::vector<int> runNetwork(std::vector<int> const& input) override;
};

class NeuralNetStats
{
        NeuralNet*                      network;
        std::vector<int>                best;
        int count;
        int correct;
        int countDown;
        bool noChange;
    public:
        NeuralNetStats(NeuralNet& network);

        NeuralNet& getNetwork() const {return *network;}

        void age();
        void overwriteWith(NeuralNet const& parent, std::default_random_engine& generator, int mods);
        void checkNet(std::vector<int> const& input, int expected);
        void validate(int score);

        int getScore() const {return correct * 100 + countDown;}

        void print(std::ostream& str) const;

        friend std::ostream& operator<<(std::ostream& str, NeuralNetStats const& data) {data.print(str);return str;}
};

}

#endif
