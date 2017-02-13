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
