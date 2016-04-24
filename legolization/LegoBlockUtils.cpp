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

bool LegoBlockUtils::are_adjacent(LegoBlock *b1, LegoBlock *b2) {

    bool overlapping_x = b1->x == b2->x
                         || (b1->x < b2->x && b1->x + b1->sx > b2->x)
                         || (b1->x > b2->x && b1->x < b2->x + b2->sx);

    bool overlapping_y = b1->y == b2->y
                         || (b1->y < b2->y && b1->y + b1->sy > b2->y)
                         || (b1->y > b2->y && b1->y < b2->y + b2->sy);

    return b1->z == b2->z
              && ((overlapping_x && (b1->y + b1->sy == b2->y || b1->y == b2->y + b2->sy))
                  || (overlapping_y && (b1->x + b1->sx == b2->x || b1->x == b2->x + b2->sx)));
}

bool LegoBlockUtils::can_colors_merge(LegoBlock *b1, LegoBlock *b2) {
    return (b1->ignore_color
            || b2->ignore_color
            || (b1->r == b2->r && b1->g == b2->g && b1->b == b2->b)
            || ((rand() % SAMPLE_COUNT) / (SAMPLE_COUNT * 1.0) < MERGE_PROBABILITY)
            );
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

int LegoBlockUtils::overlap(LegoBlock *b1, LegoBlock *b2) {
    assert(is_stacked_on(b1, b2));
    int overlapping_x = 0;
    if (b1->x == b2->x) {
        overlapping_x = min((short) b1->sx,(short) b2->sx);
    } else if (b1->x > b2->x) {
        overlapping_x = min((short)b1->sx, (short)(b2->x + b2->sx - b1->x));
    } else {
        overlapping_x = min((short)b2->sx, (short)(b1->x + b1->sx - b2->x));
    }

    int overlapping_y = 0;
    if (b1->y == b2->y) {
        overlapping_y = min((short)b1->sy, (short)b2->sy);
    } else if (b1->x > b2->x) {
        overlapping_y = min((short)b1->sy,  (short) (b2->y + b2->sy - b1->y));
    } else {
        overlapping_y = min((short)b2->sy, (short) (b1->y + b1->sy - b2->y));
    }

    return overlapping_x * overlapping_y;
}

list<pair<int, int> > LegoBlockUtils::overlaps(LegoBlock *b1, LegoBlock *b2) {
    list<pair<int, int> > points;
    for (int x = 0; x < b1->sx; x++) {
        for (int y = 0; y < b1->sy; y++) {
            int px = b1->x + x;
            int py = b1->y + y;

            if (px >= b2->x && px < b2->x + b2->sx) {
                if (py >= b2->y && py < b2->y + b2->sy) {
                    points.push_back(make_pair(x, y));
                }
            }
        }
    }

    assert(overlap(b1, b2) == points.size());

    return points;
}


short LegoBlockUtils::get_merge_color(LegoBlock *b1, LegoBlock *b2) {
    if (b1->ignore_color && b2->ignore_color)
        return 0;
    else if (b1->ignore_color)
        return 2;
    else if (b2->ignore_color)
        return 1;
    else
        return rand() % 2 + 1;
}

LegoBlock* LegoBlockUtils::merge(LegoBlock *b1, LegoBlock *b2) {
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
    } else {
        b->set_color(0, 0, 255);
        b->set_ignore_color();
    }

    return b;
}
