# 🎬 SDL2 URL Media Loader (Windows Only)

This small C++ program uses **SDL2** and **SDL2_image** to display an image and play an audio file directly from **remote URLs** — without using external libraries like libcurl.


# ⭐ Star my Reo!
It works by leveraging the built-in **Windows API (`URLDownloadToFile`)** to temporarily download the files before displaying and playing them with SDL2.

---

## 🧩 Features

- ✅ No external dependencies — only uses Windows’ built-in URL downloader  
- 🖼️ Loads and displays a full-screen WebP image  
- 🔊 Plays a WAV audio file simultaneously  
- 🕒 Automatically closes after 2 seconds (configurable)  
- ⚡ Uses borderless fullscreen mode with `SDL_SetWindowAlwaysOnTop`

---

## 📁 Code Overview

```cpp
URLDownloadToFileA(NULL, "https://silkcoding.dev/stalled/pic.webp", "pic.webp", 0, NULL);
URLDownloadToFileA(NULL, "https://silkcoding.dev/stalled/audio.wav", "audio.wav", 0, NULL);

SDL_Surface* image = IMG_Load("pic.webp");
SDL_LoadWAV("audio.wav", &wavSpec, &wavBuffer, &wavLength);
