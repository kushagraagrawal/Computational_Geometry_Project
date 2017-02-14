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
