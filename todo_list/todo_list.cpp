#include<bits/stdc++.h>

using namespace std;

class Task {
protected:
    string description;
    bool completed;

public:
    Task(const string& desc) : description(desc), completed(false) {}

    virtual ~Task() {} // Virtual destructor to make the class polymorphic

    void markAsCompleted() {
        completed = true;
    }

    string getDescription() const {
        return description;
    }

    bool isCompleted() const {
        return completed;
    }
};

// Subclass for tasks with due dates
class DatedTask : public Task {
private:
    string dueDate;

public:
    DatedTask(const string& desc, const string& due) : Task(desc), dueDate(due) {}

    string getDueDate() const {
        return dueDate;
    }

    ~DatedTask() {}
};

class ToDoList {
private:
    vector<Task> tasks;

public:
    void addTask(const string& desc, const string& due = "") {
        if (due.empty()) {
            tasks.push_back(Task(desc));
        } else {
            tasks.push_back(DatedTask(desc, due));
        }
    }

    void markTaskAsCompleted(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].markAsCompleted();
            displayTasks(); // Display the updated list after marking a task as completed
        } else {
            cout << "Invalid task index." << endl;
        }
    }

    void displayTasks() const {
    int count = 0;
    cout << "To-Do List:" << endl;
    for (vector<Task>::const_iterator it = tasks.begin(); it != tasks.end(); ++it) {
        cout << (it - tasks.begin() + 1) << ". ";
        if (it->isCompleted()) {
            cout << "[X] ";
            count++;
        } else {
            cout << "[ ] ";
        }
        cout << it->getDescription();
        if (const DatedTask* dt = dynamic_cast<const DatedTask*>(&(*it))) { // Check if task is of DatedTask type
            cout << " (Due: " << dt->getDueDate() << ")";
        }
        cout << endl;
    }
    cout << "Progress is: " << ((double)count / tasks.size()) * 100 << "%" << endl;
}

};

int main() {
    ToDoList myToDoList;
    string taskDescription, dueDate;

    char choice;
    do {
        cout << "Enter task description: ";
        getline(cin, taskDescription);
        cout << "Enter due date (optional, press Enter if none): ";
        getline(cin, dueDate);
        myToDoList.addTask(taskDescription, dueDate);

        do {
            cout << "Do you want to add another task? (y/n): ";
            cin >> choice;
            cin.ignore(); // Clear the newline character from the input buffer

            if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
                cout << "Invalid move. Please enter 'y' or 'n'." << endl;
            }
        } while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N');

    } while (choice == 'y' || choice == 'Y');

    myToDoList.displayTasks();

    int taskIndex;
    do {
        cout << "Enter the index of the task you want to mark as done (0 to exit): ";
        cin >> taskIndex;
        if (taskIndex != 0) {
            myToDoList.markTaskAsCompleted(taskIndex - 1); // Subtract 1 to convert to 0-based index
        }
    } while (taskIndex != 0);

    return 0;
}