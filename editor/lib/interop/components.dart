class ComponentField {
  final String name;

  ComponentField(this.name);
}

class Component {
  final String name;
  final List<ComponentField> fields;

  Component(this.name, this.fields);
}
