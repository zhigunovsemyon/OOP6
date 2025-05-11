#include "graphic_obj.h"

void GraphicObject::left_(){ pos_.x -= step; }

void GraphicObject::right_() { pos_.x += step; }

void GraphicObject::down_(){ pos_.y += step; }

void GraphicObject::up_(){ pos_.y -= step; }