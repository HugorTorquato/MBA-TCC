# MBA-TCC — Static Code Analysis API for C++

## 📌 Overview
This project implements a **RESTful API in C++** that performs **static analysis of C++ projects**, extracting class structures and relationships.  
The API downloads source files directly from GitHub repositories, processes them, and returns a **JSON representation** of the architecture.  

It is designed with **modularity and scalability** in mind, using **design patterns** (Strategy, Visitor, Singleton), **Google Test (gtest)** for testing, and **Crow** as the web framework.

---

## 📂 Project Structure & File Descriptions

### `API/`
- **`main.cpp`** → Entry point. Starts the Crow server and initializes API endpoints.  
- **`routes/`** → Contains the handlers for REST endpoints:
  - `listFilesInUrl` → Lists `.cpp` and `.h` files in a GitHub repo folder.  
  - `downloadFilesInUrl` → Downloads repository files into a local temp folder.  
  - `downloadAndRetreveSourceFileContent` → Returns raw file content in JSON.  

### `Core/`
Implements the compiler-inspired pipeline (scanner → tokens → parser → analysis).

- **`Scanner/`**
  - Scans each character of source files.
  - Groups characters into **lexemes** and identifies tokens.
  - Associates tokens with line numbers.

- **`Tokens/`**
  - Defines the token structures (keywords, identifiers, operators, etc).
  - Encapsulates token metadata (type, lexeme, location).

- **`Parser/`**
  - Consumes tokens to build a syntax structure (simplified AST).
  - Identifies **C++ class definitions** and their relationships.
  - Applies **Visitor pattern** for extensible operations.

- **`Analysis/`**
  - Performs static analysis on the parsed structures.
  - Extracts class hierarchies and dependencies.
  - Produces structured JSON output.

### `Logger/`
- **Singleton-based Logger**.
- Ensures consistent log management across the whole application.
- Provides debug/info/error logging.

### `Strategy/`
- Implements **Strategy pattern** for URL handling:
  - **GitHub API Strategy** → Uses GitHub REST API to list and download files.  
  - **GitHub Web Strategy** → Handles direct raw GitHub file URLs.  
- Enables dependency injection → allows mocking external HTTP in tests.

### `Tests/`
Unit and integration test suites using **Google Test**.

- **Unit Tests (~78)** → Validate individual classes (scanner, parser, tokens, strategies).  
- **Integration Tests (5)** → End-to-end API tests simulating user requests.  
- **Mocks** → Fake strategies for GitHub requests to ensure reproducibility.  

### Root Files
- **`CMakeLists.txt`** → Configures build system.  
- **`Dockerfile`** → Container environment for building/running the API.  
- **`Makefile`** (if present) → Shortcut for building/testing.  

---

## 🚀 Features
- API endpoints for file listing, downloading, and content retrieval.  
- Static code analysis pipeline for C++ class structures.  
- JSON-based results for easy integration.  
- Patterns applied: **Singleton (Logger)**, **Strategy (URLs, mocks)**, **Visitor (analysis extensibility)**.  
- Comprehensive testing (unit + integration).  

---

## ⚙️ Requirements
- **C++20**
- **Crow** (web framework)
- **libcurl** (HTTP requests)
- **Google Test** (unit testing)
- **CMake** (build system)
- **Docker** (recommended for environment isolation)

---

## 🛠️ Build & Run

### Build with CMake
```bash
mkdir build && cd build
cmake ..
make


---

## 2. File-by-File — Design Patterns Used

Here’s a **map of design patterns** across your project files:

- **`Logger/Log.*`** → **Singleton**  
  - Centralized logging system. Ensures a single global instance for logging.  

- **`Strategy/` (e.g., GitHubApiStrategy.cpp, GitHubWebStrategy.cpp)** → **Strategy**  
  - Defines interchangeable strategies for handling GitHub URLs.  
  - Enables **dependency injection** (mocking strategies in tests).  

- **`Core/Parser/*`** → **Visitor**  
  - Applied when traversing tokens/AST to support new operations without modifying core classes.  

- **`Core/Analysis/*`** → **Visitor (extension point)**  
  - Analysis logic extends parsing with visitor-based operations.  

- **`API/routes/*`** → **Strategy (indirect use)**  
  - Routes invoke strategy implementations depending on the URL type.  

- **`Tests/*`** → **Strategy + Dependency Injection**  
  - Uses mocked strategies for predictable results.  
  - Leverages flexibility of Strategy to isolate logic for unit tests.  

⚠️ Potential additional patterns:
- **Factory Method** (implicit in how tokens or strategies are instantiated).  
- **Adapter** (libcurl wrappers behave like an adapter to external HTTP).  

