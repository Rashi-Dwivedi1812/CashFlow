#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <iomanip>

using namespace std;

// Structure to hold cash flow entry
struct CashFlowEntry
{
    string description;
    double amount;
    string date;
    string name;
    CashFlowEntry *next;

    CashFlowEntry(string nm, string desc, double amt, string dt)
    {
        name = nm;
        description = desc;
        amount = amt;
        date = dt;
        next = nullptr; // Initialize next to nullptr
    }
};

// Class for managing cash flow
class CashFlowApp
{
private:
    CashFlowEntry *head;

public:
    CashFlowApp()
    {
        head = nullptr;
    }

// ADDING DETAILS/////////////////////////////////////////////////////////////////////////////////////////////
    void addEntry(const string &name, const string &description, double amount, const string &date)
    {
        CashFlowEntry *newEntry = new CashFlowEntry(name, description, amount, date);
        if (!head)
        {
            head = newEntry;
        }
        else
        {
            CashFlowEntry *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newEntry;
        }
        cout << endl;
        cout << "Entry added: " << name << " paid for " << description << " Rs." << amount << " on " << date << endl;
    }
// DISPLAY DETAILS //////////////////////////////////////////////////////////////////////////////////////////////////
    void displayEntries()
    {
        if (!head)
        {
            cout << "No entries found." << endl;
            return;
        }

        CashFlowEntry *temp = head;
        cout << "\nCash Flow Entries:\n";
        while (temp)
        {
            cout << "Name: " << temp->name
                 << " | Description: " << temp->description
                 << " | Amount: " << temp->amount
                 << " | Date: " << temp->date << endl;
            temp = temp->next;
        }
    }
// SAVE TO FILE ///////////////////////////////////////////////////////////////////////////////////////////
    void saveToFile(const string &filename)
    {
        ofstream outFile(filename);
        if (!outFile)
        {
            cout << "\nError opening file for writing.\n"
                 << endl;
            return;
        }

        CashFlowEntry *temp = head;
        while (temp)
        {
            outFile << temp->name << " paid for "
                    << temp->description << " Rs."
                    << temp->amount << " on "
                    << temp->date << "\n";
            temp = temp->next;
        }

        outFile.close();
        cout << "Entries saved to " << filename << endl;
    }

// LOAD FROM FILE ///////////////////////////////////////////////////////////////////////////
    void loadFromFile(const string &filename)
    {
        ifstream inFile(filename);
        if (!inFile)
        {
            cout << "Error opening file for reading." << endl;
            return;
        }

        while (!inFile.eof())
        {
            string name, description, date;
            double amount;
            getline(inFile, name);
            getline(inFile, description);
            inFile >> amount;
            inFile.ignore(); // Ignore newline character
            getline(inFile, date);

            if (!name.empty() && !description.empty() && amount >= 0 && !date.empty())
            {
                addEntry(name, description, amount, date);
            }
        }

        inFile.close();
        cout << "\nEntries loaded from " << filename << "\n"
             << endl;
    }

    //  SEARCH AND EDIT ///////////////////////////////////////////////////////////////
    void searchAndEditEntry(const string &name)
    {
        if (!head)
        {
            cout << "No entries found to search." << endl;
            return;
        }

        CashFlowEntry *temp = head;
        bool found = false;

        while (temp)
        {
            if (temp->name == name)
            {
                found = true;
                cout << "\nFound Entry:\n";
                cout << "Name: " << temp->name
                     << " | Description: " << temp->description
                     << " | Amount: Rs." << fixed << setprecision(2) << temp->amount
                     << " | Date: " << temp->date << endl;

                // Editing options
                int choice;
                cout << "\nDo you want to edit this entry? (1-Yes, 2-No): ";
                cin >> choice;

                if (choice == 1)
                {
                    cout << "Enter new description (or press Enter to keep unchanged): ";
                    cin.ignore();
                    string newDescription;
                    getline(cin, newDescription);

                    cout << "Enter new amount (or -1 to keep unchanged): ";
                    double newAmount;
                    cin >> newAmount;

                    cout << "Enter new date (or press Enter to keep unchanged): ";
                    cin.ignore();
                    string newDate;
                    getline(cin, newDate);

                    // Update fields if new values are provided
                    if (!newDescription.empty())
                        temp->description = newDescription;
                    if (newAmount >= 0)
                        temp->amount = newAmount;
                    if (!newDate.empty())
                        temp->date = newDate;

                    cout << "\nEntry updated successfully.\n";
                }
                break;
            }
            temp = temp->next;
        }

        if (!found)
        {
            cout << "\nNo entry found for the name: " << name << endl;
        }
    }


    ~CashFlowApp()
    {
        CashFlowEntry *temp;
        while (head)
        {
            temp = head;
            head = temp->next;
            delete temp;
        }
    }
};

// TO BE PAID ////////////////////////////////////////////////////////////////////////
void to_be_paid(vector<string> &name, vector<int> &amount)
{
    int n = name.size();
    vector<float> v;
    for (int i = 0; i < n; i++)
    {
        float el = amount[i] / n;
        v.push_back(el);
    }
    cout << "\nAmounts to be paid:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << name[i] << " has to get Rs." << v[i] << endl;
    }
    cout << endl;
}


// TRANSACTION ////////////////////////////////////////////////////////////////////
void transaction(vector<string> &name, vector<int> &amount)
{
    int n = name.size();
    vector<float> v;
    for (int i = 0; i < n; i++)
    {
        float el = amount[i] / n;
        v.push_back(el);
    }
    cout << "\nTransactions:" << endl;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (i != j)
            {
                int am = v[i] - v[j];
                if (am < 0)
                {
                    cout << name[i] << " has to pay Rs." << abs(am) << " to " << name[j] << endl;
                }
                else if(am > 0)
                {
                    cout << name[j] << " has to pay Rs." << abs(am) << " to " << name[i] << endl;
                }
            }
        }
    }
    cout << endl;
}

int main()
{
    CashFlowApp app;
    int choice;
    string description, date, name;
    double amount;
    string filename = "entry.txt";
    vector<int> money;
    vector<string> mem;
    int n = 0;

    do
    {
        cout << "\n--- Cash Flow App ---\n";
        cout << "1. Add Cash Flow Entry\n";
        cout << "2. Display Cash Flow Entries\n";
        cout << "3. Load Entries from File\n";
        cout << "4. Display The Amount to be Paid\n";
        cout << "5. Display Transactions\n";
        cout << "6. Search and Edit Entry\n";
        cout << "7. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (n == 0)
            {
                cout << "Enter the name:";
                cin.ignore();
                getline(cin, name);
                mem.push_back(name);
                cout << "Enter description: ";
                //  cin.ignore();
                getline(cin, description);
                cout << "Enter amount: ";
                cin >> amount;
                if (amount < 0)
                {
                    cout << " invalid input " << endl;
                    exit(0);
                }
                money.push_back(amount);
                cout << "Enter date (DD/MM/YYYY): ";
                cin.ignore();
                bool slash = true;

                while (slash)
                {
                    getline(cin, date);

                    // Ensure the date length is exactly 10
                    if (date.length() != 10)
                    {
                        cout << "Error happened!" << endl
                             << "Invalid date format ;(" << endl;
                        exit(0);
                    }

                    // Validate day digits
                    if (!isdigit(date[0]) || !isdigit(date[1]))
                    {
                        cout << "Error happened!" << endl
                             << "Invalid date format ;(" << endl;
                        exit(0);
                    }

                    // Validate '/' separators
                    if (date[2] != '/' || date[5] != '/')
                    {
                        cout << "Error happened!" << endl
                             << "Invalid date format ;(" << endl;
                        exit(0);
                    }

                    // Validate month digits
                    if (!isdigit(date[3]) || !isdigit(date[4]))
                    {
                        cout << "Error happened!" << endl
                             << "Invalid date format ;(" << endl;
                        exit(0);
                    }

                    // Validate year digits
                    if (!isdigit(date[6]) || !isdigit(date[7]) || !isdigit(date[8]) || !isdigit(date[9]))
                    {
                        cout << "Error happened!" << endl
                             << "Invalid date format ;(" << endl;
                        exit(0);
                    }

                    // Convert parts to integers for further validation
                    int day = stoi(date.substr(0, 2));
                    int month = stoi(date.substr(3, 2));
                    int year = stoi(date.substr(6, 4));

                    // Validate day range
                    if (day < 1 || day > 31)
                    {
                        cout << "Error happened!" << endl
                             << "Invalid date format ;(" << endl;
                        exit(0);
                    }

                    // Validate month range
                    if (month < 1 || month > 12)
                    {
                        cout << "Error happened!" << endl
                             << "Invalid date format ;(" << endl;
                        exit(0);
                    }

                    slash = false;
                }

                cout << "Valid date format!" << endl;
                app.addEntry(name, description, amount, date);
                cout << endl;
                n++;
                //cout << "Enter filename to load entries: ";
                //  cin >> filename;
                app.saveToFile(filename);
                break;
            }
            else
            {
                cout << "Enter the name:";
                cin.ignore();
                getline(cin, name);
                cout << "Enter description: ";
                //     cin.ignore();
                getline(cin, description);
                cout << "Enter amount: ";
                cin >> amount;
                if (amount < 0)
                {
                    cout << " invalid input " << endl;
                    exit(0);
                }
                cout << "Enter date (DD/MM/YYYY): ";
                cin.ignore();
                bool slash = true;

                while (slash)
                {
                    getline(cin, date);

                    // Ensure the date length is exactly 10
                    if (date.length() != 10)
                    {
                        cout << "Error happened!" << endl
                             << "Invalid date format ;(" << endl;
                        exit(0);
                    }

                    // Validate day digits
                    if (!isdigit(date[0]) || !isdigit(date[1]))
                    {
                        cout << "Error happened!" << endl
                             << "Invalid date format ;(" << endl;
                        exit(0);
                    }

                    // Validate '/' separators
                    if (date[2] != '/' || date[5] != '/')
                    {
                        cout << "Error happened!" << endl
                             << "Invalid date format ;(" << endl;
                        exit(0);
                    }

                    // Validate month digits
                    if (!isdigit(date[3]) || !isdigit(date[4]))
                    {
                        cout << "Error happened!" << endl
                             << "Invalid date format ;(" << endl;
                        exit(0);
                    }

                    // Validate year digits
                    if (!isdigit(date[6]) || !isdigit(date[7]) || !isdigit(date[8]) || !isdigit(date[9]))
                    {
                        cout << "Error happened!" << endl
                             << "Invalid date format ;(" << endl;
                        exit(0);
                    }

                    // Convert parts to integers for further validation
                    int day = stoi(date.substr(0, 2));
                    int month = stoi(date.substr(3, 2));
                    int year = stoi(date.substr(6, 4));

                    // Validate day range
                    if (day < 1 || day > 31)
                    {
                        cout << "Error happened!" << endl
                             << "Invalid date format ;(" << endl;
                        exit(0);
                    }

                    // Validate month range
                    if (month < 1 || month > 12)
                    {
                        cout << "Error happened!" << endl
                             << "Invalid date format ;(" << endl;
                        exit(0);
                    }

                    slash = false;
                }

                cout << "Valid date format!" << endl;
                app.addEntry(name, description, amount, date);
                cout << endl;
                /*  cout << "Enter filename to load entries: ";
                cin >> filename;*/
                app.saveToFile(filename);

                int o = 0;
                for (int i = 0; i < n; i++)
                {
                    if (name == mem[i])
                    {
                        money[i] += amount;
                        o++;
                    }
                }
                if (o == 0)
                {
                    mem.push_back(name);
                    money.push_back(amount);
                    n++;
                }
                break;
            }
            break;
        case 2:
            app.displayEntries();
            break;

        case 3:
        {
            app.loadFromFile(filename);
            break;
        }
        case 4:
        {
            cout << endl;
            cout << "details of amount to be paid." << endl;
            to_be_paid(mem, money);
            break;
        }
        case 5:
        {
            cout << endl;
            cout << "Transactions:" << endl;
            transaction(mem, money);
            break;
        }
        case 6:
        {
            cout << "Enter name to search and edit: ";
            cin.ignore();
            getline(cin, name);
            app.searchAndEditEntry(name);
            break;
        }
        case 7:
            cout << "....Exiting the application...." << endl;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    }
    while (choice != 7);

    return 0;
}
