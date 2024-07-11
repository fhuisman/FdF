<div align="center">
  <h1>FdF</h1>
  <p>A 3D wireframe renderer for representing landscapes using lines to connect points on a grid, developed as part of the 42 curriculum. This project involves parsing a file of coordinates and drawing a 3D representation using the MLX42 library.</p>
</div>

## Description

FdF (Fil de Fer) is a graphics project that reads a file containing a grid of elevations and generates a 3D wireframe representation of the terrain. This project helps in understanding the basics of computer graphics, coordinate systems, and transformations.

## Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/fdf.git FdF
    ```

2. Install the [MiniLibX](https://github.com/codam-coding-college/MLX42) library (make sure you have the necessary dependencies installed)

3. Go into the philosophers directory and compile by using make:

    ```sh
    cd FdF
    make
    ```

## Usage

To run the FdF program, use the following command:
```sh
./fdf [path_to_map_file]
```
Example:
```sh
./fdf maps/42.fdf
```

### Controls

- **ASWDQE keys**: Move the view
- **mouse scroll wheel**: Zoom in/out
- **+/- keys**: Adjust the altitude
- **ESC**: Exit the program
