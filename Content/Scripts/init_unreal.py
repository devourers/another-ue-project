import unreal

print("loading custom editor python scripts")

@unreal.uclass()
class InteractableConfigSpawner(unreal.PythonEditorHelper):
    @unreal.ufunction(override=True)
    def create_interactable_configs(self, loader_name):
        unreal.log_warning("hello world but from python class")