import matplotlib.pyplot as plt
import math
import sys

'''with open(sys.argv[1],'r') as pointFile:
	tempPoint = pointFile.read().split("\n")

for pair in tempPoint:
	point.append(float(pair.split(" ")))'''

with open(sys.argv[1],'r') as edgeFile:
	tempEdge = edgeFile.read().split("\n")
edge = []
for pair in tempEdge[:-1]:
	temp = []
	for i in pair.split(" "):
		temp.append(float(i))
#		print temp
	edge.append(temp)

for e in edge:
	plt.plot([e[0], e[2]], [e[1], e[3]], color = 'brown', marker = 'o',linewidth =2)
plt.gca().set_aspect('equal', adjustable='box')

with open(sys.argv[2],'r') as circlefile:
	tempcircle = circlefile.read().split("\n")
	
clist = []
for p in tempcircle[:-1]:
	temp = []
	for i in p.split(" "):
		temp.append(float(i))
#		print temp
	clist.append(temp)

for c in clist:
	circle = plt.Circle( [c[0],c[1]] , c[2] , color='c',fill=False,clip_on=False)
	plt.gcf().gca().add_artist(circle)

plt.show()
