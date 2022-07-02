#include "forward_lista.hpp"
#include <iostream>
#include <string>

int generateId()
{
    static int counter = 0;
    return ++counter;
}

class ToDoTask
{
    int id_;
    std::string naslov_;
    std::string opis_;
    int prioritet_;

public:
    int GetId() const
    {
        return id_;
    }
    std::string Getnaslov() const
    {
        return naslov_;
    }
    std::string Getopis() const
    {
        return opis_;
    }
    int Getprioritet() const
    {
        return prioritet_;
    }
    ToDoTask() = default;
    ToDoTask(int id, std::string naslov, std::string opis, int prioritet) : id_{id}, naslov_{naslov}, opis_{opis}, prioritet_{prioritet} {}
    bool operator<(const ToDoTask &other) const
    {
        return prioritet_ < other.prioritet_;
    }
    bool operator>(const ToDoTask &other) const
    {
        return prioritet_ > other.prioritet_;
    }
    bool operator>=(const ToDoTask &other) const
    {
        return prioritet_ >= other.prioritet_;
    }
};

std::ostream &operator<<(std::ostream &out, const ToDoTask &other)
{
    out << "********\n"
        << "* Task *\n"
        << "********\n"
        << "Title: " << other.Getnaslov() << '\n'
        << "Description: " << other.Getopis() << '\n'
        << "Priotity: " << other.Getprioritet() << '\n';
    return out;
}

bool postoji(forwards_lista<ToDoTask> &taskovi, int izbor)
{
    for (auto i = 0; i < taskovi.size(); i++)
    {
        if (taskovi.at(i).GetId() == izbor)
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char const *argv[])
{
    forwards_lista<ToDoTask> taskovi;
    int izbor;
    while (1)
    {
        std::cout << "Choose one of the options" << std::endl;
        std::cout << "***************************************" << std::endl;
        std::cout << "1.Display the current list of ToDoTask" << std::endl;
        std::cout << "2.Enter a new ToDoTask" << std::endl;
        std::cout << "3.Mark ToDoTast as done" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> izbor;
        std::cout << "***************************************" << std::endl;

        if (izbor == 1)
        {
            if (taskovi.size() == 0)
            {
                std::cout << "Your notes is empty" << std::endl;
                std::cout << "Enter number 0 to exit program,or something else to continue:";
                std::cin >> izbor;
                if (izbor == 0)
                    break;
                else
                    continue;
            }
            else
            {
                for (auto i : taskovi)
                {
                    std::cout << i << std::endl;
                }
                std::cout << "Enter number 0 to exit program,or something else to continue:";
                std::cin >> izbor;
                if (izbor == 0)
                    break;
                else
                    continue;
            }
        }
        else if (izbor == 2)
        {
            std::cout << "Enter a new ToDoTask: " << std::endl;
            std::string naslov, opis, trash;
            int prioritet;
            std::cin.ignore(1);
            std::cout << "Enter the title of the task: ";
            std::getline(std::cin, naslov);
            std::cout << "Enter the description of the task: ";
            std::getline(std::cin, opis);
            std::cout << "Enter a priority(>0): ";
            std::cin >> prioritet;
            std::cin.clear();
            ToDoTask task(generateId(), naslov, opis, prioritet);
            taskovi.add(task);
            std::cout << "Enter number 0 to exit program,or something else to continue:";
            std::cin >> izbor;
            if (izbor == 0)
                break;
            else
                continue;
        }
        else
        {
            if (taskovi.size() == 0)
            {
                std::cout << "Your notes is empty" << std::endl;
                std::cout << "Enter number 0 to exit program,or something else to continue:";
                std::cin >> izbor;
                if (izbor == 0)
                    break;
                else
                    continue;
            }
            else
            {
                std::cout << "***************************************" << std::endl;
                for (auto i = 0; i < taskovi.size(); i++)
                {
                    std::cout << "Title: " << taskovi.at(i).Getnaslov() << std::endl;
                    std::cout << "Description: " << taskovi.at(i).Getopis() << std::endl;
                    std::cout << "Priority: " << taskovi.at(i).Getprioritet() << std::endl;
                    std::cout << "Id: " << taskovi.at(i).GetId() << '\n'
                              << std::endl;
                }
                std::cout << "***************************************" << std::endl;
                std::cout << "Enter id of the task which you want to mark as done: ";
                std::cin.clear();
                std::cin >> izbor;
                std::cout << std::endl;
                if (postoji(taskovi, izbor))
                {
                    taskovi.remove(taskovi.find([&](const ToDoTask &a)
                                                { return a.GetId() == izbor; }));
                }
                else
                {
                    std::cout << "Task with id " << izbor << " does not exist" << std::endl;
                }
            }
        }
    }
    return 0;
}
