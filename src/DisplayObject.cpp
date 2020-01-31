#include "DisplayObject.h"

Scene * DisplayObject::getParent()
{
	return m_pParentScene;
}

void DisplayObject::setParent(Scene * parent)
{
	m_pParentScene = parent;
}
