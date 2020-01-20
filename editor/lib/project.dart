import 'package:flutter/material.dart';
import 'package:flutter_form_bloc/flutter_form_bloc.dart';
import 'package:form_bloc/form_bloc.dart';
import 'package:unnecessary_editor/editor.dart';

class Project {
  final String name;

  Project(this.name);
}

class Projects extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    var theme = Theme.of(context);
    var bloc = UnnecessaryEditorBloc.instance();
    return Scaffold(
      body: Container(
        padding: const EdgeInsets.all(128),
        child: Card(
          child: Padding(
            padding: const EdgeInsets.all(16.0),
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: <Widget>[
                Text(
                  "Projects",
                  style: theme.textTheme.display1,
                ),
                ButtonBar(
                  children: <Widget>[
                    RaisedButton(
                      child: Text("Create new project"),
                      onPressed: () {
                        showDialog(
                          context: context,
                          builder: (_) => ProjectCreator(),
                        );
                      },
                    )
                  ],
                ),
                StreamBuilder<List<Project>>(
                  stream: bloc.projects,
                  builder: (BuildContext context, AsyncSnapshot snapshot) {
                    if (!snapshot.hasData) {
                      return Expanded(
                        child: Center(
                          child: CircularProgressIndicator(),
                        ),
                      );
                    }
                    var list = snapshot.data;
                    if (list.isEmpty) {
                      return Expanded(
                        child: Center(
                          child: Text("No projects available."),
                        ),
                      );
                    }
                    return GridView.extent(
                      children: <Widget>[
                        for (var p in list)
                          Card(
                            shape: RoundedRectangleBorder(
                              borderRadius: BorderRadius.circular(4),
                              side: BorderSide(
                                color: Colors.grey.withOpacity(0.2),
                                width: 2,
                              ),
                            ),
                            elevation: 0,
                            child: InkWell(
                              borderRadius: BorderRadius.circular(4),
                              onTap: () {
                                Navigator.push(
                                  context,
                                  MaterialPageRoute(
                                    builder: (context) => UnnecessaryEditor(),
                                  ),
                                );
                              },
                              child: Container(
                                child: Column(
                                  children: [
                                    ListTile(
                                      title: Text(p.name),
                                    ),
                                  ],
                                ),
                              ),
                            ),
                          )
                      ],
                      maxCrossAxisExtent: 300,
                      shrinkWrap: true,
                    );
                  },
                )
              ],
            ),
          ),
        ),
      ),
    );
  }
}

class ProjectCreator extends StatefulWidget {
  @override
  _ProjectCreatorState createState() => _ProjectCreatorState();
}

class _ProjectCreatorState extends State<ProjectCreator> {
  ProjectCreatorBloc _bloc;
  @override
  void initState() {
    _bloc ??= new ProjectCreatorBloc();
    super.initState();
  }

  @override
  void dispose() {
    _bloc?.close();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return FormBlocListener(
      formBloc: _bloc,
      onSuccess: (context, s) {
        Navigator.pop(context);
      },
      child: AlertDialog(
        title: Text("Create new project"),
        content: Column(
          mainAxisSize: MainAxisSize.min,
          children: <Widget>[
            TextFieldBlocBuilder(
              textFieldBloc: _bloc.nameField,
              decoration: InputDecoration(
                icon: Icon(Icons.label),
                labelText: "Name",
              ),
            ),
          ],
        ),
        actions: <Widget>[
          RaisedButton(
            child: Text("Create"),
            onPressed: () {
              _bloc.submit();
            },
          )
        ],
      ),
    );
  }
}

class ProjectCreatorBloc extends FormBloc<String, String> {
  final nameField = TextFieldBloc();
  @override
  List<FieldBloc> get fieldBlocs => [nameField];

  @override
  Stream<FormBlocState<String, String>> onSubmitting() async* {
    yield state.toLoading();
    var bloc = UnnecessaryEditorBloc.instance();
    bloc.projectAddition.add(Project(nameField.value));
    yield state.toSuccess();
  }
}
