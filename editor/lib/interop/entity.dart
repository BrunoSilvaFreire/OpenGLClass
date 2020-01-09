import 'package:rxdart/subjects.dart';

import 'components.dart';

class Entity {
  final int id;
  final int version;
  Entity(this.id, this.version);
  @override
  String toString() {
    return "Entity(id: $id, version: $version)";
  }

  Stream<List<Component>> get components async* {
    yield [
      Component("Transform", [ComponentField("value")]),
      Component("Drawable", [ComponentField("geometry")]),
    ];
  }
}
