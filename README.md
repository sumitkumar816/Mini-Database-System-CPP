# Mini Database System — C++

A menu-driven Mini Database System built with **C++17**, demonstrating **OOP, STL, CRUD operations, file handling, sorting, CSV export, and database statistics**.

## Features
- Insert, Search, Update and Delete student records
- Persistent storage in `data/database.txt`
- Duplicate ID and input validation
- Display all records
- Sort by ID or name
- Export records to CSV
- Total records, average age and branch-wise statistics
- Modular `.h` / `.cpp` architecture

## Technologies
C++17 • OOP • STL (`vector`, `algorithm`, `map`) • File Handling • CMake • Git/GitHub

## Structure
```text
Mini-Database-System-CPP/
├── include/          # Header files
├── src/              # C++ implementation files
├── data/             # Persistent database
├── exports/          # CSV export
├── screenshots/      # Optional terminal screenshots
├── README.md
├── CMakeLists.txt
├── LICENSE
└── .gitignore
```

## Build with g++
```bash
g++ -std=c++17 -Iinclude src/main.cpp src/Student.cpp src/Database.cpp -o MiniDatabase
```
Run on Windows:
```powershell
.\MiniDatabase.exe
```
Run on Linux/macOS:
```bash
./MiniDatabase
```

## Build with CMake
```bash
cmake -S . -B build
cmake --build build
```

## Menu
```text
1. Insert Student
2. Search Student
3. Update Student
4. Delete Student
5. Display All Students
6. Sort by ID
7. Sort by Name
8. Export to CSV
9. Database Statistics
0. Exit
```

## Sample Data
```text
101,Amit Kumar,20,CSE
102,Priya Sharma,21,IT
103,Rahul Verma,19,AI
104,Neha Gupta,22,ECE
105,Sumit Kumar,20,CSE
106,Anjali Singh,21,IT
```

## OOP & STL Concepts
- Encapsulation through private student data
- Constructors, getters and setters
- `vector<Student>` for record storage
- `sort()` for ordering
- `remove_if()` + `erase()` for deletion
- `map` for branch statistics
- Serialization/deserialization for file persistence

## Complexity
| Operation | Complexity |
|---|---:|
| Insert | O(n) |
| Search | O(n) |
| Update | O(n) |
| Delete | O(n) |
| Sort   | O(nlogn) |

## Future Enhancements
- Record indexing / faster search
- Authentication and roles
- Multiple tables
- Transactions and rollback
- SQLite storage
- Unit tests
- SQL-like commands

## Author
**Sumit Kumar** — Computer Science & Engineering

## License
MIT License
