# Numerical Integration Suite (1D & 2D)

A high-performance C++ library providing robust numerical integration algorithms for univariate and bivariate functions. The suite features advanced support for complex 2D domains through custom triangulation and mesh-based integration.

## 🛠 Implemented Methods (1D)

* **Composite Simpson's Rule:** A classic parabolic approximation method adapted for composite intervals to maintain high precision across large integration domains.
* **Gauss-Legendre Quadrature:** A three-point Gaussian quadrature implementation designed for maximum algebraic degree of precision.
* **Error Analysis & Benchmarking:** Integrated tools for convergence analysis, comparing numerical results with analytical solutions using logarithmic error scales.

## 📐 2D Integration & Triangulation

This advanced module extends integration to planar regions using finite element concepts:

* **Triangulation Engine:** A mesh generator that discretizes rectangular domains into triangular elements, providing precise management of internal and boundary edges.
* **Integration over Arbitrary Triangles:** Implementation of double integrals across triangular elements using coordinate transformation.
* **Gauss-Type Weights & Nodes:** Support for high-order quadrature weights (including external weight file parsing) to ensure precision on each mesh element.
* **Mesh Export:** Automated generation of `triangulation.txt` containing node coordinates and connectivity data, compatible with visualization tools or **Finite Element Method (FEM)** workflows.

## 🚀 Technical Highlights

* **Functional Programming Approach:** Utilizes C++ `std::function` and lambda expressions for universal and flexible function passing.
* **Performance-Driven:** Optimized mesh traversal loops and efficient memory management using `std::vector` for large-scale computations.
* **Research Toolkit:** Automated data logging for generating convergence plots and verifying numerical stability.

## Usage Example

Integrating a bivariate function $f(x, y) = x^4 + (xy)^2 + y^4$ over a triangulated mesh:

```cpp
#include "integration.hpp"
#include <cmath>
#include <iostream>

int main() {
    // Define the integrand using a lambda expression
    auto f = [](double x, double y) { 
        return std::pow(x, 4) + std::pow(x * y, 2) + std::pow(y, 4); 
    };

    // Perform integration over the generated mesh
    // Nx, Ny - grid resolution, Lx, Ly - domain dimensions
    double result = integrate(f, Nx, vertices, triangles, weights);
  
    std::cout << "Result: " << result << std::endl;
    return 0;
}
```
