from typing import Tuple

def find_max(vertex : list, points : list) -> int:

	coord0 = str(vertex[int(points[1])]).split(' ')
	coord1 = str(vertex[int(points[2])]).split(' ')
	coord2 = str(vertex[int(points[3])]).split(' ')
	coord3 = str(vertex[int(points[4])]).split(' ')
	
	
	

def	create_triangle_from_square(vertex : list, line : str) -> tuple[str, str]:
	
	points = line.split(' ')
	find_max(vertex, points)

def convert(infile, outfile):
	
	i = 0
	vertex = []
	fd_obj = open(infile, 'r')
	fd_rt = open(outfile, 'w')
	contenu = 'start'
	
	while contenu:
		contenu = fd_obj.readline()
		if contenu.startswith('v'):
			vertex.append(contenu.removeprefix('v'))
			print(vertex[i], end = '')
			i += 1
	
	fd_obj = open(infile, 'r')
	contenu = 'start'
	while contenu:
		contenu = fd_obj.readline()
		if contenu.startswith('f') and contenu.count(' ') == 4:
			create_triangle_from_square(vertex, contenu.removeprefix('f'))

	fd_obj.close()
	fd_rt.close()

convert('Male.OBJ', 'male.rt')