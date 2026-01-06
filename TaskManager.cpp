#include "TaskManager.h"
#include "Task.h"
#include "Person.h"
#include "SortedList.h"

int TaskManager::find_person(const string &personName) {
    for (int i = 0; i < MAX_PERSONS; i++) {
        if (workers[i].getName() == personName) {
            return i;
        }
    }
    return -1;
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
    SortedList<Task> new_tasks;
    for (int i = 0; i < num_of_workers; i++) {
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