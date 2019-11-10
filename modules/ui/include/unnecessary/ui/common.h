#include <glm/vec4.hpp>
#include <string>

namespace un {
    struct Graphic {
        glm::vec4 color;
    };
    struct View {
        /**
         * How "hidden" or "shown" this view currently is.
         * Many properties may be updated in proportion to this variable, for example:
         * - Opacity
         * - Translation
         * - Scale
         */
        float presentationScalar;
    };
    struct Label {
        std::string text;
    };

}