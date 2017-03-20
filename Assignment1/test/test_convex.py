import numpy as np
import subprocess
import sys
import os
import math
import glob
import random
from matplotlib import pyplot as plt
from matplotlib.patches import Polygon

point_gen = {'all-txt': 1, 'gaussian': 2, 'uniform' : 3, 'op-sensitive' : 4}
algo_select = {'graham' : 1, 'jarvis' : 2, 'andrew' : 3}

def genCircle(n,m):
	points = []
	radius = 10
	for i in range(m):
		theta = i * ((2*math.pi)/(float(m)))		# (i*2PI)/m
		x1 = radius * math.cos(theta)
		y1 = radius * math.sin(theta)
		points.append([float(x1),float(y1)])
	for j in range(n-m):
		r = random.random()*(radius/(2**(0.5)))
		theta = 2*math.pi*random.random()
		x1 = r * math.cos(theta)
		y1 = r * math.sin(theta)
		points.append([float(x1),float(y1)])
	return np.array(points)

if (__name__=="__main__"):
	exec_file = str(sys.argv[1])
	algo = algo_select.get(str(sys.argv[2]),0)
	test_type = point_gen.get(str(sys.argv[3]),0)
	input_file = []
	if (test_type == 0 or algo == 0):
		print('Invalid arguments. Aborting.\n')
		exit()
	
	try:
		os.mkdir('test_convex')
	except Exception: 
		pass
	
	if(test_type == 1):
		input_file = glob.glob('./test_convex/*.txt')
		n_tests = len(input_file)
	else:
		n_tests = int(sys.argv[4])
		n = int(sys.argv[5])
		if(test_type == 4):
			m = int(sys.argv[6])
		else:
			seed = int(sys.argv[6])
			r = np.random.RandomState(seed)
			a = float(sys.argv[7])
			b = float(sys.argv[8])
	
	if(test_type > 1):
		for i in range(n_tests):
			input_file.append('./test_convex/test_case_'+str(i)+'.txt')
			
			try:
				os.remove(input_file[i])
			except Exception: 
				pass
			
			if(test_type == 2):
				points = r.normal(a,b, size = (n,2))
			elif(test_type == 3):
				points = (a-b)*r.random_sample((n,2)) + a
			else:
				points = genCircle(n,m)
			
			with open(input_file[i],'w') as f:
				for p in points:
					f.write(str(p[0])+" "+str(p[1])+"\n")
			if(test_type != 4):
				seed = seed + 10
	
	for i in range(n_tests):
		output_file = input_file[i][:-4] + '_output.txt'
		proc = subprocess.call([exec_file  + ' ' + input_file[i] + ' ' + output_file + ' '+ str(algo)], shell = True)
		print('Test #' + str(i) + ' completed.\n')
