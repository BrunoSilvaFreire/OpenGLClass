import me.ddevil.unnecessary.thirdPartyHeadersAttributes

configurations {
    val headers by creating {

        thirdPartyHeadersAttributes(project)
    }
    val library by creating {
        isCanBeConsumed = true
        isCanBeResolved = false
        extendsFrom(headers)
        attributes {
            attribute(Usage.USAGE_ATTRIBUTE, project.objects.named(Usage::class.java, Usage.NATIVE_LINK))
        }
    }
}