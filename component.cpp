#include "component.h"
#include "animation.h"

/*-----------------------------------------------------------------------------------------------*/

CAnimation::CAnimation()
{
}

CAnimation::CAnimation(Animation* a) : animation(a)
{
}

Animation* CAnimation::getAnimation()
{
    return animation;
}

/*-----------------------------------------------------------------------------------------------*/

CTransform::CTransform()
{
}

/*-----------------------------------------------------------------------------------------------*/

CBoundingBox::CBoundingBox()
{
}

CBoundingBox::CBoundingBox(const Vec2& s) : size(s), halfSize(s.x/2, s.y/2)
{
}
