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
import random
from matplotlib import pyplot as plt
from matplotlib.patches import Polygon

exec_file = './main.o'
choice = sys.argv[1]		# choice = '1' or '2' or '3'

n = 100000 					# total points
m = int(sys.argv[2])		# points on CH
radius = float(sys.argv[3])

try:
	os.remove('test_cases.txt')
except Exception: 
	pass

points = []


with open('test_cases.txt','w') as f:
	for i in range(m):
		theta = i * ((2*math.pi)/(float(m)))		# (i*2PI)/m
		x1 = radius * math.cos(theta)
		y1 = radius * math.sin(theta)
		points.append([float(x1),float(y1)])
		f.write(str(x1)+" "+str(y1)+"\n")
	for j in range(n-m):
		r = random.random()*(radius/(2**(0.5)))
		theta = 2*math.pi*random.random()
		x1 = r * math.cos(theta)
		y1 = r * math.sin(theta)
		points.append([float(x1),float(y1)])
		f.write(str(x1)+" "+str(y1)+"\n")

proc = subprocess.call([exec_file + ' test_cases.txt test_output.txt '+ choice], shell = True)

points = np.array(points)

with open('test_output.txt','r') as f:
	text = f.read()

s = text.split('\n')
s.pop()
h = []
hull_vertices = []

for x in s:
	y = x.split(' ')
	print(y)
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
poly = Polygon(k*(np.array(pts)- cent) + cent,
               facecolor=color, edgecolor='black', alpha=0.2)
#poly.set_capstyle('butt')
plt.gca().add_patch(poly)
plt.plot(pts[:,0], pts[:,1], 'ko')
plt.axis(radius*np.array([-1.2, 1.2, -1.2, 1.2]))
plt.savefig('convex.png')
print("Image successfully saved.")
plt.show()
#plt.close(1)

