//
// Created by Bijoy Kochar on 3/26/16.
//

#include "LegoBlockUtils.h"
#include "LegoBlock.h"

bool LegoBlockUtils::can_merge(LegoBlock *b1, LegoBlock *b2) {
    return (can_colors_merge(b1, b2)
            && b1->z == b2->z
            && ((b1->x == b2->x
                 && b1->sx == b2->sx
                 && (b1->y + b1->sy == b2->y || b1->y == b2->y + b2->sy)
                 && LegoBlock::has_valid_size(b1->sx, b1->sy + b2->sy))
            || (b1->y == b2->y
                && b1->sy == b2->sy
                && (b1->x + b1->sx == b2->x || b1->x == b2->x + b2->sx)
                && LegoBlock::has_valid_size(b1->sx + b2->sx, b1->sy)))
            && (!(b1->x == b2->x && b1->y == b2->y && b1->z == b2->z)));
}

bool LegoBlockUtils::can_colors_merge(LegoBlock *b1, LegoBlock *b2) {
    return (true || b1->ignore_color
            || b2->ignore_color
            || (b1->r == b2->r && b1->g == b2->g && b1->b == b2->b));
}

bool LegoBlockUtils::are_connected(LegoBlock *b1, LegoBlock *b2) {
    return is_stacked_on(b1, b2) || is_stacked_on(b2, b1);
}

bool LegoBlockUtils::is_stacked_on(LegoBlock *b1, LegoBlock *b2) {
    bool stacked_z = b2->z == b1->z + 1;
    bool overlapping_x = b1->x == b2->x
                         || (b1->x < b2->x && b1->x + b1->sx > b2->x)
                         || (b1->x > b2->x && b1->x < b2->x + b2->sx);
    bool overlapping_y = b1->y == b2->y
                         || (b1->y < b2->y && b1->y + b1->sy > b2->y)
                         || (b1->y > b2->y && b1->y < b2->y + b2->sy);

    return stacked_z && overlapping_x && overlapping_y;
}

short LegoBlockUtils::get_merge_color(LegoBlock *b1, LegoBlock *b2) {
    assert(can_colors_merge(b1, b2));

    if (b1->ignore_color && b2->ignore_color)
        return 0;
    else if (b1->ignore_color)
        return 2;
    return 1;
}

LegoBlock* LegoBlockUtils::merge(LegoBlock *b1, LegoBlock *b2) {
    assert(can_merge(b1, b2));
    LegoBlock *b;

    if (b1->x == b2->x) {
        if (b1->y > b2->y)
            return merge(b2, b1);
        b = new LegoBlock(b1->x, b1->y, b1->z, b1->sx, b1->sy + b2->sy);
    } else if (b1->y == b2->y) {
        if (b1->x > b2->x)
            return merge(b2, b1);
        b = new LegoBlock(b1->x, b1->y, b1->z, b1->sx + b2->sx, b1->sy);
    }

    assert(b != NULL);

    short merge_color = get_merge_color(b1, b2);
    if (merge_color == 1) {
        b->set_color(b1->r, b1->g, b1->b);
    } else if (merge_color == 2) {
        b->set_color(b2->r, b2->g, b2->b);
    }

    return b;
}
