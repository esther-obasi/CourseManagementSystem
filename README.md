# Course Management System

A simple console-based C++ application for managing departments, courses, and student course selection. The program provides separate student and admin interfaces for browsing the catalog, adding courses, and saving administrative changes.

## Overview

This project simulates a basic course registration system with the following capabilities:

- Student portal for browsing departments and courses
- Shopping cart functionality for selecting courses
- Admin portal for adding departments and courses
- CSV export for saved admin data
- Menu-driven terminal interaction

## Project Structure

- [main.cpp](main.cpp) — entry point of the application
- [interface.h](interface.h) and [interface.cpp](interface.cpp) — shared interface logic and menu handling
- [adminInterface.cpp](adminInterface.cpp) — admin-specific features
- [studentInterface.cpp](studentInterface.cpp) — student-specific features
- [utility.h](utility.h) and [utility.cpp](utility.cpp) — department and course data models
- [admin.csv](admin.csv) — CSV file used for saved admin data
- [run](run) — shell script to compile and run the program

## Requirements

- A C++ compiler such as g++
- A Unix-like terminal environment (Linux, macOS, or WSL)

## How to Run

From the project directory, run:

```bash
./run
```

This script compiles the source files and starts the application.

You can also run it manually with:

```bash
g++ -o cms main.cpp interface.cpp adminInterface.cpp studentInterface.cpp utility.cpp
./cms
```

## How to Use

1. Launch the program.
2. Choose between the Student or Admin portal.
3. Students can browse departments, view course details, and manage a cart.
4. Admins can add departments, add courses, and save updates to CSV.

## Notes

The application is designed as a simple command-line project and uses in-memory storage during runtime, with admin changes written to the CSV file when saved.