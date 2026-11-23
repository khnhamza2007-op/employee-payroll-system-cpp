#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>
#include <new>
using namespace std;

// ── Constants ────────────────────────────────────────────────
const float HRA_RATE          = 0.20f;  // House Rent Allowance = 20% of basic
const float DA_RATE           = 0.10f;  // Dearness Allowance   = 10% of basic
const float DEDUCTION_RATE    = 0.10f;  // Deduction            = 10% of basic
const int   WORKING_DAYS      = 30;     // Days in a month
const int   ALLOWED_ABSENCES  = 2;      // More than this -> deduction applies

// ── Employee record ──────────────────────────────────────────
struct Employee
{
    int id;
    string name;
    string designation;
    float basicSalary;
    int daysWorked;

    float hra;
    float da;
    float grossSalary;
    float deductions;
    float netSalary;
};

// ── Input helpers ────────────────────────────────────────────

// Clears a bad input state and throws away the rest of the line
void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Keeps asking until the user enters an int within [low, high]
int readInt(const string &prompt, int low, int high)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value && value >= low && value <= high)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Enter a number between " << low << " and " << high << ".\n";
        clearInput();
    }
}

// Keeps asking until the user enters a non-negative number
float readSalary(const string &prompt)
{
    float value;
    while (true)
    {
        cout << prompt;
        if (cin >> value && value >= 0)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Salary must be a non-negative number.\n";
        clearInput();
    }
}

// Reads a full line (so names like "Ali Raza" work)
string readText(const string &prompt)
{
    string text;
    do
    {
        cout << prompt;
        getline(cin, text);
    } while (text.empty());
    return text;
}

// ── Salary calculation ───────────────────────────────────────
void calculateSalary(Employee &e)
{
    e.hra = e.basicSalary * HRA_RATE;
    e.da  = e.basicSalary * DA_RATE;

    e.grossSalary = e.basicSalary + e.hra + e.da;

    int absentDays = WORKING_DAYS - e.daysWorked;

    if (absentDays > ALLOWED_ABSENCES)
        e.deductions = e.basicSalary * DEDUCTION_RATE;
    else
        e.deductions = 0;

    e.netSalary = e.grossSalary - e.deductions;
}

// ── Salary slip ──────────────────────────────────────────────
void generateSlip(const Employee &e)
{
    cout << "\n================================";
    cout << "\n        SALARY SLIP";
    cout << "\n================================";
    cout << "\nID: " << e.id;
    cout << "\nName: " << e.name;
    cout << "\nDesignation: " << e.designation;
    cout << "\nBasic Salary: " << e.basicSalary;
    cout << "\nHRA (20%): " << e.hra;
    cout << "\nDA (10%): " << e.da;
    cout << "\nGross Salary: " << e.grossSalary;
    cout << "\nDeductions: " << e.deductions;
    cout << "\nNet Salary: " << e.netSalary;
    cout << "\n================================\n";
}

// ── Bubble sort (highest net salary first) ───────────────────
void sortBySalary(Employee *emp, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (emp[j].netSalary < emp[j + 1].netSalary)
            {
                Employee temp = emp[j];
                emp[j] = emp[j + 1];
                emp[j + 1] = temp;
            }
        }
    }
}

// ── Main ─────────────────────────────────────────────────────
int main()
{
    cout << fixed << setprecision(2);

    int n = readInt("Enter number of employees: ", 1, 100000);

    // Dynamic memory allocation: the array size is decided at run time
    Employee *emp = nullptr;
    try
    {
        emp = new Employee[n];
    }
    catch (const bad_alloc &)
    {
        cout << "Error: not enough memory to store " << n << " employees.\n";
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter Details of Employee " << i + 1 << endl;

        emp[i].id          = readInt("ID: ", 1, numeric_limits<int>::max());
        emp[i].name        = readText("Name: ");
        emp[i].designation = readText("Designation: ");
        emp[i].basicSalary = readSalary("Basic Salary: ");
        emp[i].daysWorked  = readInt("Days Worked (out of 30): ", 0, WORKING_DAYS);

        calculateSalary(emp[i]);
    }

    ofstream file("payroll.txt");
    if (!file)
    {
        cout << "Warning: could not open payroll.txt for writing.\n";
    }
    file << fixed << setprecision(2);

    for (int i = 0; i < n; i++)
    {
        generateSlip(emp[i]);

        if (file)
        {
            file << "ID: " << emp[i].id
                 << ", Name: " << emp[i].name
                 << ", Designation: " << emp[i].designation
                 << ", Net Salary: " << emp[i].netSalary
                 << endl;
        }
    }

    file.close();

    sortBySalary(emp, n);

    cout << "\nEmployees Sorted By Net Salary (Highest to Lowest)\n";

    for (int i = 0; i < n; i++)
    {
        cout << emp[i].id << " - "
             << emp[i].name << " - "
             << emp[i].netSalary << endl;
    }

    // Free the dynamically allocated memory
    delete[] emp;
    emp = nullptr;

    return 0;
}
