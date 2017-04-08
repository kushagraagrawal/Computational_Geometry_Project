import matplotlib.pyplot as plt
import sys

point = []
edge = []

'''with open(sys.argv[1],'r') as pointFile:
	tempPoint = pointFile.read().split("\n")

for pair in tempPoint:
	point.append(float(pair.split(" ")))'''

with open(sys.argv[1],'r') as edgeFile:
	tempEdge = edgeFile.read().split("\n")

for pair in tempEdge[:-1]:
	temp = []
	for i in pair.split(" "):
		temp.append(float(i))
	print temp
	edge.append(temp)

fig = plt.figure()
for e in edge:
	plt.plot([e[0], e[2]], [e[1], e[3]], color = 'brown', marker = 'o')
plt.show()
