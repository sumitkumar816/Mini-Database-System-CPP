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
    std::string branch; // नया फ़ील्ड जोड़ा गया
    std::string course; // नया फ़ील्ड जोड़ा गया
    float gpa;

    // ऑब्जेक्ट डेटा को केवल 2 डेसिमल GPA के साथ CSV फॉर्मेट में बदलना
    std::string serialize() const {
        std::stringstream ss;
        ss << id << "," << name << "," << branch << "," << course << "," << std::fixed << std::setprecision(2) << gpa;
        return ss.str();
    }

    // CSV लाइन को तोड़कर वापस Student ऑब्जेक्ट बनाना
    static Student deserialize(const std::string& line) {
        std::stringstream ss(line);
        std::string idStr, nameStr, branchStr, courseStr, gpaStr;

        std::getline(ss, idStr, ',');
        std::getline(ss, nameStr, ',');
        std::getline(ss, branchStr, ',');
        std::getline(ss, courseStr, ',');
        std::getline(ss, gpaStr, ',');

        return { std::stoi(idStr), nameStr, branchStr, courseStr, std::stof(gpaStr) };
    }
};

// ==========================================
// 2. DATABASE SYSTEM CONTROLLER CLASS
// ==========================================
class Database {
private:
    std::string filename;

    std::vector<Student> loadAllRecords() const {
        std::vector<Student> students;
        std::ifstream file(filename);
        std::string line;
        
        while (std::getline(file, line)) {
            if (!line.empty()) {
                try {
                    students.push_back(Student::deserialize(line));
                } catch (...) {
                    continue; 
                }
            }
        }
        return students;
    }

    void saveAllRecords(const std::vector<Student>& students) const {
        std::ofstream file(filename, std::ios::trunc);
        for (const auto& student : students) {
            file << student.serialize() << "\n";
        }
    }

public:
    explicit Database(std::string dbFilename) : filename(std::move(dbFilename)) {
        std::ofstream file(filename, std::ios::app);
        file.close();
    }
    
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

    void displayAllRecords() const {
        std::vector<Student> students = loadAllRecords();
        if (students.empty()) {
            std::cout << "\n[!] No records found inside the database system.\n";
            return;
        }
        std::cout << "\n=========================================================================================\n";
        std::cout << std::left << std::setw(8) << "ID" 
                  << std::setw(22) << "NAME" 
                  << std::setw(20) << "BRANCH" 
                  << std::setw(15) << "COURSE" 
                  << "GPA\n";
        std::cout << "-----------------------------------------------------------------------------------------\n";
        for (const auto& s : students) {
            std::cout << std::left << std::setw(8) << s.id 
                      << std::setw(22) << s.name 
                      << std::setw(20) << s.branch 
                      << std::setw(15) << s.course 
                      << std::fixed << std::setw(5) << std::setprecision(2) << s.gpa << "\n";
        }
        std::cout << "=========================================================================================\n";
    }

    // अपडेट फ़ंक्शन में ब्रांच और कोर्स भी शामिल किया गया
    bool updateRecord(int id, const std::string& newName, const std::string& newBranch, const std::string& newCourse, float newGpa) {
        std::vector<Student> students = loadAllRecords();
        bool found = false;
        for (auto& s : students) {
            if (s.id == id) {
                s.name = newName;
                s.branch = newBranch;
                s.course = newCourse;
                s.gpa = newGpa;
                found = true;
                break;
            }
        }
        if (found) saveAllRecords(students);
        return found;
    }

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

                std::cout << "Enter Branch (e.g., CSE, Mechanical): ";
                std::getline(std::cin, s.branch);

                std::cout << "Enter Course (e.g., B.Tech, M.Tech): ";
                std::getline(std::cin, s.course);

                std::cout << "Enter Student GPA (0.0 - 10.0): ";
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
                    std::cout << "\n[Record Found]\n"
                              << "ID: " << found.id 
                              << "\nName: " << found.name 
                              << "\nBranch: " << found.branch 
                              << "\nCourse: " << found.course 
                              << "\nGPA: " << std::fixed << std::setprecision(2) << found.gpa << "\n";
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
                    std::string newName, newBranch, newCourse;
                    float newGpa;
                    
                    std::cout << "Current context: Name: " << target.name 
                              << " | Branch: " << target.branch 
                              << " | Course: " << target.course 
                              << " | GPA: " << std::fixed << std::setprecision(2) << target.gpa << "\n\n";
                    
                    std::cout << "Enter New Name: ";
                    std::getline(std::cin, newName);
                    
                    std::cout << "Enter New Branch: ";
                    std::getline(std::cin, newBranch);
                    
                    std::cout << "Enter New Course: ";
                    std::getline(std::cin, newCourse);
                    
                    std::cout << "Enter New GPA: ";
                    std::cin >> newGpa;
                    
                    db.updateRecord(updateId, newName, newBranch, newCourse, newGpa);
                    std::cout << "[+] Database parameters updated correctly.\n";
                } 
                else
                {std::cout << "[-] Error: Requested Student record does not exist.\n";}
                break;
            }
            case 5: {
                int deleteId;
                std::cout << "Enter target ID for deletion: ";
                std::cin >> deleteId;
                if (db.deleteRecord(deleteId))
                {
                    std::cout << "[+] Record purged out cleanly.\n";
                }
                else 
                {std::cout << "[-] Error: Identification entry missing inside storage.\n";}
                break;
            }
            default:
                std::cout << "[!] Choice out of range. Provide an option code from 1 to 6.\n";
                }
                }
                std::cout << "\nClosing environment database stream engine safely.\n";
                return 0;
            }
