#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <stdio.h>
#include <set>
#include <memory>
#include <queue>
#include <vector>
#include <stack>
#include <span>
#include <iostream>
#include <array>
#include <bitset>
#include <cassert>
#include <unordered_map>
#include <Windows.h>
#include <entt/entt.hpp>
#include <entt/entity/registry.hpp>
#include <chrono>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_win32.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "glad/glad.h"
#include "glad/glad_wgl.h"
#include "core/base.h"