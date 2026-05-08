
# Linear Algebra Solvers

This directory contains a collection of high-performance numerical algorithms for solving systems of linear equations (SLE) and eigenvalue problems. The implementations focus on numerical stability, computational efficiency, and scalability.

---

## 📁 Directory Structure

| Folder                                                                      | Method               | Description                                                                 |
| :-------------------------------------------------------------------------- | :------------------- | :-------------------------------------------------------------------------- |
| [**parallel-gaussian-elimination**](./parallel-gaussian-elimination)     | Gaussian Elimination | Parallel implementation using `pthreads` and custom barriers.             |
| [**sequential-gaussian-elimination**](./sequential-gaussian-elimination) | Gaussian Elimination | Standard sequential baseline with partial pivoting.                         |
| [**eigen-bisection-givens**](./eigen-bisection-givens)                   | Givens + Bisection   | Eigenvalue extraction for symmetric matrices using Sturm sequences.         |
| [**fourier-spectral-solver**](./fourier-spectral-solver)                 | Fourier Method       | A direct solver for boundary value problems via spectral decomposition.     |
| [**richardson-iterative-solver**](./richardson-iterative-solver)         | Richardson Iteration | Simple iteration method (SIM) with optimal$\tau$ parameter selection.     |
| [**preconditioned-iterative-solver**](./preconditioned-iterative-solver) | B-Method             | Two-layer iterative process with preconditioning for variable coefficients. |

---

## 🚀 Key Modules

### 1. Gaussian Elimination (Direct Methods)

A robust solver for $Ax = b$ systems using **partial pivoting** (row-wise maximum element selection) to ensure numerical stability.

* **Parallelization:** The `parallel-gaussian-elimination` module utilizes `POSIX Threads` to distribute the elimination workload across multiple CPU cores.
* **Custom Synchronization:** To ensure compatibility across different POSIX implementations, thread synchronization is handled via a custom barrier mechanism using `pthread_mutex_t` and `pthread_cond_t`.
* **Performance:** Memory access is optimized using pointer arithmetic on 1D-mapped arrays to minimize row-index calculation overhead.

### 2. Eigenvalue Problems (Symmetric Matrices)

A two-stage algorithm designed for high-precision eigenvalue computation:

* **Tridiagonalization:** Transforms the initial symmetric matrix into a similar tridiagonal matrix using **Givens rotations**.
* **Localization:** Uses the **Bisection method** and **Sturm sequences** (evaluating determinants of principal minors) to find specific eigenvalues.
* **Stability:** Implements a robust scheme to prevent overflow and division-by-zero during recurrence calculations.

### 3. Fourier Spectral Solver

A direct method for solving discrete boundary value problems derived from second-order differential equations.

* Instead of iterative refinement, it projects the right-hand side onto the **eigenfunction basis** (trigonometric basis).
* Features high computational efficiency for regular grids and uses `long double` precision for critical sum calculations.

### 4. Iterative Methods

Designed for large-scale systems where direct methods become computationally expensive.

* **Richardson Method:** Automatically estimates the spectrum boundaries $[m, M]$ to determine the optimal step parameter $\tau = 2 / (m + M)$. It compares real convergence rates against theoretical predictions ($q$).
* **Preconditioning (B-Method):** Solves complex systems with variable coefficients (e.g., $p(x) = 1 + \sin^2(\pi x)$) by using a simpler operator $B$ to accelerate convergence. The inversion of $B$ is handled via the fast Fourier spectral method.

---

## 🛠 Technical Highlights

* **Precision:** Uses `long double` for sensitive calculations to mitigate rounding errors.
* **Verification:** All solvers include automatic residual norm calculation ($||Ax - b||$) to verify solution accuracy.
* **Analysis:** Iterative solvers log convergence data to `.txt` files (e.g., `result2.txt`) for plotting and performance analysis.
* **Versatility:** Supports matrix initialization via formula-based generation (Hilbert matrices, band matrices) or file input.

---

*This sub-project is part of a larger repository dedicated to Numerical Methods.*
