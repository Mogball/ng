#pragma once

#include <vector>

namespace nn {

    class Neat {
        struct Node {
            std::vector<Node *> incoming;
            std::vector<float> weights;
            float accumulator;
            float output;
        };

        std::vector<Node> m_nodes;
        std::vector<std::size_t> m_inputs;
        std::vector<std::size_t> m_outputs;

    public:
        std::vector<float> operator()(const std::vector<float> &args);
    };

}
