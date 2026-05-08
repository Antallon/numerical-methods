# Function Approximation & Interpolation Suite

A comprehensive collection of numerical methods for function approximation and optimal grid generation. This suite includes advanced C++ implementations for minimax polynomials and Python-based tension splines for smooth data fitting.

## 🛠 Implemented Methods

### 1. High-Order Interpolation & Minimax (C++)

* **Minimax Approximation (Valle-Poussin Algorithm):** An iterative process for finding the polynomial of best uniform approximation (minimizing the maximum error).
* **Lagrange Interpolation:** Classical polynomial construction for various node distributions.
* **Grid Generation Strategies:**
  * **Uniform Nodes:** Standard equidistant distribution.
  * **Chebyshev Nodes:** Optimized nodes to mitigate **Runge's Phenomenon** in high-degree polynomial interpolation.
  * **Random Nodes:** Stochastic grid generation using `std::mt19937` for robustness testing.
* **Automated Grid Refinement:** An algorithm for local mesh density adjustment to increase approximation accuracy in "difficult" regions.

### 2. Tension Spline Interpolation (Python)

* **Weighted Tension Splines:** A sophisticated cubic spline variant that controls curve "vibrations" and oscillations using tension weight coefficients ($w$).
* **Adaptive Weight Computation:** Automatic calculation of tension parameters based on divided differences, making the curve more "physical" and avoiding overshoot.
* **Natural Boundary Conditions:** Ensures second derivatives are zero at the endpoints for a smooth, natural fit.
* **Interactive Visualization:** Integration with **Plotly** for detailed, interactive exploration of spline behavior.

## 🔬 Mathematical Highlights

* **Linear Systems (SLAE):** Features a built-in Gaussian elimination solver with partial pivoting for high numerical stability.
* **Search Optimization:** The Valle-Poussin implementation utilizes binary search (`std::lower_bound`) for efficient node insertion and grid management.
* **Runge's Function Analysis:** Standard testing against $f(x) = 1 / (1 + 25x^2)$ to demonstrate the clear advantage of Chebyshev nodes over uniform grids.

## 🚀 Tech Stack

* **C++:** Core performance-critical algorithms, STL containers, and random number engines.
* **Python:** High-level data analysis using **NumPy** for matrix operations and **Plotly** for advanced visualization.

## Usage

### C++ Suite:

Compile the project using g++:

```bash
g++ main.cpp -o approx_suite
./approx_suite <n_nodes> <grid_type> <lower_bound> <upper_bound>
```
