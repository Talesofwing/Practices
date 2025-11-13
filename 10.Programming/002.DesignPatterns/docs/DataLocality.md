# Data Locality

> Game Programming Pattern
>
> Avoid unnecessary work by deferring it until the result is needed.

### Data Access

One often overlooked issue is that no matter how fast the CPU is, its performance is limited by data access speed. The CPU speed and RAM speed are not proportional.

CPU cache is one solution to this problem. Every time data is fetched from RAM, the CPU automatically grabs an entire contiguous block of memory—typically about 64 to 128 bytes—and loads it into the cache. This block of memory is called a cache line.

> Modern CPUs have multiple levels of cache, commonly referred to as L1, L2, and L3 caches. Each level is larger but slower than the previous one.

If the next piece of required data happens to be within this cache line, the CPU reads directly from the cache. Successfully finding data in the cache is called a cache hit. If not found, it must read from the main memory, which is a cache miss.

	The fact is:

	Whenever the chip reads some memory, it fetches an entire cache line. The more useful data you can use from this cache line, the faster the performance. Therefore, the goal is to organize data structures so that the data being processed is located contiguously in memory.

	One way to achieve this is to eliminate the -> operator, i.e., pointers.

	This also partially explains why `ECS` is so fast.

#### Contiguous Arrays

	In a contiguous array, if not all instances in the array are active, cache misses will occur frequently. In this case, you can improve cache hit rate by "swapping" active instances to the front of the array and inactive ones to the back, then only iterate over the active instances.

	If cache hit rate is improved, the cost of swapping memory addresses can appear low. Of course, this depends on the specific case.

### Branch Prediction

Another performance factor is caused by branch selection. In an if branch, the CPU performs branch prediction and speculatively executes the predicted branch. Once the actual result of the if is known:

If the prediction is correct, execution continues.

Otherwise, the CPU flushes the instruction pipeline and re-executes.

### Hot/Cold Splitting

Since the amount of data actually loaded into a cache line is limited, if a component contains many unused or rarely used data fields, this will reduce the amount of useful data fitting in the cache line and thus lower cache hit rate.

Therefore, data can be split into two parts:

- Hot: Frequently used data; stored directly within the instance

- Cold: Rarely used data; accessed via pointers to reduce instance size

### References

- [Data-Oriented Design](https://gamesfromwithin.com/data-oriented-design)
