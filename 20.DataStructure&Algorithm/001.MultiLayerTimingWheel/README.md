# 001.MultiLayerTimingWheel

    Unity 2022.3.36f1

To practice code structuring, I used some design patterns which affected performance; if `BaseTimerTickHandler` and `Timer` were made more specialized to serve the `MultiLayerTimingWheel` specifically, the performance could be improved.

### References
- [[中文]Linux定时器实现](https://github.com/liexusong/linux-source-code-analyze/blob/master/kernel-timer.md)