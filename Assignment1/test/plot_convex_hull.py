import sys
import numpy as np
from matplotlib import pyplot as plt
from matplotlib.patches import Polygon

def plotHull(input_file, output_file):
	with open(input_file,'r') as f:
		text_in = f.read()
	
	with open(output_file,'r') as f:
		text_out = f.read()
	
	s0 = text_in.split('\n')
	s1 = text_out.split('\n')
	
	p = []
	h = []

	for x in s0:
		if(x != ''):
			y = x.split(' ')
			#print(y)
			p.append([float(y[0]),float(y[1])])
	
	for x in s1:
		if(x != ''):
			y = x.split(' ')
			#print(y)
			h.append([float(y[0]),float(y[1])])
	
	points = np.array(p)
	hull = np.array(h)

	hull_vertices = []

	for j in range(len(hull)):
		for i in range(len(points)):
			if(np.all(np.isclose(points[i,:], hull[j,:]))):
				hull_vertices.append(i)

	plt.plot(points[:,0], points[:,1], 'r+')
	cent = np.mean(points, 0)
	pts = points[hull_vertices]

	k = 1.0
	color = 'cyan'
	poly = Polygon(k*(np.array(pts)- cent) + cent, facecolor=color, edgecolor='black', alpha=0.2)
	#poly.set_capstyle('butt')
	plt.gca().add_patch(poly)
	plt.plot(pts[:,0], pts[:,1], 'ko')
	plt.axis(np.array([np.amin(points)-1, np.amax(points)+1, np.amin(points)-1, np.amax(points)+1]))
	plt.savefig('convex.png')
	print("Image successfully saved.")
	plt.show()
	
if (__name__=="__main__"):
	plotHull(str(sys.argv[1]), str(sys.argv[2]))
