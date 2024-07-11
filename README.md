# Ray/Path Tracer

![Example Cornell Box Scene render, 2048 samples per pixel, 8 bounces per ray](Github/cornell.png)
![Example Simple Scene render, 2000 samples per pixel](Github/simple.png)

This repository is the final project for Photorealistic Graphics class at Lodz University of Technology.

The project is a CPU path tracer application.

It is recommended to run in release mode for faster renders. 

### Features
- Path tracing: Fuzzy Reflections, Refraction, Diffuse Lighting
- Cornell Box example scene
- `omp parallel for` for speed up of main path tracing loop
- renders to TGA format
