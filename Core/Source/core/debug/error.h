#pragma once

namespace Core {

	static class Error {

	public:
		static void Exit(std::wstring message);

	};

	inline void Error::Exit(std::wstring message) {
		MessageBox(NULL, message.c_str(), L"Critical Error", MB_ICONERROR);
		exit(1);
	}

}
