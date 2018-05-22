import copy

def permutate(arr, keyMap):
    return list(map(lambda x:arr[keyMap[x[1]]], zip(arr, range(len(arr)))))

# 记录了正六面体的二十四种面置换方式。
PERMUTATION_LIST = [
        [0,1,2,3,4,5],
        [2,3,1,0,4,5],
        [1,0,3,2,4,5],
        [3,2,0,1,4,5],

        [1,0,2,3,5,4],
        [3,2,1,0,5,4],
        [0,1,3,2,5,4],
        [2,3,0,1,5,4],

        [4,5,2,3,1,0],
        [2,3,5,4,1,0],
        [5,4,3,2,1,0],
        [3,2,4,5,1,0],

        [5,4,2,3,0,1],
        [3,2,5,4,0,1],
        [4,5,3,2,0,1],
        [2,3,4,5,0,1],

        [4,5,1,0,3,2],
        [0,1,4,5,3,2],
        [5,4,0,1,3,2],
        [1,0,5,4,3,2],

        [5,4,1,0,2,3],
        [1,0,4,5,2,3],
        [4,5,0,1,2,3],
        [0,1,5,4,2,3],

    ]
def permutationOfHexahedron(arr):
    # 传入一个长为 6 的 list arr，传出按正六面体旋转群旋转后的全部排列
    assert(isinstance(arr, list))
    assert(len(arr) == 6)

    result = [permutate(arr, permutation) for permutation in PERMUTATION_LIST]
    return result

class PrismProblem(object):
    def __init__(self, colorIndex, cubes):
        # cubes : n 个立方体的列表，每个立方体用一个长度为 6 的数字列表表示其 6 个面的颜色。
        # colorIndex : 一个字符串，起颜色索引的作用，如 colorIndex[i] = 'R' 表示第 i 个颜色为 'R'。
        self.colorIndex = colorIndex
        self.cubes = cubes
        self.n = len(cubes)
        self.permutatedCubes = [permutationOfHexahedron(cube) for cube in self.cubes]

    def startBacktrack(self):
        self.piledCubes = [None] * self.n   # 自下到上的立方体放置方案，在填充之后类似于 [[0,2,1,3,0,0], [3,0,2,1,0,1], ...]
        self.result = []
        self._backtrack(0)
        return self.result

    def _backtrack(self, depth):
        if depth >= self.n:
            self.result.append('\n'.join([''.join([self.colorIndex[color] for color in cube]) for cube in self.piledCubes]))
            return

        for permutatedCube in self.permutatedCubes[depth]:
            # 对于第 depth 个立方体的所有可能旋转
            self.piledCubes[depth] = permutatedCube
            # 如果发现一侧撞色，则不展开它
            if len(self.result) != 0:
                return
            valid = True
            for side in range(4):
                thisSide = [cube[side] for cube in self.piledCubes[0:depth + 1]]    # 从第 0 个到第 depth 个立方体这一侧的颜色
                if len(set(thisSide)) != len(thisSide):  # 如果这些颜色有重复
                    valid = False
                    break

            if valid:
                self._backtrack(depth + 1)

def main():
    colorIndex = "RGBY"
    cubes = [
        [0,2,1,3,0,0],
        [3,0,2,1,0,1],
        [2,1,0,2,1,3],
        [1,3,3,0,2,2]
        ]
    result = PrismProblem(colorIndex, cubes).startBacktrack()
    print("原立方体：")
    print('\n'.join([''.join([colorIndex[color] for color in cube]) for cube in cubes]))

    print("堆叠立方体：")

    for line in result:
        print(line)
        print("")
     
    print("运行完成。")

    colorIndex = "RGBY"
    cubes = [
        [0,2,1,3,0,0],
        [3,0,2,1,0,1],
        [2,1,0,2,1,3],
        [1,1,3,0,3,2]
        ]
    result = PrismProblem(colorIndex, cubes).startBacktrack()
    print("原立方体：")
    print('\n'.join([''.join([colorIndex[color] for color in cube]) for cube in cubes]))

    print("堆叠立方体：")

    for line in result:
        print(line)
        print("")
     
    print("运行完成。")

    
main()