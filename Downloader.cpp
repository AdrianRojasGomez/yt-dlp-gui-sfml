#include "Downloader.h"
#include <SFML/System.hpp>
#include <filesystem>
#include <iostream>
#include <cstdlib>          

using std::filesystem::exists;
using std::filesystem::create_directory;
using std::filesystem::path;

// ---------- inicialización de estáticos ----------
bool                   Downloader::_hasLocalFFmpeg = false;
sf::Thread* Downloader::_thread = nullptr;
std::atomic<bool>      Downloader::_busy(false);
std::string            Downloader::_url = "";

// ---------- utilidades ----------------------------
bool Downloader::EnsureDirectoryExists()
{
    if (exists("MusicYT")) return true;
    try { return create_directory("MusicYT"); }
    catch (const std::exception& e)
    {
        std::cerr << "[Downloader] Error creando carpeta: " << e.what() << '\n';
        return false;
    }
}

bool Downloader::EnsureYTDLPInstalled()
{
#ifdef _WIN32
    path exe{ "yt-dlp.exe" };
    std::string fetch =
        "powershell -Command \"Invoke-WebRequest -Uri "
        "https://github.com/yt-dlp/yt-dlp/releases/latest/download/yt-dlp.exe "
        "-OutFile yt-dlp.exe\"";
#else
    path exe{ "yt-dlp" };
    std::string fetch =
        "curl -L https://github.com/yt-dlp/yt-dlp/releases/latest/download/yt-dlp -o yt-dlp";
#endif
    if (exists(exe)) return true;

    std::cout << "[Downloader] yt-dlp no encontrado. Descargando...\n";
    if (std::system(fetch.c_str()) != 0)
    {
        std::cerr << "[Downloader] Fallo al descargar yt-dlp\n";
        return false;
    }
#ifndef _WIN32
    std::system("chmod +x yt-dlp");
#endif
    return exists(exe);
}

bool Downloader::EnsureFfmpegInstalled()
{
#ifdef _WIN32
    if (exists("ffmpeg.exe") && exists("ffprobe.exe"))
    {
        _hasLocalFFmpeg = true;
        return true;
    }
    if (std::system("where ffmpeg >nul 2>&1") == 0 &&
        std::system("where ffprobe >nul 2>&1") == 0)
    {
        _hasLocalFFmpeg = false;
        return true;
    }

    std::cout << "[Downloader] FFmpeg no encontrado. Descargando paquete estatico...\n";
    std::string dl =
        "powershell -Command \"Invoke-WebRequest -Uri "
        "https://www.gyan.dev/ffmpeg/builds/ffmpeg-release-essentials.zip -OutFile ffmpeg.zip\"";
    if (std::system(dl.c_str()) != 0) return false;

    std::string unzip =
        "powershell -Command \"Expand-Archive -Path ffmpeg.zip -DestinationPath . -Force\"";
    if (std::system(unzip.c_str()) != 0) return false;

    std::string move =
        "powershell -Command \"$d=Get-ChildItem -Directory -Filter 'ffmpeg-*essentials_build' "
        "| Select-Object -First 1; "
        "$src=$d.FullName+'\\\\bin\\\\'; "
        "Copy-Item ($src+'ffmpeg.exe') . -Force; "
        "Copy-Item ($src+'ffprobe.exe') . -Force\"";
    if (std::system(move.c_str()) != 0) return false;

    _hasLocalFFmpeg = true;
    return true;
#else
    bool ok = std::system("which ffmpeg >/dev/null 2>&1") == 0 &&
        std::system("which ffprobe >/dev/null 2>&1") == 0;
    if (!ok)
        std::cerr << "[Downloader] Instala FFmpeg (ej: sudo apt install ffmpeg).\n";
    _hasLocalFFmpeg = false;
    return ok;
#endif
}

// ---------- versión bloqueante -------------------
void Downloader::DownloadAudioSync(const std::string& url)
{
    if (!EnsureDirectoryExists()) return;
    if (!EnsureYTDLPInstalled())  return;
    if (!EnsureFfmpegInstalled()) return;

#ifdef _WIN32
    std::string ytdlp = ".\\yt-dlp.exe";
#else
    std::string ytdlp = "./yt-dlp";
#endif
    std::string cmd = ytdlp +
        " -x --audio-format mp3 -o \"MusicYT/%(title)s.%(ext)s\" \"" + url + "\"";

    std::cout << "[Downloader] Ejecutando: " << cmd << '\n';
    int result = std::system(cmd.c_str());
    if (result != 0)
        std::cerr << "[Downloader] yt-dlp devolvio codigo " << result << '\n';
    else
        std::cout << "[Downloader] Descarga finalizada con exito.\n";
}

// ---------- cuerpo del hilo ----------------------
void Downloader::Worker()
{
    std::string localUrl = _url;   // copia de seguridad
    DownloadAudioSync(localUrl);   // trabajo real

    _busy = false;                 // avisa que termino
}

// ---------- API publica --------------------------
void Downloader::DownloadAudio(const std::string& url)
{
    if (_busy)
    {
        std::cout << "[Downloader] Ya hay una descarga en curso.\n";
        return;
    }

    _url = url;
    _busy = true;

    // Limpia hilo anterior, si quedara alguno (sanidad)
    if (_thread)
    {
        _thread->wait();   // retorno inmediato si ya termino
        delete _thread;
    }

    _thread = new sf::Thread(&Downloader::Worker);
    _thread->launch();    // no bloquea la GUI
}

bool Downloader::IsBusy()
{
    // Si la descarga termino, libera el hilo
    if (!_busy && _thread)
    {
        _thread->wait();
        delete _thread;
        _thread = nullptr;
    }
    return _busy;
}
