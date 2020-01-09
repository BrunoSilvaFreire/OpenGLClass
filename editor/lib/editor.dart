import 'package:flutter/material.dart';
import 'package:rxdart/subjects.dart';
import 'package:unnecessary_editor/inspector.dart';
import 'package:unnecessary_editor/hierarchy.dart';
import 'package:unnecessary_editor/interop/entity.dart';
import 'package:unnecessary_editor/interop/scene.dart';

class UnnecessaryEditorMenu {
  final String label;
  UnnecessaryEditorMenu(this.label);
}

class UnnecessaryEditorBloc {
  static UnnecessaryEditorBloc _instance;
  static UnnecessaryEditorBloc instance() {
    return _instance ??= UnnecessaryEditorBloc._();
  }

  BehaviorSubject<Entity> _selected;
  BehaviorSubject<Entity> get selected => _selected;
  UnnecessaryEditorBloc._() {
    _selected = BehaviorSubject();
  }
}

class UnnecessaryEditor extends StatelessWidget {
  static final List<UnnecessaryEditorMenu> kMenus = [
    UnnecessaryEditorMenu("File")
  ];
  static const double kModuleWidth = 400;
  static const double kFileBrowserHeight = 200;
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Unnecessary Editor',
      theme: ThemeData.dark(),
      home: Scaffold(
        appBar: AppBar(
          title: Row(
            children: <Widget>[
              FlatButton.icon(
                icon: Icon(Icons.build),
                label: Text("File"),
                onPressed: () {},
              ),
              FlatButton.icon(
                icon: Icon(Icons.person),
                label: Text("Entities"),
                onPressed: () {},
              ),
            ],
          ),
        ),
        body: Stack(
          children: <Widget>[
            Positioned(
              child: Inspector(),
              top: 8,
              bottom: 8,
              right: 8,
              width: kModuleWidth,
            ),
            Positioned(
              child: Padding(
                child: SceneView(),
                padding: EdgeInsets.all(8),
              ),
              top: 0,
              left: kModuleWidth,
              right: kModuleWidth,
              bottom: kFileBrowserHeight,
            ),
            Positioned(
              child: Hierarchy(),
              top: 8,
              bottom: kFileBrowserHeight + 8,
              left: 8,
              width: kModuleWidth,
            )
          ],
        ),
      ),
    );
  }
}
