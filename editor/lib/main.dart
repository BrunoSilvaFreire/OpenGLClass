import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:unnecessary_editor/editor.dart';

void main() {
    debugDefaultTargetPlatformOverride = TargetPlatform.fuchsia;
    runApp(UnnecessaryEditor());
}