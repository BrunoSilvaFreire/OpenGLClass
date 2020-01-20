import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:unnecessary_editor/project.dart';

void main() {
  debugDefaultTargetPlatformOverride = TargetPlatform.fuchsia;
  runApp(
    MaterialApp(
      title: 'Unnecessary Editor',
      theme: ThemeData.dark(),
      home: Projects(),
    ),
  );
}
