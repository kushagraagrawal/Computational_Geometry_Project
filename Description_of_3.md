# Graham's Scam Algorithm
Graham Scan solves the convex hull problem by maintaining a stack of candidate points.It pushes each point of the input set Q onto the stack one time, and it eventually pops from the stack each point that is not a vertex of CH(Q). When the algorithm terminates, stack S contains exactly the vertices of CH(Q), in counterclockwise order. <br>
Pseudocode:
<pre>

	Graham-Scan(Q):
	
	1. let p_0 be the point in Q with the minimum y-coordinate,
		or the leftmost point in case of a tie.
	2. let {p_1, p_2, ... , p_m} be the remaining points in Q, sorted by
		polar angle in counterclockwise order around p_0 (if more than one point has
		the same angle, remove all but the one that is farthest from p_0)
	3. let S be an empty stack
	4. PUSH(p_0, S)
	5. PUSH(p_1, S)
	6. PUSH(p_2, S)
	7. for i := 3 to m
	8. 		do while the angle formed by points NEXT-TO-TOP(S), TOP(S), and
				p_i makes a non-left turn (straight or to the right)
	9.			do POP(S)
	10.		PUSH(p_i, S)
	11. return S

Reference: Introduction to Algorithms, Third Edition, Thomas H. Cormen
</pre>

# Andrew's Algorithm
Andrew's monotone chain convex hull algorithm constructs the convex hull of a set of 2-dimensional points in O(nlogn) time.
It does so by first sorting the points (first by x-coordinate, and in case of a tie, by y-coordinate), and then constructing upper and lower hulls of the points in O(n) time.
An upper hull is the part of the convex hull, which is visible from the above. Lower hull is the remaining part of the convex hull.

Algorithm:
<pre>

	Andrews(Point_set):
	
	1. Sort the points by x-coordinates, resulting in a sequence p1,p2,...,pn.
	   If two points have same x-coordinates then sort by y-coordinate.
	2. Put the points p1 & p2 in a list lup, with p1 as the first point.
	3. for i<- 3 to n:
	4.  	do append pi to lup
	5.		while lup contains more than 2 points and the last three points in lup don't make a right turn.
	6.			do delete the middle of the last three points from lup.
	7. Put the points pn and p(n-1) in a list ldown with pn as the first point
	8. for i<-n-2 to 1:
	9.		do append pi to ldown
	10.		while lup contains more than 2 points and the last three points in lup don't make a right turn.
	11.			do delete the middle of the last 3 points of ldown
	12. Remove the first and the last points from ldown to avoid duplication of the points where the ldown and lup meet.
	13. Append ldown to lup and output the resulting list l.
	14. return l.

Reference: A. M. Andrew, "Another Efficient Algorithm for Convex Hulls in Two Dimensions", Info. Proc. Letters 9, 216-219 (1979).
</pre>

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
