<!-- ROUGH STEPS FOR DOING PHILOSOPHERS 42 -->

1. understand the dinning philosophers problem
2. learn about threads and mutexes
3. create simple programs using threads and mutexes
4. do a simple parsing for the program
5. create an array of philos acc. to requirement
6. make philo as a thread (and a struct)
7. create an array for forks
8. figure out which forks in the array can each philo take
9. mimic the action of picking the forks and lock it using mutexes
10. figure a solution for data races of forks and deadlocks
11. start making routines now
12. start with eating and then sleeping
13. if no forks then make the philo think
14. figure out an infinite loop for eating, sleeping and thinking
15. implement the meal count for philos
16. now end the program if meal_counts are reached
17. learn about detaching or killing threads
18. now make your immortal philos mortal by implementing starvation
19. learn about getting real time values and use them to track starvation and printing of timestamps
20. create another thread for monitoring there death timing

<!-- create a sanitize make rule using -fsanitize=thread,undefined -O3 -g3  -->