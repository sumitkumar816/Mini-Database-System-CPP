#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <limits>

// ==========================================
// 1. STUDENT MODEL STRUCT
// ==========================================
struct Student {
    int id;
    std::string name;
    double gpa;

    // Convert object data directly to a CSV-ready format line
    std::string serialize() const {
        return std::to_string(id) + "," + name + "," + std::to_string(gpa);
    }

    // Parse a CSV line back into a Student structural object
    static Student deserialize(const std::string& line) {
        std::stringstream ss(line);
        std::string idStr, nameStr, gpaStr;

        std::getline(ss, idStr, ',');
        std::getline(ss, nameStr, ',');
        std::getline(ss, gpaStr, ',');

        return { std::stoi(idStr), nameStr, std::stod(gpaStr) };
    }
};

// ==========================================
// 2. DATABASE SYSTEM CONTROLLER CLASS
// ==========================================
class Database {
private:
    std::string filename;

    // Reads flat file data and loads it cleanly into an in-memory vector array
    std::vector<Student> loadAllRecords() const {
        std::vector<Student> students;
        std::ifstream file(filename);
        std::string line;
        
        while (std::getline(file, line)) {
            if (!line.empty()) {
                try {
                    students.push_back(Student::deserialize(line));
                } catch (...) {
                    continue; // Skip damaged rows silently
                }
            }
        }
        return students;
    }

    // Overwrites flat storage completely with updated vector layers
    void saveAllRecords(const std::vector<Student>& students) const {
        std::ofstream file(filename, std::ios::trunc);
        for (const auto& student : students) {
            file << student.serialize() << "\n";
        }
    }

public:
    explicit Database(std::string dbFilename) : filename(std::move(dbFilename)) {
        // Enforce physical file creation on hard drive if missing
        std::ofstream file(filename, std::ios::app);
        file.close();
    }
    
    // CREATE: Appends data while checking for duplicate ID flags
    bool createRecord(const Student& student) {
        std::vector<Student> students = loadAllRecords();
        for (const auto& s : students) {
            if (s.id == student.id) return false; 
        }
        
        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << student.serialize() << "\n";
            return true;
        }
        return false;
    }

    // READ SINGLE: Checks vector layer for specific key matching
    bool readRecord(int id, Student& foundStudent) const {
        std::vector<Student> students = loadAllRecords();
        for (const auto& s : students) {
            if (s.id == id) {
                foundStudent = s;
                return true;
            }
        }
        return false;
    }

    // READ ALL: Prints everything formatted inside grid layouts
    void displayAllRecords() const {
        std::vector<Student> students = loadAllRecords();
        if (students.empty()) {
            std::cout << "\n[!] No records found inside the database system.\n";
            return;
        }
        std::cout << "\n=============================================\n";
        std::cout << std::left << std::setw(10) << "ID" << std::setw(25) << "NAME" << "GPA\n";
        std::cout << "---------------------------------------------\n";
        for (const auto& s : students) {
            std::cout << std::left << std::setw(10) << s.id << std::setw(25) << s.name << s.gpa << "\n";
        }
        std::cout << "=============================================\n";
    }

    // UPDATE: Alters target properties internally and syncs down
    bool updateRecord(int id, const std::string& newName, double newGpa) {
        std::vector<Student> students = loadAllRecords();
        bool found = false;
        for (auto& s : students) {
            if (s.id == id) {
                s.name = newName;
                s.gpa = newGpa;
                found = true;
                break;
            }
        }
        if (found) saveAllRecords(students);
        return found;
    }

    // DELETE: Sweeps matching data rows out using shift algorithms
    bool deleteRecord(int id) {
        std::vector<Student> students = loadAllRecords();
        auto initialSize = students.size();
        
        students.erase(
            std::remove_if(students.begin(), students.end(), [id](const Student& s) { return s.id == id; }),
            students.end()
        );
        
        if (students.size() < initialSize) {
            saveAllRecords(students);
            return true;
        }
        return false;
    }
};

// ==========================================
// 3. MAIN TERMINAL CLI SYSTEM
// ==========================================
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Database db("students_db.txt");
    int choice = 0;

    while (true) {
        std::cout << "\n=== STUDENT DATA MANAGING SYSTEM ===\n";
        std::cout << "1. Create New Record\n";
        std::cout << "2. View All Records\n";
        std::cout << "3. Search Record by ID\n";
        std::cout << "4. Update Existing Record\n";
        std::cout << "5. Delete Record\n";
        std::cout << "6. Exit Application\n";
        std::cout << "Choose Option (1-6): ";
        
        if (!(std::cin >> choice)) {
            std::cout << "[!] Invalid numeric entry!\n";
            clearInputBuffer();
            continue;
        }

        if (choice == 6) break;

        switch (choice) {
            case 1: {
                Student s;
                std::cout << "Enter unique Student ID (Integer): ";
                while (!(std::cin >> s.id)) {
                    std::cout << "[!] Invalid ID style. Enter an integer: ";
                    clearInputBuffer();
                }
                clearInputBuffer();

                std::cout << "Enter Student Full Name: ";
                std::getline(std::cin, s.name);

                std::cout << "Enter Student GPA (0.0 - 4.0): ";
                while (!(std::cin >> s.gpa)) {
                    std::cout << "[!] Invalid float style. Enter GPA value: ";
                    clearInputBuffer();
                }

                if (db.createRecord(s)) {
                    std::cout << "[+] Record successfully committed to disk database storage.\n";
                } else {
                    std::cout << "[-] Error: Student with ID " << s.id << " already exists!\n";
                }
                break;
            }
            case 2:
                db.displayAllRecords();
                break;
            case 3: {
                int searchId;
                std::cout << "Enter Student ID to find: ";
                if (!(std::cin >> searchId)) {
                    clearInputBuffer();
                    break;
                }
                Student found;
                if (db.readRecord(searchId, found)) {
                    std::cout << "\n[Record Found]\nID: " << found.id << "\nName: " << found.name << "\nGPA: " << found.gpa << "\n";
                } else {
                    std::cout << "[-] Error: Student ID not located.\n";
                }
                break;
            }
            case 4: {
                int updateId;
                std::cout << "Enter Target Student ID to update: ";
                std::cin >> updateId;
                clearInputBuffer();
                
                Student target;
                if (db.readRecord(updateId, target)) {
                    std::string newName;
                    double newGpa;
                    std::cout << "Current context: Name: " << target.name << " | GPA: " << target.gpa << "\n";
                    std::cout << "Enter New Name: ";
                    std::getline(std::cin, newName);
                    std::cout << "Enter New GPA: ";
                    std::cin >> newGpa;
                    
                    db.updateRecord(updateId, newName, newGpa);
                    std::cout << "[+] Database parameters updated correctly.\n";
                } else {
                    std::cout << "[-] Error: Requested Student record does not exist.\n";
                }
                break;
            }
            case 5: {
                int deleteId;
                std::cout << "Enter target ID for deletion: ";
                std::cin >> deleteId;
                if (db.deleteRecord(deleteId)) {
                    std::cout << "[+] Record purged out cleanly.\n";
                } else {
                    std::cout << "[-] Error: Identification entry missing inside storage.\n";
                }
                break;
            }
            default:
                std::cout << "[!] Choice out of range. Provide an option code from 1 to 6.\n";
        }
    }
    std::cout << "\nClosing environment database stream engine safely. Goodbye!\n";
    return 0;
}
