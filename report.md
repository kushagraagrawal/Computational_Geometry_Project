# Computational Geometry Project Documentation

## Introduction
This project is a part of the coursework for the course *Selected Toipcs in Computer Science (CS F441)* under the guidance of *Dr. Tathagat Ray*.

## Implementation

### Graham's Scan Algorithm
Graham Scan solves the convex hull problem by maintaining a stack of candidate points.It pushes each point of the input set Q onto the stack one time, and it eventually pops from the stack each point that is not a vertex of CH(Q). When the algorithm terminates, stack S contains exactly the vertices of CH(Q), in counterclockwise order. <br>
Pseudocode:
<pre>
Graham-Scan(Q):
1. let p_0 be the point in Q with the minimum y-coordinate,
	or the leftmost point in case of a tie.
2. let {p_1, p_2, ... , p_m} be the remaining points in Q, sorted by polar angle in counterclockwise order around p_0 (if more than one 	point has the same angle, remove all but the one that is farthest from p_0).
3. let S be an empty stack
4. PUSH(p_0, S)
5. PUSH(p_1, S)
6. PUSH(p_2, S)
7. for i := 3 to m
8. 		do while the angle formed by points NEXT-TO-TOP(S), TOP(S), and p_i makes a non-left turn (straight or to the right)
9.			do POP(S)
10.		PUSH(p_i, S)
11. return S
</pre>

### Andrew's Algorithm
Andrew's monotone chain convex hull algorithm constructs the convex hull of a set of 2-dimensional points in O(nlogn) time.
It does so by first sorting the points (first by x-coordinate, and in case of a tie, by y-coordinate), and then constructing upper and lower hulls of the points in O(n) time.
An upper hull is the part of the convex hull, which is visible from the above. Lower hull is the remaining part of the convex hull.

Algorithm:
<pre>
Andrews(Point_set):
1.	Sort the points by x-coordinates, resulting in a sequence p1,p2,...,pn.
	If two points have same x-coordinates then sort by y-coordinate.
2.	Put the points p1 & p2 in a list lup, with p1 as the first point.
3.	for i from 3 to n:
4.  	do append pi to lup
5.		while lup contains more than 2 points and the last three points in lup don't make a right turn.
6.			do delete the middle of the last three points from lup.
7. 	Put the points pn and p(n-1) in a list ldown with pn as the first point
8. 	for i from n-2 to 1:
9.		do append pi to ldown
10.		while lup contains more than 2 points and the last three points in lup don't make a right turn.
11.			do delete the middle of the last 3 points of ldown
12.	Remove the first and the last points from ldown to avoid duplication of the points where the ldown and lup meet.
13.	Append ldown to lup and output the resulting list l.
14.	return l.
</pre>

### Jarvis March
Jarvis March (or gift wrapping algorithm) is an algorithm to compute the convex hull of a given set of points. Initially, the convex hull is empty. It starts from the bottommost point and repeatedly chooses the point which makes the least angle with respect to the edge of the convex hull which was discovered last. The line segment with end points as the latest discovered point on the convex hull and the point being considered is used to measure the angle.

<pre>
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
</pre>

## Running Time Analysis

![Points graph](images/points.png)

Number of Points|Graham-Scan time (in us)|Andrews time (in us)|Jarvis March time (in us)
--------------- | --------- | ----- | ----------
10|58|48|61.2
100|244|230.4|497.8
1000|2582|2480.8|8525.4
10000|19377.2|28994.2|65278.4
100000|163436.2|210378.2|792890.4
1000000|1761554.6|2252025.4|8781688.8

All the three algorithms were made to run on a given number of points 5 times, each time the points  were generated randomly, and the average of the running time was taken. From the graph, it is clear that Andrew’s and Graham Scan Algorithm are taking almost the same time for all the sets of points. On the other hand, Jarvis March on average takes more time than the other two algorithms. This is because the time consuming step in Graham and Andrews algorithm ,which is the step to sort the points , is run only once whereas in case of Jarvis March, the step to compute polar angle, takes the most time and is repeated a lot of times.

![Vertices graph](images/vertices.png)

Number of vertices|Graham-Scan time (in us)|Andrews time (in us)|Jarvis March time (in us)|
-----------------:|:---------:|:-----:|:----------:|
10|161413|210374|238600|
100|162104|209545|2369044|
1000|162210|209957|23435829|
10000|159654|209138|246883120|

All the three algorithms were made to run on a given number of points 5 times, each time the points  were generated randomly, and the average of the running time was taken. From the graph, it is clear that Andrew’s and Graham Scan Algorithm are taking almost the same time for all the sets of points.    Also, Andrew’s and Graham Scan Algorithm take almost constant time for all the vertices, further stating that they are not output dependent. Whereas time taking by Jarvis March keeps on increasing for number of vertices, proving that it is an output dependent algorithm.


## Degeneracy

After checking for Degeneracy, the following results were seen-
<ol>
<li> In the case of n (n>2) collinear points, Graham-Scan Algorithm and Andrew's Algorithm only considered the two extreme points for the Convex Hull every time.
   On the other hand, Jarvis-March considered all the collinear points as separate edges. i.e for n collinear points, n-1 edges are made.
</li>
<li> When there are no points in the input, all the three algorithms throw an exception, saying "Input file is empty". </li>
<li> For a single point in our point space, that point is taken as the Convex Hull. </li>
<li> For two points, the line segment connecting the two points is taken as the Convex Hull. </li>
</ol>

## Robustness

Algorithms in computational geometry are designed under the assumption of exact real arithmetic. However, in practical implementation of such algorithms, floating point arithmetic almost inevitably leads to robustness issues. While computing the Convex Hull of a set of finite points, such issues might lead to a hole or an extra edge in the Convex Hull. Most well-known algorithms use the signed area of three points in particular order to check whether a point lies to the left or right or on the directed line segment from the other two points. Testing whether a point lies to the right or left or on the directed line segment is subjected to numerical inaccuracy because of floating point computations.

In our assignment, we have used the method of signed area to find whether a point should be included in the Convex Hull, depending on whether it lies to the right/left/ or on the directed line segment. We have also used floating point arithmetic to find the minimum polar angle in Jarvis March algorithm, which faces similiar issues.

In order to test our program against robustness issues, we took few points in the cartesian space. Then we took three test cases, we found out that Andrew's Algorithm and Graham scan gave different results. This is due to the flipped ordering of vertices when computing the signed area. As a result of floating point multiplication, there is an error in precision which results in the inaccurate construction of Convex hull.

In order to tackle this problem, we can specify a small value 'epsilon'. If the abosulte value of signed area is less than epsilon, we consider it to be equal to zero. All values greater than epsilon are considered positive and all values less than negative epsilon are considered negative.

Given below are the snapshots of visualization of Convex Hull:-

<table style="width:100%">
  <tr>
  	<th>Test</th>
    <th>Graham</th>
    <th>Andrew</th> 
    <th>Jarvis</th>
  </tr>
  <tr>
  	<td> 1
    <td><img src = 'images/test1_graham.png', style="width: 200px;"></td>
    <td><img src = 'images/test1_andrew.png', style="width: 200px;"></td></td> 
    <td><img src = 'images/test1_jarvis.png', style="width: 200px;"></td></td>
  </tr>
  <tr>
  	<td> 2
    <td><img src = 'images/test2_graham.png', style="width: 200px;"></td>
    <td><img src = 'images/test2_andrew.png', style="width: 200px;"></td></td> 
    <td><img src = 'images/test2_jarvis.png', style="width: 200px;"></td></td>
  </tr>
  <tr>
  	<td> 3
    <td><img src = 'images/test3_graham.png', style="width: 200px;"></td>
    <td><img src = 'images/test3_andrew.png', style="width: 200px;"></td></td> 
    <td><img src = 'images/test3_jarvis.png', style="width: 200px;"></td></td>
  </tr>
</table>


## Generating and Visualizing Test Cases using Python Script

### Batch processing of Test Cases

New test cases can be generated using the ```test_convex.py``` script. The ```test_convex.cpp``` file is responsible for executing the algorithms. All test cases must stored in ```<main_folder>/test_convex/``` as ```.txt``` files. New test cases are created in this folder by default. Test cases are in the format as shown below. Each line represents a point with the first term for x-coordinate and the second term for y-coordinate. The two terms must be seperated *only* by a space.
```
0.56 0.45
4.5 5.1
100 0.6
1.34 6.7
```

There are four options for running the script.

**1. Test pre-existing cases**
```
python test_convex.py <executable_name> <algo_name> all-txt
```

**2. Test on Gaussian distribution**

```
python test_convex.py <executable_name> <algo_name> gaussian <no_of_test_cases> <no_of_sample_pts> <random_seed> <mean> <variance>
```

**3. Test on Uniform distribution**
```
python test_convex.py <executable_name> <algo_name> uniform <no_of_test_cases> <no_of_sample_pts> <random_seed> <max_value> <min_value>
```

**4. Test for output sensitive algorithms**
```
python test_convex.py <executable_name> <algo_name> output-sensitive <no_of_test_cases> <no_of_sample_pts> <no_of_hull_vertices>
```

**NOTE**: The parameter ```<algo_name>``` can take the arguments ```graham```, ```jarvis``` or ```andrew``` to select the algorithm that must be exected.

### VIsualizing the Results

To visualize the results, two ```.txt``` files are needed: an ```<input_file>``` which contains all the points in the sample space and ```<output_file>``` that contains all the points on the hull. Then, to visualize the results, simple run:
```
python plot_convex_hull.py <input_file> <output_file>
```


## References

<ol>
<li>Introduction to Algorithms, Third Edition, Thomas H. Cormen</li>
<li>A. M. Andrew, "Another Efficient Algorithm for Convex Hulls in Two Dimensions", Info. Proc. Letters 9, 216-219 (1979).</li>
<li>Joseph O'Rourke. 1998. Computational Geometry in C (2nd ed.). Cambridge University Press, New York, NY, USA.</li>
<li>Class notes.</li>
</ol>
