# 📊 Persistent Student CRUD Database System

A lightweight, high-performance console-driven relational CRUD database simulator written in clean C++17. By managing local flat-file data streams (`std::fstream`) instead of relying on heavy third-party SQL drivers (like MySQL or SQLite), this application serves as an excellent portfolio model demonstrating Object-Oriented Programming (OOP), file serialization, stream handling, and data sanitization structures.

---

## 🚀 Key Features

* **Create (Add Records):** Append entries to memory with structural identity matching checkpoints to prevent active duplicate primary key (ID) collisions.
* **Read (Query Rows):** Access database tables through clean grid layouts, or extract isolated single node lookups instantly by unique index paths.
* **Update (Modify In-Place):** Locate files instantly and rewrite attributes cleanly via in-memory vector indexing loops.
* **Delete (Data Compaction):** Purge records directly out of physical flat files using highly optimized linear data shift algorithms (`std::remove_if`).
* **Data Persistence:** Records remain preserved reliably inside `students_db.txt` even after application terminations, standard exits, or system reboots.
* **Robust Input Sanitization:** Features a robust input parsing engine that intercepts format breaking anomalies (e.g., inputting text characters into integer ID fields) to clear system buffers and prevent runtime application crashes.

---

## 📂 Core Architecture Diagram

```text
  [ User Console Menu Screen (Terminal CLI) ]
                       │
       Streams Runtime Vector Blocks
                       ▼
  [ Local Memory Database Controller Engine ]
                       │
    Performs CSV-Style Object Serialization
                       ▼
  [ Stable Hard Drive Persistence (students_db.txt) ]
```

---

## ⚙️ Compilation & Execution

This single-file setup requires no complex build automation configurations. You can build and run it natively on any platform through your system console:

### 1. Compile the Source Code
Open your platform terminal window and run the standard optimization command:
```bash
g++ -std=c++17 main.cpp -o app.exe
```

### 2. Run the Application Binary Executable
* **Windows Command Prompt / PowerShell:**
  ```bash
  ./app.exe
  ```
* **Linux / macOS Terminals:**
  ```bash
  chmod +x app.exe
  ./app.exe
  ```

---

## 🖥️ Live Application Interface Preview

When you execute the program, the system terminal generates the following clean, formatted interactive interface:

```text
=== STUDENT DATA MANAGING SYSTEM ===
1. Create New Record
2. View All Records
3. Search Record by ID
4. Update Existing Record
5. Delete Record
6. Exit Application
Choose Option (1-6): 2


```

---

## 🛠️ Technical Components Used

* **Core Stack:** C++17 Standard Core Libraries
* **File Utilities:** `<fstream>` (`std::ifstream` for secure reads, `std::ofstream` for sequential truncations)
* **Data Streams:** `<sstream>` (`std::stringstream` tokenizer layers for CSV data text splits)
* **Memory Sequences:** `<vector>` (Dynamic runtime memory block hosting arrays)
* **System Automation:** `<algorithm>` (`std::remove_if` data shift compaction utilities)

* ## 📊 Load Testing & Dataset Scalability

To evaluate the system's performance under realistic workload conditions, the project repository comes pre-loaded with a mock dataset of **500 structured student profiles** (`students_db.txt`).

* **Production Simulation**: Replaces standard 5-10 row hardcoded test samples with a bulk dataset to demonstrate real-world search and stream handling speeds.
* **Rigid Parameter Constraints**: Generated systematically to map strict institutional dynamics—allocating precise 120-row caps on CSE/CSE-AI headers, 60-row limits on Mechanical/Civil nodes, and an exact **80% enrollment skew towards B.Tech courses** across Indian structural names.
* **Algorithmic Validation**: Proves that the memory buffering logic and tabular parsing operations run efficiently with larger plain-text data sets without trailing execution delays.

