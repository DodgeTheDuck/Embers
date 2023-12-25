#pragma once

#include "dll.h"

namespace Core::Gui {

	class ENGINE_API Widget {

	public:
		virtual void Draw() = 0;

	};

}