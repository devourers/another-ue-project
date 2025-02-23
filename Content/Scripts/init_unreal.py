import unreal
import os

print("loading custom editor python scripts")
INDEX = ".index.txt"
LOCK = ".lock.txt"


@unreal.uclass()
class InteractableConfigSpawner(unreal.PythonEditorHelper):
    @unreal.ufunction(override=True)
    def create_interactable_configs(self, loader_name):
        unreal.log_warning("hello world but from python class")

    @unreal.ufunction(override=True)
    def get_level_index(self):
        levels_dir = os.path.join(unreal.Paths.project_dir(), "Content", "Configs", "Levels")
        levels = []
        index_path = os.path.join(levels_dir, INDEX)
        with open(index_path, "r", encoding="utf8") as f:
            levels = [level.strip() for level in f.readlines()]
        return levels