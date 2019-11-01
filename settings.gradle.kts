import java.net.URI

val unnecessaryDependencyPrefix = "me.ddevil.unnecessary.library"

fun unnecessaryThirdPartyLibrary(name: String) = "$unnecessaryDependencyPrefix:$name"


include(":thirdparty:glfw", ":thirdparty:glew", ":thirdparty:glm", ":thirdparty:entityx")
include(":modules:base")
