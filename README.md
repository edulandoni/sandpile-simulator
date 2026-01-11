
# Sandpile Simulator (C)

A simple sandpile simulation written in C to explore self-organized criticality and avalanche dynamics.

This project implements a discrete sandpile model and visualizes avalanche propagation step by step in the terminal. It also exports avalanche data to CSV for basic statistical analysis.

---

## Features

- Discrete sandpile model (BTW-style)
- Step-by-step avalanche relaxation
- Terminal-based visualization using ANSI escape codes
- Color-coded cell heights and active toppling cell
- Avalanche size measurement
- Data export to CSV for external analysis
- Basic statistical analysis using Python

---

## How It Works

At each iteration, a grain of sand is added to a random cell.

If any cell reaches a critical height (≥ 4), it topples and redistributes sand to its neighbors. This process continues until the system becomes stable again, forming an avalanche.

An avalanche is characterized by:

- Size: total number of toppling events

In the current version, the relaxation is sequential (one topple per step), so avalanche size and duration are equivalent.

---

## Data Collection and Analysis

The simulation exports avalanche data to a CSV file (avalanches.csv) with one row per avalanche.

Example format:

    iteration,size,duration
    1,0,0
    2,3,3
    3,12,12

Using this data, the avalanche size distribution can be analyzed externally.

A log–log plot of avalanche size frequency shows a heavy-tailed behavior, consistent with self-organized criticality: many small avalanches and a few large ones.

---

## Build and Run

### Requirements

- C compiler (GCC or compatible)
- POSIX environment (Linux, macOS)

### Build

    make

### Run

    ./build/app

The program runs continuously and updates the visualization in real time while exporting data to avalanches.csv.

---

## Notes

- The current implementation uses sequential relaxation.
- As a result, avalanche duration is equivalent to avalanche size in this version.
- Wave-based (parallel) relaxation is planned for a future version to properly measure avalanche duration.

---

## Future Work

- Wave-based relaxation to distinguish avalanche size and duration
- Larger simulations for improved statistics
- Additional analysis of scaling behavior
- Optional graphical or web-based visualization

---

## Inspiration

This project is inspired by classic sandpile models used to study self-organized criticality and power-law behavior in complex systems.
