

#include "Scene.h"

#include "task1a.h"


bool intersectRayPlane(const float3& p, const float3& d, const float4& plane, float& t)
{
	float3 n = { plane.x, plane.y , plane.z };
	float dn = dot(d, n);

	if (dn == 0.0f)
		return false;

	t = (plane.w - dot(p, n)) / dn;

	if (t < 0.0f)
		return false;

	return true;
}

bool intersectRaySphere(const float3& p, const float3& d, const float3& c, float r, float& t)
{
	// TODO: implement intersection test between a ray and a sphere.
	// If the ray given by start point p and direction d intersects the sphere given by its center c and radius r, assign the ray parameter that corresponds to the first point of intersection to t and return true.
	// Otherwise, return false.
	//
	bool flag = true;
	//Strahparameter q
	float3 q = p - c;
	float t1 = (dot(-d, q) + sqrt( (dot(d, q) * dot(d, q)) - dot(d, d) * (dot(q, q) - (r*r)))) * 1 / dot(d, d);
	float t2 = (dot(-d, q) - sqrt( (dot(d, q) * dot(d, q)) - dot(d, d) * (dot(q, q) - (r*r)))) * 1 / dot(d, d);

	float det = dot(d, q) * dot(d, q) - dot(d, d) * (dot(q, q) - (r*r));

	if (det > 0)
	{
		if ((t1 < 0) && (t2 < 0))
		{	
		  flag = false;
		}
		else
		{
			if ((t1 < 0) && (t2 >= 0))
				t = t2;
			else if ((t1 >= 0) && (t2 < 0))
				t = t1;
			else
			{
		       if (t1 <= t2)
				  t = t1;
			   else
				  t = t2;
			}	
		}
	}
	else if (det == 0)
	{
		if (t1 > 0)
			t = t1;
		else
			flag = false;
	}
	else
	  flag = false;

	if (flag)
		return true;
	else
		return false;
		
}

bool intersectRayBox(const float3& p, const float3& d, const float3& min, const float3& max, float& t)
{
	// TODO: implement intersection test between a ray and a box.
	// If the ray given by start point p and direction d intersects the box given by its miniumum and maximum coordinates min and max, assign the ray parameter that corresponds to the first point of intersection to t and return true.
	// Otherwise, return false.
	//
	/*
	float r = dot(p,t*d);

	if ( dot(r,d) == min)
	{
		t = r;
		return true;
	}
	else
	  return false;*/
}

void render(image2D<float4>& framebuffer, const Scene& scene, float w_s, float f, const float4& background_color)
{
	// TODO: implement ray casting
	//
	// Use the methods
	//     bool Scene::findClosestHit(const float3& p, const float3& d, float& t) const;
	// to check whether a ray given by start point p and direction d intersects the scene.
	//

	float t;
	bool hit;
	// Height 
	float h_s = (w_s * height(framebuffer)) / width(framebuffer);
	//Size of pixel
	float px = w_s / width(framebuffer);
	float py = h_s / height(framebuffer);
	float dz = -f;

	for (int y = 0; y < height(framebuffer); ++y)
	{
		float dy = h_s / 2 - (y * py );
		for (int x = 0; x < width(framebuffer); ++x)
		{
			float dx = -w_s/2 + (x * px);
			float3 dF = { dx,dy,dz };

			hit = scene.findClosestHit({ 0,0,0 }, dF, t);
			float s = length(t*dF);
			float s1 = 1 / s;
			if (hit)
			{
				framebuffer(x, y) = { s1,s1,s1, 1 };
			}
			else
              framebuffer(x, y) = background_color;
		}
	}
}
