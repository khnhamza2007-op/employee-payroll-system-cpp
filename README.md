# 💼 Employee Payroll System in C++

A console-based **payroll management program** written in C++. It takes employee details, calculates allowances and deductions, prints a salary slip for every employee, saves a summary to a file, and ranks employees by net salary.

Employee records are stored using **dynamic memory allocation** (`new` / `delete[]`), so the program uses exactly as much memory as the number of employees you enter.

> Built by **Hamza Khan**, Computer Engineering student at Usman Institute of Technology (UIT), as a C++ programming project.

---

## ✨ Features

- Enter any number of employees (memory is allocated at run time)
- Automatic calculation of **HRA, DA, gross salary, deductions and net salary**
- Neatly formatted **salary slip** for each employee
- Saves a payroll summary to `payroll.txt` (file handling)
- Sorts employees by **net salary, highest to lowest**
- Input validation (no negative salaries, days worked limited to 0–30, bad input is re-asked)
- Supports names with spaces, like `Ali Raza`
- Memory is safely released with `delete[]` at the end

---

## 🧮 Salary Rules

| Item | Formula |
|------|---------|
| HRA (House Rent Allowance) | 20% of basic salary |
| DA (Dearness Allowance) | 10% of basic salary |
| Gross Salary | Basic + HRA + DA |
| Absent days | 30 − days worked |
| Deductions | 10% of basic salary if absent for **more than 2 days**, otherwise 0 |
| **Net Salary** | Gross Salary − Deductions |

The rates are constants at the top of `main.cpp`, so they are easy to change.

---

## 🧠 How Dynamic Memory Is Used

A normal array like `Employee emp[100]` always reserves space for 100 employees, even if you only have 3. It is like booking a 100-seat hall for a dinner of 3 people.

This project instead asks the user for `n` first and then reserves exactly that much space:

```cpp
Employee *emp = new Employee[n];   // allocate memory at run time
// ... use emp[i] like a normal array ...
delete[] emp;                       // give the memory back
emp = nullptr;
```

If the system cannot provide the memory, the program catches `bad_alloc` and exits with a clear message instead of crashing.

---

## 🚀 Getting Started

### Requirements
- A C++ compiler such as **g++** (C++11 or later)

### Clone, compile and run

```bash
git clone https://github.com/<your-username>/employee-payroll-system-cpp.git
cd employee-payroll-system-cpp

g++ main.cpp -o payroll
./payroll          # on Windows: payroll.exe
```

---

## 🖥️ Sample Run

**Input**
```
Enter number of employees: 2

Enter Details of Employee 1
ID: 101
Name: Ali Raza
Designation: Manager
Basic Salary: 50000
Days Worked (out of 30): 28

Enter Details of Employee 2
ID: 102
Name: Sara
Designation: Engineer
Basic Salary: 40000
Days Worked (out of 30): 25
```

**Output**
```
================================
        SALARY SLIP
================================
ID: 101
Name: Ali Raza
Designation: Manager
Basic Salary: 50000.00
HRA (20%): 10000.00
DA (10%): 5000.00
Gross Salary: 65000.00
Deductions: 0.00
Net Salary: 65000.00
================================

================================
        SALARY SLIP
================================
ID: 102
Name: Sara
Designation: Engineer
Basic Salary: 40000.00
HRA (20%): 8000.00
DA (10%): 4000.00
Gross Salary: 52000.00
Deductions: 4000.00
Net Salary: 48000.00
================================

Employees Sorted By Net Salary (Highest to Lowest)
101 - Ali Raza - 65000.00
102 - Sara - 48000.00
```

**Generated file `payroll.txt`**
```
ID: 101, Name: Ali Raza, Designation: Manager, Net Salary: 65000.00
ID: 102, Name: Sara, Designation: Engineer, Net Salary: 48000.00
```

---

## 📚 Concepts Covered

- Structures (`struct`)
- Functions and pass by reference / `const` reference
- **Dynamic memory allocation** (`new`, `delete[]`, `nullptr`)
- Exception handling (`try` / `catch` with `bad_alloc`)
- File handling (`ofstream`)
- Sorting (bubble sort)
- Input validation and `getline`

---

## 📁 Project Structure

```
employee-payroll-system-cpp/
├── main.cpp       # Complete source code
├── README.md
├── LICENSE
└── .gitignore
```

---

## 🔮 Future Improvements

- Read and write employee data so records are kept between runs
- Search, update and delete employee records
- Menu-driven interface
- Replace raw arrays with `std::vector`
- Tax slabs and overtime pay

---

## 👤 Author

**Hamza Khan**
Computer Engineering, Usman Institute of Technology (UIT)

Feel free to fork this project or open an issue. ⭐ Star the repo if it helped you!
