#pragma once
#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>

enum class Category {
    SCIENCE_FICTION_FANTASY,
    HORROR,
    COMEDY,
    TENSION
};

// Overloaded comparison operator for Category enum class
inline bool operator==(const Category& lhs, const Category& rhs) {
    return static_cast<int>(lhs) == static_cast<int>(rhs);
}

#endif // CATEGORY_H

