#ifndef _AABB_H
#define _AABB_H

struct pt_cord
{
    int x;
    int y;
};

using Point = pt_cord;

class AABB
{


public:
    AABB(int top, int left, int bottom, int right);
  
    float get_top() const;
    float get_left() const;
    float get_bottom() const;
    float get_right() const;
  
    bool contain (int x, int y);
    bool contain ( struct pt_cord pt );
    bool intersect (AABB boxb);
    AABB min_bounding_box(AABB boxa);
    bool may_collide( AABB from, AABB to );
    bool collision_point(AABB from, AABB to, pt_cord& where);

private:
    float top{0};
    float left{0};
    float bottom{0};
    float right{0};
};

#endif
