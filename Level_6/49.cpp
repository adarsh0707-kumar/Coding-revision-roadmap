/*
Q49. Design a Multithreaded Logging System
Design and implement a thread-safe logging system in C++.
Requirements:
- Multiple threads can submit log messages.
- A dedicated worker thread processes messages.
- Use std::mutex and std::condition_variable.
- Write logs to a file.
- Support INFO, WARNING, and ERROR levels.
- Shut down gracefully.
- Prevent data races.
*/

