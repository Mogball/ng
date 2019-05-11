#include "neat.h"

namespace nn {

    std::vector<float> Neat::operator()(const std::vector<float> &args) {
        // Set input node outputs to arguments
        for (auto i = 0; i < std::size(args); ++i) {
            m_nodes[m_inputs[i]].output = args[i];
        }

        // For each node, multiply-add incoming outputs into accumulator
        for (auto &node : m_nodes) {
            node.accumulator = 0;
            for (auto i = 0; i < std::size(node.incoming); ++i) {
                node.accumulator += node.incoming[i]->output * node.weights[i];
            }
        }

        // Set node output to accumulator
        for (auto &node : m_nodes) {
            node.output = node.accumulator;
        }

        // Read output nodes
        std::vector<float> ret{ std::size(m_outputs) };
        for (auto i = 0; i < std::size(m_outputs); ++i) {
            ret[i] = m_nodes[m_outputs[i]].output;
        }

        return ret;
    }

}
