# Pseudo-Random Number Generators (PRNG) & Statistical Testing

This directory contains implementations of classic pseudo-random number generation algorithms and tools to analyze their statistical distribution and properties.

## 🛠 Contents

### 1. Additive Fibonacci-type Generator (`additive_generator_test.cpp`)

This program implements an additive generator using 64-bit arithmetic to handle 32-bit overflows (simulating modulo $2^{32}$ operations).

* **Mechanism:** Generates a sequence where $x_{n+2} = (x_{n+1} + x_n) \pmod{2^{32}}$ using bitwise masking (`& 0xffffffffUL`).
* **Statistical Analysis:** Performs a "Runs Test" to calculate the probability of strictly increasing ($x_0 < x_1 < x_2$) and strictly decreasing ($x_0 > x_1 > x_2$) sequences.
* **Key Concept:** Demonstrates how simple recurrence relations affect the local monotonicity of a random stream.

### 2. Linear Feedback Shift Register - LFSR (`lfsr_bit_stream.cpp`)

A classic implementation of an LFSR, which is widely used in hardware noise generators and stream ciphers.

* **Mechanism:** Uses a "feedback tap" (defined by variable `a`) and a parity check (`popcount & 1`) to shift bits into a state register.
* **Byte Distribution Analysis:** Groups every 8 generated bits into a byte (0-255) and builds a frequency histogram (`freq[256]`) over 1,000,000 iterations.
* **Key Concept:** Evaluates the quality of the generator by checking how uniformly the output bytes are distributed across the 0-255 range.

## 🔬 Scientific Context

* **Bitwise Efficiency:** Both generators utilize low-level bitwise operations (`>>`, `<<`, `&`, `|`), showcasing high-performance C++ techniques for RNG.
* **Uniformity:** The LFSR code provides a practical way to visualize whether a generator is "fair" or biased toward certain bit patterns.
* **Overflow Handling:** Demonstrates the importance of using `uint64_t` for intermediate sums to prevent undefined behavior during calculation before applying a bit-mask.

## How to Run

Compile using any C++ compiler (e.g., g++):

```bash
g++ additive_generator_test.cpp -o additive_test
./additive_test

g++ lfsr_bit_stream.cpp -o lfsr_test
./lfsr_test
```
