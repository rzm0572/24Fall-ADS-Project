import random
import os

# Generate queries
def queryGenerator(dst, batch_size, vertice_num):
    lines = [str(batch_size)]
    for i in range(batch_size):
        lines.append("%s %s" % (random.randint(0, vertice_num-1), random.randint(0, vertice_num-1)))
    
    with open(dst, "w+") as f:
        f.write("\n".join(lines))

# Do pre-processing on the graph file
def graphProcessor(src, dst, we=False):
    lines = []
    with open(src, "r") as f:
        read_lines = f.readlines()
        
        num_vertice, num_edge = map(int, read_lines[4].split()[2:4])

        if we:
            lines.append(" ".join(read_lines[4].split()[2:4]))
            for line in read_lines[7:]:
                lines.append(" ".join(line.split()[1:]))
        
        f.close()
    
    if we:
        with open(dst, "w+") as f:
            f.write("\n".join(lines))
            f.close()
    
    return num_vertice, num_edge

# For raw data of each region, generate a processed graph file and three corresponding query list files
if __name__ == "__main__":
    raw = os.listdir("./data/raw")
    for filename in raw:
        if filename.endswith(".gr"):
            num_vertice, num_edge = graphProcessor(os.path.join("./data/raw", filename), os.path.join("./data/processed", f"{filename.split(".")[1]}.gr"), we=True)
            print(f"{filename} processed, num_vertice: {num_vertice}, num_edge: {num_edge}.")

            for i in range(3):
                queryGenerator(os.path.join("./data/queries", f"{filename.split(".")[1]}_{i}.qry"), 1000, num_vertice)
                print(f"{filename.split(".")[1]}_{i}.qry generated.")
