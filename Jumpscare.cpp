#define SDL_MAIN_HANDLED
#define SDL_SetWindowAlwaysOnTop
#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <urlmon.h>
#include <thread>
#include <chrono>
#pragma comment(lib, "urlmon.lib")

int main() {
    HWND hwnd = GetConsoleWindow();
    if (hwnd) ShowWindow(hwnd, SW_HIDE);

    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_WEBP);

    URLDownloadToFileA(NULL, "https://silkcoding.dev/stalled/pic.webp", "pic.webp", 0, NULL);
    URLDownloadToFileA(NULL, "https://silkcoding.dev/stalled/audio.wav", "audio.wav", 0, NULL);

    SDL_Surface* image = IMG_Load("pic.webp");
    if (!image) {
        MessageBoxA(NULL, "Failed to load image", "Error", MB_ICONERROR);
        return 1;
    }

    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);

    SDL_Window* window = SDL_CreateWindow("",
        0, 0,
        dm.w, dm.h,
        SDL_WINDOW_BORDERLESS);

    SDL_SetWindowAlwaysOnTop(window, SDL_TRUE);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);

    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;
    if (!SDL_LoadWAV("audio.wav", &wavSpec, &wavBuffer, &wavLength)) {
        MessageBoxA(NULL, "Failed to load audio", "Error", MB_ICONERROR);
        return 1;
    }

    SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    SDL_QueueAudio(device, wavBuffer, wavLength);
    SDL_PauseAudioDevice(device, 0);

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    SDL_CloseAudioDevice(device);
    SDL_FreeWAV(wavBuffer);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    DeleteFileA("pic.webp");
    DeleteFileA("audio.wav");

    IMG_Quit();
    SDL_Quit();
    return 0;
}
