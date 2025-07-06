#pragma once
#include <SFML/System.hpp>
#include <string>
#include <atomic>

class Downloader
{
public:
    // Inicia la descarga as�ncrona del audio (MP3) del v�deo indicado.
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

    // ---------- datos est�ticos ----------
    static bool _hasLocalFFmpeg;
    static sf::Thread* _thread;
    static std::atomic<bool> _busy;
    static std::string _url;

};

