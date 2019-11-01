import org.gradle.api.internal.artifacts.ArtifactAttributes

plugins {
    `cpp-library`
}
configurations.all {
    println(this)
    println(attributes.keySet().joinToString())
}
configurations {
    val headersOnly by creating {
        attributes {
            val u = project.objects.named(Usage::class, Usage.C_PLUS_PLUS_API)
            attribute(Usage.USAGE_ATTRIBUTE, u)
            attribute(ArtifactAttributes.ARTIFACT_FORMAT, ArtifactTypeDefinition.DIRECTORY_TYPE)
        }
    }
    api {
        extendsFrom(headersOnly)
    }
}

dependencies {
    cppApiElements(project(":thirdparty:entityx"))
    add("headersOnly", project(":thirdparty:glfw"))
    add("headersOnly", project(":thirdparty:glew"))
    add("headersOnly", project(":thirdparty:glm"))
}
