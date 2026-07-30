/**
* @copyright 2025 - Max Bebök
* @license MIT
*/
#pragma once

#include "assets/assetManager.h"
#include "script/scriptTable.h"

namespace P64::Comp
{
  struct Fade
  {
    static constexpr uint32_t ID = 1;

    // performs culling of indiviudal objects
    static constexpr uint8_t FLAG_CULLING = 1 << 0;

    //Renderer::MaterialInstance material{};

    static uint32_t getAllocSize([[maybe_unused]] uint16_t* initData);

    static void initDelete([[maybe_unused]] Object& obj, Model* data, void* initData);

    static void update(Object& obj, Model* data, [[maybe_unused]] float deltaTime) {}

    static void draw([[maybe_unused]] Object& obj, Model* data, [[maybe_unused]] float deltaTime);
  };
}