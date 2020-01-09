import 'package:flutter/material.dart';
import 'package:unnecessary_editor/editor.dart';
import 'package:unnecessary_editor/interop/components.dart';
import 'package:unnecessary_editor/interop/entity.dart';

class Inspector extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    var bloc = UnnecessaryEditorBloc.instance();
    return Card(
      child: StreamBuilder<Entity>(
          stream: bloc.selected,
          builder: (context, snapshot) {
            var e = snapshot.data;
            return Column(
              children: <Widget>[
                ListTile(
                  leading: Icon(Icons.info),
                  title: Text("Inspector"),
                  subtitle:
                      Text(e == null ? "No entity selected" : e.toString()),
                ),
                if (e != null)
                  StreamBuilder<List<Component>>(
                      stream: e.components,
                      builder: (context, snapshot) {
                        var c = snapshot.data;
                        if (c == null) {
                          return Center(child: CircularProgressIndicator());
                        }
                        return Column(
                          children: [
                            for (var component in c) ...[
                              ListTile(
                                leading: Icon(Icons.widgets),
                                title: Text(component.name),
                                dense: true,
                              ),
                              for (var field in component.fields)
                                Text(field.name)
                            ]
                          ],
                        );
                      })
              ],
            );
          }),
    );
  }
}
