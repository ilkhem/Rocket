
from astar import AStar
import sys
import math




def make_maze(size, x,y):
 #   open('maze.txt', 'w').close()
    # Using the newer with construct to close the file automatically.
    with open('maze.txt', 'r+') as myfile:

        data = myfile.read()
        # myfile.seek(0)
        for iter in range(0, size):
            myfile.write('+')
        myfile.write('\n')
        size_obs = 2;

        for iter in range(1, size - 2):
            myfile.write('+')
            for iter2 in range(1, size - 1):
                # for k in range(1, 5):
                # if iter == x[1] and iter2 == y[1]:
                if abs(iter - x[0]) <= size_obs and abs(iter2 - y[0]) <= size_obs:
                    myfile.write('+')
                elif abs(iter - x[1]) <= size_obs and abs(iter2 - y[1]) <= size_obs:
                    myfile.write('+')
                elif abs(iter - x[2]) <= size_obs and abs(iter2 - y[2]) <= size_obs:
                    myfile.write('+')
                elif abs(iter - x[3]) <= size_obs and abs(iter2 - y[3]) <= size_obs:
                    myfile.write('+')
                elif abs(iter - x[4]) <= size_obs and abs(iter2 - y[4]) <= size_obs:
                    myfile.write('+')
                else:
                    myfile.write(' ')
            myfile.write('+\n')

        for iter in range(0, size):
            myfile.write('+')
        myfile.write('\n')


        #data = myfile.read()
    return data.strip()



def drawmaze(maze, set1=[], set2=[], c='#', c2='*'):
    """returns an ascii maze, drawing eventually one (or 2) sets of positions.
        useful to draw the solution found by the astar algorithm
    """
    set1 = list(set1)
    set2 = list(set2)
    lines = maze.strip().split('\n')
    width = len(lines[0])
    height = len(lines)
    result = ''
    for j in range(size-1):
        for i in range(size):
            if (i, j) in set1:
                result = result + c
            elif (i, j) in set2:
                result = result + c2
            else:
                result = result + lines[j][i]
        result = result + '\n'
    return result


class MazeSolver(AStar):

    """sample use of the astar algorithm. In this exemple we work on a maze made of ascii characters,
    and a 'node' is just a (x,y) tuple that represents a reachable position"""

    def __init__(self, maze):
        self.lines = maze.strip().split('\n')
        self.width = len(self.lines[0])
        self.height = len(self.lines)

    def heuristic_cost_estimate(self, n1, n2):
        """computes the 'direct' distance between two (x,y) tuples"""
        (x1, y1) = n1
        (x2, y2) = n2
        return math.hypot(x2 - x1, y2 - y1)

    def distance_between(self, n1, n2):
        """this method always returns 1, as two 'neighbors' are always adajcent"""
        return 1

    def neighbors(self, node):
        """ for a given coordinate in the maze, returns up to 4 adjacent(north,east,south,west)
            nodes that can be reached (=any adjacent coordinate that is not a wall)
        """
        x, y = node
        return[(nx, ny) for nx, ny in[(x, y - 1), (x, y + 1), (x - 1, y), (x + 1, y), (x+1, y - 1), (x-1, y - 1),(x+1, y + 1),(x-1, y + 1)]if 0 <= nx < self.width and 0 <= ny < self.height and self.lines[ny][nx] == ' ']

# generate an ascii maze
x = [8, 1, 3, 4, 5]
y = [6, 1, 8, 9, 2]
size = 40
m = make_maze(size, x, y)

# what is the size of it?
w = len(m.split('\n')[0])
h = len(m.split('\n'))

start = (15, 2)  # we choose to start at the upper left corner
goal = (16, 2)  # we want to reach the lower right corner

# let's solve it
foundPath = list(MazeSolver(m).astar(start, goal))

# print the solution
print(drawmaze(m, list(foundPath)))
#open('maze.txt', 'w').close()