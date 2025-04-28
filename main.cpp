#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

// ===========================
// Abstract Base Task
// ===========================
class Task
{
   public:
    virtual ~Task()           = default;
    virtual bool should_run() = 0;
    virtual void run()        = 0;
};

// ===========================
// Interval Task (runs every X seconds)
// ===========================
class IntervalTask : public Task
{
   private:
    std::function<void()>                              func;
    std::chrono::seconds                               interval;
    std::chrono::time_point<std::chrono::system_clock> last_run;

   public:
    IntervalTask(std::function<void()> f, int interval_seconds)
        : func(f),
          interval(std::chrono::seconds(interval_seconds)),
          last_run(std::chrono::system_clock::now())
    {
    }

    bool should_run() override
    {
        auto now = std::chrono::system_clock::now();
        if (now - last_run >= interval)
        {
            last_run = now;
            return true;
        }
        return false;
    }

    void run() override { std::thread(func).detach(); }
};

// ===========================
// Task Scheduler Class
// ===========================
class TaskScheduler
{
   private:
    std::vector<std::shared_ptr<Task>> tasks;
    std::mutex                         mtx;
    bool                               running = false;

   public:
    void add_task(std::shared_ptr<Task> task)
    {
        std::lock_guard<std::mutex> lock(mtx);
        tasks.push_back(task);
    }

    void start()
    {
        running = true;
        std::thread(
            [this]()
            {
                while (running)
                {
                    auto now = std::chrono::system_clock::now();
                    {
                        std::lock_guard<std::mutex> lock(mtx);
                        for (auto& task : tasks)
                        {
                            if (task->should_run())
                            {
                                task->run();
                            }
                        }
                    }
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                }
            })
            .detach();
    }

    void stop() { running = false; }
};

// ===========================
// Example Usage
// ===========================
int main()
{
    TaskScheduler scheduler;

    scheduler.add_task(std::make_shared<IntervalTask>(
        [] { std::cout << "Checking Steam Prices...\n"; }, 5));  // every 5 seconds

    scheduler.add_task(std::make_shared<IntervalTask>(
        [] { std::cout << "Checking Udemy Prices...\n"; }, 10));  // every 10 seconds

    scheduler.start();

    // Main thread stays alive
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
}
