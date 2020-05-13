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
        template<typename F>
        NeuralNetGeneric(std::vector<int>&& pLayerSize, F&& generator)
            : NeuralNetGeneric( std::move(pLayerSize),
                                std::vector<std::function<int(int)>>(pLayerSize.size(), [](int x){
                                    return x;}),
                                std::move(generator)
                              )
        {}

        template<typename F>
        NeuralNetGeneric(std::vector<int>&& pLayerSize, std::vector<std::function<int(int)>>&& sumarise, F&& generator)
            : layerSize(std::move(pLayerSize))
            , sumarise(std::move(sumarise))
        {
            auto loop   = std::begin(layerSize);
            auto end    = std::end(layerSize);

            int currentLayerSize    = *loop;
            int inputLayer          = 0;
            for (++loop;loop != end; ++loop) {

                // Calculate the number of weights we need
                int nextLayerSize = *loop;
                weights.emplace_back(nextLayerSize, std::vector<int>(currentLayerSize));

                for(int layer1Loop = 0; layer1Loop < weights[inputLayer].size(); ++layer1Loop) {
                    for(int inLoop = 0; inLoop < weights[inputLayer][layer1Loop].size(); ++inLoop) {
                        weights.back()[layer1Loop][inLoop] = generator(inputLayer, layer1Loop, inLoop);
                    }
                }
                // Set up for next loop.
                currentLayerSize = nextLayerSize;
                ++inputLayer;
            }
        }
        virtual std::vector<int> runNetwork(std::vector<int> const& inputParam)
        {
            std::vector<int>    input(inputParam);

            auto loop   = std::begin(layerSize);
            auto end    = std::end(layerSize);

            int currentLayerSize    = *loop;
            int inputLayer          = 0;
            for (++loop;loop != end; ++loop) {
                int nextLayerSize = *loop;

                std::vector<int>    output(nextLayerSize);
                runNetworkLayer(input, output, inputLayer);

                // Get ready for next layer
                currentLayerSize = nextLayerSize;
                ++inputLayer;
                input = std::move(output);
            }
            return input;
        }
    private:
        void runNetworkLayer(std::vector<int> const& input, std::vector<int>& output, int layer)
        {
            for(int layer1Loop = 0; layer1Loop < weights[layer].size(); ++layer1Loop) {
                output[layer1Loop]  = 0;
                for(int inLoop = 0; inLoop < weights[layer][layer1Loop].size(); ++inLoop) {
                    output[layer1Loop] += weights[layer][layer1Loop][inLoop] * input[inLoop];
                }
            }

            for(int layer1Loop = 0; layer1Loop < weights[layer].size(); ++layer1Loop) {
                output[layer1Loop]  = sumarise[layer](output[layer1Loop]);
            }
        }
        void print(std::ostream& str) const;
        friend std::ostream& operator<<(std::ostream& str, NeuralNetGeneric const& data) {data.print(str);return str;}
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

        void load(std::istream& str);

        friend std::istream& operator>>(std::istream& str, NeuralNet& data)       {data.load(str);return str;}
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
