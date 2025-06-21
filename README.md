# Sealeo

Sealeo is a clone of Goroutines and Channels written in modern C++23. The purpose of this project is to explore parallelism and concurrency by reimplementing user-space threads as seen in the Go runtime, using the more robust language of C++. Channels were trivial to implement, as they are just the producer consumer problem, and here were implemented with semaphores. Goroutines are much more difficult to clone. This project is work in progress. There is lots left to design.

## Roadmap
- [ ] Implement a Goroutine abstraction that enables context switching (so register dumping, switching %pc, etc.)
- [ ] Implement different schedulers that change how that abstraction decides which process to run
- [ ] Benchmark for performance, and optimise
