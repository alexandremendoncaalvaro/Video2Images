#pragma once

#include <opencv2/opencv.hpp>
#include <filesystem>
#include <string>

class FrameConverter
{
public:
    FrameConverter(const std::string& video_path, int frame_interval, const std::string& output_dir_path);
    void convert_to_images();

private:
    cv::VideoCapture cap;
    int frame_interval;
    std::filesystem::path output_dir;

    bool should_save_frame(int frame_index);
    void save_frame_as_image(const cv::Mat& frame, int frame_index);
    std::string create_image_filename(int frame_index);
    void create_output_dir_if_not_exists();
};
