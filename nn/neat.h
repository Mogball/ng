#pragma once

#include <vector>
#include <random>

namespace nn {

    struct Genome {
        struct Link {
            std::size_t innovation;
            std::size_t input;
            std::size_t output;
            float weight;
        };

        std::vector<Link> links;
        std::vector<std::size_t> inputs;
        std::vector<std::size_t> outputs;
        std::size_t nodes;
    };

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
        Neat(Genome genome);

        std::vector<float> push(const std::vector<float> &args);

        inline std::vector<float> operator()(const std::vector<float> &args) {
            return push(args);
        }
    };

    class Evolve {
    public:
        struct Parameters {
            // Per genome, expected number of perturbations to a link weight
            float avg_weight_mutations{};
            // Per genome, expected number of new links
            float avg_link_mutations{};
            // Per genome, expected number of links split in two
            float avg_node_mutations{};
        };

    private:
        Parameters m_parameters{};
        std::size_t m_innovation{};
        std::default_random_engine m_rng{};

    public:
        /**
         * User defines an initial topology and passes it
         * to assign innovation numbers.
         *
         * @param init
         */
        explicit Evolve(Genome &init);

        Genome mutate(const Genome &g);
        Genome crossover(const Genome &g0, const Genome &g1);
    };

}
