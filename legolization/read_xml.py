import xml.etree.ElementTree as ET
import math

tree = ET.parse('voxel_object.xml')
root = tree.getroot()

xs = []
ys = []
zs = []

for child in root:
	x = float(child.find('x').text)
	y = float(child.find('z').text)
	z = float(child.find('y').text)

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

xs = [ int(math.floor(x * 33.0 / xm)) for x in xs]
ys = [ int(math.floor(x * 21.0 / ym)) for x in ys]
zs = [ int(math.floor(x * 17.0 / zm)) for x in zs]

print(len(xs), max(xs) + 1, max(ys) + 1, max(zs) + 1)
for i in range(len(xs)):
	print(xs[i], ys[i], zs[i])
