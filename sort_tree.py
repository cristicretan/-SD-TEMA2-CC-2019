import os

def sort_file(in_name, out_name):
	if not os.path.isfile(in_name):
		return
	f = open(in_name, "r")

	s = f.read()
	lines = s.split('\n')
	if '' in lines:
		lines.remove('')
	lines.sort()
	new_lines = []
	for line in lines:
		p = line.split(' ')
		x = p[0]
		p = p[1:]
		p.sort()
		p = [x] + p
		s = ' '.join(p)
		new_lines.append(s)

	f.close()
	g = open(out_name, "w")
	g.write('\n'.join(new_lines))

	g.close()


def main():
	sort_file("hierarchy.out", "hierarchy.out")
	sort_file("tree.out", "tree.out")


if __name__ == '__main__':
	main()
