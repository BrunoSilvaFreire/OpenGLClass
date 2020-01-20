class UnnecessaryEngine {
  final String version;
  final List<UnnecessaryModule> availableModules;

  UnnecessaryEngine(this.version, this.availableModules);
}

enum UnnecessaryModuleStatus { eDisabled, eEnabled, eError }

class UnnecessaryModule {
  final String name;
  final String identifier;
  
  UnnecessaryModuleStatus _status = UnnecessaryModuleStatus.eDisabled;

  UnnecessaryModule(this.name, this.identifier);

  UnnecessaryModuleStatus get status => _status;
}

class UnnecessaryProject {
  final String name;

  UnnecessaryProject(this.name);
}
