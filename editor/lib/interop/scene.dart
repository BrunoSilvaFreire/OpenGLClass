import 'package:flutter/material.dart';
import 'package:unnecessary_editor/interop/entity.dart';

class Scene {
  final String name;
  final List<Entity> entities;

  Scene(this.name, this.entities);
}

class SceneView extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Card(
      child: Stack(
        children: <Widget>[
          Positioned(
            left: 0,
            right: 0,
            top: 0,
            height: 64,
            child: ListTile(
              leading: Icon(Icons.terrain),
              title: Text("Scene View"),
            ),
          )
        ],
      ),
    );
  }
}
