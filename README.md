# miniRT

*This project has been created as part of the 42 curriculum by tuaydin and abturan.*

## Description

miniRT is a compact ray tracer written in C using MiniLibX. It parses `.rt` scene files and renders them at 1289x720 with ambient, point lighting, and simple materials. Supported primitives include spheres, planes, and cylinders with diffuse/specular shading, optional checker textures, and basic UV/texture support. The goal is to give a hands-on introduction to ray-object intersections, lighting models, and scene management while staying minimal enough for quick experimentation.

Key features:
- Scene parsing for lights, camera, materials, and primitives
- Ray casting with closest-hit selection and shadow checks
- Diffuse/specular lighting with ambient term; optional checker/texture sampling
- Skybox support when a texture is provided

## Instructions

### Prerequisites
- Linux with `make` and `gcc`
- X11 development headers (e.g., `libx11-dev`, `libxext-dev`, `libbsd-dev`) for MiniLibX
- Included libs: libft, get_next_line, MiniLibX (already vendored under `libs/`)

### Compilation

```bash
make
```

### Execution

```bash
./miniRT scenes/test0.rt
```

Use any `.rt` file from the `scenes/` directory (e.g., `scenes/basics/test_sphere0.rt`). The window opens at 1289x720. Close with a key or window close button.

### Scene format essentials
- `A ratio R,G,B` — ambient light (e.g., `A 0.2 255,255,255`)
- `C x,y,z nx,ny,nz fov` — camera position, normal vector, field of view
- `L x,y,z ratio R,G,B` — point light
- `sp x,y,z diameter R,G,B [mat]` — sphere
- `pl x,y,z nx,ny,nz R,G,B [mat]` — plane
- `cy x,y,z nx,ny,nz diameter height R,G,B [mat]` — cylinder
- Materials: extras like `spc:s,d` (specular strength, shininess), `chk:size,color1,color2`, `tex:path` when supported

### Controls

- ESC — exit / close window
- WASD — move camera forward/back/strafe
- Z / X — move camera down / up
- Arrow keys — look around (yaw/pitch)
- K / L — decrease / increase FOV
- R — reload the scene file

## Resources

### Documentation & References
- [Ray Tracing in One Weekend](https://raytracing.github.io/) — foundational ray tracing walkthrough
- [Scratchapixel](https://www.scratchapixel.com/) — theory and math for rendering
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) — windowing and image routines
- [PBRT book](https://www.pbrt.org/) — deeper rendering reference (for future extensions)
- [Basic ray tracing walkthrough](https://gregorycernera.medium.com/an-explanation-of-basic-ray-tracing-313373c852ac)
- [Ray–cylinder intersection discussion](https://stackoverflow.com/questions/73866852/ray-cylinder-intersection-formula)
- [Phong specular reflection overview](https://www.geeksforgeeks.org/computer-graphics/phong-model-specular-reflection-in-computer-graphics/)

### AI Usage
AI assistance was used to:
- Brainstorm and review intersection/math logic (spheres, planes, cylinders)
- Suggest fixes for vector/matrix edge cases and shading bugs
- Draft documentation snippets and organize build/run instructions
