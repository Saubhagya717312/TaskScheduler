#include <iostream>
#include <queue>
#include <vector>

struct Task {
    std::string name;
    int priority;
    int expectedDuration;
    int finalPriority;

    Task(const std::string& n, int p, int d)
        : name(n), priority(p), expectedDuration(d), finalPriority(p / d) {}
};

struct CompareTasks {
    bool operator()(const Task& t1, const Task& t2) {
        // Comparison for the priority queue (min-heap)
        return t1.finalPriority > t2.finalPriority;
    }
};

class TaskScheduler {
public:
    void addTask(const std::string& name, int priority, int expectedDuration) {
        Task newTask(name, priority, expectedDuration);
        tasks.push(newTask);
    }

    void deleteTask(const std::string& name) {
        std::priority_queue<Task, std::vector<Task>, CompareTasks> tempQueue;
        while (!tasks.empty()) {
            if (tasks.top().name != name) {
                tempQueue.push(tasks.top());
            }
            tasks.pop();
        }
        tasks = tempQueue;
    }

    std::string getNextTask() {
        if (tasks.empty()) {
            return "No tasks in the queue";
        }

        Task nextTask = tasks.top();
        tasks.pop();
        return nextTask.name;
    }

    void printTasks() {
        std::priority_queue<Task, std::vector<Task>, CompareTasks> tempQueue = tasks;
        while (!tempQueue.empty()) {
            Task task = tempQueue.top();
            std::cout << "Task: " << task.name << ", Priority: " << task.finalPriority << std::endl;
            tempQueue.pop();
        }
    }

private:
    std::priority_queue<Task, std::vector<Task>, CompareTasks> tasks;
};

int main() {
    TaskScheduler scheduler;

    scheduler.addTask("Task 3", 1, 2);
    scheduler.addTask("Task 1", 2, 1);
    scheduler.addTask("Task 2", 3, 3);

    std::cout << "Current tasks:" << std::endl;
    scheduler.printTasks();

    std::cout << "\nNext task: " << scheduler.getNextTask() << std::endl;

    scheduler.deleteTask("Task 1");

    std::cout << "\nRemaining tasks:" << std::endl;
    scheduler.printTasks();

    return 0;
}

