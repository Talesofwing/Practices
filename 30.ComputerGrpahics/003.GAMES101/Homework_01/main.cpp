#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;

Eigen::Matrix4f get_rotation_matrix(float rotation_angle, Eigen::Vector3f axis);

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos) {
	Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

	Eigen::Matrix4f translate;
	translate <<
		1, 0, 0, -eye_pos[0],
		0, 1, 0, -eye_pos[1],
		0, 0, 1, -eye_pos[2],
		0, 0, 0, 1;

	view = translate * view;

	return view;
}

Eigen::Matrix4f get_model_matrix(float rotation_angle) {
	Eigen::Matrix4f model = Eigen::Matrix4f::Identity();

	// TODO: Implement this function
	// Create the model matrix for rotating the triangle around the Z axis.
	// Then return it.

	// rotation_angle = rotation_angle * MY_PI / 180;

	// model <<
	// 	cos(rotation_angle), -sin(rotation_angle), 0, 0,
	// 	sin(rotation_angle), cos(rotation_angle), 0, 0,
	// 	0, 0, 1, 0,
	// 	0, 0, 0, 1;

	// Rotate the triangle around the specified axis
	model = get_rotation_matrix(rotation_angle, Eigen::Vector3f(0, 1, 0));

	return model;
}

Eigen::Matrix4f get_rotation_matrix(float rotation_angle, Eigen::Vector3f axis) {
	Eigen::Matrix4f rotation = Eigen::Matrix4f::Identity();

	rotation_angle = rotation_angle * MY_PI / 180;
	float c = cos(rotation_angle);
	float s = sin(rotation_angle);
	float x = axis.x();
	float y = axis.y();
	float z = axis.z();

	rotation <<
		x * x * (1 - c) + c, x* y* (1 - c) - z * s, x* z* (1 - c) + y * s, 0,
		x* y* (1 - c) + z * s, y* y* (1 - c) + c, y* z* (1 - c) - x * s, 0,
		x* z* (1 - c) - y * s, y* z* (1 - c) + x * s, z* z* (1 - c) + c, 0,
		0, 0, 0, 1;


	return rotation;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
									  float zNear, float zFar) {
	// Students will implement this function

	Eigen::Matrix4f translation = Eigen::Matrix4f::Identity();
	Eigen::Matrix4f rotation = Eigen::Matrix4f::Identity();
	Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();

	// TODO: Implement this function
	// Create the projection matrix for the given parameters.
	// Then return it.

	float r, l, t, b, n, f;

	n = -zNear;
	f = -zFar;
	t = -n * tan(eye_fov / 2);
	b = -t;
	r = t * aspect_ratio;
	l = -r;

	translation <<
		1, 0, 0, -(r + l) / 2,
		0, 1, 0, -(t + b) / 2,
		0, 0, 1, -(n + f) / 2,
		0, 0, 0, 1;

	rotation <<
		2 / (r - l), 0, 0, 0,
		0, 2 / (t - b), 0, 0,
		0, 0, 2 / (n - f), 0,
		0, 0, 0, 1;

	projection <<
		n, 0, 0, 0,
		0, n, 0, 0,
		0, 0, n + f, -n * f,
		0, 0, 1, 0;

	return rotation * translation * projection;
}

int main(int argc, const char** argv) {
	float angle = 0;
	bool command_line = false;
	std::string filename = "output.png";

	if (argc >= 3) {
		command_line = true;
		angle = std::stof(argv[2]); // -r by default
		if (argc == 4) {
			filename = std::string(argv[3]);
		}
	}

	rst::rasterizer r(700, 700);

	Eigen::Vector3f eye_pos = {0, 0, 5};

	std::vector<Eigen::Vector3f> pos {{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};

	std::vector<Eigen::Vector3i> ind {{0, 1, 2}};

	auto pos_id = r.load_positions(pos);
	auto ind_id = r.load_indices(ind);

	int key = 0;
	int frame_count = 0;

	if (command_line) {
		r.clear(rst::Buffers::Color | rst::Buffers::Depth);

		r.set_model(get_model_matrix(angle));
		r.set_view(get_view_matrix(eye_pos));
		r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

		r.draw(pos_id, ind_id, rst::Primitive::Triangle);
		cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
		image.convertTo(image, CV_8UC3, 1.0f);

		cv::imwrite(filename, image);

		return 0;
	}

	while (key != 27) {
		r.clear(rst::Buffers::Color | rst::Buffers::Depth);

		r.set_model(get_model_matrix(angle));
		r.set_view(get_view_matrix(eye_pos));
		r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

		r.draw(pos_id, ind_id, rst::Primitive::Triangle);

		cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
		image.convertTo(image, CV_8UC3, 1.0f);
		cv::imshow("image", image);
		key = cv::waitKey(10);

		std::cout << "frame count: " << frame_count++ << '\n';

		if (key == 'a') {
			angle += 10;
		} else if (key == 'd') {
			angle -= 10;
		}
	}

	return 0;
}
