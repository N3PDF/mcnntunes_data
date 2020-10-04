# Datasets for MCNNTUNES

This repository contains the datasets of Monte Carlo runs used for testing [MCNNTUNES](https://github.com/N3PDF/mcnntunes).

Besides the actual dataset, each folder contains the files used to generate the MC runs,
namely the C++ code that executes the generator, the template configuration file for the generator,
the file with the tunable parameters with their variation ranges and some useful scripts.
The runs are already subdivided in different subsets e.g. training and validation set, with self-explanatory names.
The runs are stored twice: once in the format for MCNNTUNES and once for Professor (with suffix `_prof`).

These datasets were used for the Results section of the MCNNTUNES [paper](https://arxiv.org/abs/20xx.xxxxxx).
More details about these datasets can be found there.
The datasets with the `_large` suffix are extended version of the ones without suffix and are the ones used in the paper (unless specified).
