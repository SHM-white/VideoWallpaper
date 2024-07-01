#pragma once
class WallpaperCore
{
	public:
		void StartWallpaper();
		void StopWallpaper();
		std::wstring SetWallpaper(const std::wstring& path);
		std::wstring SetFfmpegPath(const std::wstring& path);
		std::wstring GetFfmpegPath();
		std::wstring GetWallpaperPath();
	private:
		std::wstring m_path;
		bool m_isWallpaperSet;
		std::wstring m_ffmpegPath;
};

