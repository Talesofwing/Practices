#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace fs = std::filesystem;

static void fftShift(Mat& m) {
	m = m(Rect(0, 0, m.cols & -2, m.rows & -2));
	int cx = m.cols / 2, cy = m.rows / 2;
	Mat q0(m, Rect(0, 0, cx, cy));
	Mat q1(m, Rect(cx, 0, cx, cy));
	Mat q2(m, Rect(0, cy, cx, cy));
	Mat q3(m, Rect(cx, cy, cx, cy));
	Mat tmp;
	q0.copyTo(tmp); q3.copyTo(q0); tmp.copyTo(q3);
	q1.copyTo(tmp); q2.copyTo(q1); tmp.copyTo(q2);
}

static fs::path exe_dir() {
	wchar_t buf[MAX_PATH];
	DWORD n = GetModuleFileNameW(nullptr, buf, MAX_PATH);
	fs::path exe = fs::path(std::wstring(buf, n)).remove_filename();
	return exe;
}

int main(int argc, char** argv) {
	const fs::path in_path = exe_dir() / "img.jpg";     // 固定檔名
	const fs::path out_path = exe_dir() / "spectrum.jpg";  // 輸出在同一資料夾

	Mat src = imread(in_path.string(), IMREAD_GRAYSCALE);
	if (src.empty()) { std::cerr << "讀檔失敗: " << in_path.string() << "\n"; return 1; }

	int rows = getOptimalDFTSize(src.rows);
	int cols = getOptimalDFTSize(src.cols);
	Mat padded; copyMakeBorder(src, padded, 0, rows - src.rows, 0, cols - src.cols,
							   BORDER_CONSTANT, Scalar::all(0));

	Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
	Mat complexI; merge(planes, 2, complexI);
	dft(complexI, complexI);

	split(complexI, planes);
	magnitude(planes[0], planes[1], planes[0]);
	Mat mag = planes[0];
	mag += 1.0f; log(mag, mag);
	fftShift(mag);
	normalize(mag, mag, 0, 255, NORM_MINMAX);
	mag.convertTo(mag, CV_8U);

	imwrite(out_path.string(), mag);
	std::cout << "已輸出: " << out_path.string() << "\n";
	return 0;
}
