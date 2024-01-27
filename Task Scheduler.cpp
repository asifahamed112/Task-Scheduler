#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;
struct Task
{
    string title;
    string description;
    int date;
    int hour;
    int minute;
    int isComplete;
};

void displayTask(Task task)
{
    cout << "   Title: " << task.title << endl;
    cout << "   Description: " << task.description << endl;
    cout << "   Due Date: " << int(time(nullptr) / (60 * 60 * 24 * 365.25) + 1970) << "-" << int(time(nullptr) % (31557600)) / (2592000) + 1 << "-" << task.date << endl;
    if (task.hour >= 12)
    {
        int displayHour = task.hour % 12;
        cout << "   Due Time: " << displayHour << ":" << task.minute << " PM" << endl;
    }
    else
    {
        if (task.hour == 0)
            cout << "   Due Time: 12:" << task.minute << " AM" << endl;
        else
            cout << "   Due Time: " << task.hour << ":" << task.minute << " AM" << endl;
    }
    cout << endl;
}

void searchTasks(vector<Task> tasks, string keyword)
{
    int found = 0;
    for (int i = 0; i < tasks.size(); ++i)
    {
        Task task = tasks[i];
        if (task.title == keyword)
        {
            found = 1;
            if (tasks[i].isComplete == 1)
            {
                cout << "Task #" << i << " \xfb\xfb" << endl;
            }
            else
            {
                cout << "Task #" << i << endl;
            }
            displayTask(task);
        }
    }
    if (found == 0)
    {
        cout << "No tasks matching the keyword found." << endl;
    }
}
int main()
{
    vector<Task> tasks;
    fstream file("file.txt", ios::in);

    string title, description;
    int date, hour, minute, isComplete;
    while (getline(file, title) && getline(file, description) && file >> date >> hour >> minute >> isComplete)
    {
        file.ignore();
        Task task;
        task.title = title;
        task.description = description;
        task.date = date;
        task.hour = hour;
        task.minute = minute;
        task.isComplete = isComplete;
        tasks.push_back(task);
    }

    file.close();

    cout << "\t\t==================================================\n";
    cout << "\t\t\t Task Scheduler Menu \n";
    cout << "\t\t==================================================\n\n";
    while (1)
    {
        cout << "\t\t---------------------------------------------------\n";
        cout << "\t\t||\t1. Create Task \t\t\t\t ||\n";
        cout << "\t\t||\t2. Display Tasks\t\t\t ||\n";
        cout << "\t\t||\t3. Edit Task \t\t\t\t ||\n";
        cout << "\t\t||\t4. Delete Task\t\t\t\t ||\n";
        cout << "\t\t||\t5. Search Tasks \t\t\t ||\n";
        cout << "\t\t||\t6. Mark Task as Complete\t\t ||\n";
        cout << "\t\t||\t7. Exit\t\t\t\t\t ||\n";
        cout << "\t\t---------------------------------------------------\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            Task task;
            cout << "Enter task title: ";
            getline(cin, task.title);
            cout << "Enter task description: ";
            getline(cin, task.description);
            cout << "Enter due date (DD) 01-31: ";
            cin >> task.date;
            cout << "Enter due time (HH) 01-24: ";
            cin >> task.hour;
            cout << "Enter due time (MM) 01-60: ";
            cin >> task.minute;
            task.isComplete = 0;
            tasks.push_back(task);
            file.open("file.txt", ios::out | ios::app);
            if (file.is_open())
            {
                file << task.title << endl;
                file << task.description << endl;
                file << task.date << endl;
                file << task.hour << endl;
                file << task.minute << endl;
                file << task.isComplete << endl;
                file.close();
            }
            else
            {
                cout << "Error opening the file for writing!" << endl;
            }
            cout << "Task created successfully." << endl;
            break;
        }
        case 2:
        {
            if (tasks.empty())
            {
                cout << "No tasks to display." << endl;
            }
            else
            {
                cout << "-----------------------------" << endl;
                cout << "List of Tasks:" << endl
                     << endl;
                for (int i = 0; i < tasks.size(); i++)
                {
                    if (tasks[i].isComplete == 1)
                    {
                        cout << "Task #" << i << " \xfb\xfb" << endl;
                    }
                    else
                    {
                        cout << "Task #" << i << endl;
                    }
                    displayTask(tasks[i]);
                }
                cout << endl;
            }
            break;
        }

        case 3:
        {
            if (tasks.empty())
            {
                cout << "No tasks to edit." << endl;
            }
            else
            {
                cout << "-----------------------------" << endl;
                cout << "Title List of Tasks:" << endl
                     << endl;
                for (int i = 0; i < tasks.size(); i++)
                {
                    if (tasks[i].isComplete == 1)
                    {
                        cout << "Task #" << i << " \xfb\xfb" << endl;
                    }
                    else
                    {
                        cout << "Task #" << i << endl;
                    }
                    cout << "Title: " << tasks[i].title << endl
                         << endl;
                }
                int taskIndex;
                cout << "Enter the index of the task to edit: ";
                cin >> taskIndex;
                cin.ignore();
                if (taskIndex < 0 || taskIndex >= tasks.size())
                {
                    cout << "Invalid task index. Please try again." << endl;
                }
                else
                {
                    Task &task = tasks[taskIndex];
                    cout << "Enter task title: ";
                    getline(cin, task.title);
                    cout << "Enter task description: ";
                    getline(cin, task.description);
                    cout << "Enter due date (DD) 01-31: ";
                    cin >> task.date;
                    cout << "Enter due time (HH) 01-24: ";
                    cin >> task.hour;
                    cout << "Enter due time (MM) 01-60: ";
                    cin >> task.minute;

                    file.open("file.txt", ios::out);

                    if (file.is_open())
                    {
                        for (int i = 0; i < tasks.size(); i++)
                        {
                            file << tasks[i].title << endl;
                            file << tasks[i].description << endl;
                            file << tasks[i].date << endl;
                            file << tasks[i].hour << endl;
                            file << tasks[i].minute << endl;
                            file << tasks[i].isComplete << endl;
                        }
                        file.close();
                    }
                    else
                    {
                        cout << "Error opening the file for writing!" << endl;
                    }

                    cout << "Task updated successfully." << endl;
                }
            }
            break;
        }
        case 4:
        {
            if (tasks.empty())
            {
                cout << "No tasks to delete." << endl;
            }
            else
            {
                cout << "-----------------------------" << endl;
                cout << "Title List of Tasks:" << endl
                     << endl;
                for (int i = 0; i < tasks.size(); i++)
                {
                    if (tasks[i].isComplete == 1)
                    {
                        cout << "Task #" << i << " \xfb\xfb" << endl;
                    }
                    else
                    {
                        cout << "Task #" << i << endl;
                    }
                    cout << "Title: " << tasks[i].title << endl
                         << endl;
                }
                int taskIndex;
                cout << "Enter the index of the task to delete: ";
                cin >> taskIndex;
                cin.ignore();
                if (taskIndex < 0 || taskIndex >= tasks.size())
                {
                    cout << "Invalid task index. Please try again." << endl;
                }
                else
                {
                    tasks.erase(tasks.begin() + taskIndex);
                    file.open("file.txt", ios::out);

                    if (file.is_open())
                    {
                        for (int i = 0; i < tasks.size(); i++)
                        {
                            file << tasks[i].title << endl;
                            file << tasks[i].description << endl;
                            file << tasks[i].date << endl;
                            file << tasks[i].hour << endl;
                            file << tasks[i].minute << endl;
                            file << tasks[i].isComplete << endl;
                        }
                        file.close();
                    }
                    else
                    {
                        cout << "Error opening the file for writing!" << endl;
                    }
                    cout << "Task deleted successfully." << endl;
                }
            }
            break;
        }

        case 5:
        {
            string keyword;
            cout << "Enter a keyword to search for: ";
            getline(cin, keyword);
            searchTasks(tasks, keyword);
            break;
        }
        case 6:
        {
            if (tasks.empty())
            {
                cout << "No tasks available." << endl;
                break;
            }
            cout << "Title List of Tasks:" << endl
                 << endl;
            for (int i = 0; i < tasks.size(); i++)
            {
                if (tasks[i].isComplete == 1)
                {
                    cout << "Task #" << i << " \xfb\xfb" << endl;
                }
                else
                {
                    cout << "Task #" << i << endl;
                }
                cout << "Title: " << tasks[i].title << endl
                     << endl;
            }

            cout << "Enter the Task number to mark as a complete task: ";
            int taskNumber;
            cin >> taskNumber;
            cin.ignore();

            if (taskNumber < 0 || taskNumber >= tasks.size())
            {
                cout << "Invalid task number. Please try again." << endl;
            }
            else
            {
                tasks[taskNumber].isComplete = 1;
                cout << "Task marked as complete." << endl;

                file.open("file.txt", ios::out);

                if (file.is_open())
                {
                    for (int i = 0; i < tasks.size(); i++)
                    {
                        file << tasks[i].title << endl;
                        file << tasks[i].description << endl;
                        file << tasks[i].date << endl;
                        file << tasks[i].hour << endl;
                        file << tasks[i].minute << endl;
                        file << tasks[i].isComplete << endl;
                    }
                    file.close();
                }
                else
                {
                    cout << "Error opening the file for writing!" << endl;
                }
            }
            break;
        }

        case 7:
        {
            cout << "Exiting the task scheduler." << endl;
            return 0;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    file.close();
    return 0;
}