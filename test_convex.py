# HOW TO RUN
# ...$ make [graham.o | jarvis.o]
# ...$ python test_convex.py [./graham.o | ./jarvis.o] 100 10 
#	100 = number of points in set
#	10 =  range of points (-10 to 10, both x and y)

import numpy as np
import subprocess
import sys
import os
import math
from matplotlib import pyplot as plt
from matplotlib.patches import Polygon


exec_file = './main.o'
choice = sys.argv[1]

n = int(sys.argv[2])
max_val = float(sys.argv[3])

try:
	os.remove('test_cases.txt')
except Exception: 
	pass

points = 2*max_val*(np.random.rand(n, 2)-np.array([0.5,0.5]))

with open('test_cases.txt','w') as f:
	for p in points:
		f.write(str(p[0])+" "+str(p[1])+"\n")

proc = subprocess.call([exec_file + ' test_cases.txt test_output.txt '+choice ], shell = True)

with open('test_output.txt','r') as f:
	text = f.read()

s = text.split('\n')
s.pop()
h = []
hull_vertices = []

for x in s:
	y = x.split(' ')
	# print(y)
	h.append([float(y[0]),float(y[1])])


hull = np.array(h)

for j in range(len(hull)):
	for i in range(len(points)):
		if(np.all(np.isclose(points[i,:], hull[j,:]))):
			hull_vertices.append(i)

print(len(hull_vertices))

plt.plot(points[:,0], points[:,1], 'r+')
cent = np.mean(points, 0)
pts = points[hull_vertices]

k = 1.0
color = 'cyan'
poly = Polygon(k*(np.array(pts)- cent) + cent, facecolor=color, edgecolor='black', alpha=0.2)
#poly.set_capstyle('butt')
plt.gca().add_patch(poly)
plt.plot(pts[:,0], pts[:,1], 'ko')
plt.axis(max_val*np.array([-1.2, 1.2, -1.2, 1.2]))
plt.savefig('convex.png')
print("Image successfully saved.")
plt.show()
#plt.close(1)

