import math
import json

from os import listdir
from os.path import isfile, join

onlyfiles = [f for f in listdir('./json/') if isfile(join('./json/', f))]
onlyfiles = [f for f in onlyfiles if '.json' in f]
print(onlyfiles)

for filename in onlyfiles:
	switch_dim = '_switch' in filename

	with open(join('./json/', filename)) as data_file:
		data = json.load(data_file)

	xs = []
	ys = []
	zs = []

	for child in data['voxels']:
		x = float(child['x'])
		y = float(child['y'])
		z = float(child['z'])

		xs.append(x)
		ys.append(y)
		zs.append(z)

	xm = min(xs)
	ym = min(ys)
	zm = min(zs)

	xs = [ x - xm + 1 for x in xs]
	ys = [ x - ym + 1 for x in ys]
	zs = [ x - zm + 1 for x in zs]

	xm = max(xs)
	ym = max(ys)
	zm = max(zs)

	xs = [ int(math.floor(x * float(data['dimension'][0]['width']) / xm)) for x in xs]
	ys = [ int(math.floor(x * float(data['dimension'][0]['height']) / ym)) for x in ys]
	zs = [ int(math.floor(x * float(data['dimension'][0]['depth']) / zm)) for x in zs]

	if switch_dim:
		ws = ys
		ys = zs
		zs = ws

	out_filename = open('txt/' + filename.replace('.json', '.txt'), 'w')
	out_filename.write(str(len(xs)) + " " + str(max(xs) + 1) + " " + str(max(ys) + 1) + " " + str(max(zs) + 1) + "\n")
	for i in range(len(xs)):
		out_filename.write(str(xs[i]) + " " + str(ys[i]) + " " + str(zs[i]) + "\n")
