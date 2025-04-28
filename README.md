# 🛠️ Task Scheduler in C++

This is a simple **C++ Task Scheduler** that allows you to schedule and run tasks at fixed intervals using multithreading.

It is designed with an **abstract Task interface**, a **concrete IntervalTask**, and a **TaskScheduler** that manages and runs tasks safely across threads.

---

## ✨ Features
- Define custom tasks by extending the `Task` class.
- Run functions at fixed intervals (`IntervalTask`).
- Safe multithreaded scheduling with `std::mutex`.
- Easy to extend and integrate into other C++ projects.

---

## 🚀 How to Use

### 1. Clone the code
```bash
git clone https://github.com/Abdulkhalek-1/Cpp-Scheduler.git
cd ./Cpp-Scheduler
```

### 2. Compile
```bash
g++ -std=c++17 -pthread main.cpp -o scheduler
```

### 3. Run
```bash
./scheduler
```

You will see output like:
```
Checking Steam Prices...
Checking Udemy Prices...
...
```

Tasks will automatically execute at the intervals you define.

---

## 🧩 Example: Adding a New Task
```cpp
scheduler.add_task(std::make_shared<IntervalTask>(
    [] { std::cout << "Fetching latest news...\n"; }, 15));  // every 15 seconds
```

You can pass any function or lambda that matches `void()`.

---

## ⚙️ Requirements
- C++17 or newer
- A POSIX-compatible system (Linux, Mac) or Windows with `g++` or compatible compiler.

---

## 📝 License
Feel free to use and modify this code for personal or commercial projects.
