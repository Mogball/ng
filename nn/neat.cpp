#include "neat.h"
#include <set>
#include <map>
#include <cmath>

static inline float activate(float x) {
    return 1 / (1 + exp(-x));
}

namespace nn {

    Neat::Neat(Genome genome) :
        m_nodes{ genome.nodes },
        m_inputs{ std::move(genome.inputs) },
        m_outputs{ std::move(genome.outputs) }
    {
        for (auto &link : genome.links) {
            m_nodes[link.output].incoming.push_back(&m_nodes[link.input]);
            m_nodes[link.output].weights.push_back(link.weight);
        }
    }

    std::vector<float> Neat::push(const std::vector<float> &args) {
        // Reset all accumulators
        for (auto &node : m_nodes) {
            node.accumulator = 0;
        }

        // Set the input node accumulator to arguments
        for (auto i = 0; i < std::size(args); ++i) {
            m_nodes[m_inputs[i]].accumulator = args[i];
        }

        // For each node, multiply-add incoming signals into accumulator
        for (auto &node : m_nodes) {
            for (auto i = 0; i < std::size(node.incoming); ++i) {
                node.accumulator += node.incoming[i]->output * node.weights[i];
            }
        }

        // Set node output to activation function of accumulator
        for (auto &node : m_nodes) {
            node.output = activate(node.accumulator);
        }

        // Read output nodes
        std::vector<float> ret( std::size(m_outputs) );
        for (auto i = 0; i < std::size(m_outputs); ++i) {
            ret[i] = m_nodes[m_outputs[i]].output;
        }

        return ret;
    }

    Evolve::Evolve(Genome &init) {
        for (auto &link : init.links) {
            link.innovation = m_innovation++;
        }
    }

    Genome Evolve::mutate(const Genome &g) {
        return g;
    }

    Genome Evolve::crossover(const Genome &g0, const Genome &g1) {
        std::set<std::size_t> nodes{};
        Genome ret = {
            .inputs = g0.inputs,
            .outputs = g0.outputs,
            .links = g0.links,
        };
        for (auto &link : ret.links) {
            nodes.insert(link.input);
            nodes.insert(link.output);
        }
        for (auto &link : g1.links) {
        }


        return g0;
    }
}

int main() {
}
