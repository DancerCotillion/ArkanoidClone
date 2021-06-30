#include "Walls.h"
#include <assert.h>

Walls::Walls(const Rectf& innerBounds_in, float thickness_in, Color baseColor)
	:
	innerBounds(innerBounds_in),
	thickness(thickness_in),
	bev(baseColor)
{
	assert(innerBounds.GetExpanded(thickness).isContainedBy(Graphics::GetScreenRect())); 
}

const Rectf& Walls::getInnerBounds() const
{
	return innerBounds; 
}

void Walls::Draw(Graphics& gfx) const
{
	bev.DrawBeveledFrame(innerBounds.GetExpanded(thickness), int(thickness), gfx); 
}
