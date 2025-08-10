# Krusty Krab Simulator

This is just a quick project I did because a colleague of mine caught a race condition in my source code. Having never really written any multithreaded code before besides very rudimentary stuff, and feeling a bit embarassed,
I thought I would just make a classic producer-consumer application with Krusty Krab as the setting and give myself as many mines to step on as possible with condition variables, so I can get into the headspace of being more 
careful about these things in future.

Things going on at the same time:
- Delivery truck delivers ingredients to the Krusty Krab's freezer every now and again
- Squidward is a random ticket generator and adds random tickets with a random number of menu items to the ticket line
- SpongeBob and Patrick take from the ticket line. If none, they will sleep on a condition variable until tickets are available
- SpongeBob and Patrick request ingredients from the Freezer for the current item they're making
- Freezer waits on a condition variable until requested for ingredients
- Krusty Krab waits for SpongeBob and Patrick to finish tickets when it closes -- sleeps on another condition variable
  
To build and run just do the classic CMake rodeo:

On Linux:
```
mkdir build
cd build
cmake ..
make -j $(nproc)
./KrustyKrab
```

Press any key to stop the application.
