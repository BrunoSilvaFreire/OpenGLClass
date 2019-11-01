import me.ddevil.unnecessary.thirdPartyHeadersAttributes
import me.ddevil.unnecessary.unnecessaryDependencyGroup

group = unnecessaryDependencyGroup
plugins {
    `cpp-library`
}
library {
    publicHeaders {
        from("include")
    }
}

with(components) {
    for (c in this) {
        println(c)
        if (c is CppComponent) {
            println(c.headerFiles.asPath)
        }
    }
}