# mto-ml

[mto-ml] is a work in progress c++ machine learning library entirely written by hand.

*Note: It is a snapshot extracted from a much larger monorepo with its own base code and CI.*

Although originally designed for educational purposes, its goal is:
- to serve as a tool that can be used in practice with reasonable performance
- to be capable of modeling state-of-the-art models

## Features:

- symbolic expressions recorded in a DAG (`expr/`) from c++ expressions
- forward eval + backward autodiff on that DAG, interpreted or JIT-compiled to C (`expr/compiler/`)
- model training loop with gradient descent and lr schedulers (`model/`)
- built-in helpers for losses: MSE, binary NLL, multi-class NLL
- MultiLayerPerceptron on top of all that (`mlp/`)
- makemore-style examples: bigram name generator works, MLP version is a WIP (`projects/makemore/`)


## License

GPL v3.

