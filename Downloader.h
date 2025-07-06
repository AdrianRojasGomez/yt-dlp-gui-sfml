#pragma once
#include <SFML/System.hpp>
#include <string>
#include <atomic>

class Downloader
{
public:
    // Inicia la descarga asíncrona del audio (MP3) del vídeo indicado.
    static void DownloadAudio(const std::string& url);

    // Devuelve true mientras haya una descarga activa.
    static bool IsBusy();

private:
    // ---------- utilidades internas ----------
    static bool EnsureDirectoryExists();
    static bool EnsureYTDLPInstalled();
    static bool EnsureFfmpegInstalled();

    // Descarga bloqueante (llamada desde el hilo Worker)
    static void DownloadAudioSync(const std::string& url);

    // Cuerpo del hilo: envuelve la llamada bloqueante
    static void Worker();

    // ---------- datos estáticos ----------
    static bool _hasLocalFFmpeg;
    static sf::Thread* _thread;
    static std::atomic<bool> _busy;
    static std::string _url;

};

