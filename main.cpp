#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

// Structure to store expense details
struct Expense {
    string category;
    double amount;
    string description;
};

// Function prototypes
void addExpense(vector<Expense> &expenses);
void viewExpenses(const vector<Expense> &expenses);
double calculateTotal(const vector<Expense> &expenses);
void saveToFile(const vector<Expense> &expenses, const string &filename);
void loadFromFile(vector<Expense> &expenses, const string &filename);

int main() {
    vector<Expense> expenses;
    string filename = "expenses.txt";

    // Load existing data from file
    loadFromFile(expenses, filename);

    int choice;
    do {
        cout << "\n===== Expense Tracker =====\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Calculate Total Expenses\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addExpense(expenses);
                break;
            case 2:
                viewExpenses(expenses);
                break;
            case 3:
                cout << "Total Expenses: $" << fixed << setprecision(2) << calculateTotal(expenses) << endl;
                break;
            case 4:
                saveToFile(expenses, filename);
                cout << "Data saved. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}

// Function to add a new expense
void addExpense(vector<Expense> &expenses) {
    Expense newExpense;
    cout << "Enter category: ";
    cin >> newExpense.category;
    cout << "Enter amount: $";
    cin >> newExpense.amount;
    cin.ignore(); // Ignore leftover newline character
    cout << "Enter description: ";
    getline(cin, newExpense.description);

    expenses.push_back(newExpense);
    cout << "Expense added successfully.\n";
}

// Function to view all expenses
void viewExpenses(const vector<Expense> &expenses) {
    if (expenses.empty()) {
        cout << "No expenses to display.\n";
        return;
    }

    cout << "\nExpenses:\n";
    cout << left << setw(15) << "Category" << setw(10) << "Amount" << "Description\n";
    cout << "----------------------------------------\n";

    for (const auto &expense : expenses) {
        cout << left << setw(15) << expense.category
             << "$" << setw(9) << fixed << setprecision(2) << expense.amount
             << expense.description << endl;
    }
}

// Function to calculate total expenses
double calculateTotal(const vector<Expense> &expenses) {
    double total = 0;
    for (const auto &expense : expenses) {
        total += expense.amount;
    }
    return total;
}

// Function to save expenses to a file
void saveToFile(const vector<Expense> &expenses, const string &filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Error saving data to file.\n";
        return;
    }

    for (const auto &expense : expenses) {
        file << expense.category << "," << expense.amount << "," << expense.description << "\n";
    }

    file.close();
}

// Function to load expenses from a file
void loadFromFile(vector<Expense> &expenses, const string &filename) {
    ifstream file(filename);
    if (!file) {
        // File doesn't exist, so no data to load
        return;
    }

    Expense expense;
    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);

        expense.category = line.substr(0, pos1);
        expense.amount = stod(line.substr(pos1 + 1, pos2 - pos1 - 1));
        expense.description = line.substr(pos2 + 1);

        expenses.push_back(expense);
    }

    file.close();
}