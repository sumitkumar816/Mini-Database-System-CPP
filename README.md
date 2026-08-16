# File-Based Student CRUD Database System (C++)

A lightweight, high-performance console-driven relational CRUD database simulator written in clean C++17. The program saves data records using sequential plain-text file streaming serialization frameworks, serving as a clean demo model for standard persistent data management operations without third-party external driver overhead.

## 🚀 Features

- **Create**: Add a record with unique identification validation checkpoints (prevents duplicate ID collisions).
- **Read**: Formatted database scans with structured table formatting or specific primary key single index inquiries.
- **Update**: Find specific file objects and modify metadata attributes seamlessly.
- **Delete**: Safely drop individual index nodes from flat storage via a compaction dynamic memory filter strategy.
- **Data Persistence**: Automatic serialization/deserialization into stable `.txt` configurations.
- **Robust CLI Parsing**: Clears validation failures automatically when unexpected entry formats are inserted.

## 📂 Core Architecture Diagram

```text
       [ Terminal CLI View Main Loop (main.cpp) ]
                          │
            Reads/Writes Structured Data
                          ▼
        [ Database Engine Controller (Database.cpp) ]
                          │
       Performs Serialization / Memory Management
                          ▼
        [ Hard Drive Persistence (students_db.txt) ]
```

## 🛠️ Build and Compilation Instructions

Ensure you have a C++17 compliant compiler installed (`gcc`, `clang`, or MSVC) along with CMake.

### Standard Build:
```bash
# Clone the project directory 
git clone https://github.com
cd YOUR_REPOSITORY_NAME

# Generate internal build system directories
mkdir build && cd build
cmake ..

# Run target platform project compilations
cmake --build .
```

### Running the Application executable binary:
```bash
# Windows
StudentCRUD.exe

# Linux & macOS
./StudentCRUD
```

## 📋 Technology Components Used
- **Language Stack**: C++17 Standard
- **File Utilities**: `<fstream>` (`std::ifstream`, `std::ofstream`)
- **Memory Sequences**: `<vector>`, `<algorithm>` 
- **System Automation**: CMake System Tools (v3.10+)
