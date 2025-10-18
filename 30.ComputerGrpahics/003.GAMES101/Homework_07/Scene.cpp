//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"


void Scene::buildBVH() {
	printf(" - Generating BVH...\n\n");
	this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray& ray) const {
	return this->bvh->Intersect(ray);
}

void Scene::sampleLight(Intersection& pos, float& pdf) const {
	float emit_area_sum = 0;
	for (uint32_t k = 0; k < objects.size(); ++k) {
		if (objects[k]->hasEmit()) {
			emit_area_sum += objects[k]->getArea();
		}
	}
	float p = get_random_float() * emit_area_sum;
	emit_area_sum = 0;
	for (uint32_t k = 0; k < objects.size(); ++k) {
		if (objects[k]->hasEmit()) {
			emit_area_sum += objects[k]->getArea();
			if (p <= emit_area_sum) {
				objects[k]->Sample(pos, pdf);
				break;
			}
		}
	}
}

bool Scene::trace(
		const Ray& ray,
		const std::vector<Object*>& objects,
		float& tNear, uint32_t& index, Object** hitObject) {
	*hitObject = nullptr;
	for (uint32_t k = 0; k < objects.size(); ++k) {
		float tNearK = kInfinity;
		uint32_t indexK;
		Vector2f uvK;
		if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
			*hitObject = objects[k];
			tNear = tNearK;
			index = indexK;
		}
	}


	return (*hitObject != nullptr);
}

// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray& ray, int depth) const {
	// TO DO Implement Path Tracing Algorithm here

	// 碰撞判斷
	Intersection intersToScene = intersect(ray);
	if (!intersToScene.happened)
		return Vector3f();

	Vector3f l_dir = {0, 0, 0};		// 直接光照
	Vector3f l_indir = {0, 0, 0};	// 間接光照

	// 判斷命中材質是否為光源
	if (intersToScene.m->hasEmission())
		l_dir += intersToScene.m->getEmission();

	// === 重要性采样 ===
	Intersection lightPos;
	float lightPDF = 0.0f;
	sampleLight(lightPos, lightPDF);
	Vector3f lightDir = lightPos.coords - intersToScene.coords;
	float dis = dotProduct(lightDir, lightDir);

	// 與光源之間的碰撞判斷
	Vector3f lightDir_normalized = lightDir.normalized();
	Ray rayToLight(intersToScene.coords, lightDir_normalized);
	Intersection interToLight = intersect(rayToLight);
	if (interToLight.distance - lightDir.norm() > -0.005) {
		// 光源能見
		auto f_r = intersToScene.m->eval(ray.direction, lightDir_normalized, intersToScene.normal);		// BRDF
		l_dir += lightPos.emit * f_r * dotProduct(lightDir_normalized, intersToScene.normal) * dotProduct(-lightDir_normalized, lightPos.normal) / dis / lightPDF;
	}
	// === 重要性采样 ===

	// === 俄羅斯輪盤 ===
	float RR = 1;
	if (depth > 5) {
		if (get_random_float() > RussianRoulette) {
			return l_dir;
		}
		RR = RussianRoulette;
	}
	// === 俄羅斯輪盤 ===

	// === 間接光計算 ===
	Vector3f wi = intersToScene.m->sample(ray.direction, intersToScene.normal).normalized();	// 反射方向
	Ray indirRay(intersToScene.coords, wi);
	Intersection intersToPoint = Scene::intersect(indirRay);

	// 相交且不是光源 (間接光計算)
	if (intersToPoint.happened && !intersToPoint.m->hasEmission()) {
		float pdf = intersToScene.m->pdf(ray.direction, wi, intersToScene.normal);
		l_indir = castRay(indirRay, depth + 1) * intersToScene.m->eval(ray.direction, wi, intersToScene.normal) * dotProduct(wi, intersToScene.normal) / RussianRoulette / pdf;
	}
	// === 間接光計算 ===

	return l_dir + l_indir;
}
