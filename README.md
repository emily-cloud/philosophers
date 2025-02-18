# Philosophers - 42 Berlin

## Introduction

Philosophers is a project at 42 Berlin that explores the classic **dining philosophers problem**, a fundamental problem in concurrent programming. The goal is to manage multiple philosophers eating, thinking, and sleeping while preventing **deadlocks** and ensuring proper resource management using **threads** and **mutexes**.

## Features

- Multi-threaded execution using `pthread`
- Mutex synchronization to avoid race conditions
- Philosophers eat, sleep, and think in a controlled manner
- Avoidance of **deadlocks** and **starvation**
- Command-line argument parsing
- Optional logging for debugging and analysis

## Installation

```bash
git clone https://github.com/emily-cloud/philosophers.git
cd philosophers
make
```

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Example

```bash
./philo 5 800 200 200
```

This will run a simulation with **5 philosophers**, each with:
- 800ms before dying if they don’t eat
- 200ms to eat
- 200ms to sleep

## Resources

- `man 3 pthread_create`
- `man 3 pthread_mutex_lock`
- `man 3 usleep`
- `man 2 fork`
- `man 3 sem_open`

## Authors

- Developed as part of the 42 Berlin curriculum by Huayun Ai.

## License

This project follows the academic rules of 42 and is intended for educational purposes.

