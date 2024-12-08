#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <fstream>
#include <sstream>

class Task{
    public:
    Task(int i, std::string n)
    {
        id = i;
        name = n;
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm local_time = *std::localtime(&now_time);
        std::ostringstream oss;
        oss << std::put_time(&local_time, "%d.%m.%Y at %I:%M%p");
        creation_date = oss.str();
    }
    Task(int i, std::string n, std::string d)
    {
        id = i;
        if (n.size() != 0 && n.size() <= 40)
        {
            name = n;
        }
        creation_date = d;
    }
    std::string get_name()
    {
        return name;
    }
    int get_id()
    {
        return id;
    }
    void set_id(int i)
    {
        id = i;
    }
    std::string get_creation_date()
    {
        return creation_date;
    }
    private:
    int id;
    std::string name;
    std::string creation_date;
};

void display_tasks(std::vector<Task>& tasks)
{
    for (int i = 0; i < tasks.size(); i++)
    {
        std::cout << "[" << tasks[i].get_id() << "] " << tasks[i].get_name() << " | " << tasks[i].get_creation_date() << "\n";
    }
}

void save_ids(std::vector<Task>& tasks)
{
    std::ofstream ids("ids.txt");
    int id;
    for (int i = 0; i < tasks.size(); i++)
    {
        id = tasks[i].get_id();
        ids << id << "\n";
    }
    ids.close();
}

void save_names(std::vector<Task>& tasks)
{
    std::ofstream names("names.txt");
    std::string name;
    for (int i = 0; i < tasks.size(); i++)
    {
        name = tasks[i].get_name();
        names << name << "\n";
    }
    names.close();
}

void save_dates(std::vector<Task>& tasks)
{
    std::ofstream dates("dates.txt");
    std::string date;
    for (int i = 0; i < tasks.size(); i++)
    {
        date = tasks[i].get_creation_date();
        dates << date << "\n";
    }
    dates.close();
}

void save_tasks(std::vector<Task>& tasks)
{
    save_ids(tasks);
    save_names(tasks);
    save_dates(tasks);
}

std::vector<int> load_ids()
{
    std::ifstream ids("ids.txt");
    std::vector<int> i_vec;
    int id;
    while (ids >> id)
    {
        i_vec.push_back(id);
    }
    ids.close();
    return i_vec;
}

std::vector<std::string> load_names()
{
    std::ifstream names("names.txt");
    std::vector<std::string> n_vec;
    std::string name;
    while (std::getline(names, name))
    {
        n_vec.push_back(name);
    }
    names.close();
    return n_vec;
}

std::vector<std::string> load_dates()
{
    std::ifstream dates("dates.txt");
    std::vector<std::string> d_vec;
    std::string date;
    while (std::getline(dates, date))
    {
        d_vec.push_back(date);
    }
    dates.close();
    return d_vec;
}

void load_tasks(std::vector<Task>& tasks)
{
    std::vector<int> i_vec = load_ids();
    std::vector<std::string> n_vec = load_names();
    std::vector<std::string> d_vec = load_dates();
    for (int i = 0; i < i_vec.size(); i++)
    {
        int id = i_vec[i];
        std::string name = n_vec[i];
        std::string date = d_vec[i];
        Task task(id,name,date);
        tasks.push_back(task);
    }
}

void add_task(std::vector<Task>& tasks, std::string name, int& u_id)
{
    int id = u_id;
    Task task(id,name);
    tasks.push_back(task);
    u_id++;
    save_tasks(tasks);
}

void remove_task(std::vector<Task>& tasks, int id)
{
    for (int i = 0; i < tasks.size(); i++)
    {
        if (tasks[i].get_id() > id)
        {
            tasks[i].set_id(tasks[i].get_id()-1);
        }
    }
    tasks.erase(tasks.begin() + id);
    save_tasks(tasks);
}

int main()
{
    std::vector<Task> tasks;
    load_tasks(tasks);
    int unique_id = tasks.size();
    int action;
    std::cout << "Welcome to Task Management Tool!\n";
    std::cout << "What do you want to do?\n1. Display tasks [1]\n2. Add task [2]\n3. Remove task [3]\n4. Exit [4]\n";
    while(true)
    {
        std::cout << "Action: ";
        std::cin >> action;
        if(std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid operation!\n";
        }
        else
        {
            if (action == 1)
            {
                display_tasks(tasks);
            }
            else if(action == 2)
            {
                std::string a_name;
                std::cout << "Enter a name: ";
                std::cin.ignore();
                std::getline(std::cin, a_name);
                add_task(tasks, a_name, unique_id);
            }
            else if(action == 3)
            {
                int r_id;
                std::cout << "Enter id: ";
                std::cin >> r_id;
                remove_task(tasks,r_id);
            }
            else if(action == 4)
            {
                exit(0);
            }
        }
    }
    return 0;
}