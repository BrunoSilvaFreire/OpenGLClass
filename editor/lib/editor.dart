import 'dart:async';

import 'package:flutter/material.dart';
import 'package:rxdart/subjects.dart';
import 'package:unnecessary_editor/inspector.dart';
import 'package:unnecessary_editor/hierarchy.dart';
import 'package:unnecessary_editor/interop/entity.dart';
import 'package:unnecessary_editor/interop/scene.dart';
import 'package:unnecessary_editor/project.dart';

class UnnecessaryEditorMenu extends StatefulWidget {
  final IconData icon;
  final String label;
  UnnecessaryEditorMenu(this.label, this.icon, this.items);

  final List<PopupMenuEntry<int>> items;

  @override
  _UnnecessaryEditorMenuState createState() => _UnnecessaryEditorMenuState();
}

class _UnnecessaryEditorMenuState extends State<UnnecessaryEditorMenu> {
  void showButtonMenu() {
    final PopupMenuThemeData popupMenuTheme = PopupMenuTheme.of(context);
    final RenderBox button = context.findRenderObject() as RenderBox;
    final RenderBox overlay =
        Overlay.of(context).context.findRenderObject() as RenderBox;
    final RelativeRect position = RelativeRect.fromRect(
      Rect.fromPoints(
        button.localToGlobal(Offset.zero, ancestor: overlay),
        button.localToGlobal(button.size.bottomRight(Offset.zero),
            ancestor: overlay),
      ),
      Offset.zero & overlay.size,
    );
    // Only show the menu if there is something to show
    if (widget.items.isNotEmpty) {
      showMenu(
        context: context,
        elevation: popupMenuTheme.elevation,
        items: widget.items,
        position: position,
        shape: popupMenuTheme.shape,
        color: popupMenuTheme.color,
      ).then<void>((newValue) {
        // if (!mounted) return null;
        // if (newValue == null) {
        //   if (widget.onCanceled != null) widget.onCanceled();
        //   return null;
        // }
        // if (widget.onSelected != null) widget.onSelected(newValue);
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    return FlatButton.icon(
      icon: Icon(widget.icon),
      label: Text(widget.label),
      onPressed: showButtonMenu,
    );
  }
}

class UnnecessaryEditorBloc {
  static UnnecessaryEditorBloc _instance;
  static UnnecessaryEditorBloc instance() {
    return _instance ??= UnnecessaryEditorBloc._();
  }

  BehaviorSubject<Entity> _selected;
  BehaviorSubject<List<Project>> _projects;
  BehaviorSubject<Entity> get selected => _selected;

  Stream<List<Project>> get projects => _projects;
  StreamController<Project> _projectAddition;
  Sink<Project> get projectAddition => _projectAddition;
  UnnecessaryEditorBloc._() {
    _selected = BehaviorSubject();
    _projects = BehaviorSubject()..add([]);
    _projectAddition = StreamController<Project>()
      ..stream.listen((p) {
        _projects.add(_projects.value..add(p));
      });
  }
  void close() {
    _selected.close();
    _projects.close();
    _projectAddition.close();
  }
}

class UnnecessaryEditor extends StatelessWidget {
  static const double kModuleWidth = 400;
  static const double kFileBrowserHeight = 200;
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        automaticallyImplyLeading: false,
        title: Row(
          children: <Widget>[
            UnnecessaryEditorMenu("File", Icons.build, [
              PopupMenuItem(
                child: Text("Close project"),
              )
            ])
          ],
        ),
      ),
      body: Stack(
        children: <Widget>[
          Positioned(
            child: Padding(
              padding: EdgeInsets.all(8),
              child: Inspector(),
            ),
            top: 0,
            bottom: 0,
            right: 0,
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
            child: Padding(
              padding: EdgeInsets.all(8),
              child: Hierarchy(),
            ),
            top: 0,
            bottom: kFileBrowserHeight,
            left: 0,
            width: kModuleWidth,
          ),
          Positioned(
            child: Padding(
              padding: EdgeInsets.all(8),
              child: Card(),
            ),
            height: kFileBrowserHeight,
            bottom: 0,
            left: 0,
            right: kModuleWidth,
          )
        ],
      ),
    );
  }
}
