# Each philo is a struct
- Contains data:
	- philo_id: int variable
	- *left_fork: pointer
	- *right_fork: pointer
	- meal_count: long variable
 
 # 2 arrays: philos and forks
- A philo is a struct.
	- An array of structs
- A fork is a mutex.
	- An array of mutexes.

# 🔷 Bonus rules:
### 1️⃣ All the forks are put in the middle of the table.

### 2️⃣ They have no states in memory but the number of available forks is represented by a semaphore.
- ***🧐 What are semaphores?***
- Semaphores are counters that control access to a resource with an arbitrary number of permits. 
- They can be used to limit the number of threads that can access a resource simultaneously.

### 3️⃣ Each philosopher should be a process. But the main process should not be a philosopher.

