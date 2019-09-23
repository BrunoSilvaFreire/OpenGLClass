#include <unnecessary/utility/layout.h>

namespace gl {

    LayoutElement::LayoutElement(uint8_t elementLength, uint8_t elementCount) : elementLength(elementLength),
                                                                                    elementCount(elementCount) {}

    uint8_t LayoutElement::getElementLength() const {
        return elementLength;
    }

    uint8_t LayoutElement::getCount() const {
        return elementCount;
    }

    uint8_t LayoutElement::getSize() const {
        return elementLength * elementCount;
    }

    std::ostream &operator<<(std::ostream &os, const LayoutElement &element) {
        os << "elementLength: " << element.elementLength << " elementCount: " << element.elementCount;
        return os;
    }
}