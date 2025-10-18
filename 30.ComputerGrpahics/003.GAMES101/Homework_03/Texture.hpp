//
// Created by LEI XU on 4/27/19.
//

#ifndef RASTERIZER_TEXTURE_H
#define RASTERIZER_TEXTURE_H
#include "global.hpp"
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>
class Texture {
private:
	cv::Mat image_data;

public:
	Texture(const std::string& name) {
		image_data = cv::imread(name);
		cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);
		width = image_data.cols;
		height = image_data.rows;
	}

	int width, height;

	Eigen::Vector3f getColor(float u, float v) {
		if (u < 0) u = 0;
		else if (u > 1) u = 1;

		if (v < 0) v = 0;
		else if (v > 1) v = 1;

		auto u_img = u * (width - 1);
		auto v_img = (1 - v) * (height - 1);
		auto color = image_data.at<cv::Vec3b>(v_img, u_img);
		return Eigen::Vector3f(color[0], color[1], color[2]);
	}

	Eigen::Vector3f getColorBilinear(float u, float v) {
		if (u < 0) u = 0;
		else if (u > 1) u = 1;

		if (v < 0) v = 0;
		else if (v > 1) v = 1;

		float u_img = u * (width - 1);
		float v_img = (1 - v) * (height - 1);

		int u_min = floor(u_img);
		int u_max = ceil(u_img);
		int v_min = floor(v_img);
		int v_max = ceil(v_img);

		auto color1 = image_data.at<cv::Vec3b>(v_min, u_min);
		auto color2 = image_data.at<cv::Vec3b>(v_min, u_max);
		auto color3 = image_data.at<cv::Vec3b>(v_max, u_min);
		auto color4 = image_data.at<cv::Vec3b>(v_max, u_max);

		float uLerpNum = (u_img - u_min) / (u_max - u_min);
		float vLerpNum = (v_img - v_min) / (v_max - v_min);

		auto color_lerp1 = (1 - uLerpNum) * Eigen::Vector3f(color1[0], color1[1], color1[2]) + uLerpNum * Eigen::Vector3f(color2[0], color2[1], color2[2]);
		auto color_lerp2 = (1 - uLerpNum) * Eigen::Vector3f(color3[0], color3[1], color3[2]) + uLerpNum * Eigen::Vector3f(color4[0], color4[1], color4[2]);
		auto color_lerp = (1 - vLerpNum) * color_lerp1 + vLerpNum * color_lerp2;

		return color_lerp;
	}

};
#endif //RASTERIZER_TEXTURE_H
