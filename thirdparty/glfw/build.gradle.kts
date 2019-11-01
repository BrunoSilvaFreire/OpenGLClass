import me.ddevil.unnecessary.thirdPartyHeadersAttributes
import me.ddevil.unnecessary.unnecessaryDependencyGroup

group = unnecessaryDependencyGroup

configurations {
    val headers by creating {
        outgoing {
            artifact(file("include"))
        }
        thirdPartyHeadersAttributes(project)
    }
    val x11 by creating {
        extendsFrom(headers)
        outgoing {
            artifact(file("x11/libglfw3.a"))
        }
        attributes {
            attribute(CppBinary.LINKAGE_ATTRIBUTE, Linkage.STATIC)
        }
    }
}
