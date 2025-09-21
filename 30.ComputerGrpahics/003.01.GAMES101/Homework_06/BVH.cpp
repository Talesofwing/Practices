#include <algorithm>
#include <cassert>
#include <chrono>

#include "BVH.hpp"

using namespace std::chrono;

#define SPLIT_METHOD 1	// 0 : BVH, 1 : SAH

BVHAccel::BVHAccel(std::vector<Object*> p, int maxPrimsInNode,
				   SplitMethod splitMethod)
	: maxPrimsInNode(std::min(255, maxPrimsInNode)), splitMethod(splitMethod),
	primitives(std::move(p)) {
	time_t start, stop;
	time(&start);
	if (primitives.empty())
		return;

	std::cout << " --- Building BVH ---" << std::endl;
	auto s = high_resolution_clock::now();
	root = recursiveBuild(primitives);
	auto e = high_resolution_clock::now();
	auto d = duration_cast<milliseconds>(e - s);

	std::cout << "BVH took " << d.count() / 1000.0 << "s, " << d.count() << "ms" << std::endl;

	time(&stop);
	double diff = difftime(stop, start);
	int hrs = (int)diff / 3600;
	int mins = ((int)diff / 60) - (hrs * 60);
	int secs = (int)diff - (hrs * 3600) - (mins * 60);

	printf(
		"\rBVH Generation complete: \nTime Taken: %i hrs, %i mins, %i secs\n\n",
		hrs, mins, secs);
}

BVHBuildNode* BVHAccel::recursiveBuild(std::vector<Object*> objects) {
	BVHBuildNode* node = new BVHBuildNode();
	std::vector<Object*>::iterator middling;

	// Compute bounds of all primitives in BVH node
	Bounds3 bounds;
	for (int i = 0; i < objects.size(); ++i)
		bounds = Union(bounds, objects[i]->getBounds());

	if (objects.size() == 1) {
		// Create leaf _BVHBuildNode_
		node->bounds = objects[0]->getBounds();
		node->object = objects[0];
		node->left = nullptr;
		node->right = nullptr;
		return node;
	} else if (objects.size() == 2) {
		node->left = recursiveBuild(std::vector {objects[0]});
		node->right = recursiveBuild(std::vector {objects[1]});

		node->bounds = Union(node->left->bounds, node->right->bounds);
		return node;
	} else {
		Bounds3 centroidBounds;
		for (int i = 0; i < objects.size(); ++i)
			centroidBounds = Union(centroidBounds, objects[i]->getBounds().Centroid());

		int dim = centroidBounds.maxExtent();
		switch (dim) {
			case 0:
				std::sort(objects.begin(), objects.end(), [](auto f1, auto f2) {
					return f1->getBounds().Centroid().x <
						f2->getBounds().Centroid().x;
				});
				break;
			case 1:
				std::sort(objects.begin(), objects.end(), [](auto f1, auto f2) {
					return f1->getBounds().Centroid().y <
						f2->getBounds().Centroid().y;
				});
				break;
			case 2:
				std::sort(objects.begin(), objects.end(), [](auto f1, auto f2) {
					return f1->getBounds().Centroid().z <
						f2->getBounds().Centroid().z;
				});
				break;
		}

		switch (SPLIT_METHOD) {
			case 0:
				middling = objects.begin() + (objects.size() / 2);
				break;
			case 1:
				float maxArea = centroidBounds.SurfaceArea();
				float minCost = std::numeric_limits<float>::infinity();
				int minClipNum = 0;
				float BoundingClip = 2;		// 分成多分份 (去掉就是真正的SAH)

				float BoundingClipDiv = 1.0f / BoundingClip;
				float maxAreaDiv = 1.0f / maxArea;
				for (int i = 0; i < BoundingClip; i++) {
					Bounds3 leftBounds3;
					Bounds3 rightBounds3;
					float leftCount = 0.0f;
					float rightCount = 0.0f;
					auto middlingTemp = objects.begin() + std::floor(objects.size() * (i * BoundingClipDiv));
					for (auto j = objects.begin(); j < middlingTemp; j++) {
						leftBounds3 = Union(leftBounds3, (*j)->getBounds().Centroid());
						leftCount = leftCount + 1.0f;
					}
					for (auto j = middlingTemp; j < objects.end(); j++) {
						rightBounds3 = Union(rightBounds3, (*j)->getBounds().Centroid());
						rightCount = rightCount + 1.0f;
					}

					// CI和CT都分別除了8
					float cost = 0.125f + (leftCount * leftBounds3.SurfaceArea() + rightCount * rightBounds3.SurfaceArea()) * maxAreaDiv;
					if (cost < minCost) {
						minClipNum = i;
						minCost = cost;
					}
				}
				middling = objects.begin() + std::floor(objects.size() * (minClipNum * BoundingClipDiv));
				break;
		}

		auto beginning = objects.begin();
		auto ending = objects.end();

		auto leftshapes = std::vector<Object*>(beginning, middling);
		auto rightshapes = std::vector<Object*>(middling, ending);

		assert(objects.size() == (leftshapes.size() + rightshapes.size()));

		node->left = recursiveBuild(leftshapes);
		node->right = recursiveBuild(rightshapes);

		node->bounds = Union(node->left->bounds, node->right->bounds);
	}

	return node;
}

Intersection BVHAccel::Intersect(const Ray& ray) const {
	Intersection isect;
	if (!root)
		return isect;
	isect = BVHAccel::getIntersection(root, ray);
	return isect;
}

Intersection BVHAccel::getIntersection(BVHBuildNode* node, const Ray& ray) const {
	// TODO Traverse the BVH to find intersection
	Intersection inter;

	Vector3f invdir(1.0f / ray.direction.x, 1.0f / ray.direction.y, 1.0f / ray.direction.z);
	std::array<int, 3> dirIsNeg;
	dirIsNeg[0] = invdir.x < 0;
	dirIsNeg[1] = invdir.y < 0;
	dirIsNeg[2] = invdir.z < 0;

	if (node->bounds.IntersectP(ray, ray.direction_inv, dirIsNeg)) {
		if (!node->right && !node->left) {
			return node->object->getIntersection(ray);
		}

		Intersection leftInter = getIntersection(node->left, ray);
		Intersection rightInter = getIntersection(node->right, ray);
		if (leftInter.distance < rightInter.distance)
			inter = leftInter;
		else
			inter = rightInter;
	}

	return inter;
}
