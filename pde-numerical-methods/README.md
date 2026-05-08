# PDE Numerical Methods

This section contains a comprehensive collection of numerical solvers and research modules for **Partial Differential Equations (PDEs)** and **Ordinary Differential Equations (ODEs)**. The project covers classical finite-difference schemes, spectral methods, and advanced topics such as regularization of inverse problems and modal stabilization.

---

## 📁 Directory Structure

| Folder / Notebook                                                                 | Topic                   | Methods & Features                                                     |
| :-------------------------------------------------------------------------------- | :---------------------- | :--------------------------------------------------------------------- |
| [**spectral-convergence-analysis**](./spectral-convergence-analysis)           | Fourier Spectral Method | Accuracy analysis on refining grids ($N, 3N, 9N$).                   |
| [**ode_schemes_comparison**](./ode_schemes_comparison)                         | ODE Cauchy Problem      | Comparison of Explicit/Implicit Euler, Trapezoidal, and Adams methods. |
| [**heat_equation_schemes**](./heat_equation_schemes)                           | 1D Heat Equation        | Explicit vs. Implicit (TDMA/Thomas Algorithm) schemes.                 |
| [**2d-heat-equation-solver**](./2d-heat-equation-solver)                       | 2D Heat Equation        | 2D Discrete Fourier Transform & Iterative BSolver.                     |
| [**pde-mode-stabilization.ipynb**](./pde-mode-stabilization.ipynb)             | Modal Stabilization     | Stabilizing unstable "exploding" systems via projection methods.       |
| [**convection-diffusion-schemes.ipynb**](./convection-diffusion-schemes.ipynb) | Convection-Diffusion    | Stability study: Central vs. Upwind vs. Downwind schemes.              |
| [**tikhonov-regularization-pde.ipynb**](./tikhonov-regularization-pde.ipynb)   | Inverse Source Problem  | Tikhonov regularization & L-curve optimal$\alpha$ selection.         |
| [**inverse-heat-conduction.ipynb**](./inverse-heat-conduction.ipynb)           | Inverse Heat Problem    | Quasireversibility method for backward-in-time recovery.               |

---

## 🚀 Key Research Areas

### 1. Classical Solvers & Stability Analysis

* **ODE Comparison:** Quantitative analysis of convergence orders. Demonstrates how the Trapezoidal rule (2nd order) outperforms Euler schemes as the step size $h$ decreases.
* **1D & 2D Heat Equation:** Implementation of the **Thomas Algorithm (TDMA)** for implicit schemes. For 2D problems, a spectral approach (2D DFT) is used to handle the Laplacian operator efficiently.
* **Convection-Diffusion:** A study on the **Peclet number ($Pe$)**. Shows why central differences fail (Gibbs oscillations) at high velocities and how Upwind schemes provide stability through numerical diffusion.

### 2. Spectral Methods

* **Fourier Decomposition:** Utilization of the trigonometric basis (cosines) for solving boundary value problems.
* **Convergence Study:** Experimental verification of spectral accuracy, showing the exponential decay of error for smooth functions compared to polynomial-order finite difference methods.

### 3. Inverse & Ill-posed Problems

* **Tikhonov Regularization:** Solving the Hadamard ill-posed problem of source recovery. The module demonstrates how to find a "best $\alpha$" to balance residual error and solution smoothness.
* **Quasireversibility:** A "time-machine" for the heat equation. It stabilizes the inherently unstable backward heat conduction by filtering high-frequency noise that would otherwise cause the solution to explode.

### 4. Dynamic Stabilization

* **Modal Control:** For systems with unstable spectra ($\text{Re}(\lambda) > 0$), this module implements a controller that zeros out unstable projections using biorthogonal bases.
* **Visualization:** Includes 3D evolution plots comparing "exploding" original systems versus stabilized ones.

---

## 🛠 Tech Stack

* **Core Logic:** C++ (for high-performance solvers) and Python (for research and visualization).
* **Libraries:** `NumPy`, `SciPy` (linear algebra and sparse matrices), `Matplotlib` (3D surface plots, error analysis).
* **Key Algos:** TDMA (Thomas Algorithm), 2D DFT, Tikhonov Regularization, Bisection for Eigenvalues.

---

*This sub-project is part of a larger repository dedicated to Numerical Methods.*
