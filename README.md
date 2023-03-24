<h1 align=center>
	<b>philosophers</b>
</h1>

<h2 align=center>
	 <i>42cursus' project #9</i>
</h2>

<p align=center>
	In computer science, the dining philosopher’s problem is a classic approach to illustrate what concurrency and race conditions are, and further highlighting the necessity to understand synchronization issues and possible techniques for resolving them. It was simple yet complex little project to work on, that managed to gather everything we’ve seen so far on the 42 syllabus – pointers, processes, signals, complex types and so much more. We’ve never, indeed, thought philosophy could be so deadly – nor so fun.
</p>
---
<div align=center>
<h2>
	Final score
</h2>

</div>

---
> Global variables are forbidden!
> 
> Your(s) program(s) should take the following arguments: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
> - number_of_philosophers: The number of philosophers and also the number of forks.
> - time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation,
> they die.
> - time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
> - time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
> - number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
> 
> Each philosopher has a number ranging from 1 to number_of_philosophers.
> 
> Philosopher number 1 sits next to philosopher number number_of_philosophers.
> 
> Any other philosopher number N sits between philosopher number N - 1 and philosopher
> number N + 1.
> 
> About the logs of your program (Any state change of a philosopher must be formatted as follows):
> - timestamp_in_ms X has taken a fork
> - timestamp_in_ms X is eating
> - timestamp_in_ms X is sleeping
> - timestamp_in_ms X is thinking
> - timestamp_in_ms X died
> Replace timestamp_in_ms with the current timestamp in milliseconds and X with the philosopher number.
> 
> A displayed state message should not be mixed up with another message.
> 
> A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
> 
> Again, philosophers should avoid dying!
<h3 align=center>
Mandatory
</h3>

> - Each philosopher should be a thread.
> - There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.
> - To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.

<h3 align=center>
Bonus
</h3>

> - All the forks are put in the middle of the table.
> - They have no states in memory but the number of available forks is represented by a semaphore.
> - Each philosopher should be a process. But the main process should not be a philosopher.

---

<h2>
The project
</h2>

In this problem, a pre-determined number of philosophers eat together at the same table. Each philosopher has their own place at the table and there is only one fork available per philosopher. They will need to eat, sleep, think and start the process all over again… again and again.

<p align="center">
  <img src="https://user-images.githubusercontent.com/80178342/227601334-852baa9d-6748-4a44-9cf7-b3cc0f853061.png" />
</p>

The problem lies in the fact that in order to eat, a philosopher needs to grab - one at a time - two forks, one in each hand. Also, they must eat every few moments from the moment they sit by the table or from the moment they last ate (this is also pre-determined by the user). If not, they will die. 
This all may sound simple enough, but believe me… it isn’t.

How can we make each philosopher eat independently from everyone else?

How can we prevent each philosopher from immediately grabbing a fork, and completely blocking everyone else from picking the second, eventually leading all to their imminent deaths?

How can we make sure that no two philosophers are eating simultaneously with the same fork?

How can we monitor whoever dies of finishes eating first, further preventing the simulation to continue?

This is the core concept of the philosopher’s project.

---
<h2>
Usage
</h2>

### Instructions

Clone this repository in your local computer:

```sh
$> git clone https://github.com/caroldaniel/42sp-cursus-philosophers.git path/to/philosophers
```

In your local repository, run `make`

```sh
$> make 
```

> `make` suports 5 flags:
> - `make all` or simply `make` compiles philosophers in its mandatory format
> - `make clean` deletes the `.o` files generated during compilation
> - `make fclean` deletes the `.o` and the `fdf` file generated
> - `make re` executes `fclean` and `all` in sequence, recompiling the program
> - `make leak` executes valgrind to check for any possible leaks and puts it into a log file

To run `philosophers`, type:
```sh
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```
> - number_of_philosophers: The number of philosophers and also the number of forks.
> - time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die. 
> - time_to_eat (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
> -  time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
> -  number_of_times_each_philosopher_must_eat (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.
