#include "TaskManager.h"
#include "Task.h"
#include "Person.h"
#include "SortedList.h"

TaskManager::TaskManager() : num_of_workers(0) {
}

int TaskManager::find_person(const string &personName) {
    for (int i = 0; i < MAX_PERSONS; i++) {
        if (workers[i].getName() == personName) {
            return i;
        }
    }
    return -1;
}

void TaskManager::assignTask(const string &name, const Task &task) {
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
        const SortedList<Task> &tasks = workers[i].getTasks();
        SortedList<Task> new_tasks = tasks.apply(
            [type, priority](const Task &task) {
                if (task.getType() == type) {
                    Task new_task(task.getPriority() + priority, task.getType(),
                                  task.getDescription());
                    new_task.setId(task.getId());
                    return new_task;
                }
                    return task;
                }
                );
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
            const SortedList<Task> &personTasks = workers[i].getTasks();
            for (const Task &task: personTasks) {
                allTasks.insert(task);
            }
        }

        for (const Task &task: allTasks) {
            std::cout << task << std::endl;
        }
    }

    void TaskManager::printTasksByType(TaskType type) const {
        SortedList<Task> to_print;
        for (int i = 0; i < num_of_workers; i++) {
            SortedList<Task> filtered = workers[i].getTasks().filter([type](const Task& task) {
                return task.getType() == type;
            }
            );
            for (SortedList<Task>::ConstIterator it = filtered.begin();
                 it != filtered.end(); ++it) {
                    to_print.insert(*it);
            }
        }
        for (SortedList<Task>::ConstIterator it = to_print.begin();
             it != to_print.end(); ++it) {
            std::cout << *it << std::endl;
        }
    }
