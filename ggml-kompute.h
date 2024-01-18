#pragma once

#include "ggml-backend.h"

#include <cstddef>
#include <vector>
#include <string>

struct ggml_kompute_context;

namespace vk {
    class DeviceMemory;
    class Buffer;
};

struct ggml_vk_memory {
    void *data = nullptr;
    size_t size = 0;
    vk::DeviceMemory *primaryMemory = nullptr;
    vk::Buffer *primaryBuffer = nullptr;
    vk::DeviceMemory *stagingMemory = nullptr;
    vk::Buffer *stagingBuffer = nullptr;
};

struct ggml_vk_device {
    int index = 0;
    int type = 0;           // same as VkPhysicalDeviceType
    size_t heapSize = 0;
    std::string name;
    std::string vendor;
    int subgroupSize = 0;
};

std::vector<ggml_vk_device> ggml_vk_available_devices(size_t memoryRequired);
bool ggml_vk_init_device(size_t memoryRequired, const std::string &device);
bool ggml_vk_init_device(const ggml_vk_device &device);
bool ggml_vk_init_device(int device);
bool ggml_vk_free_device();
bool ggml_vk_has_vulkan();
bool ggml_vk_has_device();
bool ggml_vk_using_vulkan();
ggml_vk_device ggml_vk_current_device();
struct ggml_kompute_context * ggml_vk_init(void);
void ggml_vk_free(struct ggml_kompute_context * ctx);
void ggml_vk_free_memory(ggml_vk_memory &memory);

void ggml_vk_graph_compute(struct ggml_kompute_context * ctx, struct ggml_cgraph * gf);

//
// backend API
// user-code should use only these functions
//

#ifdef __cplusplus
extern "C" {
#endif

// forward declaration
typedef struct ggml_backend * ggml_backend_t;

GGML_API ggml_backend_t ggml_backend_kompute_init(void);

GGML_API bool ggml_backend_is_kompute(ggml_backend_t backend);

GGML_API ggml_backend_buffer_type_t ggml_backend_kompute_buffer_type(void);

#ifdef __cplusplus
}
#endif
