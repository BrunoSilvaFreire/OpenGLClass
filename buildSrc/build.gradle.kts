buildscript {
    repositories {
        mavenCentral()
        jcenter()
        gradlePluginPortal()
    }

    dependencies {
        classpath(kotlin("gradle-plugin"))
    }
}

plugins {
    `kotlin-dsl`
}
repositories {
    jcenter()
}