### Jarvis March
Jarvis March (or gift wrapping algorithm) is an algorithm to compute the convex hull of a given set of points. Initially, the convex hull is empty. It starts from the bottommost point and repeatedly chooses the point which makes the least angle with respect to the edge of the convex hull which was discovered last. The line segment with end points as the latest discovered point on the convex hull and the point being considered is used to measure the angle.

```
JarvisMarch(Q):

1.     i0 := index of point with lowest y-coordinate
2.     i := i0
3.     repeat:
4.         for each j != i do
5.             Compute counterclockwise angle theta from last discovered edge
6.         Let k be the index of point with smallest theta
7.         Add Q[k] to convex hull
8.         i := k
9.     until i = i0
