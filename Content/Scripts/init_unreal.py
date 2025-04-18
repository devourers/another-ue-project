import unreal
import os

print("loading custom editor python scripts")
INDEX = ".index.txt"
LOCK = ".lock.txt"


@unreal.uclass()
class InteractableConfigSpawner(unreal.PythonEditorHelper):
    @unreal.ufunction(override=True)
    def create_interactable_configs(self, level_name, loader_name):
        level_dir = os.path.join(unreal.Paths.project_dir(), "Content", "Configs", "Levels", level_name)
        level_index_path = os.path.join(level_dir, INDEX)
        level_lock_path = os.path.join(level_dir, LOCK)

        with open(level_lock_path, "w") as f:
            f.write("ADD")

        with open(level_index_path, "a") as f:
            f.write(loader_name)
            f.write("\n")

        loader_dialogue_dir = os.path.join(level_dir, "Dialogue", loader_name + ".json")
        with open(loader_dialogue_dir, "w") as f: pass

        loader_inventory_dir = os.path.join(level_dir, "Inventory", loader_name + ".json")
        with open(loader_inventory_dir, "w") as f: pass

        loader_lore_dir = os.path.join(level_dir, "Lore", loader_name + ".json")
        with open(loader_lore_dir, "w") as f: pass

        loader_notes_dir = os.path.join(level_dir, "Notes", loader_name + ".json")
        with open(loader_notes_dir, "w") as f: pass

    @unreal.ufunction(override=True)
    def get_level_index(self):
        levels_dir = os.path.join(unreal.Paths.project_dir(), "Content", "Configs", "Levels")
        levels = []
        index_path = os.path.join(levels_dir, INDEX)
        with open(index_path, "r", encoding="utf8") as f:
            levels = [level.strip() for level in f.readlines()]
        return levels

    @unreal.ufunction(override=True)
    def get_actors_index(self, level):
        actors = []
        actors_dir = os.path.join(unreal.Paths.project_dir(), "Content", "Configs", "Levels", level)
        index_path = os.path.join(actors_dir, INDEX)
        with open(index_path, "r", encoding="utf8") as f:
            actors = [actor.strip() for actor in f.readlines()]
        return actors

    @unreal.ufunction(override=True)
    def init_level_folder_structure(self, level_name):
        levels_dir = os.path.join(unreal.Paths.project_dir(), "Content", "Configs", "Levels")
        index_path = os.path.join(levels_dir, INDEX)
        lock_path = os.path.join(levels_dir, LOCK)

        with open(lock_path, "w") as f:
            f.write("ADD")

        with open(index_path, "a") as f:
            f.write(level_name)
            f.write("\n")


        level_dir = os.path.join(levels_dir, level_name)
        os.mkdir(level_dir)

        level_dialogue_dir = os.path.join(level_dir, "Dialogue")
        os.mkdir(level_dialogue_dir)

        level_inventory_dir = os.path.join(level_dir, "Inventory")
        os.mkdir(level_inventory_dir)

        level_lore_dir = os.path.join(level_dir, "Lore")
        os.mkdir(level_lore_dir)

        level_notes_dir = os.path.join(level_dir, "Notes")
        os.mkdir(level_notes_dir)

        new_index_path = os.path.join(level_dir, INDEX)
        new_lock_path = os.path.join(level_dir, LOCK)
        with open(new_index_path, "w") as f: pass
        with open(new_lock_path, "w") as f: pass


