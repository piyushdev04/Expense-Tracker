#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;


struct Expense {
    string category;
    double amount;
    string description;
};


void addExpense(vector<Expense> &expenses);
void viewExpenses(const vector<Expense> &expenses);
double calculateTotal(const vector<Expense> &expenses);
void saveToFile(const vector<Expense> &expenses, const string &filename);
void loadFromFile(vector<Expense> &expenses, const string &filename);
void editExpense(vector<Expense> &expenses);
void deleteExpense(vector<Expense> &expenses);
void filterByCategory(const vector<Expense> &expenses);
void sortExpensesByAmount(vector<Expense> &expenses, bool ascending = true);
void searchByDescription(const vector<Expense> &expenses);
void exportToCSV(const vector<Expense> &expenses);

int main() {
    vector<Expense> expenses;
    string filename = "expenses.txt";

    
    loadFromFile(expenses, filename);

    int choice;
    do {
        cout << "\n===== Expense Tracker =====\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Calculate Total Expenses\n";
        cout << "4. Exit\n";
        cout << "5. Edit Expense\n";
        cout << "6. Delete Expense\n";
        cout << "7. Filter Expernses by Category\n";
        cout << "8. Sort Expenses by Amount\n";
        cout << "9. Search Expenses by Description\n";
        cout << "10. Export to CSV\n";
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
            case 5:
                editExpense(expenses);
                break;
            case 6:
                deleteExpense(expenses);
                break;
            case 7:
                filterByCategory(expenses);
                break;
            case 8:
                sortExpensesByAmount(expenses);
                break;
            case 9:
                searchByDescription(expenses);
                break;
            case 10:
                exportToCSV(expenses);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}


void addExpense(vector<Expense> &expenses) {
    Expense newExpense;
    cout << "Enter category: ";
    cin >> newExpense.category;
    cout << "Enter amount: $";
    cin >> newExpense.amount;
    cin.ignore(); 
    cout << "Enter description: ";
    getline(cin, newExpense.description);

    expenses.push_back(newExpense);
    cout << "Expense added successfully.\n";
}


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


double calculateTotal(const vector<Expense> &expenses) {
    double total = 0;
    for (const auto &expense : expenses) {
        total += expense.amount;
    }
    return total;
}


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


void loadFromFile(vector<Expense> &expenses, const string &filename) {
    ifstream file(filename);
    if (!file) {
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

void editExpense(vector<Expense> &expenses){
    int index;
    cout << "Enter the index of the expense to edit: ";
    cin >> index;

    if (index < 0 || index >= expenses.size()) {
        cout << "Invalid index.\n";
        return;
    }

    cout << "Editing Expense at index" << index << ":\n";
    cout << "Currency Category: " << expenses[index].category << "\n";
    cout << "Currency Amount: $" << fixed << setprecision(2) << expenses[index].amount << "\n";
    cout << "Current Description: " << expenses[index].description << "\n";

    cout << "Enter new category: ";
    cin >> expenses[index].category;
    cout << "Enter new amount: $";
    cin >> expenses[index].amount;
    cin.ignore();
    cout << "Enter new description: ";
    getline(cin, expenses[index].description);

    cout << "Expense updated successfully.\n";
}

void deleteExpense(vector<Expense> &expenses) {
    int index;
    cout << "Enter the index of the expense to delete: ";
    cin >> index;

    if (index < 0 || index >= expenses.size()) {
        cout << "Invalid index.\n";
        return;
    }

    expenses.erase(expenses.begin() + index);
    cout << "Expense deleted successfully.\n";
}

void filterByCategory(const vector<Expense> &expenses) {
    string category;
    cout << "Enter category to filter by: ";
    cin >> category;

    bool found = false;
    cout << "\nFiltered Expenses:\n";
    cout << left << setw(15) << "Category" << setw(10) << "Amount" << "Description\n";
    cout << "-----------------------------------------\n";

    for (const auto &expense : expenses) {
        if (expense.category == category) {
            cout << left << setw(15) << expense.category
            << "$" << setw(9) << fixed << setprecision(2) << expense.amount
            << expense.description << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No expenses found for this category.\n";
    }
}

void sortExpensesByAmount(vector<Expense> &expenses, bool ascending) {
    sort(expenses.begin(), expenses.end(), [ascending](const Expense &a, const Expense &b) {
        return ascending ? a.amount < b.amount : a.amount > b.amount;
    });
    cout << "Expenses sorted successfully.\n";
}

void searchByDescription(const vector<Expense> &expenses) {
    string keyword;
    cout << "Enter description keyword to search: ";
    cin.ignore();
    getline(cin, keyword);

    bool found = false;
    cout << "\nSearch Results:\n";
    cout << left << setw(15) << "Category" << setw(10) << "Amount" << "Description\n";
    cout << "----------------------------------------\n";

    for (const auto &expense : expenses) {
        if (expense.description.find(keyword) != string::npos) {
            cout << left << setw(15) << expense.category
                 << "$" << setw(9) << fixed << setprecision(2) << expense.amount
                 << expense.description << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No expenses found matching the description.\n";
    }
}

void exportToCSV(const vector<Expense> &expenses) {
    string filename;
    cout << "Enter the filename to export to (e.g., expenses.csv): ";
    cin >> filename;

    ofstream file(filename);
    if (!file) {
        cout << "Error creating file.\n";
        return;
    }

    file << "Category,Amount,Description\n"; // CSV header
    for (const auto &expense : expenses) {
        file << expense.category << "," << expense.amount << "," << expense.description << "\n";
    }

    file.close();
    cout << "Data exported successfully.\n";
}