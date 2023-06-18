#include "FrameConverter.h"
#include <stdexcept>
#include <sstream>

FrameConverter::FrameConverter(const std::string& video_path, int frame_interval, const std::string& output_dir_path)
    : cap(video_path), frame_interval(frame_interval), output_dir(output_dir_path)
{
    if (!cap.isOpened())
    {
        throw std::runtime_error("Erro ao abrir o vídeo.");
    }

    create_output_dir_if_not_exists();
}

void FrameConverter::convert_to_images()
{
    cv::Mat frame;
    int frame_index = 0;

    while (cap.read(frame))
    {
        if (should_save_frame(frame_index))
        {
            save_frame_as_image(frame, frame_index);
        }

        frame_index++;
    }
}

bool FrameConverter::should_save_frame(int frame_index)
{
    return frame_index % frame_interval == 0;
}

void FrameConverter::save_frame_as_image(const cv::Mat& frame, int frame_index)
{
    auto filename = create_image_filename(frame_index);

    if (!cv::imwrite(filename, frame))
    {
        throw std::runtime_error("Não foi possível salvar a imagem.");
    }
}

std::string FrameConverter::create_image_filename(int frame_index)
{
    std::stringstream ss;
    ss << output_dir.string() << "/frame" << frame_index << ".jpg";
    return ss.str();
}

void FrameConverter::create_output_dir_if_not_exists()
{
    if (!std::filesystem::exists(output_dir))
    {
        std::filesystem::create_directories(output_dir);
    }
}
