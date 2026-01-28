# miniRT

*This project has been created as part of the 42 curriculum by tuaydin.*

## Description

miniRT is a ray tracer implementation written in C. The project renders 3D scenes using ray tracing techniques, supporting basic geometric objects (spheres, planes, cylinders) with lighting, shadows, and materials. It provides a foundation for understanding computer graphics and 3D rendering algorithms.

## Instructions

### Compilation

```bash
make
```

### Execution

```bash
./miniRT scenes/test0.rt
```

The program accepts a scene file (.rt format) as an argument. Example scene files are provided in the `scenes/` directory.

### Controls

- `ESC` - Exit the program
- `Q` - Quit

## Resources

### Documentation & References
- [Ray Tracing in One Weekend](https://raytracing.github.io/) - Fundamental ray tracing concepts
- [Scratchapixel](https://www.scratchapixel.com/) - Computer graphics theory
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) - Graphics library reference

### AI Usage
AI tools were used for:
- Debugging mathematical calculations in vector operations and intersection algorithms
- Code optimization suggestions
- Understanding ray-sphere and ray-plane intersection formulas
