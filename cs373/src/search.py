# ----------
# User Instructions:
#
# Define a function, search() that returns a list
# in the form of [optimal path length, row, col]. For
# the grid shown below, your function should output
# [11, 4, 5].
#
# If there is no valid path from the start point
# to the goal, your function should return the string
# 'fail'
# ----------

# Grid format:
#   0 = Navigable space
#   1 = Occupied space

grid = [[0, 0, 1, 0, 0, 0],
        [0, 0, 1, 0, 0, 0],
        [0, 0, 0, 0, 1, 0],
        [0, 0, 1, 1, 1, 0],
        [0, 0, 0, 0, 1, 0]]
init = [0, 0]
goal = [len(grid) - 1, len(grid[0]) - 1]
cost = 1

delta = [[-1, 0],  # go up
         [0, -1],  # go left
         [1, 0],  # go down
         [0, 1]]  # go right

delta_name = ['^', '<', 'v', '>']


def search(grid, init, goal, cost):
    open_set = []
    close_set = []
    g_values = []
    path = []
    open_set.append(init)
    g_values.append(0)
    while len(open_set) > 0:
        min_value = min(g_values)
        min_value_index = g_values.index(min_value)
        min_value_loc = open_set[min_value_index]
        if min_value_loc == goal:
            path = [min_value, min_value_loc[0], min_value_loc[1]]
            break
        else:
            # 从open集与g_values中移除掉，并将其放到close集中去
            open_set.remove(min_value_loc)
            g_values.remove(min_value)
            close_set.append(min_value_loc)
            # 生成当前loc移动之后可能的所有位置
            maybe_loc = []
            for d in delta:
                maybe_loc.append([min_value_loc[0] + d[0], min_value_loc[1] + d[1]])
            # 判断是否是有效的loc以及是否已经在close集中
            for loc in maybe_loc:
                if 0 <= loc[0] <= len(grid) - 1 and 0 <= loc[1] <= len(grid[0]) - 1:
                    if grid[loc[0]][loc[1]] != 1 and loc not in close_set:
                        # 将有效loc添加进open集与g_values中（g_values记得+cost）
                        open_set.append(loc)
                        g_values.append(min_value + cost)
    if len(path) == 0:
        return 'fail'
    else:
        return path


print(search(grid, init, goal, cost))
