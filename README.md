# Numerical Methods & Scientific Computing Library

A comprehensive collection of high-performance numerical algorithms and research modules. This repository covers a wide spectrum of computational mathematics, ranging from fundamental linear algebra to advanced partial differential equations (PDEs), spectral analysis, and inverse problems.

## 🏗 Project Architecture

The library is organized into specialized modules, each targeting a specific domain of numerical analysis:

### 1. [Linear Algebra Solvers](./linear-algebra) (C++)

Robust implementations of direct and iterative methods for large-scale systems.

* **Direct Methods:** Parallel Gaussian elimination (pthreads), Givens rotations, and Tridiagonalization.
* **Iterative Methods:** Richardson iteration with optimal parameters and Preconditioned (B-Method) solvers.
* **Eigenvalue Problems:** Bisection method and Sturm sequences for symmetric matrices.


### 2. [PDE &amp; ODE Numerical Methods](./pde-numerical-methods) (C++ & Python)

Advanced solvers for differential equations and stability research. This is the core research module of the repository.

* **Classical Finite-Difference Schemes:**
  * **Heat Equation (1D/2D):** Implementation of explicit and implicit schemes (TDMA/Thomas Algorithm).
  * **ODE Analysis:** Comparative study of Euler, Trapezoidal, and Adams methods with convergence order verification.
  * **Convection-Diffusion:** Stability analysis of Upwind vs. Central difference schemes based on the **Peclet number ($Pe$)**.
* **Spectral Methods:**
  * **Fourier Spectral Solvers:** High-accuracy boundary value problem solvers using trigonometric bases.
  * **Convergence Research:** Experimental proof of spectral (exponential) accuracy on refining grids.
* **Inverse & Ill-posed Problems:**
  * **Tikhonov Regularization:** Solving Hadamard ill-posed source recovery problems with optimal $\alpha$ selection via L-curve analysis.
  * **Quasireversibility Method:** "Backward-in-time" heat conduction recovery, stabilizing high-frequency noise in unstable parabolic systems.
* **Dynamic Stabilization:**
  * **Modal Control:** Stabilization of "exploding" systems ($\text{Re}(\lambda) > 0$) using projection onto biorthogonal bases.

### 3. [Numerical Integration Suite](./numerical-integration) (C++)

High-precision integration for univariate and bivariate functions.

* **1D Quadratures:** Composite Simpson’s rule and 3-point Gauss-Legendre methods.
* **2D Integration:** Integration over arbitrary triangular meshes with custom triangulation engines.

### 4. [Approximation &amp; Interpolation](./approximation-and-interpolation) (C++ & Python)

Tools for smooth data fitting and optimal grid generation.

* **Polynomials:** Minimax approximation (Valle-Poussin), Lagrange interpolation, and Chebyshev grid optimization.
* **Splines:** Advanced Tension Splines with adaptive weight computation for oscillation control.

### 5. [Fourier &amp; Spectral Analysis](./fourier-analysis) (C++)

Spectral decomposition for signal and surface reconstruction.

* **1D/2D Fourier Transforms:** Decomposition into orthogonal trigonometric bases for boundary value problems.
* **Convergence Analysis:** Experimental verification of spectral accuracy, showing the exponential decay of error for smooth functions.

### 6. [Nonlinear Equation Solvers](./nonlinear-equation-solvers) (Python)

Iterative methods for roots and systems.

* **Newton-Fedorenko:** Stabilized system solver with adaptive damping ($\tau$) and weighted norms.
* **High-Order Chebyshev:** Root-finding with cubic and higher-order convergence rates.

### 7. [Random Number Generators](./random-generators) (C++)

Low-level PRNG implementations and statistical quality testing.

* **Algorithms:** Additive Fibonacci-type generators and Linear Feedback Shift Registers (LFSR).
* **Testing:** Runs tests for monotonicity and byte-frequency distribution analysis.

---

## 🚀 Technical Highlights

* **Multi-Language Core:** High-performance computation engine in **C++** (STL, Pthreads) combined with an analytical and visualization layer in **Python** (NumPy, SciPy, Plotly, SymPy).
* **Numerical Stability:** Extensive use of `long double` precision, partial pivoting, and regularization techniques (Tikhonov) to handle ill-conditioned problems.
* **Performance Optimization:** Optimized memory access patterns, custom synchronization barriers, and efficient spectral transforms.
* **Research Driven:** Every module includes convergence logs and error analysis plots ($L_\infty$ and $L_2$ norms).
