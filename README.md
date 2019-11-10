# tsp
Implementation of some TSP solvers.

In the current state, the application supports only symmetric problems, and the following solvers: 

* Exact:
  * Brute force (naïve).
  * Dynamic programming (based on the Bellman-Held-Karp algorithm).
* Heuristics:
  * Nearest neighbor.
  * Nearest insertion.
  * Bellmore-Nemhauser.
