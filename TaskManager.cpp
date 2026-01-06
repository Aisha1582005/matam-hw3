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