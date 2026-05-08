# Nonlinear Equation Solvers

This directory contains advanced numerical methods for solving nonlinear algebraic equations and systems. The focus is on stability, convergence speed, and handling high-order approximations.

## 🛠 Contents

### 1. Newton-Fedorenko Method (`newton_fedorenko_system.py`)

A stabilized modification of Newton's method designed for solving **systems of nonlinear equations**.

* **Adaptive Damping ($\tau$):** Uses backtracking line search to ensure the residual decreases at each step, significantly widening the convergence basin compared to the standard Newton method.
* **Weighted Error Metric:** Implements a specialized norm $|F(x_k)|_\alpha$ that accounts for local Jacobian scaling, providing a more robust stopping criterion.
* **Visualization:** Interactive convergence tracking using Plotly.

### 2. Chebyshev's High-Order Method (`chebyshev_high_order.py`)

An iterative solver for finding roots of functions using **Chebyshev's inverse interpolation** (or high-order Taylor expansions of the inverse function).

* **High-Order Convergence:** Beyond the standard quadratic convergence of Newton's method, this implementation allows for cubic and higher-order terms to accelerate root-finding.
* **Symbolic Support:** Utilizes `sympy` for high-order derivative computation, allowing the solver to adapt to various mathematical models (roots of powers, logarithms, etc.).
* **Error Analysis:** Compares numerical approximations against exact analytical roots to demonstrate the efficiency of adding more terms to the expansion.

## 🚀 Key Concepts

* **Convergence Rate:** Comparison of linear, quadratic, and cubic convergence behaviors.
* **Stability:** Techniques to handle poor initial guesses (relaxation and damping).
* **Symbolic-to-Numerical:** Seamless integration of symbolic differentiation with numerical iteration.

## Requirements

* `numpy`
* `sympy`
* `plotly`
* `tqdm` (for parameter sweeps)

## Usage Example

To analyze the convergence of the Newton-Fedorenko system:

```bash
python newton_fedorenko_system.py
```
