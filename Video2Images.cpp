#include <CLI/CLI.hpp>
#include "FrameConverter.h"
#include <iostream>

int main(int argc, char** argv)
{
    CLI::App app{"Converte frames de vídeos em imagens"};

    std::string video_path;
    app.add_option("video", video_path, "Caminho do arquivo de vídeo")->required()->check(CLI::ExistingFile);

    int frame_interval = 30;
    app.add_option("-i,--interval", frame_interval, "Intervalo de frames");

    std::string output_dir_path = "frames";
    app.add_option("-d,--directory", output_dir_path, "Caminho do diretório de saída");

    CLI11_PARSE(app, argc, argv);

    try
    {
        FrameConverter converter(video_path, frame_interval, output_dir_path);
        converter.convert_to_images();
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
