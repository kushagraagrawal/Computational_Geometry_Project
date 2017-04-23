import numpy as np
import sys
import os

for arg in sys.argv[1:]:
     print arg

cx, cy = np.random.rand()*100, np.random.rand()*100
angle = np.sort(np.random.rand(int(sys.argv[1]))*2*np.pi).tolist()
points = []

try:
	os.remove(sys.argv[2])
	print "Existing file deleted."
except:
	pass

for theta in angle:
	r = np.random.rand()*100
	points.append(np.round([cx+r*np.cos(theta), cy+r*np.sin(theta)],3))

print points

with open(sys.argv[2],'w+') as pointFile:
	for i in range(len(points)):
		pointFile.write(str(points[i][0]) + " " + str(points[i][1]) + "\n")

print ("Points written successfully.")
	
