import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle

color = ['blue', 'green', 'red', 'yellow', 'purple', 'orange', 'brown', 'pink', 'gray', 'olive']

def draw_texture(w, h, textures, path):
    fig = plt.figure(num=1, figsize=(3, 5))
    axes = fig.add_subplot(1, 1, 1)
    axes.set_xlim(0, w)
    axes.set_ylim(0, h)
    axes.set_aspect('equal')
    alpha = np.linspace(0.1, 1, len(textures))
    for texture in textures:
        r = Rectangle(xy=(texture[0], texture[1]), width=texture[2], height=texture[3], fill=True, alpha=alpha[textures.index(texture)], color=color[(textures.index(texture) // 20) % len(color)])
        axes.add_patch(r)
    plt.title(path+"\nTotal height: "+str(h))
    plt.savefig(path, dpi=300)
    fig.delaxes(axes)

def parsing_output(output : str):
    textures = []
    output = output.strip().split('\n')
    flag = False
    h = 0
    time = 0.0
    for line in output:
        line = line.strip()
        if line.startswith("Total height:"):
            h = int(line.split(":")[1].strip())
            flag = True
        elif flag:
            if line.startswith("Running Time:"):
                time = float(line.split(":")[1].strip())
                break
            texture = list(map(int, line.strip().split()))
            textures.append(texture)
    return h, textures, time

if __name__ == "__main__":
    output = """
        Level 1 0 10 0:
        13 10 0 0
        3 7 13 0
        4 5 16 0

        Level 2 0 9 10:
        18 9 0 10
        2 7 18 10

        Level 3 1 9 19:
        12 9 0 19
        5 6 12 19
        1 5 17 19
        1 4 18 19

        Level 4 0 8 28:
        19 8 0 28
        1 7 19 28

        Total height: 36
        0 0 13 10
        0 10 18 9
        0 19 12 9
        0 28 19 8
        18 10 2 7
        13 0 3 7
        19 28 1 7
        12 19 5 6
        16 0 4 5
        17 19 1 5
        18 19 1 4
    """
    w = 20
    h, textures = parsing_output(output)
    draw_texture(w, h, textures)
