# Student Management System

A beginner-friendly C++ console application that manages students, subjects, and enrollments using object-oriented design principles and modern C++ (C++20).

## Features

- **Student Management** — add, edit, delete, search (by ID or name), and list students
- **Subject Management** — load subjects from file, view available subjects
- **Enrollment** — enroll students into existing subjects
- **Persistence** — subjects are loaded from a local text file on startup

## Architecture

The project follows a layered design with clear separation between entities and managers:

```text
                User
                   │
                   ▼
            Console UI (main.cpp)
                   │
      ┌────────────┼────────────┐
      ▼            ▼            ▼
StudentManager SubjectManager EnrollmentManager
      │            │            │
      ▼            ▼            ▼
   Student      Subject       Enrollment
```

### Entities

| Class | Responsibility |
|-------|----------------|
| `Student` | Stores student data (id, first name, last name, year level, optional email/phone) |
| `Subject` | Stores subject data (id, code, title, units) |
| `Enrollment` | Links a student to a subject by their IDs |

### Managers

| Class | Responsibility |
|-------|----------------|
| `StudentManager` | CRUD operations for students using a simple hash table |
| `SubjectManager` | Loads subjects from file and provides access |
| `EnrollmentManager` | Adds and manages enrollment records |

### UI

`main.cpp` presents a menu-driven console interface. All user interactions are handled in `main()` and delegated to the appropriate manager.

## Building

### Prerequisites

- CMake 4.2+
- A C++20-compatible compiler (GCC or Clang)
- [vcpkg](https://vcpkg.io/) (for Boost UUID dependency)

### Build with CMake

```bash
make cmake_debug   # Debug build with -g
make cmake_release # Release build with -O2
make run_cmake     # Build (debug) and run
```

### Build directly with g++

```bash
make run   # Debug build with -g -Wall -Wextra -Wpedantic
make prod  # Release build with -O2
```

### Clean

```bash
make clean
```

## Data

Subjects are defined in `data/subjects.txt` using the format:

```text
code,title,units
```

Example:

```text
CS101,Programming 1,3
CS102,Discrete Mathematics,3
CS103,Data Structures,4
```

## Key Concepts Practiced

- C++20 features (`std::optional`)
- Object-oriented design (classes, encapsulation)
- STL containers (`std::vector`, `std::string`)
- Standard algorithms (`std::copy_if`, `std::transform`)
- File I/O
- Rule of Five (copy/move semantics in `StudentManager`)
- Separate compilation (`include/` + `src/`)
