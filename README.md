<h1 align=center>
	<b>philosophers</b>
</h1>

<h2 align=center>
	 <i>42cursus' project #9</i>
</h2>

<p align=center>
	
---
<div align=center>
<h2>
	Final score
</h2>

</div>

---

<h3 align=center>
Mandatory
</h3>

<h3 align=center>
Bonus
</h3>


---

<h2>
The project
</h2>

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
