arrays = {
	'a': ['1', '2', '3', '4'],
	'b': ['a', 'b', 'c', ],
	'c': ['f', 't'],
}

objects = []

# Determine total item count
itemCount = 1
for k,array in arrays.items():
	itemCount *= len(array)

# Construct all items
for i in range(itemCount):
	objects.append({})

# Initialize items
blockSize = 1
for k,array in arrays.items():
	for i in range(itemCount):
		idx = int(i/blockSize)%len(array)
		objects[i][k] = array[idx]

	blockSize *= len(array)

# print
for o in objects:
	print('{a}	{b}	{c}'.format(**o))
