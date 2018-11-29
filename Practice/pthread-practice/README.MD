# pthread_create(&a_thread, &a_thread_with_attr, pointer to the function that will run aka service routine, (void*)a_param->NULL can be passed)

a pthread with attr will be called ta from now on

# pthread_attr_init(&a_pthread) -> a_pthread with attr

# pthread_attr_setschedpolicy(&ta, SCHED_RR)
here SCHED_RR is defined as 2 and stands for round robin scheduler

# sem_t a_semaphore_var

# sem_wait(&semaphore_var) sem_value--

# sem_post(&semaphore_var) sem_value++

# sem_init(&a semaphore var, 0, initial value for sem) 

0 means semaphore is local to the calling process

# pthread_mutex_init(&pthread_mutex_t var, attr-> 0 or null)

