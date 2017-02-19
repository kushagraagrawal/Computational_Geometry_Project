# Test for Degeneracy


After checking for Degeneracy, the following results were seen-
<ol>
<li> In the case of n (n>2) collinear points, Graham-Scan Algorithm and Andrew's Algorithm only considered the two extreme points for the Convex Hull every time.
   On the other hand, Jarvis-March considered all the collinear points as separate edges. i.e for n collinear points, n-1 edges are made.
</li>
<li> When there are no points in the input, all the three algorithms throw an exception. </li>
<li> For a single point in out point space, that point is taken as the Convex Hull. </li>
<li> For two points, the line segment connecting the two points is taken as the Convex Hull. </li>
