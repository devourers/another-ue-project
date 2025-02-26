import unreal
import os

INDEX = ".index.txt"
LOCK = ".lock.txt"

def main():
    levels_dir = os.path.join(unreal.Paths.project_dir(), "Content", "Configs", "Levels")
    levels = []
    index_path = os.path.join(levels_dir, INDEX)
    with open(index_path, "r", encoding="utf8") as f:
        levels = [level.strip() for level in f.readlines()]
    return levels

if __name__ == "__main__":
    print(" ".join(main()).strip())