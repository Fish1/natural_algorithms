#!/usr/bin/python3

import sys
import random

start = 5
end = 100
inc = 15

test = 1
for stack_cnt in range(start, end + 1, inc):
	f = open('test' + str(test) + '.txt', 'w')
	disks = stack_cnt * (5 * test)
	stacks = [0] * stack_cnt
	center1 = random.randint(0, stack_cnt - 1)
	center2 = random.randint(0, stack_cnt - 1)
	for i in range(disks):
		num = random.randint(0, stack_cnt - 1) + random.randint(0, stack_cnt - 1)
		num //= 2
		if i % 2 == 0:
			num += center1
		else:
			num += center2
		num %= stack_cnt
		stacks[num] += 1
	f.write(str(stack_cnt) + '\n')
	f.write(str(stacks[0]))
	for i in range(1, len(stacks)):
		f.write(' ' + str(stacks[i]))
	f.write('\n')

	stacks = [0] * stack_cnt
	center1 = random.randint(0, stack_cnt - 1)
	center2 = random.randint(0, stack_cnt - 1)
	for i in range(disks):
		num = random.randint(0, stack_cnt - 1) + random.randint(0, stack_cnt - 1)
		num //= 2
		if i % 2 == 0:
			num += center1
		else:
			num += center2
		num %= stack_cnt
		stacks[num] += 1
	f.write(str(stacks[0]))
	for i in range(1, len(stacks)):
		f.write(' ' + str(stacks[i]))
	f.write('\n')

	f.close()
	test += 1
