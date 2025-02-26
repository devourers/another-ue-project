import unreal
import os
import sys

INDEX = ".index.txt"
LOCK = ".lock.txt"

def main():
    level = sys.argv[1]
    actors = []
    actors_dir = os.path.join(unreal.Paths.project_dir(), "Content", "Configs", "Levels", level)
    index_path = os.path.join(actors_dir, INDEX)
    with open(index_path, "r", encoding="utf8") as f:
        actors = [actor.strip() for actor in f.readlines()]
    return actors

if __name__ == "__main__":
    print(" ".join(main()).strip())