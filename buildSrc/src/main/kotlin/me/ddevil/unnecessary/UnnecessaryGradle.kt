package me.ddevil.unnecessary

import org.gradle.api.Project
import org.gradle.api.artifacts.Configuration
import org.gradle.api.artifacts.type.ArtifactTypeDefinition
import org.gradle.api.attributes.Usage
import org.gradle.api.internal.artifacts.ArtifactAttributes
import java.io.File

val unnecessaryDependencyGroup = "me.ddevil.unnecessary.library"

fun unnecessaryThirdPartyLibrary(name: String) = "$unnecessaryDependencyGroup:$name"

fun Configuration.thirdPartyHeadersAttributes(project: Project) {
    isCanBeConsumed = true
    isCanBeResolved = false
    outgoing {
        artifact(File(project.projectDir, "include"))
    }
    val cppUsage = project.objects.named(Usage::class.java, Usage.C_PLUS_PLUS_API)
    attributes {
        attribute(org.gradle.language.cpp.CppBinary.DEBUGGABLE_ATTRIBUTE, true)
        attribute(ArtifactAttributes.ARTIFACT_FORMAT, ArtifactTypeDefinition.DIRECTORY_TYPE)
        attribute(Usage.USAGE_ATTRIBUTE, cppUsage)
    }
}