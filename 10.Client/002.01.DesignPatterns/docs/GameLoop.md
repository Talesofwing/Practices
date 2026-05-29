# Double Buffer

> Game Programming Pattern
>
> Decouple the progression of game time from user input and processor speed.

This essentially describes a lifecycle, such as the game loop in Unity. The key issue to handle is the timestep.

There are four main approaches
- Fixed time step with no synchronization

	Both update and render use a fixed timestep, without synchronization.

	This causes different results on machines with different performance.

- Fixed time step with synchronization

	Both update and render use a fixed timestep, with synchronization considered.

- Variable time step (not recommended)

	Both update and render use a variable timestep.

	This easily leads to desynchronization issues. If the timestep suddenly becomes very large due to some factors, physics calculations in update can break down.

- Fixed update time step, variable rendering (commonly used)

	update uses a fixed timestep (Unity’s FixedUpdate).

	render uses a variable timestep (Unity’s Update).

	Additionally, render interpolation is often introduced to make things smoother—by rendering interpolated states between two physics frames instead of just the previous one. Although this can cause issues like clipping, it makes the visuals appear smoother.

Additional considerations
- The execution order in the game loop is critical.
- In networked games, frame synchronization must be carefully handled.
- On mobile devices, power consumption matters—CPU usage should be minimized, and idle time should be allowed when possible.

In simpler terms
- Use a fixed timestep for physics.
- Use a variable timestep for everything else.


### References
- [deWiTTERS Game Loop](https://dewitters.com/dewitters-gameloop/)
- [Fix Your Timestep!](https://gafferongames.com/post/fix_your_timestep/)
