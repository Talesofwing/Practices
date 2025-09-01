#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>

int points_count = 4;

std::vector<cv::Point2f> control_points;

void mouse_handler(int event, int x, int y, int flags, void* userdata) {
	if (event == cv::EVENT_LBUTTONDOWN && control_points.size() < points_count) {
		std::cout << "Left button of the mouse is clicked - position (" << x << ", "
			<< y << ")" << '\n';
		control_points.emplace_back(x, y);
	}
}

void naive_bezier(const std::vector<cv::Point2f>& points, cv::Mat& window) {
	auto& p_0 = points[0];
	auto& p_1 = points[1];
	auto& p_2 = points[2];
	auto& p_3 = points[3];

	for (double t = 0.0; t <= 1.0; t += 0.001) {
		auto point = std::pow(1 - t, 3) * p_0 + 3 * t * std::pow(1 - t, 2) * p_1 +
			3 * std::pow(t, 2) * (1 - t) * p_2 + std::pow(t, 3) * p_3;

		window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
	}
}

cv::Point2f recursive_bezier(const std::vector<cv::Point2f>& control_points, float t) {
	// TODO: Implement de Casteljau's algorithm

	if (control_points.size() == 1) return control_points[0];

	std::vector<cv::Point2f> new_control_points;
	for (int i = 0; i < control_points.size() - 1; ++i) {
		auto p0 = control_points[i];
		auto p1 = control_points[i + 1];
		new_control_points.emplace_back(p0.x + t * (p1.x - p0.x), p0.y + t * (p1.y - p0.y));
	}

	return recursive_bezier(new_control_points, t);
}

void bezier(const std::vector<cv::Point2f>& control_points, cv::Mat& window) {
	// TODO: Iterate through all t = 0 to t = 1 with small steps, and call de Casteljau's
	// recursive Bezier algorithm.

	for (float t = 0; t <= 1; t += 0.0001f) {
		auto point = recursive_bezier(control_points, t);
		window.at<cv::Vec3b>(point.y, point.x)[1] = 255;
	}
}

inline float get_distance(const cv::Point2f& p1, const cv::Point2f& p2) {
	return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

void bezier_with_antialiasing(const std::vector<cv::Point2f>& control_points, cv::Mat& window) {
	for (float t = 0; t <= 1.0f; t += 0.001f) {
		cv::Point2f point = recursive_bezier(control_points, t);

		int minx = static_cast<int>(std::floor(point.x));
		int miny = static_cast<int>(std::floor(point.y));

		for (int k = 0; k <= 1; ++k) {
			for (int j = 0; j <= 1; ++j) {
				int px = minx + k;
				int py = miny + j;

				if (px < 0 || px >= window.cols || py < 0 || py >= window.rows)
					continue;

				float distance = get_distance(cv::Point2f(px + 0.5f, py + 0.5f), point);
				float weight = std::max(0.0f, 1.0f - distance);
				uchar color = static_cast<uchar>(
					std::max(weight * 255.0f, static_cast<float>(window.at<cv::Vec3b>(py, px)[1]))
				);

				window.at<cv::Vec3b>(py, px)[1] = color;
			}
		}
	}
}

int main(int argc, const char* argv[]) {
	cv::Mat window = cv::Mat(700, 700, CV_8UC3, cv::Scalar(0));
	cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
	cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);

	cv::setMouseCallback("Bezier Curve", mouse_handler, nullptr);

	int key = -1;
	while (key != 27) {
		for (auto& point : control_points) {
			cv::circle(window, point, 3, {255, 255, 255}, 3);
		}

		bool anti = false;
		if (argc >= 2 && std::stoi(argv[1]) >= 2) points_count = std::stoi(argv[1]);
		if (argc >= 3 && std::string(argv[2]) == "-a") anti = true;

		if (control_points.size() == points_count) {
			// naive_bezier(control_points, window);
			if (!anti) {
				bezier(control_points, window);
			} else {
				bezier_with_antialiasing(control_points, window);
			}

			cv::imshow("Bezier Curve", window);
			cv::imwrite("my_bezier_curve.png", window);
			key = cv::waitKey(0);

			return 0;
		}

		cv::imshow("Bezier Curve", window);
		key = cv::waitKey(20);
	}

	return 0;
}
