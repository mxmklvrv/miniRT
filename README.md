# Ray Tracing Engine

A basic ray tracing engine written in C as part of the Hive Helsinki curriculum.

The goal of this project was to better understand the fundamentals of computer graphics, rendering pipelines, and mathematical concepts used in 3D environments.
The project focuses on simulating how rays interact with objects and light sources to generate rendered scenes.

---

## 📌 Project Goals

Through this project, I wanted to strengthen my understanding of:

- Ray tracing fundamentals
- Vector mathematics and 3D transformations
- Rendering pipelines
- Scene parsing and object management
- Lighting calculations
- Performance optimization in C

---

## ⚙️ Features

- Rendering of basic geometric objects:
  - spheres
  - planes
  - cylinders
- Camera positioning and transformations
- Ambient and diffuse lighting
- Scene parsing from configuration files
- Object intersection calculations
- Real-time scene rendering in a window

---

## 🛠 Technical Approach

The rendering engine was built around ray-object intersection calculations using vector mathematics.

For each pixel, rays are projected from the camera into the scene to determine object intersections and lighting information. I implemented separate intersection logic for different object types to keep the rendering pipeline modular and easier to maintain.

Scene parsing was designed to convert configuration input into structured scene objects, allowing dynamic scene generation and easier debugging.

One important focus during development was keeping the code modular and separating rendering, parsing, math utilities, and object handling into independent components.

---

## 🚧 Challenges

Some of the most challenging parts of the project included:

- Understanding and implementing vector mathematics correctly
- Debugging rendering artifacts and incorrect intersections
- Managing object transformations and camera positioning
- Handling floating-point precision issues
- Structuring the rendering loop efficiently

This project required a lot of experimentation and debugging, which significantly improved my problem-solving skills and understanding of graphics programming.

---

## 📚 What I Learned

Through this project, I gained practical experience with:

- Computer graphics fundamentals
- Ray-object intersection algorithms
- Vector math and geometric transformations
- Rendering architecture
- Performance considerations in graphics applications
- Debugging complex visual and mathematical problems

It also improved my ability to design larger projects with cleaner architecture and modular code organization.

---
