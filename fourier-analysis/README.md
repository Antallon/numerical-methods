# Fourier Series Approximation (1D & 2D)

This module implements function approximation using discrete trigonometric Fourier series. It provides tools to decompose complex continuous signals and surfaces into a sum of orthogonal cosine and sine basis functions.

## 🛠 Contents

### 1. 1D Fourier Decomposition (`fourier_approx_1d.cpp`)

Approximates a univariate function $u(x)$ on a discrete grid.

* **Numerical Integration:** Uses the rectangle rule to compute Fourier coefficients $\alpha_k$.
* **Grid Management:** Implements shifted grids ($h/2$ offset) to minimize boundary errors.
* **Error Estimation:** Automatic calculation of the $L_\infty$ norm (maximum absolute error) between the original function and its spectral reconstruction.

### 2. 2D Surface Approximation (`fourier_approx_2d.cpp`)

Extends spectral decomposition to bivariate functions $u(x, y)$.

* **Coefficient Matrices:** Computes 2D Fourier coefficients by applying 1D transformations sequentially across rows and columns (Separable Transform).
* **Surface Reconstruction:** Rebuilds the surface at any point $(x, y)$ using the precomputed coefficient matrix $D_{ij}$.
* **High-Precision Grids:** Supports fine mesh generation for error analysis across the entire domain.

## 🚀 Technical Features

* **Orthogonal Basis:** Implementation relies on the cosine basis, effectively performing a Discrete Cosine Transform (DCT) type approximation.
* **Separable Transform Logic:** The 2D implementation uses an efficient $O(N^3)$ approach instead of a naive $O(N^4)$ by decomposing the 2D transform into two 1D stages.
* **Flexible Integrands:** Easily swap test functions $u(x)$ or $u(x, y)$ using C++ function pointers or lambdas.

## 📈 Methodology

The approximation is based on the formula:

$$
u(x) \approx \alpha_0 + \sum_{i=1}^{N-1} \alpha_i \cos(\pi i x)
$$

For 2D:

$$
u(x, y) \approx \sum_{i=0}^{N-1} \sum_{j=0}^{N-1} D_{ij} \cos(\pi i x) \cos(\pi j y)
$$

## How to Run

```bash
g++ fourier_approx_1d.cpp -o fourier1d
./fourier1d [number_of_points]

g++ fourier_approx_2d.cpp -o fourier2d
./fourier2d [number_of_points]
```
