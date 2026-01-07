#include "TaskManager.h"
#include "Task.h"
#include "Person.h"
#include "SortedList.h"

TaskManager::TaskManager() : num_of_workers(0) {}

int TaskManager::find_person(const string &personName) {
    for (int i = 0; i < MAX_PERSONS; i++) {
        if (workers[i].getName() == personName) {
            return i;
        }
    }
    return -1;
}

void TaskManager::assignTask(const string& name, const Task& task) {
    int personIndex = find_person(name);
    Task newTask = task;
    newTask.setId(id++);
    if (personIndex == -1) {
        if (num_of_workers >= MAX_PERSONS) {
            throw std::runtime_error("TaskManager is FULL");
        }
       workers[num_of_workers] = Person(name);
       personIndex = num_of_workers;
       num_of_workers++;
    }
    workers[personIndex].assignTask(newTask);
}

void TaskManager::completeTask(const string &personName) {
    int person_num = find_person(personName);
    if (person_num != -1)
        workers[person_num].completeTask();
}

void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    if (priority < 0) {
        return;
    }
    for (int i = 0; i < num_of_workers; i++) {
        SortedList<Task> new_tasks;
        const SortedList<Task> &tasks = workers[i].getTasks();
        for (SortedList<Task>::ConstIterator it = tasks.begin(); it != tasks.end(); ++it) {
            Task curr_task = (*it);
            if (curr_task.getType() == type) {
                Task new_task(curr_task.getPriority() + priority, curr_task.getType(), curr_task.getDescription());
                new_task.setId(curr_task.getId());
                new_tasks.insert(new_task);
            } else {
                new_tasks.insert(curr_task);
            }
        }
        workers[i].setTasks(new_tasks);
    }
}

void TaskManager::printAllEmployees() const {
    for (int i = 0; i < num_of_workers; i++) {
        std::cout << workers[i] << std::endl;
    }
}

void TaskManager::printAllTasks() const {
    SortedList<Task> allTasks;

    for (int i = 0; i < num_of_workers; i++) {
        const SortedList<Task>& personTasks = workers[i].getTasks();
        for (const Task& task : personTasks) {
            allTasks.insert(task);
        }
    }

    for (const Task& task : allTasks) {
        std::cout << task << std::endl;
    }
}

void TaskManager::printTasksByType(TaskType type) const {
    SortedList<Task> to_print;
    for (int i = 0; i < num_of_workers; i++) {
        const SortedList<Task> &tasks = workers[i].getTasks();
        for (SortedList<Task>::ConstIterator it = tasks.begin(); it != tasks.end(); ++it) {

            if ((*it).getType() == type) {
                to_print.insert(*it);
            }
        }
    }
    for (SortedList<Task>::ConstIterator it = to_print.begin(); it != to_print.end(); ++it) {
        std::cout << *it << std::endl;
    }
}
