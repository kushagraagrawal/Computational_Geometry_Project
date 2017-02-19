# Generating and Visualizing Test Cases using Python Script

## Batch processing of Test Cases

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

## VIsualizing the Results

To visualize the results, two ```.txt``` files are needed: an ```<input_file>``` which contains all the points in the sample space and ```<output_file>``` that contains all the points on the hull. Then, to visualize the results, simple run:
```
python plot_convex_hull.py <input_file> <output_file>
```
