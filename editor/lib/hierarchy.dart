import 'package:flutter/material.dart';
import 'package:rxdart/rxdart.dart';
import 'package:unnecessary_editor/editor.dart';
import 'package:unnecessary_editor/interop/entity.dart';
import 'package:unnecessary_editor/interop/scene.dart';

class Hierarchy extends StatefulWidget {
  @override
  _HierarchyState createState() => _HierarchyState();
}

class _HierarchyState extends State<Hierarchy> {
  final Scene scene = Scene(
    "Dummy Scene",
    [Entity(0, 0), Entity(1, 0), Entity(2, 0), Entity(3, 0)],
  );
  @override
  Widget build(BuildContext context) {
    var bloc = UnnecessaryEditorBloc.instance();
    return Card(
      child: StreamBuilder<Entity>(
          stream: bloc.selected,
          builder: (context, snapshot) {
            Entity selected;
            if (!snapshot.hasData) {
              selected = null;
            } else {
              selected = snapshot.data;
            }
            return Column(
              children: <Widget>[
                ListTile(
                  leading: Icon(Icons.transform),
                  title: Text("Hierarchy"),
                  subtitle: Text(scene.name),
                ),
                for (var e in scene.entities)
                  ListTile(
                    leading: Icon(Icons.person),
                    title: Text(e.toString()),
                    selected: selected == e,
                    dense: true,
                    onTap: () {
                      bloc.selected.add(e);
                    },
                  )
              ],
            );
          }),
    );
  }
}
