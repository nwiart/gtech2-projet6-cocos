#pragma once


namespace lemmings
{

class AABB
{
public:

	AABB(float x0, float y0, float x1, float y1);

	/// <summary>
	/// Perform a collision test with another AABB.
	/// </summary>
	/// <param name="other">The static AABB to check collision with.</param>
	/// <param name="dx">Distance the AABB wants to move along X</param>
	/// <returns>The new dx</returns>
	float collideX(const AABB& other, float dx) const;

	/// <summary>
	/// Perform a collision test with another AABB.
	/// </summary>
	/// <param name="other">The static AABB to check collision with.</param>
	/// <param name="dx">Distance the AABB wants to move along Y</param>
	/// <returns>The new dy</returns>
	float collideY(const AABB& other, float dy) const;



public:

	float x0;
	float y0;
	float x1;
	float y1;
};

}
